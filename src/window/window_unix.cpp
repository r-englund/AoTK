#include <AoTK/window_handler.h>

#ifdef AoTK_UNIX

#include <assert.h>

bool test = false;

 
static bool ctxErrorOccurred = false;
static int ctxErrorHandler( Display *dpy, XErrorEvent *ev )
{
    ctxErrorOccurred = true;
    return 0;
}



namespace AoTK{
	KEY translateKEY(KeySym w);

	
    Window* Window::createWindow(uint16_t width,uint16_t height,std::string title,bool force32){
        __window = new Window();
        __window->window_width = width;
        __window->window_height = height;
        __window->client_width = width;
        __window->client_height = height;

        if(force32)
            std::cerr << "force32 not yet supported " << __FILE__ << " " << __LINE__<<std::endl;

        __window->disp = XOpenDisplay(0);
        if(__window->disp == NULL){
			std::cerr << "Could not open a display" << std::endl;
			exit(1);
			Window *v;
			return v;
        }else if(test)
        	std::cout << "Dispaly OK" << std::endl;

        __window->scr = DefaultScreen(__window->disp);

		

		
		if(test)
			std::cout << "Default screen  = " << __window->scr << std::endl;

		XF86VidModeModeInfo ** vidmodes;
		int c;
		if(!XF86VidModeGetAllModeLines(__window->disp,__window->scr,&c,&vidmodes)){
			std::cerr << "Could not qeury videomodes" << std::endl;
			exit(2);
			Window *w;
			return w;
		}else if(test)
        	std::cout << "Query OK: " << c<< std::endl;


        for(int i = 0;i<c && test;i++){
			std::cout << "Mode " << i << std::endl;
			std::cout << "dotclock " << vidmodes[i]->dotclock << std::endl;
			std::cout << "hdisplay " << vidmodes[i]->hdisplay << std::endl;
			std::cout << "hsyncstart " << vidmodes[i]->hsyncstart << std::endl;
			std::cout << "hsyncend " << vidmodes[i]->hsyncend << std::endl;
			std::cout << "htotal " << vidmodes[i]->htotal << std::endl;
			std::cout << "hskew " << vidmodes[i]->hskew << std::endl;
			std::cout << "vdisplay " << vidmodes[i]->vdisplay << std::endl;
			std::cout << "vsyncstart " << vidmodes[i]->vsyncstart << std::endl;
			std::cout << "vsyncend " << vidmodes[i]->vsyncend << std::endl;
			std::cout << "vtotal " << vidmodes[i]->vtotal << std::endl;
			std::cout << "flags " << vidmodes[i]->flags << std::endl;
			std::cout << "privsize " << vidmodes[i]->privsize << std::endl;
			std::cout << std::endl;
        }

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
       	glXSwapBuffers ( __window->disp, __window->win );
    }


    KEY translateKEY(KeySym w){
        switch(w){
            case XK_F1 : return F1;
            case XK_F2 : return F2;
            case XK_F3 : return F3;
            case XK_F4 : return F4;
            case XK_F5 : return F5;
            case XK_F6 : return F6;
            case XK_F7 : return F7;
            case XK_F8 : return F8;
            case XK_F9 : return F9;
            case XK_F10 : return F10;
            case XK_F11 : return F11;
            case XK_F12 : return F12;
            case XK_F13 : return F13;
            case XK_F14 : return F14;
            case XK_F15 : return F15;
            case XK_F16 : return F16;
            case XK_F17 : return F17;
            case XK_F18 : return F18;
            case XK_F19 : return F19;
            case XK_F20 : return F20;
            case XK_F21 : return F21;
            case XK_F22 : return F22;
            case XK_F23 : return F23;
            case XK_F24 : return F24;
			case XK_Shift_L: return SHIFT;
			case XK_Shift_R: return SHIFT;
			case XK_Control_L : return CTRL;
			case XK_Control_R : return CTRL;
			case XK_Caps_Lock : return CAPSLOCK;
			case XK_Num_Lock : return NUMLOCK;
			case XK_Scroll_Lock : return SCROLLLOCK;
			case XK_Alt_L : return ALT;
			case XK_Alt_R : return ALT;
			case XK_Super_L : return SUPER;
			case XK_Super_R : return SUPER;
			case XK_Return : return ENTER;
			case XK_Tab : return TAB;
			case XK_BackSpace : return BACKSPACE;
			case XK_Escape : return ESC;
			case XK_Delete : return DEL;
			case XK_q : return Q;
			case XK_w : return W;
			case XK_e : return E;
			case XK_r : return R;
			case XK_t : return T;
			case XK_y : return Y;
			case XK_u : return U;
			case XK_i : return I;
			case XK_o : return O;
			case XK_p : return P;
			case XK_a : return A;
			case XK_s : return S;
			case XK_d : return D;
			case XK_f : return F;
			case XK_g : return G;
			case XK_h : return H;
			case XK_j : return J;
			case XK_k : return K;
			case XK_l : return L;
			case XK_z : return Z;
			case XK_x : return X;
			case XK_c : return C;
			case XK_v : return V;
			case XK_b : return B;
			case XK_n : return N;
			case XK_m : return M;
			case XK_0 : return KEY0;
			case XK_1 : return KEY1;
			case XK_2 : return KEY2;
			case XK_3 : return KEY3;
			case XK_4 : return KEY4;
			case XK_5 : return KEY5;
			case XK_6 : return KEY6;
			case XK_7 : return KEY7;
			case XK_8 : return KEY8;
			case XK_9 : return KEY9;
		//	case 0xFE03 : return ALTGR;
			case XK_space : return SPACE; // OR XP_KP_        20
			case XK_Home : return HOME;
			case XK_End : return END;
			case XK_Insert : return INS;
			case XK_Page_Up : return PGUP;
			case XK_Page_Down : return PGDOWN;
			case XK_Left: return ARROW_LEFT;
			case XK_Right: return ARROW_RIGHT;
			case XK_Up: return ARROW_UP;
			case XK_Down: return ARROW_DOWN;
		//	case 0x : return PRINT;
		//	case 0x : return PRINTSCREEN;
		//	case 0x : return MULTI;
			case XK_plus : return ADD;
			case XK_minus : return SUB;
			case XK_comma : return DECIMAL; 
		//	case 0x : return DIVIDE; 
		    case  XK_Pause : return PAUSE;
            default:
            	char str[30];
            	sprintf(str,"%X", w);
                std::cout << "WARNING: unhandled key pressed: " << str << std::endl;
                return UNASIGNED_KEY;
        }
    }


};


#endif
