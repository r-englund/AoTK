#ifndef WINDOW_H
#define WINDOW_H


#include <functional>

#include <map>
#include <AoTK/aotk.h>
#include "../math.h"

namespace AoTK{
    class Window{
        std::vector<Listeners::KeyboardListener*> keyboardListeners;
//        std::map<int,void (*)(KEY key)> keyUpListenerFunctions; unsigned int __keyUpId;
        std::map<int,std::function<void(KEY key)> > keyUpListenerFunctions; unsigned int __keyUpId;
//        std::map<int,void (*)(KEY key)> keyDownListenerFunctions; unsigned int __keyDownId;
        std::map<int,std::function<void(KEY key)> > keyDownListenerFunctions; unsigned int __keyDownId;
//        std::map<int,void (*)(unsigned char key)> keyImpuleListenerFunctions; unsigned int __keyImpulseId;
        std::map<int,std::function<void(unsigned char key)> > keyImpuleListenerFunctions; unsigned int __keyImpulseId;

        std::vector<Listeners::ResizeListener*> resizeListeners;
//        std::map<int,void (*)(unsigned int, unsigned int)> resizeListenerFunctions;  unsigned int __resizeId;
        std::map<int,std::function<void(unsigned int, unsigned int)> > resizeListenerFunctions;  unsigned int __resizeId;

        std::vector<Listeners::MouseListener*> mouseListeners;
//        std::map<int,void (*)(MOUSE_BUTTON mb,unsigned int x,unsigned int y)> mousePressListenerFunctions;  unsigned int __mousePressId;
//        std::map<int,void (*)(MOUSE_BUTTON mb,unsigned int x,unsigned int y)> mouseReleaseListenerFunctions;  unsigned int __mouseReleaseId;

        std::map<int,std::function<void(MOUSE_BUTTON mb,unsigned int x,unsigned int y)> > mousePressListenerFunctions;  unsigned int __mousePressId;
        std::map<int,std::function<void(MOUSE_BUTTON mb,unsigned int x,unsigned int y)> > mouseReleaseListenerFunctions;  unsigned int __mouseReleaseId;


        std::vector<Listeners::MouseMotionListener*> mouseMotionListeners;
//        std::map<int,void (*)(int dx,int dy)> mouseMotionListenerFunctions;  unsigned int __mouseMotionId;
//        std::map<int,void (*)(int dx,int dy)> passiveMouseMotionListenerFunctions;  unsigned int __mousePassiveMotionId;
        std::map<int,std::function<void (int dx,int dy)> > mouseMotionListenerFunctions;  unsigned int __mouseMotionId;
        std::map<int,std::function<void (int dx,int dy)> > passiveMouseMotionListenerFunctions;  unsigned int __mousePassiveMotionId;


        std::vector<Listeners::ScrollListener*> scrollListeners;
//        std::map<int,void (*)(int p)> scrollListenerFunctions;  unsigned int __scrollId;
            std::map<int,std::function<void(int p)> > scrollListenerFunctions;  unsigned int __scrollId;

        std::vector<Listeners::IdleListener*> idleListeners;
//        std::map<int,void (*)()> idleListenerFunctions;  unsigned int __idleId;
        std::map<int,std::function<void()> > idleListenerFunctions;  unsigned int __idleId;

        uint16_t window_width,window_height;
        uint16_t client_width,client_height;
        std::string title;

        bool redisplay;

        Window()/*:
        keyboardListeners(),
        keyUpListenerFunctions(),__keyUpId(0),
        keyDownListenerFunctions(),__keyDownId(0),
        keyImpuleListenerFunctions(),__keyImpulseId(0),
        resizeListeners(),
        resizeListenerFunctions(),__resizeId(0),
        mouseListeners(),
        mousePressListenerFunctions(),__mousePressId(0),
        mouseReleaseListenerFunctions(),__mouseReleaseId(0),
        mouseMotionListeners(),
        mouseMotionListenerFunctions(),__mouseMotionId(0),
        passiveMouseMotionListenerFunctions(),__mousePassiveMotionId(0),
        scrollListeners(),
        scrollListenerFunctions(),__scrollId(0),
        idleListeners(0),__idleId(0),
        window_width(0),
        window_height(0),
        client_width(0),
        client_height(0),
        title(""),
        redisplay(0),
        __run(false),
        __dispFunc(false)
        #ifdef AoTK_WIN
        ,hwndConsole(NULL),
        hwnd(),
        hInst(),
        pixelformat(),
        wincl(),
        hDC(),
        hRC()
        #endif*/
        {
        }
        Window(const Window &w);
        Window& operator=(const Window &w);
        ~Window();

        void checkForMessages();
        void swapBuffers();
        void setSizes();


        bool __run;
        bool fullscreen;

//        void (*__dispFunc)(void);

        std::function<void()> __dispFunc;


        #ifdef AoTK_WIN
        HWND hwndConsole; //Window handler for the console
        HWND hwnd;        //Window handler
        HINSTANCE hInst;  //APplication instance
        GLuint pixelformat;//Pixelforment
        WNDCLASSEX wincl;  //Window class
        HDC hDC;           //display content
        HGLRC hRC;         //rendering content
		
		long styles;

		 friend BOOL CALLBACK _initDevices(HMONITOR hMonitor,HDC hdcMonitor,LPRECT lprcMonitor,LPARAM dwData);
        friend BOOL CALLBACK _countDevices(HMONITOR hMonitor,HDC hdcMonitor,LPRECT lprcMonitor,LPARAM dwData);
		

