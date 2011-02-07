#ifndef LISTENERS_H
#define LISTENERS_H

#include "enums.h"

namespace AoTK{
class KeyboardListener{
    friend class AOTK;
private:
    std::string name;
public:
    virtual void keyDown(KEY key) = 0;
    virtual void keyUp(KEY key) = 0;
    virtual void keyImpulse(unsigned char key) = 0;

    KeyboardListener(std::string name ="");
    virtual ~KeyboardListener();

};


class ResizeListener{
    friend class AOTK;
private:
    std::string name;
public:
    virtual void resize(unsigned int w,unsigned int h) = 0;

    ResizeListener(std::string name ="");
    virtual ~ResizeListener();
};
};



#endif
