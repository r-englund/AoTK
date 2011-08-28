#include <AoTK/aotk.h>

#ifdef AoTK_WIN



namespace AoTK{
	

	HWND hwndConsole; //Window handler for the console
	HINSTANCE hInst;  //Application instance
	
	AoTK::Math::Vector4<int> *devices;
    int number_of_devices;
	
	bool ___isInit = false;
	void init(){
		if(___isInit)
			throw "AoTK::init called two times, can only be called once";
		___isInit = true;
		
		char t[500];
        GetConsoleTitleA( t, 500 );
        hwndConsole = FindWindowA( NULL, t );
        hInst = (HINSTANCE)GetWindowLong(hwndConsole, GWL_HINSTANCE);
	}
	
	BOOL CALLBACK _countDevices(HMONITOR hMonitor,HDC hdcMonitor,LPRECT lprcMonitor,LPARAM dwData){
        number_of_devices++;
        return 1;
    }

    BOOL CALLBACK _initDevices(HMONITOR hMonitor,HDC hdcMonitor,LPRECT lprcMonitor,LPARAM dwData){
        MONITORINFO info;
        info.cbSize = sizeof(MONITORINFO);
        GetMonitorInfo(hMonitor,&info);

        devices[number_of_devices].x = info.rcMonitor.left;
        devices[number_of_devices].y = info.rcMonitor.top;
        devices[number_of_devices].z = info.rcMonitor.right-info.rcMonitor.left;
        devices[number_of_devices].w = info.rcMonitor.bottom-info.rcMonitor.top;
        number_of_devices++;
        return 1;
    }
	void initDevices(){
        number_of_devices = 0;
        EnumDisplayMonitors(0,0,_countDevices,0);
        devices = new AoTK::Math::Vector4<int>[number_of_devices];
        number_of_devices = 0;
        EnumDisplayMonitors(0,0,_initDevices,0);
    }
	AoTK::Math::Vector4<int> *getDevices(){return devices;}
	unsigned int getNumberOfDevices(){return number_of_devices;}

    

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


};

#endif