		bool initWindowClass();
		bool createWindow(std::string);
		bool setPixelFormat();
        #endif
        #ifdef AoTK_UNIX
		Display *disp;
		int scr;
		XVisualInfo* vi;
		GLXContext glContext;
		bool GL3;
		XSetWindowAttributes XAttr;
		Colormap cmap;
		Atom wmDelete;
    	::Window win;
        #endif
        #ifdef AoTK_GLUT
        friend void display();
        friend void idle();
        friend void resize(int w, int h);
        friend void mouseClick(int button, int state, int x, int y);
        friend void passiveMotion(int x, int y);
        friend void motion(int x, int y);
        friend void keyboard(unsigned char key,int x, int y);
        friend void keyboardUp(unsigned char key,int x, int y);
        #endif

        AoTK::Math::Vector4<int> *devices;
        int number_of_devices;

        unsigned long long __start;


        void fullscreenOn(unsigned int device = 0);
        void fullscreenOff();
        AoTK::Math::Vector2<uint16_t> oldSize;
        AoTK::Math::Vector2<uint16_t> oldPos;


       

    public:
        unsigned long long getRunTime();

        AoTK::Math::Vector4<int> *getDevices(){return devices;}
        unsigned int getNumberOfDevices(){return number_of_devices;}
        void redraw(){redisplay = true;}
        void initDevices();

        void addKeyboardListener(Listeners::KeyboardListener *l);
//        unsigned int addKeyUpListener(void (*keyUp)(KEY key));
        unsigned int addKeyUpListener(std::function<void (KEY key)> );
//        unsigned int addKeyDownListener(void (*keyDown)(KEY key));
        unsigned int addKeyDownListener(std::function<void (KEY key)> );
//        unsigned int addKeyImpulseListener(void (*keyImpulse)(unsigned char key));
        unsigned int addKeyImpulseListener(std::function<void (unsigned char key)> );

        void addResizeListener(Listeners::ResizeListener *l);
//        unsigned int addResizeListener(void (*resize)(unsigned int, unsigned int));
        unsigned int addResizeListener(std::function<void (unsigned int, unsigned int)> );

        void addMouseListener(Listeners::MouseListener *l);
//        unsigned int addMousePressListener(void (*)(MOUSE_BUTTON mb,unsigned int x,unsigned int y));
//        unsigned int addMouseReleaseListener(void (*)(MOUSE_BUTTON mb,unsigned int x,unsigned int y));
        unsigned int addMousePressListener(std::function<void(MOUSE_BUTTON mb,unsigned int x,unsigned int y)> );
        unsigned int addMouseReleaseListener(std::function<void(MOUSE_BUTTON mb,unsigned int x,unsigned int y)> );

        void addMouseMotionListener(Listeners::MouseMotionListener *l);
//        unsigned int addMouseMotionListener(void (*)(int dx,int dy));
//        unsigned int addPassiveMouseMotionListener(void (*)(int dx,int dy));
        unsigned int addMouseMotionListener(std::function<void(int dx,int dy)> );
        unsigned int addPassiveMouseMotionListener(std::function<void(int dx,int dy)> );

        void addScrollListener(Listeners::ScrollListener *l);
//        unsigned int addScrollListener(void (*)(int p));
        unsigned int addScrollListener(std::function<void(int p)> );

        void addIdleListener(Listeners::IdleListener *l);
//        unsigned int addIdleListener(void (*)());
        unsigned int addIdleListener(std::function<void()> );

        void setFullscreen(bool set = true,unsigned int device = 0);
        void toggleFullscreen();
        bool isFullscreen()const;

        void removeKeyboardListener(Listeners::KeyboardListener *l);
        void removeResizeListener(Listeners::ResizeListener *l);
        void removeMouseListener(Listeners::MouseListener *l);
        void removeMouseMotionListener(Listeners::MouseMotionListener *l);
        void removeScrollListener(Listeners::ScrollListener *l);
        void removeIdleListener(Listeners::IdleListener *l);

        void removeKeyUpListener(unsigned int id);
        void removeKeyDownListener(unsigned int id);
        void removeKeyImpulseListener(unsigned int id);
        void removeResizeListener(unsigned int id);
        void removeMousePressListener(unsigned int id);
        void removeMouseReleaseListener(unsigned int id);
        void removeMouseMotionListener(unsigned int id);
        void removePassiveMouseMotionListener(unsigned int id);
        void removeScrollListener(unsigned int id);
        void removeIdleListener(unsigned int id);


        void keyDownEvent(KEY key);
        void keyUpEvent(KEY key);
        void keyImpulseEvent(unsigned char key);
        void resizeEvent();
        void mousePressEvent(MOUSE_BUTTON mb,unsigned int x,unsigned int y);
        void mouseReleaseEvent(MOUSE_BUTTON mb,unsigned int x,unsigned int y);
        void mousemotionEvent(int dx,int dy);
        void passiveMousemotionEvent(int dx,int dy);
        void scrollEvent(int p);
        void idleEvent();

        void start();
        void stop();

        static Window* createWindow(uint16_t width,uint16_t height,std::string title,bool force32 = false);
        static Window* getWindow();

        void setDisplayFunction(std::function<void()> dispFunc){
            __dispFunc = dispFunc;
        }
//        void setDisplayFunction(void (*dispFunc)(void)){
//            __dispFunc = dispFunc;
//        }

        void getWindowSize(uint16_t &width,uint16_t &height)const;
        void getClientSize(uint16_t &width,uint16_t &height)const;
    };
};

#endif
