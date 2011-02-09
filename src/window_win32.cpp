#include <AoTK/aotk.h>


#ifdef _WIN32


namespace AoTK{

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
KEY translateKEY(WPARAM w);
       union _wParam{
        WPARAM wp;
        char c[4];
    };

    union _lParam{
        LPARAM lp;
        char c[4];
    };

    KEY translateKEY(WPARAM w){
        switch(w){
            case VK_F1:
                return F1;
            case VK_F2:
                return F2;
            case VK_F3:
                return F3;
            case VK_F4:
                return F4;
            case VK_F5:
                return F5;
            case VK_F6:
                return F6;
            case VK_F7:
                return F7;
            case VK_F8:
                return F8;
            case VK_F9:
                return F9;
            case VK_F10:
                return F10;
            case VK_F11:
                return F11;
            case VK_F12:
                return F12;
            case VK_F13:
                return F13;
            case VK_F14:
                return F14;
            case VK_F15:
                return F15;
            case VK_F16:
                return F16;
            case VK_F17:
                return F17;
            case VK_F18:
                return F18;
            case VK_F19:
                return F19;
            case VK_F20:
                return F20;
            case VK_F21:
                return F21;
            case VK_F22:
                return F22;
            case VK_F23:
                return F23;
            case VK_F24:
                return F24;
            case VK_ESCAPE:
                return ESC;
            case VK_CAPITAL:
                return CAPSLOCK;
            case VK_SCROLL:
                return SCROLLLOCK;
            case VK_NUMLOCK:
                return NUMLOCK;
            case VK_SHIFT:
            case VK_RSHIFT:
            case VK_LSHIFT:
                return SHIFT;
            case VK_CONTROL:
            case VK_RCONTROL:
            case VK_LCONTROL:
                return CTRL;
            case VK_MENU:
                return ALT;
            case VK_SPACE:
                return SPACE;
            case VK_TAB:
                return TAB;
            case VK_HOME:
                return HOME;
            case VK_END:
                return END;
            case VK_DELETE:
                return DEL;
            case VK_INSERT:
                return INS;
            case VK_PRIOR:
                return PGUP;
            case VK_NEXT:
                return PGDOWN;
            case VK_LEFT:
                return ARROW_LEFT;
            case VK_UP:
                return ARROW_UP;
            case VK_RIGHT:
                return ARROW_RIGHT;
            case VK_DOWN:
                return ARROW_DOWN;
            case VK_BACK:
                return BACKSPACE;
            case VK_PAUSE:
                return PAUSE;
            case VK_PRINT:
                return PRINT;
            case VK_SNAPSHOT:
                return PRINTSCREEN;
            case 0x30:
                return KEY0;
            case 0x31:
                return KEY1;
            case 0x32:
                return KEY2;
            case 0x33:
                return KEY3;
            case 0x34:
                return KEY4;
            case 0x35:
                return KEY5;
            case 0x36:
                return KEY6;
            case 0x37:
                return KEY7;
            case 0x38:
                return KEY8;
            case 0x39:
                return KEY9;
            case VK_MULTIPLY:
                return MULTI;
            case VK_ADD:
                return ADD;
            case VK_SUBTRACT:
                return SUB;
            case VK_DECIMAL:
                return DECIMAL;
            case VK_DIVIDE:
                return DIVIDE;
            case 0x41: return A;
            case 0x42: return B;
            case 0x43: return C;
            case 0x44: return D;
            case 0x45: return E;
            case 0x46: return F;
            case 0x47: return G;
            case 0x48: return H;
            case 0x49: return I;
            case 0x4A: return J;
            case 0x4B: return K;
            case 0x4C: return L;
            case 0x4D: return M;
            case 0x4E: return N;
            case 0x4F: return O;
            case 0x50: return P;
            case 0x51: return Q;
            case 0x52: return R;
            case 0x53: return S;
            case 0x54: return T;
            case 0x55: return U;
            case 0x56: return V;
            case 0x57: return W;
            case 0x58: return X;
            case 0x59: return Y;
            case 0x5A: return Z;

            default:
                std::cout << "WARNING: unhandled key pressed: " << w <<" " << (char) w << std::endl;
        }
    }

    int prev_x = -1,prev_y = -1,dx,dy;
    float maxl = 0;
    float l;


    LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
        switch (message)                  /* handle the messages */
        {
            case WM_DESTROY:
                aotk->stop();
                break;
            case WM_KEYDOWN:
                aotk->keyDown(translateKEY(wParam));
                break;
            case WM_KEYUP:
                aotk->keyUp(translateKEY(wParam));
                break;
            case WM_CHAR:
                aotk->keyImpulse((unsigned char)wParam);
                break;
            case WM_SIZE:
                aotk->resize(LOWORD(lParam),HIWORD(lParam));
                break;
            case WM_LBUTTONUP:
                aotk->mouseRelease(LEFT_BUTTON,LOWORD(lParam),HIWORD(lParam));
                break;
            case WM_LBUTTONDOWN:
                aotk->mousePress(LEFT_BUTTON,LOWORD(lParam),HIWORD(lParam));
                break;
            case WM_RBUTTONUP:
                aotk->mouseRelease(RIGHT_BUTTON,LOWORD(lParam),HIWORD(lParam));
                break;
            case WM_RBUTTONDOWN:
                aotk->mousePress(RIGHT_BUTTON,LOWORD(lParam),HIWORD(lParam));
                break;
            case WM_MBUTTONUP:
                aotk->mouseRelease(MIDDLE_BUTTON,LOWORD(lParam),HIWORD(lParam));
                break;
            case WM_MBUTTONDOWN:
                aotk->mousePress(MIDDLE_BUTTON,LOWORD(lParam),HIWORD(lParam));
                break;
            case WM_MOUSEWHEEL:
                aotk->scroll((short)HIWORD(wParam) / 120);
                break;
            case WM_MOUSELEAVE:
                prev_x = -1;
                prev_y = -1;
                break;
            case WM_MOUSEMOVE:
                if(prev_x == -1 || prev_y == -1){
                    prev_x = LOWORD(lParam);
                    prev_y = HIWORD(lParam);
                    break;
                }
                dx = LOWORD(lParam) - prev_x;
                prev_x = LOWORD(lParam);
                dy = HIWORD(lParam) - prev_y;
                prev_y = HIWORD(lParam);

                switch(wParam){
                    case MK_LBUTTON:
                    case MK_RBUTTON:
                    case MK_MBUTTON:
                        aotk->mousemotion(dx,dy);
                        break;
                    default:
                        aotk->passiveMousemotion(dx,dy);
                }
                break;
            default:
                return DefWindowProc (hwnd, message, wParam, lParam);
        }


