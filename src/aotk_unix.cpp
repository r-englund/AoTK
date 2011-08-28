#include <AoTK/aotk.h>

#ifdef AoTK_UNIX

namespace AoTK{
	Display *disp;
	int scr;
	
	AoTK::Math::Vector4<int> *devices;
	int number_of_devices;
	
	
	bool ___isInit = false;
	void init(){
		if(___isInit)
			return;//throw "AoTK::init called two times, can only be called once";
		___isInit = true;
		
		 disp = XOpenDisplay(0);
        if(disp == NULL){
			std::cerr << "Could not open a display" << std::endl;
			exit(1);
			return;
        }

        scr = DefaultScreen(disp);
		
	}
	
	AoTK::Math::Vector4<int> *getDevices(){return devices;}
	unsigned int getNumberOfDevices(){return number_of_devices;}
	


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
