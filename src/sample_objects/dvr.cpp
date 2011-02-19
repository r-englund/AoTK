#include <AoTK/aotk.h>

#define INDEX(x,y,z,w,h) ((x)+((w)*(y))+((z)*(w)*(h)))
//
//#include <stdio.h>
//#include <cmath>
//#include <assert.h>

namespace AoTK{

DVR::DVR(GLint _shader,VolumeInfo vi,Matrix _toWorld,std::string _name):
 Object(_shader,_toWorld, _name),
 KeyboardListener(_name),
 MouseMotionListener(_name),
 ScrollListener(_name),
 type(density),
 roty(0),
 rotx(0),
 threshold(0.5),
 div_coeff(0.5)
{
    volumeInfo = vi;
    FILE *f;
    f = fopen(vi.filename.c_str(),"rb");
    assert(f != NULL);
    uint8_t *buf = new uint8_t[vi.width*vi.height*vi.depth]();

    fread(buf,sizeof(uint8_t),vi.width*vi.height*vi.depth,f);
    assert(ferror(f)==0);
    fclose(f);

    unsigned int x,y,z;
    x = 0;
    y = 0;
    z = 0;
    unsigned int pow2width,pow2height,pow2depth;
    pow2width = pow(2,ceil(log(vi.width) / log(2.0f)));
    pow2height = pow(2,ceil(log(vi.height) / log(2.0f)));
    pow2depth = pow(2,ceil(log(vi.depth) / log(2.0f)));
    stepsize = 1.0/sqrt(pow2width*pow2width+pow2height*pow2height+pow2depth*pow2depth);
    std::cout << vi.width << " " << vi.height << " " << vi.depth << std::endl;
    std::cout << pow2width << " " << pow2height << " " << pow2depth << std::endl;
    data = new GLubyte[pow2width*pow2height*pow2depth*4]();
    int kernelsize = 1; // actually kernel divded by two plus 1
    for(unsigned int i = 0;i<pow2width*pow2height*pow2depth*4;i++)
        data[i] = 0;
    for(unsigned int i = 0;i<vi.width*vi.height*vi.depth;i++){
        unsigned int index = INDEX(x,y,z,pow2width,pow2height);
        data[index*4+0] = 0;
        data[index*4+1] = 0;
        data[index*4+2] = 0;
        float ff = 0;
        unsigned int div = 0;
        for(unsigned int c = std::max(0,(int)z-kernelsize)   ;   c<std::min(z+kernelsize,vi.depth);c++)
            for(unsigned int b = std::max(0,(int)y-kernelsize)   ;   b<std::min(y+kernelsize,vi.height);b++)
                for(unsigned int a = std::max(0,(int)x-kernelsize)   ;   a<std::min(x+kernelsize,vi.width);a++){
                    div++;
                    ff += buf[INDEX(a,b,c,vi.width,vi.height)];
                }
        data[index*4+3] = (GLubyte) (ff/div);

        x++;
        if(x>=vi.width){
            x = 0;
            y++;
            if(y>=vi.height){
                y = 0;
                z++;
            }
        }
    }
    volumeInfo.depth = pow2depth;
    volumeInfo.height = pow2height;
    volumeInfo.width = pow2width;
    calcGradients();

    getAllError(__FILE__,__LINE__);
    glGenTextures(1,&tex);
    glBindTexture(GL_TEXTURE_3D,tex);
    getAllError(__FILE__,__LINE__);

    glTexParameterf(GL_TEXTURE_3D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameterf(GL_TEXTURE_3D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    getAllError(__FILE__,__LINE__);

    glTexParameterf(GL_TEXTURE_3D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_3D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_3D,GL_TEXTURE_WRAP_R,GL_CLAMP_TO_EDGE);
    getAllError(__FILE__,__LINE__);

    glTexImage3D(GL_TEXTURE_3D,0,4,volumeInfo.width,volumeInfo.height,volumeInfo.depth,0,GL_RGBA,GL_UNSIGNED_BYTE,&data[0]);
    getAllError(__FILE__,__LINE__);

    glBindTexture(GL_TEXTURE_3D,0);
    getAllError(__FILE__,__LINE__);

//    assert(pgm);
    glUseProgram(pgm);

    getAllError(__FILE__,__LINE__);
    vol_tex_loc   = glGetUniformLocation(pgm,"vol_tex");
    front_tex_loc = glGetUniformLocation(pgm,"front_tex");
    back_tex_loc  = glGetUniformLocation(pgm,"back_tex");
    window_size_loc  = glGetUniformLocation(pgm,"window_size");
    threshold_loc  = glGetUniformLocation(pgm,"threshold");
    stepsize_loc  = glGetUniformLocation(pgm,"stepsize");
    div_coeff_loc  = glGetUniformLocation(pgm,"div_coeff");
    type_loc  = glGetUniformLocation(pgm,"type");

    std::cout << front_tex_loc << std::endl;
    std::cout << back_tex_loc << std::endl;
    std::cout << vol_tex_loc << std::endl;
    std::cout << window_size_loc << std::endl;
    std::cout << threshold_loc << std::endl;
    std::cout << stepsize_loc << std::endl;
    std::cout << div_coeff_loc << std::endl;
    std::cout << std::endl;

    getAllError(__FILE__,__LINE__);
    glUseProgram(0);

    getAllError(__FILE__,__LINE__);
    delete buf;
};

void DVR::scroll(int p){
    if(aotk->keyState(SHIFT)){
        threshold += 0.03 * p;
        if(threshold < 0) threshold = 0;
        if(threshold > 1) threshold = 1;
        std::cout << threshold << std::endl;
    }else if(aotk->keyState(CTRL)){
        stepsize *= 1.0 + p/30.0;
        if(stepsize < 0) stepsize = 0;
        if(stepsize > 1) stepsize = 1;
        std::cout << stepsize << std::endl;
    }else if(aotk->keyState((Z))){
        div_coeff *= 1.0 + p/30.0;
        if(div_coeff < 0) div_coeff = 0;
        if(div_coeff > 1) div_coeff = 1;
        std::cout << div_coeff << std::endl;
    }
}
void DVR::resize(unsigned int w,unsigned int h){
    win_w = w;
    win_h = h;
    frontFace.create(w,h);
    backFace.create(w,h);
}

DVR::~DVR(){
    delete data;
}


void DVR::calcGradients(){
    unsigned int i;
    int gx,gy,gz;
    for(unsigned int z = 0;z<volumeInfo.depth;z++)for(unsigned int y = 0;y<volumeInfo.height;y++)for(unsigned int x = 0;x<volumeInfo.width;x++){
        i = INDEX(x,y,z,volumeInfo.width,volumeInfo.height);
        if((z==0||z==volumeInfo.depth-1) || (y==0||y==volumeInfo.height-1) || (x==0||x==volumeInfo.width-1)){
            data[i*4+0] = 128;
            data[i*4+1] = 128;
            data[i*4+2] = 128;
        }else{
            gx = data[INDEX(x+1,y,z,volumeInfo.width,volumeInfo.height)*4+3] - data[INDEX(x-1,y,z,volumeInfo.width,volumeInfo.height)*4+3];
            gy = data[INDEX(x,y+1,z,volumeInfo.width,volumeInfo.height)*4+3] - data[INDEX(x,y-1,z,volumeInfo.width,volumeInfo.height)*4+3];
            gz = data[INDEX(x,y,z+1,volumeInfo.width,volumeInfo.height)*4+3] - data[INDEX(x,y,z-1,volumeInfo.width,volumeInfo.height)*4+3];

            data[i*4+0] = 128 + 0.5*gx;
            data[i*4+1] = 128 + 0.5*gy;
            data[i*4+2] = 128 + 0.5*gz;
        }
//        std::cout << data[i*4+3] << std::endl;
    }
}

void DVR::logic(){}
void DVR::graphic(){}
void DVR::prepare(){

}
void DVR::render(){
    glMultMatrixf(trans._1d);

    frontFace.clear();
    frontFace.bind();
    glClear(GL_DEPTH_BUFFER_BIT);
    drawFaces();
    frontFace.unbind();

    backFace.clear();
    backFace.bind();
    glClearDepth(0);
    glDepthFunc(GL_GREATER);
    glClear(GL_DEPTH_BUFFER_BIT);
    drawFaces();
    backFace.unbind();


    glClearDepth(1);
    glDepthFunc(GL_LESS);
    glClear(GL_DEPTH_BUFFER_BIT);

    backFace.render();
    glUseProgram(0);
    glBindTexture(GL_TEXTURE_2D,0);
//    drawFaces();

    glUseProgram(pgm);


    glUniform2f(window_size_loc,win_w,win_h);
    glUniform1f(threshold_loc,threshold);
    glUniform1f(stepsize_loc,stepsize);
    glUniform1f(div_coeff_loc,div_coeff);

    glUniform1i(type_loc,type);

    glUniform1i(front_tex_loc, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, frontFace.getTex());

    glUniform1i(back_tex_loc, 1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, backFace.getTex());

    glUniform1i(vol_tex_loc, 2);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_3D, tex);

    drawFaces();


    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, 0);

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_3D, 0);
    glActiveTexture(GL_TEXTURE0);
    glUseProgram(0);
    getAllError(__FILE__,__LINE__);
}

