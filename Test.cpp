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
