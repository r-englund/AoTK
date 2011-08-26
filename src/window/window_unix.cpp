#include <AoTK/window_handler.h>

#ifdef AoTK_UNIX

#include <assert.h>

//static bool ctxErrorOccurred = false;
//static int ctxErrorHandler( Display *dpy, XErrorEvent *ev )
//{
//    ctxErrorOccurred = true;
//    return 0;
//}



namespace AoTK{
	
	
    Window* Window::createWindow(uint16_t width,uint16_t height,std::string title,bool force32){
        __window = new Window();
        __window->window_width = width;
        __window->window_height = height;
        __window->client_width = width;
        __window->client_height = height;

        if(force32)
            std::cerr << "force32 not yet supported " << __FILE__ << " " << __LINE__<<std::endl;

		XF86VidModeModeInfo ** vidmodes;
		int c;
		if(!XF86VidModeGetAllModeLines(__window->disp,__window->scr,&c,&vidmodes)){
			std::cerr << "Could not qeury videomodes" << std::endl;
			exit(2);
			Window *w;
			return w;
		}else if(test)
        	std::cout << "Query OK: " << c<< std::endl;

		int doubleBufferedAttribList [] = {
			GLX_RGBA, GLX_DOUBLEBUFFER,
			GLX_RED_SIZE, 8,
			GLX_GREEN_SIZE, 8,
			GLX_BLUE_SIZE, 8,
			GLX_DEPTH_SIZE, 16,
			None
		};
		 
		__window->vi = glXChooseVisual(__window->disp, __window->scr, doubleBufferedAttribList);
        if(__window->vi==NULL){
			std::cerr << "Could not create a dubble buffered window" << std::endl;
			exit(3);
			Window *w;
			return w;
        }else if(test)
        	std::cout << "Doubble Buffer OK: "<< std::endl;


		GLXContext gl2context = glXCreateContext(__window->disp,__window->vi,0,GL_TRUE);
		if(gl2context==NULL){
			std::cerr << "Could not create a OpenGL 2 context" << std::endl;
			exit(4);
			Window *w;
			return w;
        }else if(test)
        	std::cout << "OpenGL 2 OK: "<< std::endl;

		//GLenum err = glewInit();
		//if (GLEW_OK != err){
		// 	std::cerr << "Could not init glew: " << glewGetErrorString(err) << std::endl;
		// 	exit(5);
		// 	Window *w;
		// 	return w;
		//}

		//Get a pointer to the GL 3.0 context creation
		PFNGLXCREATECONTEXTATTRIBSARBPROC glXCreateContextAttribs = (PFNGLXCREATECONTEXTATTRIBSARBPROC)glXGetProcAddress((GLubyte*)"glXCreateContextAttribsARB");
		//PFNGLXGETFBCONFIGSPROC glXGetFBConfigs = (PFNGLXGETFBCONFIGSPROC)glXGetProcAddress((GLubyte*)"glXGetFBConfigsARB");


		
		 
		if (glXCreateContextAttribs == NULL )
		{
			std::cerr << "OpenGL 3.0 is not supported, falling back to 2.1" << std::endl;
			__window->glContext = gl2context;
			__window->GL3 = false;
		}
		else
		{
			//Create a GL 3.0 context
		 
			int attribs[] = {
				GLX_CONTEXT_MAJOR_VERSION_ARB, 3,//we want a 3.0 context
				GLX_CONTEXT_MINOR_VERSION_ARB, 0,
				0 //zero indicates the end of the array
			};
		 	std::cerr << "CREATE GL 3.0 context not yet implemented " << __FILE__ << " " << __LINE__ << std::endl;
			//auto m_glContext = glXCreateContextAttribs(disp, framebufferConfig, 0, true, &attribs[0]);
			glXDestroyContext(__window->disp, gl2context); //We can destroy the GL 2.0 context once the 3.0 one has bene created
			__window->GL3 = true;
		}

		


		__window->cmap = XCreateColormap(__window->disp, RootWindow(__window->disp, __window->vi->screen),__window->vi->visual, AllocNone);
		__window->XAttr.colormap = __window->cmap;
		__window->XAttr.border_pixel = 0;
		__window->XAttr.event_mask = ExposureMask | KeyPressMask | KeyReleaseMask | ButtonPressMask |ButtonReleaseMask | PointerMotionMask | StructureNotifyMask | PropertyChangeMask | ResizeRedirectMask | EnterWindowMask | LeaveWindowMask;
		__window->XAttr.override_redirect = False;
		 
		unsigned long windowAttributes = CWBorderPixel | CWColormap | CWEventMask;
		 	 
		__window->win = XCreateWindow(__window->disp, RootWindow(__window->disp, __window->vi->screen),
				                      0, 0, width, height, 0, __window->vi->depth, InputOutput, __window->vi->visual,
				                      CWBorderPixel | CWColormap | CWEventMask, &__window->XAttr);
		
		std::cout <<"Win type "<< typeid(__window->win).name() << std::endl;

		__window->wmDelete = XInternAtom(__window->disp, "WM_DELETE_WINDOW", True);
		XSetWMProtocols(__window->disp, __window->win, &__window->wmDelete, 1);


		XSetStandardProperties(__window->disp, __window->win, title.c_str(), None, NULL, NULL, 0, NULL);
		XMapRaised(__window->disp, __window->win);


		int (*oldHandler)(Display*, XErrorEvent*) =      XSetErrorHandler(&ctxErrorHandler);
		XSync( __window->disp, False );

		XSetErrorHandler( oldHandler );

		if ( ! glXIsDirect ( __window->disp, __window->glContext ) ){
			printf( "Indirect GLX rendering context obtained\n" );
		}
		else		{
			printf( "Direct GLX rendering context obtained\n" );
		}
	
		XFree(vidmodes);

		//fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
		glXMakeCurrent( __window->disp, __window->win, __window->glContext );

		GLenum err = glewInit();
		if (GLEW_OK != err){
		 	std::cerr << "Could not init glew: " << glewGetErrorString(err) << std::endl;
		 	exit(5);
		 	Window *w;
		 	return w;
		}

			
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

		__window->initDevices();
		
		__window->setSizes();
        return __window;
    }

