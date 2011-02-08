#ifndef ENUMS_H
#define ENUMS_H

namespace AoTK{

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
        A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z
    };


    enum MOUSE_BUTTON{
        LEFT_BUTTON,RIGHT_BUTTON,MIDDLE_BUTTON
    };

    enum LIGHT_TYPE{
        POINT,
        DIRECTION,
        SPOT
    };

    enum IMG_MODE{
        GREYSCALE,
        RGB,
        RGBA
    };

    enum IMG_CONVOLUTION_PADDIN{
        zerofill
    };






};




#endif
