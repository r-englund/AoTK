
#include <AoTK/aotk.h>




namespace AoTK{

ResizeListener::ResizeListener(std::string _name){
    if(_name.length() == 0){
        static int uid = 0;
        char buf[30];
        sprintf(buf,"unnamed_ResizeListener_%i",uid++);
        name = buf;
    }else
        name = _name;

    aotk->registerResizeListener(this);
    std::cout << "Created ResizeListnere: " << name << std::endl;
}

ResizeListener::~ResizeListener(){
    aotk->unregisterResizeListener(this);
}

KeyboardListener::KeyboardListener(std::string _name){
    if(_name.length() == 0){
        static int uid = 0;
        char buf[30];
        sprintf(buf,"unnamed_keyboardlistener_%i",uid++);
        name = buf;
    }else
        name = _name;

    aotk->registerKeyboardListener(this);
    std::cout << "Created KeyboardListnere: " << name << std::endl;
}

KeyboardListener::~KeyboardListener(){
    aotk->unregisterKeyboardListener(this);
}


MouseListener::MouseListener(std::string _name){
    if(_name.length() == 0){
        static int uid = 0;
        char buf[30];
        sprintf(buf,"unnamed_mouselistener_%i",uid++);
        name = buf;
    }else
        name = _name;

    aotk->registerMouseListener(this);
    std::cout << "Created MouseListener: " << name << std::endl;
}

MouseListener::~MouseListener(){
    aotk->unregisterMouseListener(this);
}


MouseMotionListener::MouseMotionListener(std::string _name){
    if(_name.length() == 0){
        static int uid = 0;
        char buf[30];
        sprintf(buf,"unnamed_mouseMotionlistener_%i",uid++);
        name = buf;
    }else
        name = _name;

    aotk->registerMouseMotionListener(this);
    std::cout << "Created MouseMotionListener: " << name << std::endl;
}

MouseMotionListener::~MouseMotionListener(){
    aotk->unregisterMouseMotionListener(this);
}

ScrollListener::ScrollListener(std::string _name){
    if(_name.length() == 0){
        static int uid = 0;
        char buf[30];
        sprintf(buf,"unnamed_ScrollListener_%i",uid++);
        name = buf;
    }else
        name = _name;

    aotk->registerScrollListener(this);
    std::cout << "Created ScrollListener: " << name << std::endl;
}

ScrollListener::~ScrollListener(){
    aotk->unregisterScrollListener(this);
}

};




