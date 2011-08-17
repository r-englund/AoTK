
#include <AoTK/window_handler.h>
#include <AoTK/aotk.h>

#ifdef AoTK_WIN


#include <assert.h>

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
                return UNASIGNED_KEY;
        }
    }

    int prev_x = -1,prev_y = -1,dx,dy;
    float ml = 0;
    float l;


    LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
        switch (message)                  /* handle the messages */
        {
            case WM_DESTROY:
                __window->stop();
                break;
            case WM_KEYDOWN:
                __window->keyDownEvent(translateKEY(wParam));
                break;
            case WM_KEYUP:
                __window->keyUpEvent(translateKEY(wParam));
                break;
            case WM_CHAR:
                __window->keyImpulseEvent((unsigned char)wParam);
                break;
            case WM_SIZE:
                __window->resizeEvent();
//                __window->resizeEvent(LOWORD(lParam),HIWORD(lParam));
                break;
            case WM_LBUTTONUP:
                __window->mouseReleaseEvent(LEFT_BUTTON,LOWORD(lParam),HIWORD(lParam));
                break;
            case WM_LBUTTONDOWN:
                __window->mousePressEvent(LEFT_BUTTON,LOWORD(lParam),HIWORD(lParam));
                break;
            case WM_RBUTTONUP:
                __window->mouseReleaseEvent(RIGHT_BUTTON,LOWORD(lParam),HIWORD(lParam));
                break;
            case WM_RBUTTONDOWN:
                __window->mousePressEvent(RIGHT_BUTTON,LOWORD(lParam),HIWORD(lParam));
                break;
            case WM_MBUTTONUP:
                __window->mouseReleaseEvent(MIDDLE_BUTTON,LOWORD(lParam),HIWORD(lParam));
                break;
            case WM_MBUTTONDOWN:
                __window->mousePressEvent(MIDDLE_BUTTON,LOWORD(lParam),HIWORD(lParam));
                break;
            case WM_MOUSEWHEEL:
                __window->scrollEvent((short)HIWORD(wParam) / 120);
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
                        __window->mousemotionEvent(dx,dy);
                        break;
                    default:
                        __window->passiveMousemotionEvent(dx,dy);
                }
                break;
            default:
                return DefWindowProc (hwnd, message, wParam, lParam);
        }

        return 0;
    }
	
	
	bool Window::initWindowClass(){
		
        wincl.hInstance = hInst;
        wincl.lpszClassName = "OpenGLwindow";
        wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
        wincl.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;                 /* Catch double-clicks */
        wincl.cbSize = sizeof (WNDCLASSEX);

        /* Use default icon and mouse-pointer */
        wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
        wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
        wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
        wincl.lpszMenuName = NULL;                 /* No menu */
        wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
        wincl.cbWndExtra = 0;                      /* structure or the window instance */
        /* Use Windows's default colour as the background of the window */
        wincl.hbrBackground = NULL;

        /* Register the window class, and if it fails quit the program */
		return RegisterClassEx(&wincl);
	}


	bool Window::createWindow(std::string title){
		hwnd = CreateWindowEx (
			0,                   /* Extended possibilites for variation */
			"OpenGLwindow",         /* Classname */
			title.c_str(),       /* Title Text */
			__window->styles, /* default window */
			//           WS_POPUP , /* default window */
			50,       /* Windows decides the position */
			50,       /* where the window ends up on the screen */
			window_width,                 /* The programs width */
			window_height,                 /* and height in pixels */
			HWND_DESKTOP,        /* The window is a child-window to desktop */
			NULL,                /* No menu */
			hInst,       /* Program Instance handler */
			NULL                 /* No Window Creation data */
		);

		return hwnd != NULL;
	}

	bool Window::setPixelFormat(){
		PIXELFORMATDESCRIPTOR pfd;
        memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
        pfd.nSize  = sizeof(PIXELFORMATDESCRIPTOR);
        pfd.nVersion   = 1;
        pfd.dwFlags    = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
        pfd.iPixelType = PFD_TYPE_RGBA;
        pfd.cColorBits = 32;
        pfd.cDepthBits = 32;
        pfd.iLayerType = PFD_MAIN_PLANE;
		
		if(!(pixelformat=ChoosePixelFormat(hDC,&pfd))){
			std::cerr << "Could not choose pixelformat" << std::endl;
			return 0;
		}
		
        return SetPixelFormat(hDC,pixelformat,&pfd);
	}

    Window* Window::createWindow(uint16_t width,uint16_t height,std::string title,bool force32){
        __window = new Window();
        __window->window_width = width;
        __window->window_height = height;
        char t[500];
        GetConsoleTitleA( t, 500 );
        __window->hwndConsole = FindWindowA( NULL, t );;
        __window->hInst = (HINSTANCE)GetWindowLong(__window->hwndConsole, GWL_HINSTANCE);
		
		__window->styles = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME;

        assert(__window->initWindowClass() && "Could not register winclass");
        assert(__window->createWindow(title) && "Could not create window");
		assert(__window->hDC=GetDC(__window->hwnd));
        
		assert(__window->setPixelFormat());

        
        HGLRC tmp;
        assert(tmp=wglCreateContext(__window->hDC));
        assert(wglMakeCurrent(__window->hDC,tmp));

		GLint a = 0,b = 0;
		double v;

		GLubyte *c = new GLubyte[10];
		memcpy(c,glGetString(GL_VERSION),10);
		int i = 0,j = 0;
		while(c[++i]!='\0'){if(c[i] == '.' && 1==j++){c[i] = '\0';break;}}
		v = atof((const char*) c);a = v;v -=a;b = v*10;
		delete c;

        GLenum err = glewInit();
        assert(err == GLEW_OK && glewGetErrorString(err));

        if(a>2&&wglewIsSupported("WGL_ARB_create_context") == 1){
            std::cout << "Context creation support: OK" << std::endl;
        }else
            std::cout << "Context creation support: NOT OK" << std::endl;
		 if(a>2&&wglewIsSupported("WGL_ARB_create_context") == 1){
            if(force32){
                int attribs[] = {
                    WGL_CONTEXT_MAJOR_VERSION_ARB, a,
                    WGL_CONTEXT_MINOR_VERSION_ARB, b,
                    WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
                    0
                };

                assert(__window->hRC=wglCreateContextAttribsARB(__window->hDC,0,attribs));

                wglMakeCurrent(NULL,NULL);
                wglDeleteContext(tmp);
            }else{
                int attribs[] = {
                    WGL_CONTEXT_MAJOR_VERSION_ARB, a,
                    WGL_CONTEXT_MINOR_VERSION_ARB, b,
                    WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB ,
                    0
                };
				
				std::cout << __window->hDC << " " << attribs[1] << " " << attribs[3] << std::endl;

                assert(__window->hRC=wglCreateContextAttribsARB(__window->hDC,0,attribs));

                wglMakeCurrent(NULL,NULL);
                wglDeleteContext(tmp);
            }
        }else{
            assert(__window->hRC = tmp);
        }
        assert(wglMakeCurrent(__window->hDC,__window->hRC));
        wglSwapIntervalEXT(0); //Disable vsync

        ShowWindow (__window->hwnd, SW_SHOWNORMAL);

		

        std::cout << "OpenGL window created, using:" << std::endl;
        std::cout << "Using GLEW version: " << glewGetString(GLEW_VERSION) << std::endl;
        std::cout << "Using OpenGL version " << glGetString(GL_VERSION) << std::endl;
        std::cout << "Using OpenGL vender " << glGetString(GL_VENDOR) << std::endl;
        std::cout << "Using OpenGL renderer " << glGetString(GL_RENDERER) << std::endl;
        std::cout << "Using GLSL version " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
        if(GLEW_ARB_vertex_buffer_object)
            std::cout << "VBO suport: OK" << std::endl;
        else
            std::cout << "VBO suport: NOT OK" << std::endl;

        __window->setSizes();
        __window->initDevices();
        return __window;
    }



    void Window::setSizes(){
        RECT lpRect;
        GetClientRect(hwnd,&lpRect);
        client_width = (uint16_t)lpRect.right-(uint16_t)lpRect.left;
        client_height = (uint16_t)lpRect.bottom - (uint16_t)lpRect.top;

        GetWindowRect(hwnd,&lpRect);
        window_width = (uint16_t)lpRect.right-(uint16_t)lpRect.left;
        window_height = (uint16_t)lpRect.bottom - (uint16_t)lpRect.top;
    }

    void Window::checkForMessages(){
        MSG msg;
        if(PeekMessage (&msg, hwnd, 0, 0, PM_REMOVE)){
           // switch(msg.message){
           //     default:
                    TranslateMessage(&msg);				// Translate The Message
                    DispatchMessage(&msg);
            //}
            checkForMessages();
        }else{
//            LPPOINT p = NULL;
//            GetCursorPos(p);
//            WINDOWINFO  wi;
//            GetWindowInfo(aotk->hwnd,&wi);
//            if(aotk->mouseInside){ //TODO felet �r h�r
//                if(!(p->x > wi.rcClient.left && p->x < wi.rcClient.right && p->y > wi.rcClient.top && p->y < wi.rcClient.bottom)){
//                    TRACKMOUSEEVENT tmt;
//                    tmt.cbSize = sizeof(TRACKMOUSEEVENT);
//                    tmt.dwFlags = TME_LEAVE;
//                    tmt.hwndTrack = aotk->hwnd;
//                    TrackMouseEvent(&tmt);
//                }
//                aotk->mouseInside = 0;
//            }else
//                aotk->mouseInside = (p->x > wi.rcClient.left && p->x < wi.rcClient.right && p->y > wi.rcClient.top && p->y < wi.rcClient.bottom);
        }



    }
    void Window::swapBuffers(){
        SwapBuffers(hDC);
    }

    BOOL CALLBACK _countDevices(HMONITOR hMonitor,HDC hdcMonitor,LPRECT lprcMonitor,LPARAM dwData){
        __window->number_of_devices++;
        return 1;
    }

    BOOL CALLBACK _initDevices(HMONITOR hMonitor,HDC hdcMonitor,LPRECT lprcMonitor,LPARAM dwData){
        MONITORINFO info;
        info.cbSize = sizeof(MONITORINFO);
        GetMonitorInfo(hMonitor,&info);

        __window->devices[__window->number_of_devices].x = info.rcMonitor.left;
        __window->devices[__window->number_of_devices].y = info.rcMonitor.top;
        __window->devices[__window->number_of_devices].z = info.rcMonitor.right-info.rcMonitor.left;
        __window->devices[__window->number_of_devices].w = info.rcMonitor.bottom-info.rcMonitor.top;
        __window->number_of_devices++;
        return 1;
    }

    void Window::fullscreenOn(unsigned int device){
        RECT lpRect;
        GetWindowRect(hwnd,&lpRect);
        oldPos.x = (uint16_t)lpRect.left;
        oldPos.y = (uint16_t)lpRect.top;
        getWindowSize(oldSize.x,oldSize.y);
		
		
	//	SetWindowLong(hwnd,GWL_STYLE,WS_POPUP);

       /* 
	   SetWindowPos(this->hwnd,
                     HWND_TOP,
                     devices[device].x,
                     devices[device].y,
                     devices[device].z,
                     devices[device].w,
                     SWP_SHOWWINDOW); //*/
		//ShowWindow (__window->hwnd, SW_SHOWMAXIMIZED);
		//SHFullScreen(hwnd,SHFS_HIDETASKBAR | SHFS_HIDESTARTICON | SHFS_HIDESIPBUTTON);
		SetWindowPos(hwnd, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), SWP_FRAMECHANGED);
 
		this->setSizes();
        fullscreen = true;
    }


    void Window::fullscreenOff(){
       // SetWindowPos(this->hwnd,HWND_TOP,oldPos.x,oldPos.y,oldSize.x,oldSize.y,SWP_SHOWWINDOW);
		//ShowWindow (__window->hwnd, SW_SHOWNORMAL);
        fullscreen = false;
    }

    void Window::initDevices(){
        number_of_devices = 0;
        EnumDisplayMonitors(0,0,_countDevices,0);
        devices = new AoTK::Math::Vector4<int>[number_of_devices];
        number_of_devices = 0;
        EnumDisplayMonitors(0,0,_initDevices,0);
    }

};


#endif