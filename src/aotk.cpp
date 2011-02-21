#include <AoTK/aotk.h>


namespace AoTK{
    AOTK *aotk = 0;

#ifdef _WIN32

void InitAoTKwin(){
    char t[500];
    GetConsoleTitleA( t, 500 );
    aotk->hwndConsole = FindWindowA( NULL, t );
    aotk->hInst = (HINSTANCE)GetWindowLong(aotk->hwndConsole, GWL_HINSTANCE);
    aotk->mouseInside = 0;
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

time_t tt,cur;
void AOTK::mainLoop(){
    unsigned int frame = 1;
    tt = time(NULL);
    while(running){
////        cur = time(NULL);
////        long ds = cur-tt;
////        if(ds > 10){
////            std::cout << frame / float(ds) << "fps" << std::endl;
////            tt = time(NULL);
////        }
//
//        std::cout << time(NULL) <<std::endl;

        window->checkForMessages();
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);

        for(auto vp = window->viewports.begin();vp != window->viewports.end() ; ++vp){
            (*vp)->cam->doLogic(frame);
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

        frame++;
    }
}

void AOTK::stop(){running = 0;}
bool AOTK::keyState(KEY key){
    return keyStates[key];
}

void AOTK::keyUp(KEY key){
    keyStates[key] = 0;
    for(auto o = keyboardListeners.begin(); o != keyboardListeners.end();++o){
        o->second->keyUp(key);
    }
}
void AOTK::keyDown(KEY key){
    keyStates[key] = 1;
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

void AOTK::mousemotion(int dx,int dy){
    for(auto o = mouseMotionListeners.begin(); o != mouseMotionListeners.end();++o){
        o->second->mousemotion(dx,dy);
    }
}
void AOTK::passiveMousemotion(int dx,int dy){
    for(auto o = mouseMotionListeners.begin(); o != mouseMotionListeners.end();++o){
        o->second->passiveMousemotion(dx,dy);
    }
}
void AOTK::mousePress(MOUSE_BUTTON mb,unsigned int x,unsigned int y){
    for(auto o = mouseListeners.begin(); o != mouseListeners.end();++o){
        o->second->mousePress(mb,x,y);
    }
}
void AOTK::mouseRelease(MOUSE_BUTTON mb,unsigned int x,unsigned int y){
    for(auto o = mouseListeners.begin(); o != mouseListeners.end();++o){
        o->second->mouseRelease(mb,x,y);
    }
}
void AOTK::scroll(int p){
    for(auto o = scrollListeners.begin(); o != scrollListeners.end();++o){
        o->second->scroll(p);
    }
}

Scene* AOTK::createWindow(Size2D<unsigned int> size,std::string title){
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

void AOTK::registerMouseListener(MouseListener *ml){
    assert(mouseListeners.count(ml->name) == 0 && "MouseListener already exists");
    mouseListeners[ml->name] = ml;
}

void AOTK::registerMouseMotionListener(MouseMotionListener *ml){
    assert(mouseMotionListeners.count(ml->name) == 0 && "MouseMotionListener already exists");
    mouseMotionListeners[ml->name] = ml;
}

void AOTK::registerScrollListener(ScrollListener *sl){
    assert(scrollListeners.count(sl->name) == 0 && "ScrollListener already exists");
    scrollListeners[sl->name] = sl;
}

void AOTK::registerLightSource(Light *l){
    assert(lights.count(l->name) == 0 && "Light already exists");
    lights[l->name] = l;
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

void AOTK::unregisterMouseListener(MouseListener *ml){
    assert(mouseListeners.count(ml->name) != 0 && "MouseListener doesnt exists");
    mouseListeners.erase(ml->name);
}

void AOTK::unregisterMouseMotionListener(MouseMotionListener *ml){
    assert(mouseMotionListeners.count(ml->name) != 0 && "MouseMotionListener doesnt exists");
    mouseMotionListeners.erase(ml->name);
}

void AOTK::unregisterScrollListener(ScrollListener *sl){
    assert(scrollListeners.count(sl->name) != 0 && "ScrollListener doesnt exists");
    scrollListeners.erase(sl->name);
}

void AOTK::unregisterLightSource(Light *l){
    assert(lights.count(l->name) != 0 && "LightSource doesnt exists");
    lights.erase(l->name);
}



};