void DVR::keyUp(KEY key){
}

void DVR::keyImpulse(unsigned char key){

}

void DVR::keyDown(KEY key){
    if(key == SPACE){
        switch(type){
            case RayInCoord:
                type = RayOutCoord;
                break;
            case RayOutCoord:
                type = avg;
                break;
            case avg:
                type = GradMag;
                break;
            case GradMag:
                type = mip;
                break;
            case mip:
                type = density;
                break;
            case density:
                type = RayInCoord;
                break;
            default:
                break;
        }
    }
}

void DVR::mousemotion(int dx,int dy){
    rotx += dx * 0.03;
    roty += dy * 0.03;
    trans = Matrix::rotateX(roty)*Matrix::rotateY(-rotx);
}

void DVR::drawFaces(){
    glBegin(GL_QUADS);
    glColor3f(0,0,0);glVertex3f(-1,-1,-1);
    glColor3f(1,0,0);glVertex3f(1,-1,-1);
    glColor3f(1,1,0);glVertex3f(1,1,-1);
    glColor3f(0,1,0);glVertex3f(-1,1,-1);

    glColor3f(0,0,1);glVertex3f(-1,-1,1);
    glColor3f(1,0,1);glVertex3f(1,-1,1);
    glColor3f(1,1,1);glVertex3f(1,1,1);
    glColor3f(0,1,1);glVertex3f(-1,1,1);

    glColor3f(0,0,0);glVertex3f(-1,-1,-1);
    glColor3f(1,0,0);glVertex3f(1,-1,-1);
    glColor3f(1,0,1);glVertex3f(1,-1,1);
    glColor3f(0,0,1);glVertex3f(-1,-1,1);

    glColor3f(0,1,0);glVertex3f(-1,1,-1);
    glColor3f(1,1,0);glVertex3f(1,1,-1);
    glColor3f(1,1,1);glVertex3f(1,1,1);
    glColor3f(0,1,1);glVertex3f(-1,1,1);

    glColor3f(0,0,0);glVertex3f(-1,-1,-1);
    glColor3f(0,1,0);glVertex3f(-1,1,-1);
    glColor3f(0,1,1);glVertex3f(-1,1,1);
    glColor3f(0,0,1);glVertex3f(-1,-1,1);

    glColor3f(1,0,0);glVertex3f(1,-1,-1);
    glColor3f(1,1,0);glVertex3f(1,1,-1);
    glColor3f(1,1,1);glVertex3f(1,1,1);
    glColor3f(1,0,1);glVertex3f(1,-1,1);


    glEnd();
}
};
