#include <AoTK/aotk.h>

using namespace AoTK;

Scene *s;

class TestObject : public Object{
public:
    TestObject(std::string _name,Matrix _toWorld):Object(0,_toWorld,_name){}
    virtual void logic(){}
    virtual void graphic(){}
    virtual void prepare(){}
    virtual void render(){
        glBegin(GL_QUADS);
        glColor3f(1,1,0);glVertex3f(1,1,0);
        glColor3f(0,1,0);glVertex3f(-1,1,0);
        glColor3f(1,0,0);glVertex3f(-1,-1,0);
        glColor3f(0,0,1);glVertex3f(1,-1,0);
        glEnd();
    }
};

class WireframeToggle : public KeyboardListener{
public:
    WireframeToggle():KeyboardListener("WireframeToogle"){
        wfstate = 1;
        culstate = 0;
    }
    void takeScreenShoot(){
        Image i(aotk->window->getSize().x,aotk->window->getSize().y,RGB);
        float *f = new float[(int)(3*aotk->window->getSize().x*aotk->window->getSize().y)]();
        glReadPixels(0,0,aotk->window->getSize().x,aotk->window->getSize().y,GL_RGB,GL_FLOAT,f);
        i.setData(f);

        char img_name[40];
        sprintf(img_name,"screens/%i.bmp",(int)time(NULL));
        std::cout << "f"<< std::endl;
        i.saveBMP(img_name);
        std::cout << img_name << std::endl;
    }

    bool wfstate;
    int culstate;
    virtual void keyDown(KEY key){
        if(key == KEY::P){
            takeScreenShoot();
        }
        if(key == M){
            if(wfstate){
                glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
                wfstate = 0;
            }else{
                glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
                wfstate = 1;
            }
        }
        if(key == C){
            switch(culstate){
            case 0:
                glEnable(GL_CULL_FACE);
                glCullFace(GL_BACK);
                culstate = 1;
                std::cout << "Cull back face" << std::endl;
                break;
            case 1:
                glDisable(GL_CULL_FACE);
                culstate = 2;
                std::cout << "Cull No faces" << std::endl;
                break;
            case 2:
                glEnable(GL_CULL_FACE);
                glCullFace(GL_FRONT);

                std::cout << "Cull front face" << std::endl;
                culstate = 0;
                break;
            default:
                break;
            }
        }
    };
    virtual void keyUp(KEY key){};
    virtual void keyImpulse(unsigned char key){};
};



void initGL();
void createObjects();
void createObjects(){
    Matrix m = Matrix::translate(0,0,-1);
//    TestObject *t = new TestObject("test",m);
////    s->addObject(t);
//
//    Light *l = Light::CreatePointLight("Light1");
////    s->addLight(l);
//
//    Sphere *sp = new Sphere(0.01,m,4,"Sphere");
//    sp->setTexture(Create2DTexture(Image::LoadBMP("C:/Users/rickard/Pictures/earth.bmp")));
//    s->addObject(sp);

    // 384,384, 240

    Volume<uint16_t> v = Volume<uint16_t>::loadRawVolume(256,256,256,(char *)"volumes/3dhead.raw");

    DVR::VolumeInfo vi;
    vi.width  = 128;
    vi.height = 256;
    vi.depth  = 256;
    vi.filename = "volumes/vismale.raw";
    GLuint pgm = loadShaderProgram("shaders/dvr_vert.glsl","shaders/dvr_frag.glsl");
    DVR *d = new DVR(pgm,vi,m,"Volume Rendering Test");
    s->addObject(d);
}

void initGL(){
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glDepthFunc(GL_LESS);
    glClearDepth(1.0f);
    glClearColor(0.0,0.0,0.0,0.0);
}

int main(int argc, const char** argv){
    std::cout << clamp(1,2,3) << std::endl;
    std::cout << clamp(2.5,2,3) << std::endl;
    std::cout << clamp(5,2,3) << std::endl;
//    initAoTK();
//    Size2D<unsigned int> size;
//    size.w = 800;
//    size.h = 600;
//
//    new WireframeToggle();
//
//    s = aotk->createWindow(size,"AoTK test Window");
//    //aotk->createSubWindow(size);
//    initGL();
//
//    createObjects();
//    int i;
//    glGetIntegerv(GL_MAX_TEXTURE_SIZE,&i);
//    aotk->start();
}
