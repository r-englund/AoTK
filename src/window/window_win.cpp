
#include <AoTK/window_handler.h>
#include <AoTK/aotk.h>

#ifdef AoTK_WIN


#include <assert.h>

namespace AoTK{

Window *___window;
LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
    int prev_x = -1,prev_y = -1,dx,dy;
    float ml = 0;
    float l;


    LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
        switch (message)                  /* handle the messages */
        {
            case WM_DESTROY:
                ___window->stop();
                break;
            case WM_KEYDOWN:
                ___window->keyDownEvent(translateKEY(wParam));
                break;
            case WM_KEYUP:
                ___window->keyUpEvent(translateKEY(wParam));
                break;
            case WM_CHAR:
                ___window->keyImpulseEvent((unsigned char)wParam);
                break;
            case WM_SIZE:
                ___window->resizeEvent();
                break;
            case WM_LBUTTONUP:
                ___window->mouseReleaseEvent(LEFT_BUTTON,LOWORD(lParam),HIWORD(lParam));
                break;
            case WM_LBUTTONDOWN:
                ___window->mousePressEvent(LEFT_BUTTON,LOWORD(lParam),HIWORD(lParam));
                break;
            case WM_RBUTTONUP:
                ___window->mouseReleaseEvent(RIGHT_BUTTON,LOWORD(lParam),HIWORD(lParam));
                break;
            case WM_RBUTTONDOWN:
                ___window->mousePressEvent(RIGHT_BUTTON,LOWORD(lParam),HIWORD(lParam));
                break;
            case WM_MBUTTONUP:
                ___window->mouseReleaseEvent(MIDDLE_BUTTON,LOWORD(lParam),HIWORD(lParam));
                break;
            case WM_MBUTTONDOWN:
                ___window->mousePressEvent(MIDDLE_BUTTON,LOWORD(lParam),HIWORD(lParam));
                break;
            case WM_MOUSEWHEEL:
                ___window->scrollEvent((short)HIWORD(wParam) / 120);
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
                        ___window->mousemotionEvent(dx,dy);
                        break;
                    default:
                        ___window->passiveMousemotionEvent(dx,dy);
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
			this->styles, /* default window */
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
        Window * w = new Window();
        w->window_width = width;
        w->window_height = height;
        
		
		w->styles = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME;

        assert(w->initWindowClass() && "Could not register winclass");
        assert(w->createWindow(title) && "Could not create window");
		assert(w->hDC=GetDC(w->hwnd));
        
		assert(w->setPixelFormat());

        
        HGLRC tmp;
        assert(tmp=wglCreateContext(w->hDC));
        assert(wglMakeCurrent(w->hDC,tmp));

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

                assert(w->hRC=wglCreateContextAttribsARB(w->hDC,0,attribs));

                wglMakeCurrent(NULL,NULL);
                wglDeleteContext(tmp);
            }else{
                int attribs[] = {
                    WGL_CONTEXT_MAJOR_VERSION_ARB, a,
                    WGL_CONTEXT_MINOR_VERSION_ARB, b,
                    WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB ,
                    0
                };
				
				std::cout << w->hDC << " " << attribs[1] << " " << attribs[3] << std::endl;

                assert(w->hRC=wglCreateContextAttribsARB(w->hDC,0,attribs));

                wglMakeCurrent(NULL,NULL);
                wglDeleteContext(tmp);
            }
        }else{
            assert(w->hRC = tmp);
        }
        assert(wglMakeCurrent(w->hDC,w->hRC));
        wglSwapIntervalEXT(0); //Disable vsync

        ShowWindow (w->hwnd, SW_SHOWNORMAL);

		

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

        w->setSizes();
        initDevices();
        return w;
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
			while(___window != 0)
			___window = this;
           // switch(msg.message){
           //     default:
                    TranslateMessage(&msg);				// Translate The Message
                    DispatchMessage(&msg);
            //}
			___window = 0;
            checkForMessages();
        }
    }

    void Window::swapBuffers(){
        SwapBuffers(hDC);
    }

    void Window::fullscreenOn(unsigned int device){
        RECT lpRect;
        GetWindowRect(hwnd,&lpRect);
        oldPos.x = (uint16_t)lpRect.left;
        oldPos.y = (uint16_t)lpRect.top;
        getWindowSize(oldSize.x,oldSize.y);
		
		ShowWindow (this->hwnd, SW_SHOWMAXIMIZED);
	
		this->setSizes();
        fullscreen = true;
    }


    void Window::fullscreenOff(){
		//SetWindowLong(hwnd,GWL_STYLE,styles);
		//SetWindowPos(this->hwnd,HWND_TOP,oldPos.x,oldPos.y,oldSize.x,oldSize.y,SWP_SHOWWINDOW);
		//ShowWindow (__window->hwnd, SW_SHOWNORMAL);
        fullscreen = false;
    }

};


#endif
