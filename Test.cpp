#include <AoTK/aotk.h>

using namespace AoTK;

Scene *s;

class TestObject : public Object{
public:
    TestObject(std::string name,Matrix toWorld):Object(0,toWorld,name){}
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
    bool wfstate;
    int culstate;
    virtual void keyDown(KEY key){
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
            }
        }
    };
    virtual void keyUp(KEY key){};
    virtual void keyImpulse(unsigned char key){};
};

void initGL();
void createObjects();
void createObjects(){
    Matrix m = Matrix::translate(0,0,0);
    TestObject *t = new TestObject("test",m);
//    s->addObject(t);

    Light *l = Light::CreatePointLight("Light1");
//    s->addLight(l);

    Sphere *sp = new Sphere(0.6,m,4,"Sphere");
    sp->setTexture(Create2DTexture(Image::LoadBMP("C:/Users/rickard/Pictures/lines.bmp")));
    s->addObject(sp);
}

void initGL(){
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glDepthFunc(GL_LESS);
    glClearDepth(1.0f);
    glClearColor(0.0,0.0,0.0,0.0);
}

int main(int argc, const char** argv){
    initAoTK();
    Size2D size;
    size.w = 800;
    size.h = 600;

    new WireframeToggle();

    s = aotk->createWindow(size,"AoTK test Window");
    initGL();

    createObjects();

    aotk->start();
}
