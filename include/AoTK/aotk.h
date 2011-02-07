#ifndef AOTK_H
#define AOTK_H

#ifdef _WIN32
#define GLEW_STATIC
#include <windows.h>
#include <gl/glew.h>
#include <gl/wglew.h>
#endif

#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <iostream>
#include <cmath>
#include <fstream>
#include <stdint.h>
#include <assert.h>
#include <cstdlib>
#include <stdio.h>


#include "enums.h"

#include "math.h"
#include "fbo.h"
#include "glsl.h"
#include "error.h"
#include "image.h"
#include "texture.h"
#include "viewport.h"
#include "window.h"
#include "listeners.h"
#include "object.h"
#include "scene.h"

namespace AoTK{
    class AOTK{
    friend class Window;
    public:
        Scene* createWindow(Size2D size,std::string title="AoTK Window");
        void start();
        void stop();
        void keyUp(KEY key);
        void keyDown(KEY key);
        void keyImpulse(unsigned char key);
        void resize(unsigned int w,unsigned int h);

        void registerViewport(Viewport *vp);
        void registerScene(Scene *s);
        void registerObject(Object *o);
        void registerKeyboardListener(KeyboardListener *kl);
        void registerResizeListener(ResizeListener *rl);
        void unregisterViewport(Viewport *vp);
        void unregisterScene(Scene *s);
        void unregisterObject(Object *o);
        void unregisterKeyboardListener(KeyboardListener *kl);
        void unregisterResizeListener(ResizeListener *rl);
    private:
        std::map<std::string,Object*> objects;
        std::map<std::string,Viewport*> viewports;
        std::map<std::string,Scene*> scenes;
        std::map<std::string,KeyboardListener*> keyboardListeners;
        std::map<std::string,ResizeListener*>     resizeListeners;

        AOTK();
        AOTK(const AOTK &) = delete;
        AOTK &operator=(const AOTK &) = delete;
        ~AOTK();

        bool running;

        Window *window;
        void mainLoop();
    friend void initAoTK();
#ifdef _WIN32
    friend void InitAoTKwin();
    HWND hwndConsole; //Window handler for the console
    HWND hwnd;        //Window handler for the rendering content
    HINSTANCE hInst;  //APplication instance
    GLuint pixelformat;//Pixelforment
    WNDCLASSEX wincl;  //Window class
    HDC hDC;           //display content
    HGLRC hRC;         //rendering content
#endif


    };


    void initAoTK();
    extern AOTK *aotk;

};

#endif
