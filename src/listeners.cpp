
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

};




