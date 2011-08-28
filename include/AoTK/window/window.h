#ifndef WINDOW_H
#define WINDOW_H


#include <functional>

#include <map>
#include <AoTK/aotk.h>
#include "../math.h"

namespace AoTK{
    class Window{
        std::vector<Listeners::KeyboardListener*> keyboardListeners;
        std::map<int,std::function<void(KEY key)> > keyUpListenerFunctions; unsigned int __keyUpId;
        std::map<int,std::function<void(KEY key)> > keyDownListenerFunctions; unsigned int __keyDownId;
        std::map<int,std::function<void(unsigned char key)> > keyImpuleListenerFunctions; unsigned int __keyImpulseId;

        std::vector<Listeners::ResizeListener*> resizeListeners;
        std::map<int,std::function<void(unsigned int, unsigned int)> > resizeListenerFunctions;  unsigned int __resizeId;

        std::vector<Listeners::MouseListener*> mouseListeners;

        std::map<int,std::function<void(MOUSE_BUTTON mb,unsigned int x,unsigned int y)> > mousePressListenerFunctions;  unsigned int __mousePressId;
        std::map<int,std::function<void(MOUSE_BUTTON mb,unsigned int x,unsigned int y)> > mouseReleaseListenerFunctions;  unsigned int __mouseReleaseId;


        std::vector<Listeners::MouseMotionListener*> mouseMotionListeners;
        std::map<int,std::function<void (int dx,int dy)> > mouseMotionListenerFunctions;  unsigned int __mouseMotionId;
        std::map<int,std::function<void (int dx,int dy)> > passiveMouseMotionListenerFunctions;  unsigned int __mousePassiveMotionId;


        std::vector<Listeners::ScrollListener*> scrollListeners;
        std::map<int,std::function<void(int p)> > scrollListenerFunctions;  unsigned int __scrollId;

        std::vector<Listeners::IdleListener*> idleListeners;
        std::map<int,std::function<void()> > idleListenerFunctions;  unsigned int __idleId;

        uint16_t window_width,window_height;
        uint16_t client_width,client_height;
        std::string title;

        bool redisplay;

        Window()
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

        std::function<void()> __dispFunc;


        #ifdef AoTK_WIN
        HWND hwnd;        //Window handler
        GLuint pixelformat;//Pixelforment
        WNDCLASSEX wincl;  //Window class
        HDC hDC;           //display content
        HGLRC hRC;         //rendering content
		
		long styles;
		

		bool initWindowClass();
		bool createWindow(std::string);
		bool setPixelFormat();
        #endif
        #ifdef AoTK_UNIX
		XVisualInfo* vi;
		GLXContext glContext;
		bool GL3;
		XSetWindowAttributes XAttr;
		Colormap cmap;
		Atom wmDelete;
		::Window win;
        #endif
        
        unsigned long long __start;


        void fullscreenOn(unsigned int device = 0);
        void fullscreenOff();
        AoTK::Math::Vector2<uint16_t> oldSize;
        AoTK::Math::Vector2<uint16_t> oldPos;


       

    public:
        unsigned long long getRunTime();

        void redraw(){redisplay = true;}

        void addKeyboardListener(Listeners::KeyboardListener *l);
        unsigned int addKeyUpListener(std::function<void (KEY key)> );
        unsigned int addKeyDownListener(std::function<void (KEY key)> );
        unsigned int addKeyImpulseListener(std::function<void (unsigned char key)> );

        void addResizeListener(Listeners::ResizeListener *l);
        unsigned int addResizeListener(std::function<void (unsigned int, unsigned int)> );

        void addMouseListener(Listeners::MouseListener *l);
        unsigned int addMousePressListener(std::function<void(MOUSE_BUTTON mb,unsigned int x,unsigned int y)> );
        unsigned int addMouseReleaseListener(std::function<void(MOUSE_BUTTON mb,unsigned int x,unsigned int y)> );

        void addMouseMotionListener(Listeners::MouseMotionListener *l);
        unsigned int addMouseMotionListener(std::function<void(int dx,int dy)> );
        unsigned int addPassiveMouseMotionListener(std::function<void(int dx,int dy)> );

        void addScrollListener(Listeners::ScrollListener *l);
        unsigned int addScrollListener(std::function<void(int p)> );

        void addIdleListener(Listeners::IdleListener *l);
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

        void getWindowSize(uint16_t &width,uint16_t &height)const;
        void getClientSize(uint16_t &width,uint16_t &height)const;
    };
};

#endif
