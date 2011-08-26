#ifndef AOTK_WINDOW_HANDLER_H
#define AOTK_WINDOW_HANDLER_H


#include <stdint.h>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>

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
        ARROW_LEFT,ARROW_RIGHT,ARROW_DOWN,ARROW_UP,
        ALTGR,ENTER,
        BACKSPACE,
        PAUSE,
        PRINT,
        PRINTSCREEN,
        KEY0,KEY1,KEY2,KEY3,KEY4,KEY5,KEY6,KEY7,KEY8,KEY9,
        MULTI,ADD,SUB,DECIMAL,DIVIDE,
        A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,
        SUPER,
        UNASIGNED_KEY
    };

    enum MOUSE_BUTTON{
        LEFT_BUTTON,RIGHT_BUTTON,MIDDLE_BUTTON
    };
};

//#define AoTK_FORCE_GLUT

#define UNIX

#if defined(_WIN32) && !defined(AoTK_FORCE_GLUT)

#define AoTK_WIN
    #ifdef _MSC_VER
	
    #pragma comment(lib, "gdi32")
    #pragma comment(lib, "kernel32")
    #pragma comment(lib, "user32")
    #endif

    #define GLEW_STATIC
    #define WINVER 0x7600
    #include <windows.h>
    #include <AoTK/externals/glew.h>
    #include <AoTK/externals/wglew.h>

	namespace AoTK{
		extern HWND hwndConsole; //Window handler for the console
		extern HINSTANCE hInst;  //Application instance

		KEY translateKEY(WPARAM w);

		BOOL CALLBACK _initDevices(HMONITOR hMonitor,HDC hdcMonitor,LPRECT lprcMonitor,LPARAM dwData);
        BOOL CALLBACK _countDevices(HMONITOR hMonitor,HDC hdcMonitor,LPRECT lprcMonitor,LPARAM dwData);
	};
	


#elif defined(UNIX)// && !defined(AoTK_FORCE_GLUT)
    #define AoTK_UNIX
	#define GLX_GLXEXT_PROTOTYPES
	#define GL_GLEXT_PROTOTYPES
    #include <AoTK/externals/glew.h>
    #include <AoTK/externals/glxew.h>
    #include <X11/extensions/xf86vmode.h>
	#include <X11/Xutil.h>

	namespace AoTK{
		extern Display *disp;
		extern int scr;

		
		KEY translateKEY(KeySym w);
	};

#else //anything else uses glut for the moment, very buggy
    #define AoTK_GLUT
    #define GLEW_STATIC
    #if defined(_WIN32)
        #include <windows.h>
        #define GLUT_DISABLE_ATEXIT_HACK
    #endif
    #include <AoTK/externals/glew.h>
    #ifdef __APPLE__
        #include <GLUT/glut.h>
    #else
        #include <GL/glut.h>
    #endif
#endif

#define GLERRORS() AoTK::getAllError(__FILE__,__LINE__)



#include "window/listeners.h"
#include "window/window.h"

namespace AoTK{
    extern Window *__window;
};

#endif
