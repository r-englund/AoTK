#ifndef WINDOW_H
#define WINDOW_H



namespace AoTK{
    class Window{
        std::vector<KeyboardListener*> keyboardListeners;
        std::vector<ResizeListener*> resizeListeners;
        std::vector<MouseListener*> mouseListeners;
        std::vector<MouseMotionListener*> mouseMotionListeners;
        std::vector<ScrollListener*> scrollListeners;
        std::vector<RedrawListener*> redrawListeners;

        uint16_t width,height;
        std::string title;

        Window():
        keyboardListeners(),
        resizeListeners(),
        mouseListeners(),
        mouseMotionListeners(),
        scrollListeners(),
        redrawListeners(),
        width(0),
        height(0),
        title(""),
        __run(false),
        __dispFunc(false)
        #ifdef _WIN32
        ,hwndConsole(NULL),
        hwnd(),
        hInst(),
        pixelformat(),
        wincl(),
        hDC(),
        hRC()
        #endif
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
        void addResizeListener(ResizeListener *l);
        void addMouseListener(MouseListener *l);
        void addMouseMotionListener(MouseMotionListener *l);
        void addScrollListener(ScrollListener *l);
        void addRedrawListener(RedrawListener *l);

        void removeKeyboardListener(KeyboardListener *l);
        void removeResizeListener(ResizeListener *l);
        void removeMouseListener(MouseListener *l);
        void removeMouseMotionListener(MouseMotionListener *l);
        void removeScrollListener(ScrollListener *l);
        void removeRedrawListener(RedrawListener *l);

        void keyDownEvent(KEY key);
        void keyUpEvent(KEY key);
        void keyImpulseEvent(unsigned char key);
        void resizeEvent(unsigned int w,unsigned int h);
        void mousePressEvent(MOUSE_BUTTON mb,unsigned int x,unsigned int y);
        void mouseReleaseEvent(MOUSE_BUTTON mb,unsigned int x,unsigned int y);
        void mousemotionEvent(int dx,int dy);
        void passiveMousemotionEvent(int dx,int dy);
        void scrollEvent(int p);

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
