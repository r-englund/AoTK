#include <AoTK/aotk.h>


#define BUFFER_OFFSET(i) ((const GLvoid*)(i))
#define INDEX(x,y,w) ((x)+((w)*(y)))

namespace AoTK{
Scene::Scene(std::string _name){
    if(_name.length() == 0){
        static int uid = 0;
        char buf[30];
        sprintf(buf,"unnamed_scene_%i",uid++);
        name = buf;
    }else
        name = _name;
    aotk->registerScene(this);
    std::cout << "Created Scene: " << name << std::endl;
}

Scene::~Scene(){
    aotk->unregisterScene(this);
}

void Scene::doLogic(unsigned int frame){
    for(auto obj = objects.begin();obj != objects.end();++obj){
        (*obj)->doLogic(frame);
    }
}
void Scene::doGraphics(unsigned int frame){
    for(auto obj = objects.begin();obj != objects.end();++obj)
        (*obj)->doGraphic(frame);
}
void Scene::doPrepare(unsigned int frame){
    for(auto obj = objects.begin();obj != objects.end();++obj)
        (*obj)->doPrepare(frame);
}
void Scene::render(){
    getAllError(__FILE__,__LINE__);
    GLint maxLights;
    glGetIntegerv(GL_MAX_LIGHTS,&maxLights);
    if(lights.size() > 0){
        glEnable(GL_LIGHTING);
        unsigned int numLights = 0;
        for(auto li = lights.begin();li != lights.end();++li){
            if(numLights >= maxLights){
                std::cout << "Trying to enable more lights than possible. max light is: " << maxLights <<std::endl;
                break;
            }else{
                (*li)->setLight(GL_LIGHT0+numLights++);
            }
        }
    }

    for(auto obj = objects.begin();obj != objects.end();++obj)
        (*obj)->doRender();
    if(lights.size() > 0){
        glDisable(GL_LIGHTING);
        for(int i = 0; i< lights.size() && i < maxLights;i++)
            glDisable(GL_LIGHT0+i);
    }
    getAllError(__FILE__,__LINE__);
}


void Scene::addObject(Object *o){
    if(std::count(objects.begin(),objects.end(),o) != 0)
        return;
    objects.push_back(o);
}

void Scene::removeObject(Object *o){
    if(std::count(objects.begin(),objects.end(),o) == 0)
        return;
    objects.erase(std::find(objects.begin(),objects.end(),o));
}

void Scene::addLight(Light *l){
    if(std::count(lights.begin(),lights.end(),l) != 0)
        return;
    lights.push_back(l);
}

void Scene::removeLight(Light *l){
    if(std::count(lights.begin(),lights.end(),l) == 0)
        return;
    lights.erase(std::find(lights.begin(),lights.end(),l));
}
};
