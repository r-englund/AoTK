#ifndef WINDOW_H
#define WINDOW_H

#include <map>

namespace AoTK{
    class Window{
        std::vector<KeyboardListener*> keyboardListeners;
        std::map<int,void (*)(KEY key)> keyUpListenerFunctions; unsigned int __keyUpId;
        std::map<int,void (*)(KEY key)> keyDownListenerFunctions; unsigned int __keyDownId;
        std::map<int,void (*)(unsigned char key)> keyImpuleListenerFunctions; unsigned int __keyImpulseId;

        std::vector<ResizeListener*> resizeListeners;
        std::map<int,void (*)(unsigned int, unsigned int)> resizeListenerFunctions;  unsigned int __resizeId;

        std::vector<MouseListener*> mouseListeners;
        std::map<int,void (*)(MOUSE_BUTTON mb,unsigned int x,unsigned int y)> mousePressListenerFunctions;  unsigned int __mousePressId;
        std::map<int,void (*)(MOUSE_BUTTON mb,unsigned int x,unsigned int y)> mouseReleaseListenerFunctions;  unsigned int __mouseReleaseId;


        std::vector<MouseMotionListener*> mouseMotionListeners;
        std::map<int,void (*)(int dx,int dy)> mouseMotionListenerFunctions;  unsigned int __mouseMotionId;
        std::map<int,void (*)(int dx,int dy)> passiveMouseMotionListenerFunctions;  unsigned int __mousePassiveMotionId;


        std::vector<ScrollListener*> scrollListeners;
        std::map<int,void (*)(int p)> scrollListenerFunctions;  unsigned int __scrollId;

        std::vector<IdleListener*> idleListeners;
        std::map<int,void (*)()> idleListenerFunctions;  unsigned int __idleId;

        uint16_t width,height;
        std::string title;

        Window():
        keyboardListeners(),
        resizeListeners(),
        mouseListeners(),
        mouseMotionListeners(),
        scrollListeners(),
        width(0),
        height(0),
        title(""),
        __run(false),
        __dispFunc(false),
        #ifdef _WIN32
        hwndConsole(NULL),
        hwnd(),
        hInst(),
        pixelformat(),
        wincl(),
        hDC(),
        hRC(),
        #endif
        __keyUpId(0),
        __keyDownId(0),
        __keyImpulseId(0),
        __resizeId(0),
        __mousePressId(0),
        __mouseReleaseId(0),
        __mouseMotionId(0),
        __mousePassiveMotionId(0),
        __scrollId(0),
        __idleId(0)
        {
        }
        Window(const Window &w);
        Window& operator=(const Window &w);
        ~Window();

        void checkForMessages();
        void swapBuffers();


        bool __run;


        void (*__dispFunc)(void);

        #ifdef _WIN32
        HWND hwndConsole; //Window handler for the console
        HWND hwnd;        //Window handler
        HINSTANCE hInst;  //APplication instance
        GLuint pixelformat;//Pixelforment
        WNDCLASSEX wincl;  //Window class
        HDC hDC;           //display content
        HGLRC hRC;         //rendering content

        #endif


    public:
        void addKeyboardListener(KeyboardListener *l);
        unsigned int addKeyUpListener(void (*keyUp)(KEY key));
        unsigned int addKeyDownListener(void (*keyDown)(KEY key));
        unsigned int addKeyImpulseListener(void (*keyImpulse)(unsigned char key));

        void addResizeListener(ResizeListener *l);
        unsigned int addResizeListener(void (*resize)(unsigned int, unsigned int));

        void addMouseListener(MouseListener *l);
        unsigned int addMousePressListener(void (*)(MOUSE_BUTTON mb,unsigned int x,unsigned int y));
        unsigned int addMouseReleaseListener(void (*)(MOUSE_BUTTON mb,unsigned int x,unsigned int y));

        void addMouseMotionListener(MouseMotionListener *l);
        unsigned int addMouseMotionListener(void (*)(int dx,int dy));
        unsigned int addPassiveMouseMotionListener(void (*)(int dx,int dy));

        void addScrollListener(ScrollListener *l);
        unsigned int addScrollListener(void (*)(int p));

        void addIdleListener(IdleListener *l);
        unsigned int addIdleListener(void (*)());

        void removeKeyboardListener(KeyboardListener *l);
        void removeResizeListener(ResizeListener *l);
        void removeMouseListener(MouseListener *l);
        void removeMouseMotionListener(MouseMotionListener *l);
        void removeScrollListener(ScrollListener *l);
        void removeIdleListener(IdleListener *l);

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
        void resizeEvent(unsigned int w,unsigned int h);
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

        void setDisplayFunction(void (*dispFunc)(void)){
            __dispFunc = dispFunc;
        }

        void getSize(uint16_t &width,uint16_t &height)const;
    };
};

#endif