	void Window::initDevices(){
        number_of_devices = XScreenCount(__window->disp);
        devices = new AoTK::Math::Vector4<int>[number_of_devices];
        for(int i = 0;i<number_of_devices;i++){
        	Screen *s = ScreenOfDisplay(disp,i);
        	int w = WidthOfScreen(s);
        	int h = HeightOfScreen(s);
			devices[i].x = 0;
			devices[i].y = 0;
			devices[i].z = w;
			devices[i].w = h;
        }
    }
    

    void Window::fullscreenOn(unsigned int device){
        throw "Not yet implemented";
    }


    void Window::fullscreenOff(){
        throw "Not yet implemented";
    }
	
    void Window::setSizes(){
		
    }

    void Window::checkForMessages(){
		while (XPending(disp)!=0) {
		  XEvent event;
		  XNextEvent(disp, &event);

		  static int oldx = -1;
		  static int oldy = -1;
	   	  static int mouseState = 0;
	   	  static bool mouseInside = true;		

		  
		  switch(event.type){
				case ClientMessage:
                    if(event.xclient.data.l[0] == wmDelete)
                    	stop();
                    else{
						std::cout << "HRM" << std::endl;
                    }
                break;
                case ConfigureNotify:
                	client_width = window_width = event.xconfigure.width;
                	client_height = window_height =  event.xconfigure.height;
			    	resizeEvent();
			    	break;
			    case ResizeRequest:
                	client_width = window_width = event.xresizerequest.width;
                	client_height = window_height =  event.xresizerequest.height; 
                	resizeEvent();
			    	break;
   				case KeyPress: //KeyPress
					{
					KeySym sym = XKeycodeToKeysym(disp,event.xkey.keycode,0);
   					KEY key = translateKEY(sym);
   					break;
   					}
   	  				case KeyRelease: //KeyReleas
   					std::cout << "Key Release" << std::endl;
   					break;
				case ButtonPress: //Mouse
				    oldx = event.xbutton.x;
				    oldy = event.xbutton.y;
					switch(event.xbutton.button){
						case Button1:
							mousePressEvent(LEFT_BUTTON,event.xbutton.x,event.xbutton.y);
							mouseState++;
							break;
						case Button2:
							mousePressEvent(MIDDLE_BUTTON,event.xbutton.x,event.xbutton.y);
							mouseState++;
							break;
						case Button3:
							mousePressEvent(RIGHT_BUTTON,event.xbutton.x,event.xbutton.y);
							mouseState++;
							break;
						case Button4:
							scrollEvent(1);
							break;
						case Button5:
							scrollEvent(-1);
							break;
					}
   					break;
				case ButtonRelease://Mouse
					switch(event.xbutton.button){
						case Button1:
							mouseReleaseEvent(LEFT_BUTTON,event.xbutton.x,event.xbutton.y);
							mouseState--;
							break;
						case Button2:
							mouseReleaseEvent(MIDDLE_BUTTON,event.xbutton.x,event.xbutton.y);
							mouseState--;
							break;
						case Button3:
							mouseReleaseEvent(RIGHT_BUTTON,event.xbutton.x,event.xbutton.y);
							mouseState--;
							break;
					}
   					break;
				case MotionNotify:	//Mouse
					if(!mouseInside)
						break;
	   				if(mouseState){
						int x = event.xbutton.x;
						int y = event.xbutton.y;
                        int dx = x - oldx;
                        int dy = y - oldy;
                        oldx = x;
                        oldy = y;
						mousemotionEvent(dx,dy);
	   				}else{
						int x = event.xbutton.x;
						int y = event.xbutton.y;
                        int dx = x - oldx;
                        int dy = y - oldy;
                        oldx = x;
                        oldy = y;
						passiveMousemotionEvent(dx,dy);
	   				}
   					break;
   				case LeaveNotify:
   					mouseInside = false;
   					break;
   				case EnterNotify:
   					mouseInside = true;
   					break;
				default:
					std::cout << "Unhandled event: " << event.type << std::endl;
			}
		  
	   }
    }
    
    void Window::swapBuffers(){
       	glXSwapBuffers ( disp, __window->win );
    }



};


#endif
