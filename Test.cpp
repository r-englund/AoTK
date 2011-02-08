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

void initGL();
void createObjects();
void createObjects(){
    Matrix m = Matrix::translate(0,0,-3);
    TestObject *t = new TestObject("test",m);
    s->addObject(t);


    s->addLight(Light::CreatePointLight("Light1"));
    s->addLight(Light::CreatePointLight("Light2"));
    s->addLight(Light::CreatePointLight("Light3"));
    s->addLight(Light::CreatePointLight("Light4"));
    s->addLight(Light::CreatePointLight("Light5"));
    s->addLight(Light::CreatePointLight("Light6"));
    s->addLight(Light::CreatePointLight("Light7"));
    s->addLight(Light::CreatePointLight("Light8"));
    s->addLight(Light::CreatePointLight("Light9"));
    s->addLight(Light::CreatePointLight("Light10"));
}

void initGL(){
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearDepth(1.0f);
    glClearColor(0.0,0.0,0.0,0.0);
}

int main(int argc, const char** argv){
    initAoTK();
    initGL();
    Size2D size;
    size.w = 800;
    size.h = 600;

    s = aotk->createWindow(size,"AoTK test Window");

    createObjects();

    aotk->start();
}
