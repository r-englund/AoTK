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

class MouseListener{
    friend class AOTK;
private:
    std::string name;
public:
     MouseListener(std::string name ="");
    virtual ~MouseListener();

    virtual void mousePress(MOUSE_BUTTON mb,unsigned int x,unsigned int y) = 0;
    virtual void mouseRelease(MOUSE_BUTTON mb,unsigned int x,unsigned int y) = 0;

};

class MouseMotionListener{
    friend class AOTK;
private:
    std::string name;
public:
    MouseMotionListener(std::string name ="");
    virtual ~MouseMotionListener();

   virtual void mousemotion(int dx,int dy) = 0;
   virtual void passiveMousemotion(int dx,int dy) = 0;

};

class ScrollListener{
    friend class AOTK;
private:
    std::string name;
public:
     ScrollListener(std::string name ="");
    virtual ~ScrollListener();

   virtual void scroll(int p) = 0;

};

};

#endif
