#ifndef LISTENERS_H
#define LISTENERS_H

namespace AoTK{
namespace Listeners{
class KeyboardListener{
public:
    virtual void keyDown(KEY key) = 0;
    virtual void keyUp(KEY key) = 0;
    virtual void keyImpulse(unsigned char key) = 0;

    KeyboardListener(){}
    virtual ~KeyboardListener(){}
};

class ResizeListener{
public:
    virtual void resize(unsigned int w,unsigned int h) = 0;
    ResizeListener(){}
    virtual ~ResizeListener(){}
};

class MouseListener{
public:
    virtual ~MouseListener(){}
    MouseListener(){}

    virtual void mousePress(MOUSE_BUTTON mb,unsigned int x,unsigned int y) = 0;
    virtual void mouseRelease(MOUSE_BUTTON mb,unsigned int x,unsigned int y) = 0;
};

class MouseMotionListener{
public:
    MouseMotionListener(){}
    virtual ~MouseMotionListener(){}

   virtual void mousemotion(int dx,int dy) = 0;
   virtual void passiveMousemotion(int dx,int dy) = 0;
};

class ScrollListener{
public:
    ScrollListener(){}
    virtual ~ScrollListener(){}

    virtual void scroll(int p) = 0;
};

class IdleListener{
public:
    IdleListener(){}
    virtual ~IdleListener(){}
    virtual void idle() = 0;
};

};
};

#endif
