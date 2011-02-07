#include <AoTK/aotk.h>


namespace AoTK{
    AOTK *aotk = 0;

#ifdef _WIN32

void InitAoTKwin(){
    char t[500];
    GetConsoleTitleA( t, 500 );
    aotk->hwndConsole = FindWindowA( NULL, t );
    aotk->hInst = (HINSTANCE)GetWindowLong(aotk->hwndConsole, GWL_HINSTANCE);
}
#endif


void initAoTK(){
    assert(aotk==0 && "rOGE inti should only be called once");
    aotk = new AOTK(),
    #ifdef _WIN32
        InitAoTKwin();
    #else
        #error AoTK not yet implmented for your OP SYS
    #endif

    std::cout << "AoTK initialized" << std::endl;
}
AOTK::AOTK(){
    running = 0;
    window = 0;
}
AOTK::~AOTK(){

}

void AOTK::start(){
    assert(window && "No window created");
    running = 1;
    getAllError(__FILE__,__LINE__);
    resize(window->size.w,window->size.h);
    mainLoop();
}

void AOTK::mainLoop(){
    unsigned int frame = 1;
    while(running){
        window->checkForMessages();
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);

        for(auto vp = window->viewports.begin();vp != window->viewports.end() ; ++vp){
            (*vp)->scene->doLogic(frame);
            getAllError(__FILE__,__LINE__);
        }
        for(auto vp = window->viewports.begin();vp != window->viewports.end() ; ++vp){
            (*vp)->scene->doGraphics(frame);
            getAllError(__FILE__,__LINE__);
        }
        for(auto vp = window->viewports.begin();vp != window->viewports.end() ; ++vp){
            (*vp)->scene->doPrepare(frame);
            getAllError(__FILE__,__LINE__);
        }
        for(auto vp = window->viewports.begin();vp != window->viewports.end() ; ++vp){
            (*vp)->setViewport();
            glMatrixMode(GL_PROJECTION);
            glLoadMatrixf((*vp)->cam->getProjectionMatrix()._1d);
            glMatrixMode(GL_MODELVIEW);
            glLoadMatrixf((*vp)->cam->getToWorldMatrix()._1d);

            getAllError(__FILE__,__LINE__);
            (*vp)->scene->render();
            getAllError(__FILE__,__LINE__);
        }

        window->swapBuffers();
    }
}

void AOTK::stop(){running = 0;}

void AOTK::keyUp(KEY key){
    for(auto o = keyboardListeners.begin(); o != keyboardListeners.end();++o){
        o->second->keyUp(key);
    }
}
void AOTK::keyDown(KEY key){
    for(auto o = keyboardListeners.begin(); o != keyboardListeners.end();++o){
        o->second->keyDown(key);
    }
}
void AOTK::keyImpulse(unsigned char key){
    for(auto o = keyboardListeners.begin(); o != keyboardListeners.end();++o){
        o->second->keyImpulse(key);
    }
}
void AOTK::resize(unsigned int w,unsigned int h){
    for(auto o = resizeListeners.begin(); o != resizeListeners.end();++o){
        o->second->resize(w,h);
    }
}


Scene* AOTK::createWindow(Size2D size,std::string title){
    window = new Window(size,title);
    assert(window && "Couldnt create a window instance");
    return aotk->scenes["main_scene"];
}


void AOTK::registerObject(Object *o){
    assert(objects.count(o->name) == 0 && "Object already exists");
    objects[o->name] = o;
}

void AOTK::registerScene(Scene *s){
    assert(scenes.count(s->name) == 0 && "Scene already exists");
    scenes[s->name] = s;
}

void AOTK::registerViewport(Viewport *vp){
    assert(viewports.count(vp->name) == 0 && "Viewport already exists");
    viewports[vp->name] = vp;
}


void AOTK::registerKeyboardListener(KeyboardListener *kl){
    assert(keyboardListeners.count(kl->name) == 0 && "KeyboardListener already exists");
    keyboardListeners[kl->name] = kl;
}

void AOTK::registerResizeListener(ResizeListener *rl){
    assert(resizeListeners.count(rl->name) == 0 && "ResizeListener already exists");
    resizeListeners[rl->name] = rl;
}

void AOTK::unregisterObject(Object *o){
    assert(objects.count(o->name) != 0 && "Object doesnt exists");
    objects.erase(o->name);
}

void AOTK::unregisterScene(Scene *s){
    assert(scenes.count(s->name) != 0 && "Scene doesnt exists");
    scenes.erase(s->name);
}

void AOTK::unregisterViewport(Viewport *vp){
    assert(viewports.count(vp->name) != 0 && "Viewport doesnt exists");
    viewports.erase(vp->name);
}

void AOTK::unregisterKeyboardListener(KeyboardListener *kl){
    assert(keyboardListeners.count(kl->name) != 0 && "KeyboardListener doesnt exists");
    keyboardListeners.erase(kl->name);
}

void AOTK::unregisterResizeListener(ResizeListener *rl){
    assert(resizeListeners.count(rl->name) != 0 && "ResizeListener doesnt exists");
    resizeListeners.erase(rl->name);
}



};
