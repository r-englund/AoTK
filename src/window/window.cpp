#include <AoTK/window_handler.h>

namespace AoTK{
Window *__window;

Window * Window::getWindow(){
    return __window;
}

#ifndef AoTK_GLUT
void Window::start(){
    std::cout << "starting" << std::endl;
    __run = true;
    while(__run){
        checkForMessages();
        idleEvent();
        if(redisplay){
            if(__dispFunc != NULL){
            __dispFunc();
        }
//        getAllError("Main Loop",-1);
        swapBuffers();
        redisplay = false;
        }
    }

}
#endif

void Window::getClientSize(uint16_t &w,uint16_t &h)const{
    w = this->client_width;
    h = this->client_height;
}
void Window::getWindowSize(uint16_t &w,uint16_t &h)const{
    w = this->window_width;
    h = this->window_height;
}

void Window::stop(){
    __run = false;
}

void Window::addKeyboardListener(Listeners::KeyboardListener *l){
    if(std::count(keyboardListeners.begin(),keyboardListeners.end(),l) == 0)
        keyboardListeners.push_back(l);
}
unsigned int Window::addKeyUpListener(void (*l)(KEY key)){
    keyUpListenerFunctions[__keyUpId] = l;
    return __keyUpId++;
}
unsigned int Window::addKeyDownListener(void (*l)(KEY key)){
    keyDownListenerFunctions[__keyDownId] = l;
    return __keyDownId++;
}

unsigned int Window::addKeyImpulseListener(void (*l)(unsigned char key)){
    keyImpuleListenerFunctions[__keyImpulseId] = l;
    return __keyImpulseId++;
}

void Window::addResizeListener(Listeners::ResizeListener *l){
    if(std::count(resizeListeners.begin(),resizeListeners.end(),l) == 0)
        resizeListeners.push_back(l);
}

unsigned int Window::addResizeListener(void (l)(unsigned int, unsigned int)){
    resizeListenerFunctions[__resizeId] = l;
    return __resizeId++;
}


void Window::addMouseListener(Listeners::MouseListener *l){
    if(std::count(mouseListeners.begin(),mouseListeners.end(),l) == 0)
        mouseListeners.push_back(l);
}

unsigned int Window::addMousePressListener(void (*l)(MOUSE_BUTTON mb,unsigned int x,unsigned int y)){
    mousePressListenerFunctions[__mousePressId] = l;
    return __mousePressId++;
}

unsigned int Window::addMouseReleaseListener(void (*l)(MOUSE_BUTTON mb,unsigned int x,unsigned int y)){
    mouseReleaseListenerFunctions[__mouseReleaseId] = l;
    return __mouseReleaseId++;
}


void Window::addMouseMotionListener(Listeners::MouseMotionListener *l){
    if(std::count(mouseMotionListeners.begin(),mouseMotionListeners.end(),l) == 0)
        mouseMotionListeners.push_back(l);
}

unsigned int Window::addMouseMotionListener(void (*l)(int dx,int dy)){
    mouseMotionListenerFunctions[__mouseMotionId] = l;
    return __mouseMotionId++;
}

unsigned int Window::addPassiveMouseMotionListener(void (*l)(int dx,int dy)){
    passiveMouseMotionListenerFunctions[__mousePassiveMotionId] = l;
    return __mousePassiveMotionId++;
}


void Window::addScrollListener(Listeners::ScrollListener *l){
    if(std::count(scrollListeners.begin(),scrollListeners.end(),l) == 0)
        scrollListeners.push_back(l);
}

unsigned int Window::addScrollListener(void (*l)(int p)){
    scrollListenerFunctions[__scrollId] = l;
    return __scrollId++;
}

void Window::addIdleListener(Listeners::IdleListener *l){
    if(std::count(idleListeners.begin(),idleListeners.end(),l) == 0)
        idleListeners.push_back(l);
}

unsigned int Window::addIdleListener(void (*l)()){
    idleListenerFunctions[__idleId] = l;
    return __idleId++;
}

void Window::removeKeyboardListener(Listeners::KeyboardListener *l){
    while(std::count(keyboardListeners.begin(),keyboardListeners.end(),l) != 0)
        keyboardListeners.erase(std::find(keyboardListeners.begin(),keyboardListeners.end(),l));
}
void Window::removeResizeListener(Listeners::ResizeListener *l){
    while(std::count(resizeListeners.begin(),resizeListeners.end(),l) != 0)
        resizeListeners.erase(std::find(resizeListeners.begin(),resizeListeners.end(),l));
}
void Window::removeMouseListener(Listeners::MouseListener *l){
    while(std::count(mouseListeners.begin(),mouseListeners.end(),l) != 0)
        mouseListeners.erase(std::find(mouseListeners.begin(),mouseListeners.end(),l));
}
void Window::removeMouseMotionListener(Listeners::MouseMotionListener *l){
    while(std::count(mouseMotionListeners.begin(),mouseMotionListeners.end(),l) != 0)
        mouseMotionListeners.erase(std::find(mouseMotionListeners.begin(),mouseMotionListeners.end(),l));
}
void Window::removeScrollListener(Listeners::ScrollListener *l){
    while(std::count(scrollListeners.begin(),scrollListeners.end(),l) != 0)
        scrollListeners.erase(std::find(scrollListeners.begin(),scrollListeners.end(),l));
}

void Window::removeKeyUpListener(unsigned int id){
    auto it = keyUpListenerFunctions.find(id);
    if(it != keyUpListenerFunctions.end())
        keyUpListenerFunctions.erase(it);
}
void Window::removeKeyDownListener(unsigned int id){
    auto it = keyDownListenerFunctions.find(id);
    if(it != keyDownListenerFunctions.end())
        keyDownListenerFunctions.erase(it);
}
void Window::removeKeyImpulseListener(unsigned int id){
    auto it = keyImpuleListenerFunctions.find(id);
    if(it != keyImpuleListenerFunctions.end())
        keyImpuleListenerFunctions.erase(it);
}
void Window::removeResizeListener(unsigned int id){
    auto it = resizeListenerFunctions.find(id);
    if(it != resizeListenerFunctions.end())
        resizeListenerFunctions.erase(it);
}
void Window::removeMousePressListener(unsigned int id){
    auto it = mousePressListenerFunctions.find(id);
    if(it != mousePressListenerFunctions.end())
        mousePressListenerFunctions.erase(it);
}
void Window::removeMouseReleaseListener(unsigned int id){
    auto it = mouseReleaseListenerFunctions.find(id);
    if(it != mouseReleaseListenerFunctions.end())
        mouseReleaseListenerFunctions.erase(it);
}
void Window::removeMouseMotionListener(unsigned int id){
    auto it = mouseMotionListenerFunctions.find(id);
    if(it != mouseMotionListenerFunctions.end())
        mouseMotionListenerFunctions.erase(it);
}
void Window::removePassiveMouseMotionListener(unsigned int id){
    auto it = passiveMouseMotionListenerFunctions.find(id);
    if(it != passiveMouseMotionListenerFunctions.end())
        passiveMouseMotionListenerFunctions.erase(it);
}
void Window::removeScrollListener(unsigned int id){
    auto it = scrollListenerFunctions.find(id);
    if(it != scrollListenerFunctions.end())
        scrollListenerFunctions.erase(it);
}

void Window::removeIdleListener(unsigned int id){
    auto it = idleListenerFunctions.find(id);
    if(it != idleListenerFunctions.end())
        idleListenerFunctions.erase(it);
}



void Window::keyDownEvent(KEY key){
	for(auto l = keyboardListeners.begin();l != keyboardListeners.end();++l)
        (*l)->keyDown(key);
    for(auto l = keyUpListenerFunctions.begin();l != keyUpListenerFunctions.end();++l)
        (l->second)(key);
}
void Window::keyUpEvent(KEY key){
	for(auto l = keyboardListeners.begin();l != keyboardListeners.end();++l)
        (*l)->keyUp(key);
    for(auto l = keyDownListenerFunctions.begin();l != keyDownListenerFunctions.end();++l)
        (l->second)(key);
}
void Window::keyImpulseEvent(unsigned char key){
    for(auto l = keyboardListeners.begin();l != keyboardListeners.end();++l)
        (*l)->keyImpulse(key);
    for(auto l = keyImpuleListenerFunctions.begin();l != keyImpuleListenerFunctions.end();++l)
        (l->second)(key);
}
void Window::resizeEvent(){
    setSizes();
    for(auto l = resizeListeners.begin();l != resizeListeners.end();++l)
        (*l)->resize(client_width,client_height);
    for(auto l = resizeListenerFunctions.begin();l != resizeListenerFunctions.end();++l)
        (l->second)(client_width,client_height);
}
void Window::mousePressEvent(MOUSE_BUTTON mb,unsigned int x,unsigned int y){
    for(auto l = mouseListeners.begin();l != mouseListeners.end();++l)
        (*l)->mousePress(mb,x,y);
    for(auto l = mousePressListenerFunctions.begin();l != mousePressListenerFunctions.end();++l)
        (l->second)(mb,x,y);
}
void Window::mouseReleaseEvent(MOUSE_BUTTON mb,unsigned int x,unsigned int y){
    for(auto l = mouseListeners.begin();l != mouseListeners.end();++l)
        (*l)->mouseRelease(mb,x,y);
    for(auto l = mouseReleaseListenerFunctions.begin();l != mouseReleaseListenerFunctions.end();++l)
        (l->second)(mb,x,y);
}

void Window::mousemotionEvent(int dx,int dy){
	for(auto l = mouseMotionListeners.begin();l != mouseMotionListeners.end();++l)
        (*l)->mousemotion(dx,dy);
    for(auto l = mouseMotionListenerFunctions.begin();l != mouseMotionListenerFunctions.end();++l)
        (l->second)(dx,dy);
}
void Window::passiveMousemotionEvent(int dx,int dy){
    for(auto l = mouseMotionListeners.begin();l != mouseMotionListeners.end();++l)
        (*l)->passiveMousemotion(dx,dy);
    for(auto l = passiveMouseMotionListenerFunctions.begin();l != passiveMouseMotionListenerFunctions.end();++l)
        (l->second)(dx,dy);
}
void Window::scrollEvent(int p){
	for(auto l = scrollListeners.begin();l != scrollListeners.end();++l)
        (*l)->scroll(p);
    for(auto l = scrollListenerFunctions.begin();l != scrollListenerFunctions.end();++l)
        (l->second)(p);
}

void Window::idleEvent(){
	for(auto l = idleListeners.begin();l != idleListeners.end();++l)
        (*l)->idle();
    for(auto l = idleListenerFunctions.begin();l != idleListenerFunctions.end();++l)
        (l->second)();
}


void getAllError(std::string file, int line){
    int i = 0;
    GLenum err = glGetError();
    while(err != GL_NO_ERROR){
        static int i = 0;
        if(i++)
            return;
        switch (err){
            case GL_NO_ERROR:
                break;
            #ifdef GL_INVALID_ENUM
            case GL_INVALID_ENUM:
                std::cerr <<i++ << " GL_INVALID_ENUM @ " << file <<":"<<line << ": An unacceptable value is specified for an enumerated argument. The offending command is ignored and has no other side effect than to set the error flag." << std::endl;
                break;
            #endif
            #ifdef GL_INVALID_VALUE
            case GL_INVALID_VALUE:
                std::cerr <<i++  << "GL_INVALID_VALUE @ " << file <<":"<<line  << ": A numeric argument is out of range. The offending command is ignored and has no other side effect than to set the error flag." << std::endl;
                break;
            #endif
            #ifdef GL_INVALID_OPERATION
            case GL_INVALID_OPERATION:
                std::cerr <<i++  << "GL_INVALID_OPERATION @ " << file <<":"<<line  << ": The specified operation is not allowed in the current state. The offending command is ignored and has no other side effect than to set the error flag." << std::endl;
                break;
            #endif
            #ifdef GL_STACK_OVERFLOW
            case GL_STACK_OVERFLOW:
                std::cerr <<i++  << "GL_STACK_OVERFLOW @ " << file <<":"<<line  << ": This command would cause a stack overflow. The offending command is ignored and has no other side effect than to set the error flag." << std::endl;
                break;
            #endif
            #ifdef GL_STACK_UNDERFLOW
            case GL_STACK_UNDERFLOW:
                std::cerr <<i++  << "GL_STACK_UNDERFLOW @ " << file <<":"<<line  << ": This command would cause a stack underflow. The offending command is ignored and has no other side effect than to set the error flag." << std::endl;
                break;
            #endif
            #ifdef GL_OUT_OF_MEMORY
            case GL_OUT_OF_MEMORY:
                std::cerr <<i++  << "GL_OUT_OF_MEMORY @ " << file <<":"<<line  << ": There is not enough memory left to execute the command. The state of the GL is undefined, except for the state of the error flags, after this error is recorded." << std::endl;
                break;
            #endif
            #ifdef GL_TABLE_TOO_LARGE
            case GL_TABLE_TOO_LARGE:
                std::cerr <<i++  << "GL_TABLE_TOO_LARGE @ " << file <<":"<<line  << ": The specified table exceeds the implementation's maximum supported table size. The offending command is ignored and has no other side effect than to set the error flag." << std::endl;
                break;
            #endif
            #ifdef GL_INVALID_FRAMEBUFFER_OPERATION
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                std::cerr <<i++  << "GL_INVALID_FRAMEBUFFER_OPERATION @ " << file <<":"<<line  << ": The framebuffer object is not complete. The offending command is ignored and has no other side effect than to set the error flag." << std::endl;
                break;
            #endif

            default:
                std::cerr <<i++  << "GL_ERROR @ " << file <<":"<<line  << ": Unkown error:" << err << std::endl;
        }
        err = glGetError();
    }
}


};
