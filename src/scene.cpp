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
    for(auto obj = objects.begin();obj != objects.end();++obj)
        (*obj)->doRender();
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
};