        return 0;
    }


    VOID Window::createWindow(){
        aotk->wincl.hInstance = aotk->hInst;
        aotk->wincl.lpszClassName = "OpenGLwindow";
        aotk->wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
        aotk->wincl.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;                 /* Catch double-clicks */
        aotk->wincl.cbSize = sizeof (WNDCLASSEX);

        /* Use default icon and mouse-pointer */
        aotk->wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
        aotk->wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
        aotk->wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
        aotk->wincl.lpszMenuName = NULL;                 /* No menu */
        aotk->wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
        aotk->wincl.cbWndExtra = 0;                      /* structure or the window instance */
        /* Use Windows's default colour as the background of the window */
        aotk->wincl.hbrBackground = NULL;

        /* Register the window class, and if it fails quit the program */
        assert(RegisterClassEx (&aotk->wincl) && "Could not register winclass");


        aotk->hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           "OpenGLwindow",         /* Classname */
           title.c_str(),       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           size.w,                 /* The programs width */
           size.h,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           aotk->hInst,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

        assert(aotk->hwnd && "Could not create window");

        PIXELFORMATDESCRIPTOR pfd;
        memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
        pfd.nSize  = sizeof(PIXELFORMATDESCRIPTOR);
        pfd.nVersion   = 1;
        pfd.dwFlags    = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
        pfd.iPixelType = PFD_TYPE_RGBA;
        pfd.cColorBits = 32;
        pfd.cDepthBits = 32;
        pfd.iLayerType = PFD_MAIN_PLANE;


        assert(aotk->hDC=GetDC(aotk->hwnd));
        assert(aotk->pixelformat=ChoosePixelFormat(aotk->hDC,&pfd));
        assert(SetPixelFormat(aotk->hDC,aotk->pixelformat,&pfd));
        HGLRC tmp;
        assert(tmp=wglCreateContext(aotk->hDC));
        assert(wglMakeCurrent(aotk->hDC,tmp));

        getAllError( __FILE__, __LINE__);

        GLenum err = glewInit();
        assert(err == GLEW_OK && glewGetErrorString(err));

        if(wglewIsSupported("WGL_ARB_create_context") == 1){
            std::cout << "Context creation support: OK" << std::endl;
        }else
            std::cout << "Context creation support: NOT OK" << std::endl;

        if(wglewIsSupported("WGL_ARB_create_context") == 1){
            int attribs[] = {
                WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
                WGL_CONTEXT_MINOR_VERSION_ARB, 2,
//                WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
        		WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB ,
                0
            };
            glGetIntegerv(GL_MAJOR_VERSION, &attribs[1]);
            glGetIntegerv(GL_MINOR_VERSION, &attribs[3]);


            assert(aotk->hRC=wglCreateContextAttribsARB(aotk->hDC,0,attribs));
            wglMakeCurrent(NULL,NULL);
            wglDeleteContext(tmp);
        }else{
            assert(aotk->hRC = tmp);
        }
        assert(wglMakeCurrent(aotk->hDC,aotk->hRC));
        wglSwapIntervalEXT(0); //Disable vsync

        getAllError( __FILE__, __LINE__);

        ShowWindow (aotk->hwnd, SW_SHOWNORMAL);

        getAllError( __FILE__, __LINE__);
    }

    void Window::checkForMessages(){
        MSG msg;
        if(PeekMessage (&msg, aotk->hwnd, 0, 0, PM_REMOVE)){
            switch(msg.message){
                default:
                    TranslateMessage(&msg);				// Translate The Message
                    DispatchMessage(&msg);
            }
            checkForMessages();
        }else{
            LPPOINT p;
            GetCursorPos(p);
            WINDOWINFO  wi;
            GetWindowInfo(aotk->hwnd,&wi);
            if(aotk->mouseInside){
                if(!(p->x > wi.rcClient.left && p->x < wi.rcClient.right && p->y > wi.rcClient.top && p->y < wi.rcClient.bottom)){
                    TRACKMOUSEEVENT tmt;
                    tmt.cbSize = sizeof(TRACKMOUSEEVENT);
                    tmt.dwFlags = TME_LEAVE;
                    tmt.hwndTrack = aotk->hwnd;
                    TrackMouseEvent(&tmt);
                }
                aotk->mouseInside = 0;
            }else
                aotk->mouseInside = (p->x > wi.rcClient.left && p->x < wi.rcClient.right && p->y > wi.rcClient.top && p->y < wi.rcClient.bottom);
        }
    }
    void Window::swapBuffers(){
        SwapBuffers(aotk->hDC);
    }

};


#endif
