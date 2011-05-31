#ifndef AOTK_WINDOW_HANDLER_H
#define AOTK_WINDOW_HANDLER_H

#include <stdint.h>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>


#ifdef _WIN32

#pragma comment(lib, "gdi32")
#pragma comment(lib, "kernel32")
#pragma comment(lib, "user32")


#define GLEW_STATIC
#include <windows.h>
#include <AoTK/externals/glew.h>
#include <AoTK/externals/wglew.h>

#else //UNIX
#define AoTK_UNIX
#include <AoTK/externals/glew.h>
#include <AoTK/externals/glxew.h>
#endif

#define GLERRORS() AoTK::getAllError(__FILE__,__LINE__)

namespace AoTK{
    void getAllError(std::string file, int line);

    enum KEY{
        F1,F2,F3,F4,F5,F6,F7,F8,F9,F10,F11,F12,F13,F14,F15,F16,F17,F18,F19,F20,F21,F22,F23,F24,
        ESC,
        CAPSLOCK,NUMLOCK,SCROLLLOCK,
        SHIFT,
        CTRL,
        ALT,
        SPACE,
        TAB,
        HOME,
        END,
        DEL,
        INS,
        PGUP,PGDOWN,
        ARROW_LEFT,ARROW_RIGHT,ARROW_DOWN,ARROW_UP,ALTGR,ENTER,
        BACKSPACE,
        PAUSE,
        PRINT,
        PRINTSCREEN,
        KEY0,KEY1,KEY2,KEY3,KEY4,KEY5,KEY6,KEY7,KEY8,KEY9,
        MULTI,ADD,SUB,DECIMAL,DIVIDE,
        A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,
        UNASIGNED_KEY
    };

    enum MOUSE_BUTTON{
        LEFT_BUTTON,RIGHT_BUTTON,MIDDLE_BUTTON
    };
};


#include "window/listeners.h"
#include "window/window.h"

namespace AoTK{
    extern Window *__window;
};

#endif
