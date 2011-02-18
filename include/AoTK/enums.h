#ifndef ENUMS_H
#define ENUMS_H

namespace AoTK{

    enum HITANDMISS_BOOLEAN : signed int{
        SKIP = -1,
        ONE = 1,
        ZERO = 0
    };

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

    enum FILTER_WRAP{
        zero_padding, // all elements outside equal to zero
        one_padding, // all elements outside equal to one ( or maximum)
        shrink, //Only use the elements where kernel has perfect fit
        clamp, //cpoy the closest element
        mirror,  //miror along the axis eg : -3 = 3 and max + 3 = max - 3
        repeat //max + 3 = 3 and -3 = max -3
    };






};




#endif
