#include <AoTK/window_handler.h>

namespace AoTK{
Window *__window;
void Window::start(){
    std::cout << "starting" << std::endl;
    __run = true;
    while(__run){
        checkForMessages();

        if(__dispFunc != NULL){
            __dispFunc();
        }else{
            for(auto l = redrawListeners.begin();l != redrawListeners.end();++l)
                (*l)->draw();
        }

//        getAllError("Main Loop",-1);
        swapBuffers();
    }

}

void Window::getSize(uint16_t &w,uint16_t &h)const{
    w = this->width;
    h = this->height;
}

void Window::stop(){
    __run = false;
}

void Window::addKeyboardListener(KeyboardListener *l){
    if(std::count(keyboardListeners.begin(),keyboardListeners.end(),l) == 0)
        keyboardListeners.push_back(l);
}

void Window::addRedrawListener(RedrawListener *l){
    if(std::count(redrawListeners.begin(),redrawListeners.end(),l) == 0)
        redrawListeners.push_back(l);
}

void Window::addResizeListener(ResizeListener *l){
    if(std::count(resizeListeners.begin(),resizeListeners.end(),l) == 0)
        resizeListeners.push_back(l);
}
void Window::addMouseListener(MouseListener *l){
    if(std::count(mouseListeners.begin(),mouseListeners.end(),l) == 0)
        mouseListeners.push_back(l);
}
void Window::addMouseMotionListener(MouseMotionListener *l){
    if(std::count(mouseMotionListeners.begin(),mouseMotionListeners.end(),l) == 0)
        mouseMotionListeners.push_back(l);
}
void Window::addScrollListener(ScrollListener *l){
    if(std::count(scrollListeners.begin(),scrollListeners.end(),l) == 0)
        scrollListeners.push_back(l);
}

void Window::removeKeyboardListener(KeyboardListener *l){
    while(std::count(keyboardListeners.begin(),keyboardListeners.end(),l) != 0)
        keyboardListeners.erase(std::find(keyboardListeners.begin(),keyboardListeners.end(),l));
}
void Window::removeResizeListener(ResizeListener *l){
    while(std::count(resizeListeners.begin(),resizeListeners.end(),l) != 0)
        resizeListeners.erase(std::find(resizeListeners.begin(),resizeListeners.end(),l));
}
void Window::removeMouseListener(MouseListener *l){
    while(std::count(mouseListeners.begin(),mouseListeners.end(),l) != 0)
        mouseListeners.erase(std::find(mouseListeners.begin(),mouseListeners.end(),l));
}
void Window::removeMouseMotionListener(MouseMotionListener *l){
    while(std::count(mouseMotionListeners.begin(),mouseMotionListeners.end(),l) != 0)
        mouseMotionListeners.erase(std::find(mouseMotionListeners.begin(),mouseMotionListeners.end(),l));
}
void Window::removeScrollListener(ScrollListener *l){
    while(std::count(scrollListeners.begin(),scrollListeners.end(),l) != 0)
        scrollListeners.erase(std::find(scrollListeners.begin(),scrollListeners.end(),l));
}

void Window::removeRedrawListener(RedrawListener *l){
    while(std::count(redrawListeners.begin(),redrawListeners.end(),l) != 0)
        redrawListeners.erase(std::find(redrawListeners.begin(),redrawListeners.end(),l));
}


void Window::keyDownEvent(KEY key){
	for(auto l = keyboardListeners.begin();l != keyboardListeners.end();++l)
        (*l)->keyDown(key);
}
void Window::keyUpEvent(KEY key){
	for(auto l = keyboardListeners.begin();l != keyboardListeners.end();++l)
        (*l)->keyUp(key);
}
void Window::keyImpulseEvent(unsigned char key){
    for(auto l = keyboardListeners.begin();l != keyboardListeners.end();++l)
        (*l)->keyImpulse(key);
}
void Window::resizeEvent(unsigned int w,unsigned int h){
    for(auto l = resizeListeners.begin();l != resizeListeners.end();++l)
        (*l)->resize(w,h);
}
void Window::mousePressEvent(MOUSE_BUTTON mb,unsigned int x,unsigned int y){
    for(auto l = mouseListeners.begin();l != mouseListeners.end();++l)
        (*l)->mousePress(mb,x,y);
}
void Window::mouseReleaseEvent(MOUSE_BUTTON mb,unsigned int x,unsigned int y){
    for(auto l = mouseListeners.begin();l != mouseListeners.end();++l)
        (*l)->mouseRelease(mb,x,y);
}

void Window::mousemotionEvent(int dx,int dy){
	for(auto l = mouseMotionListeners.begin();l != mouseMotionListeners.end();++l)
        (*l)->mousemotion(dx,dy);
}
void Window::passiveMousemotionEvent(int dx,int dy){
    for(auto l = mouseMotionListeners.begin();l != mouseMotionListeners.end();++l)
        (*l)->passiveMousemotion(dx,dy);
}
void Window::scrollEvent(int p){
	for(auto l = scrollListeners.begin();l != scrollListeners.end();++l)
        (*l)->scroll(p);
}


void getAllError(std::string file, int line){
    int i = 0;
    GLenum err = glGetError();
    while(err != GL_NO_ERROR){
        switch (err){
            case GL_NO_ERROR:
                break;
            case GL_INVALID_ENUM:
                std::cerr <<i++ << " GL_INVALID_ENUM @ " << file <<":"<<line << ": An unacceptable value is specified for an enumerated argument. The offending command is ignored and has no other side effect than to set the error flag." << std::endl;
                break;
            case GL_INVALID_VALUE:
                std::cerr <<i++  << "GL_INVALID_VALUE @ " << file <<":"<<line  << ": A numeric argument is out of range. The offending command is ignored and has no other side effect than to set the error flag." << std::endl;
                break;
            case GL_INVALID_OPERATION:
                std::cerr <<i++  << "GL_INVALID_OPERATION @ " << file <<":"<<line  << ": The specified operation is not allowed in the current state. The offending command is ignored and has no other side effect than to set the error flag." << std::endl;
                break;
            case GL_STACK_OVERFLOW:
                std::cerr <<i++  << "GL_STACK_OVERFLOW @ " << file <<":"<<line  << ": This command would cause a stack overflow. The offending command is ignored and has no other side effect than to set the error flag." << std::endl;
                break;
            case GL_STACK_UNDERFLOW:
                std::cerr <<i++  << "GL_STACK_UNDERFLOW @ " << file <<":"<<line  << ": This command would cause a stack underflow. The offending command is ignored and has no other side effect than to set the error flag." << std::endl;
                break;
            case GL_OUT_OF_MEMORY:
                std::cerr <<i++  << "GL_OUT_OF_MEMORY @ " << file <<":"<<line  << ": There is not enough memory left to execute the command. The state of the GL is undefined, except for the state of the error flags, after this error is recorded." << std::endl;
                break;
            case GL_TABLE_TOO_LARGE:
                std::cerr <<i++  << "GL_TABLE_TOO_LARGE @ " << file <<":"<<line  << ": The specified table exceeds the implementation's maximum supported table size. The offending command is ignored and has no other side effect than to set the error flag." << std::endl;
                break;
            default:
                std::cerr <<i++  << "GL_ERROR @ " << file <<":"<<line  << ": Unkown error:" << err << std::endl;
        }
        err = glGetError();
    }
}


};
