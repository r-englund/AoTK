#include <AoTK/aotk.h>

#define INDEX(x,y,z,w,h) ((x)+((w)*(y))+((z)*(w)*(h)))
//
//#include <stdio.h>
//#include <cmath>
//#include <assert.h>

namespace AoTK{

DVR::DVR(GLint _shader,GLuint _tex,Matrix _toWorld,std::string _name):
 Object(_shader,_toWorld, _name),
 KeyboardListener(_name),
 MouseMotionListener(_name),
 ScrollListener(_name),
 type(density),
 tex(_tex),
 roty(0),
 rotx(0),
 threshold(0.5),
 div_coeff(0.5),
 stepsize(1.0/450.0)
{
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
};

void DVR::scroll(int p){
    if(aotk->keyState(SHIFT)){
        threshold += 0.005 * p;
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
