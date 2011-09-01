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
	
	std::string message2String(UINT msg){
		switch(msg){
			#ifdef WM_APP
				case WM_APP: return "WM_APP";
			#endif
			#ifdef WM_ACTIVATE
				case WM_ACTIVATE: return "WM_ACTIVATE";
			#endif
			#ifdef WM_ACTIVATEAPP
				case WM_ACTIVATEAPP: return "WM_ACTIVATEAPP";
			#endif
			#ifdef WM_AFXFIRST
				case WM_AFXFIRST: return "WM_AFXFIRST";
			#endif
			#ifdef WM_AFXLAST
				case WM_AFXLAST: return "WM_AFXLAST";
			#endif
			#ifdef WM_ASKCBFORMATNAME
				case WM_ASKCBFORMATNAME: return "WM_ASKCBFORMATNAME";
			#endif
			#ifdef WM_CANCELJOURNAL
				case WM_CANCELJOURNAL: return "WM_CANCELJOURNAL";
			#endif
			#ifdef WM_CANCELMODE
				case WM_CANCELMODE: return "WM_CANCELMODE";
			#endif
			#ifdef WM_CAPTURECHANGED
				case WM_CAPTURECHANGED: return "WM_CAPTURECHANGED";
			#endif
			#ifdef WM_CHANGECBCHAIN
				case WM_CHANGECBCHAIN: return "WM_CHANGECBCHAIN";
			#endif
			#ifdef WM_CHAR
				case WM_CHAR: return "WM_CHAR";
			#endif
			#ifdef WM_CHARTOITEM
				case WM_CHARTOITEM: return "WM_CHARTOITEM";
			#endif
			#ifdef WM_CHILDACTIVATE
				case WM_CHILDACTIVATE: return "WM_CHILDACTIVATE";
			#endif
			#ifdef WM_CLEAR
				case WM_CLEAR: return "WM_CLEAR";
			#endif
			#ifdef WM_CLOSE
				case WM_CLOSE: return "WM_CLOSE";
			#endif
			#ifdef WM_COMMAND
				case WM_COMMAND: return "WM_COMMAND";
			#endif
			#ifdef WM_COMMNOTIFY
				case WM_COMMNOTIFY: return "WM_COMMNOTIFY";
			#endif
			#ifdef WM_COMPACTING
				case WM_COMPACTING: return "WM_COMPACTING";
			#endif
			#ifdef WM_COMPAREITEM
				case WM_COMPAREITEM: return "WM_COMPAREITEM";
			#endif
			#ifdef WM_CONTEXTMENU
				case WM_CONTEXTMENU: return "WM_CONTEXTMENU";
			#endif
			#ifdef WM_COPY
				case WM_COPY: return "WM_COPY";
			#endif
			#ifdef WM_COPYDATA
				case WM_COPYDATA: return "WM_COPYDATA";
			#endif
			#ifdef WM_CREATE
				case WM_CREATE: return "WM_CREATE";
			#endif
			#ifdef WM_CTLCOLORBTN
				case WM_CTLCOLORBTN: return "WM_CTLCOLORBTN";
			#endif
			#ifdef WM_CTLCOLORDLG
				case WM_CTLCOLORDLG: return "WM_CTLCOLORDLG";
			#endif
			#ifdef WM_CTLCOLOREDIT
				case WM_CTLCOLOREDIT: return "WM_CTLCOLOREDIT";
			#endif
			#ifdef WM_CTLCOLORLISTBOX
				case WM_CTLCOLORLISTBOX: return "WM_CTLCOLORLISTBOX";
			#endif
			#ifdef WM_CTLCOLORMSGBOX
				case WM_CTLCOLORMSGBOX: return "WM_CTLCOLORMSGBOX";
			#endif
			#ifdef WM_CTLCOLORSCROLLBAR
				case WM_CTLCOLORSCROLLBAR: return "WM_CTLCOLORSCROLLBAR";
			#endif
			#ifdef WM_CTLCOLORSTATIC
				case WM_CTLCOLORSTATIC: return "WM_CTLCOLORSTATIC";
			#endif
			#ifdef WM_CUT
				case WM_CUT: return "WM_CUT";
			#endif
			#ifdef WM_DEADCHAR
				case WM_DEADCHAR: return "WM_DEADCHAR";
			#endif
			#ifdef WM_DELETEITEM
				case WM_DELETEITEM: return "WM_DELETEITEM";
			#endif
			#ifdef WM_DESTROY
				case WM_DESTROY: return "WM_DESTROY";
			#endif
			#ifdef WM_DESTROYCLIPBOARD
				case WM_DESTROYCLIPBOARD: return "WM_DESTROYCLIPBOARD";
			#endif
			#ifdef WM_DEVICECHANGE
				case WM_DEVICECHANGE: return "WM_DEVICECHANGE";
			#endif
			#ifdef WM_DEVMODECHANGE
				case WM_DEVMODECHANGE: return "WM_DEVMODECHANGE";
			#endif
			#ifdef WM_DISPLAYCHANGE
				case WM_DISPLAYCHANGE: return "WM_DISPLAYCHANGE";
			#endif
			#ifdef WM_DRAWCLIPBOARD
				case WM_DRAWCLIPBOARD: return "WM_DRAWCLIPBOARD";
			#endif
			#ifdef WM_DRAWITEM
				case WM_DRAWITEM: return "WM_DRAWITEM";
			#endif
			#ifdef WM_DROPFILES
				case WM_DROPFILES: return "WM_DROPFILES";
			#endif
			#ifdef WM_ENABLE
				case WM_ENABLE: return "WM_ENABLE";
			#endif
			#ifdef WM_ENDSESSION
				case WM_ENDSESSION: return "WM_ENDSESSION";
			#endif
			#ifdef WM_ENTERIDLE
				case WM_ENTERIDLE: return "WM_ENTERIDLE";
			#endif
			#ifdef WM_ENTERMENULOOP
				case WM_ENTERMENULOOP: return "WM_ENTERMENULOOP";
			#endif
			#ifdef WM_ENTERSIZEMOVE
				case WM_ENTERSIZEMOVE: return "WM_ENTERSIZEMOVE";
			#endif
			#ifdef WM_ERASEBKGND
				case WM_ERASEBKGND: return "WM_ERASEBKGND";
			#endif
			#ifdef WM_EXITMENULOOP
				case WM_EXITMENULOOP: return "WM_EXITMENULOOP";
			#endif
			#ifdef WM_EXITSIZEMOVE
				case WM_EXITSIZEMOVE: return "WM_EXITSIZEMOVE";
			#endif
			#ifdef WM_FONTCHANGE
				case WM_FONTCHANGE: return "WM_FONTCHANGE";
			#endif
			#ifdef WM_GETDLGCODE
				case WM_GETDLGCODE: return "WM_GETDLGCODE";
			#endif
			#ifdef WM_GETFONT
				case WM_GETFONT: return "WM_GETFONT";
			#endif
			#ifdef WM_GETHOTKEY
				case WM_GETHOTKEY: return "WM_GETHOTKEY";
			#endif
			#ifdef WM_GETICON
				case WM_GETICON: return "WM_GETICON";
			#endif
			#ifdef WM_GETMINMAXINFO
				case WM_GETMINMAXINFO: return "WM_GETMINMAXINFO";
			#endif
			#ifdef WM_GETTEXT
				case WM_GETTEXT: return "WM_GETTEXT";
			#endif
			#ifdef WM_GETTEXTLENGTH
				case WM_GETTEXTLENGTH: return "WM_GETTEXTLENGTH";
			#endif
			#ifdef WM_HANDHELDFIRST
				case WM_HANDHELDFIRST: return "WM_HANDHELDFIRST";
			#endif
			#ifdef WM_HANDHELDLAST
				case WM_HANDHELDLAST: return "WM_HANDHELDLAST";
			#endif
			#ifdef WM_HELP
				case WM_HELP: return "WM_HELP";
			#endif
			#ifdef WM_HOTKEY
				case WM_HOTKEY: return "WM_HOTKEY";
			#endif
			#ifdef WM_HSCROLL
				case WM_HSCROLL: return "WM_HSCROLL";
			#endif
			#ifdef WM_HSCROLLCLIPBOARD
				case WM_HSCROLLCLIPBOARD: return "WM_HSCROLLCLIPBOARD";
			#endif
			#ifdef WM_ICONERASEBKGND
				case WM_ICONERASEBKGND: return "WM_ICONERASEBKGND";
			#endif
			#ifdef WM_INITDIALOG
				case WM_INITDIALOG: return "WM_INITDIALOG";
			#endif
			#ifdef WM_INITMENU
				case WM_INITMENU: return "WM_INITMENU";
			#endif
			#ifdef WM_INITMENUPOPUP
				case WM_INITMENUPOPUP: return "WM_INITMENUPOPUP";
			#endif
			#ifdef WM_INPUT
				case WM_INPUT: return "WM_INPUT";
			#endif
			#ifdef WM_INPUTLANGCHANGE
				case WM_INPUTLANGCHANGE: return "WM_INPUTLANGCHANGE";
			#endif
			#ifdef WM_INPUTLANGCHANGEREQUEST
				case WM_INPUTLANGCHANGEREQUEST: return "WM_INPUTLANGCHANGEREQUEST";
			#endif
			#ifdef WM_KEYDOWN
				case WM_KEYDOWN: return "WM_KEYDOWN";
			#endif
			#ifdef WM_KEYUP
				case WM_KEYUP: return "WM_KEYUP";
			#endif
			#ifdef WM_KILLFOCUS
				case WM_KILLFOCUS: return "WM_KILLFOCUS";
			#endif
			#ifdef WM_MDIACTIVATE
				case WM_MDIACTIVATE: return "WM_MDIACTIVATE";
			#endif
			#ifdef WM_MDICASCADE
				case WM_MDICASCADE: return "WM_MDICASCADE";
			#endif
			#ifdef WM_MDICREATE
				case WM_MDICREATE: return "WM_MDICREATE";
			#endif
			#ifdef WM_MDIDESTROY
				case WM_MDIDESTROY: return "WM_MDIDESTROY";
			#endif
			#ifdef WM_MDIGETACTIVE
				case WM_MDIGETACTIVE: return "WM_MDIGETACTIVE";
			#endif
			#ifdef WM_MDIICONARRANGE
				case WM_MDIICONARRANGE: return "WM_MDIICONARRANGE";
			#endif
			#ifdef WM_MDIMAXIMIZE
				case WM_MDIMAXIMIZE: return "WM_MDIMAXIMIZE";
			#endif
			#ifdef WM_MDINEXT
				case WM_MDINEXT: return "WM_MDINEXT";
			#endif
			#ifdef WM_MDIREFRESHMENU
				case WM_MDIREFRESHMENU: return "WM_MDIREFRESHMENU";
			#endif
			#ifdef WM_MDIRESTORE
				case WM_MDIRESTORE: return "WM_MDIRESTORE";
			#endif
			#ifdef WM_MDISETMENU
				case WM_MDISETMENU: return "WM_MDISETMENU";
			#endif
			#ifdef WM_MDITILE
				case WM_MDITILE: return "WM_MDITILE";
			#endif
			#ifdef WM_MEASUREITEM
				case WM_MEASUREITEM: return "WM_MEASUREITEM";
			#endif
			#ifdef WM_GETOBJECT
				case WM_GETOBJECT: return "WM_GETOBJECT";
			#endif
			#ifdef WM_CHANGEUISTATE
				case WM_CHANGEUISTATE: return "WM_CHANGEUISTATE";
			#endif
			#ifdef WM_UPDATEUISTATE
				case WM_UPDATEUISTATE: return "WM_UPDATEUISTATE";
			#endif
			#ifdef WM_QUERYUISTATE
				case WM_QUERYUISTATE: return "WM_QUERYUISTATE";
			#endif
			#ifdef WM_UNINITMENUPOPUP
				case WM_UNINITMENUPOPUP: return "WM_UNINITMENUPOPUP";
			#endif
			#ifdef WM_MENURBUTTONUP
				case WM_MENURBUTTONUP: return "WM_MENURBUTTONUP";
			#endif
			#ifdef WM_MENUCOMMAND
				case WM_MENUCOMMAND: return "WM_MENUCOMMAND";
			#endif
			#ifdef WM_MENUGETOBJECT
				case WM_MENUGETOBJECT: return "WM_MENUGETOBJECT";
			#endif
			#ifdef WM_MENUDRAG
				case WM_MENUDRAG: return "WM_MENUDRAG";
			#endif
			#ifdef WM_APPCOMMAND
				case WM_APPCOMMAND: return "WM_APPCOMMAND";
			#endif
			#ifdef WM_MENUCHAR
				case WM_MENUCHAR: return "WM_MENUCHAR";
			#endif
			#ifdef WM_MENUSELECT
				case WM_MENUSELECT: return "WM_MENUSELECT";
			#endif
			#ifdef WM_NEXTMENU
				case WM_NEXTMENU: return "WM_NEXTMENU";
			#endif
			#ifdef WM_MOVE
				case WM_MOVE: return "WM_MOVE";
			#endif
			#ifdef WM_MOVING
				case WM_MOVING: return "WM_MOVING";
			#endif
			#ifdef WM_NCACTIVATE
				case WM_NCACTIVATE: return "WM_NCACTIVATE";
			#endif
			#ifdef WM_NCCALCSIZE
				case WM_NCCALCSIZE: return "WM_NCCALCSIZE";
			#endif
			#ifdef WM_NCCREATE
				case WM_NCCREATE: return "WM_NCCREATE";
			#endif
			#ifdef WM_NCDESTROY
				case WM_NCDESTROY: return "WM_NCDESTROY";
			#endif
			#ifdef WM_NCHITTEST
				case WM_NCHITTEST: return "WM_NCHITTEST";
			#endif
			#ifdef WM_NCLBUTTONDBLCLK
				case WM_NCLBUTTONDBLCLK: return "WM_NCLBUTTONDBLCLK";
			#endif
			#ifdef WM_NCLBUTTONDOWN
				case WM_NCLBUTTONDOWN: return "WM_NCLBUTTONDOWN";
			#endif
			#ifdef WM_NCLBUTTONUP
				case WM_NCLBUTTONUP: return "WM_NCLBUTTONUP";
			#endif
			#ifdef WM_NCMBUTTONDBLCLK
				case WM_NCMBUTTONDBLCLK: return "WM_NCMBUTTONDBLCLK";
			#endif
			#ifdef WM_NCMBUTTONDOWN
				case WM_NCMBUTTONDOWN: return "WM_NCMBUTTONDOWN";
			#endif
			#ifdef WM_NCMBUTTONUP
				case WM_NCMBUTTONUP: return "WM_NCMBUTTONUP";
			#endif
			#ifdef WM_NCXBUTTONDOWN
				case WM_NCXBUTTONDOWN: return "WM_NCXBUTTONDOWN";
			#endif
			#ifdef WM_NCXBUTTONUP
				case WM_NCXBUTTONUP: return "WM_NCXBUTTONUP";
			#endif
			#ifdef WM_NCXBUTTONDBLCLK
				case WM_NCXBUTTONDBLCLK: return "WM_NCXBUTTONDBLCLK";
			#endif
			#ifdef WM_NCMOUSEHOVER
				case WM_NCMOUSEHOVER: return "WM_NCMOUSEHOVER";
			#endif
			#ifdef WM_NCMOUSELEAVE
				case WM_NCMOUSELEAVE: return "WM_NCMOUSELEAVE";
			#endif
			#ifdef WM_NCMOUSEMOVE
				case WM_NCMOUSEMOVE: return "WM_NCMOUSEMOVE";
			#endif
			#ifdef WM_NCPAINT
				case WM_NCPAINT: return "WM_NCPAINT";
			#endif
			#ifdef WM_NCRBUTTONDBLCLK
				case WM_NCRBUTTONDBLCLK: return "WM_NCRBUTTONDBLCLK";
			#endif
			#ifdef WM_NCRBUTTONDOWN
				case WM_NCRBUTTONDOWN: return "WM_NCRBUTTONDOWN";
			#endif
			#ifdef WM_NCRBUTTONUP
				case WM_NCRBUTTONUP: return "WM_NCRBUTTONUP";
			#endif
			#ifdef WM_NEXTDLGCTL
				case WM_NEXTDLGCTL: return "WM_NEXTDLGCTL";
			#endif
			#ifdef WM_NOTIFY
				case WM_NOTIFY: return "WM_NOTIFY";
			#endif
			#ifdef WM_NOTIFYFORMAT
				case WM_NOTIFYFORMAT: return "WM_NOTIFYFORMAT";
			#endif
			#ifdef WM_NULL
				case WM_NULL: return "WM_NULL";
			#endif
			#ifdef WM_PAINT
				case WM_PAINT: return "WM_PAINT";
			#endif
			#ifdef WM_PAINTCLIPBOARD
				case WM_PAINTCLIPBOARD: return "WM_PAINTCLIPBOARD";
			#endif
			#ifdef WM_PAINTICON
				case WM_PAINTICON: return "WM_PAINTICON";
			#endif
			#ifdef WM_PALETTECHANGED
				case WM_PALETTECHANGED: return "WM_PALETTECHANGED";
			#endif
			#ifdef WM_PALETTEISCHANGING
				case WM_PALETTEISCHANGING: return "WM_PALETTEISCHANGING";
			#endif
			#ifdef WM_PARENTNOTIFY
				case WM_PARENTNOTIFY: return "WM_PARENTNOTIFY";
			#endif
			#ifdef WM_PASTE
				case WM_PASTE: return "WM_PASTE";
			#endif
			#ifdef WM_PENWINFIRST
				case WM_PENWINFIRST: return "WM_PENWINFIRST";
			#endif
			#ifdef WM_PENWINLAST
				case WM_PENWINLAST: return "WM_PENWINLAST";
			#endif
			#ifdef WM_POWER
				case WM_POWER: return "WM_POWER";
			#endif
			#ifdef WM_POWERBROADCAST
				case WM_POWERBROADCAST: return "WM_POWERBROADCAST";
			#endif
			#ifdef WM_PRINT
				case WM_PRINT: return "WM_PRINT";
			#endif
			#ifdef WM_PRINTCLIENT
				case WM_PRINTCLIENT: return "WM_PRINTCLIENT";
			#endif
			#ifdef WM_QUERYDRAGICON
				case WM_QUERYDRAGICON: return "WM_QUERYDRAGICON";
			#endif
			#ifdef WM_QUERYENDSESSION
				case WM_QUERYENDSESSION: return "WM_QUERYENDSESSION";
			#endif
			#ifdef WM_QUERYNEWPALETTE
				case WM_QUERYNEWPALETTE: return "WM_QUERYNEWPALETTE";
			#endif
			#ifdef WM_QUERYOPEN
				case WM_QUERYOPEN: return "WM_QUERYOPEN";
			#endif
			#ifdef WM_QUEUESYNC
				case WM_QUEUESYNC: return "WM_QUEUESYNC";
			#endif
			#ifdef WM_QUIT
				case WM_QUIT: return "WM_QUIT";
			#endif
			#ifdef WM_RENDERALLFORMATS
				case WM_RENDERALLFORMATS: return "WM_RENDERALLFORMATS";
			#endif
			#ifdef WM_RENDERFORMAT
				case WM_RENDERFORMAT: return "WM_RENDERFORMAT";
			#endif
			#ifdef WM_SETCURSOR
				case WM_SETCURSOR: return "WM_SETCURSOR";
			#endif
			#ifdef WM_SETFOCUS
				case WM_SETFOCUS: return "WM_SETFOCUS";
			#endif
			#ifdef WM_SETFONT
				case WM_SETFONT: return "WM_SETFONT";
			#endif
			#ifdef WM_SETHOTKEY
				case WM_SETHOTKEY: return "WM_SETHOTKEY";
			#endif
			#ifdef WM_SETICON
				case WM_SETICON: return "WM_SETICON";
			#endif
			#ifdef WM_SETREDRAW
				case WM_SETREDRAW: return "WM_SETREDRAW";
			#endif
			#ifdef WM_SETTEXT
				case WM_SETTEXT: return "WM_SETTEXT";
			#endif
			#ifdef WM_SHOWWINDOW
				case WM_SHOWWINDOW: return "WM_SHOWWINDOW";
			#endif
			#ifdef WM_SIZE
				case WM_SIZE: return "WM_SIZE";
			#endif
			#ifdef WM_SIZECLIPBOARD
				case WM_SIZECLIPBOARD: return "WM_SIZECLIPBOARD";
			#endif
			#ifdef WM_SIZING
				case WM_SIZING: return "WM_SIZING";
			#endif
			#ifdef WM_SPOOLERSTATUS
				case WM_SPOOLERSTATUS: return "WM_SPOOLERSTATUS";
			#endif
			#ifdef WM_STYLECHANGED
				case WM_STYLECHANGED: return "WM_STYLECHANGED";
			#endif
			#ifdef WM_STYLECHANGING
				case WM_STYLECHANGING: return "WM_STYLECHANGING";
			#endif
			#ifdef WM_SYSCHAR
				case WM_SYSCHAR: return "WM_SYSCHAR";
			#endif
			#ifdef WM_SYSCOLORCHANGE
				case WM_SYSCOLORCHANGE: return "WM_SYSCOLORCHANGE";
			#endif
			#ifdef WM_SYSCOMMAND
				case WM_SYSCOMMAND: return "WM_SYSCOMMAND";
			#endif
			#ifdef WM_SYSDEADCHAR
				case WM_SYSDEADCHAR: return "WM_SYSDEADCHAR";
			#endif
			#ifdef WM_SYSKEYDOWN
				case WM_SYSKEYDOWN: return "WM_SYSKEYDOWN";
			#endif
			#ifdef WM_SYSKEYUP
				case WM_SYSKEYUP: return "WM_SYSKEYUP";
			#endif
			#ifdef WM_TCARD
				case WM_TCARD: return "WM_TCARD";
			#endif
			#ifdef WM_THEMECHANGED
				case WM_THEMECHANGED: return "WM_THEMECHANGED";
			#endif
			#ifdef WM_TIMECHANGE
				case WM_TIMECHANGE: return "WM_TIMECHANGE";
			#endif
			#ifdef WM_TIMER
				case WM_TIMER: return "WM_TIMER";
			#endif
			#ifdef WM_UNDO
				case WM_UNDO: return "WM_UNDO";
			#endif
			#ifdef WM_USER
				case WM_USER: return "WM_USER";
			#endif
			#ifdef WM_USERCHANGED
				case WM_USERCHANGED: return "WM_USERCHANGED";
			#endif
			#ifdef WM_VKEYTOITEM
				case WM_VKEYTOITEM: return "WM_VKEYTOITEM";
			#endif
			#ifdef WM_VSCROLL
				case WM_VSCROLL: return "WM_VSCROLL";
			#endif
			#ifdef WM_VSCROLLCLIPBOARD
				case WM_VSCROLLCLIPBOARD: return "WM_VSCROLLCLIPBOARD";
			#endif
			#ifdef WM_WINDOWPOSCHANGED
				case WM_WINDOWPOSCHANGED: return "WM_WINDOWPOSCHANGED";
			#endif
			#ifdef WM_WINDOWPOSCHANGING
				case WM_WINDOWPOSCHANGING: return "WM_WINDOWPOSCHANGING";
			#endif
			#ifdef WM_WININICHANGE
				case WM_WININICHANGE: return "WM_WININICHANGE";
			#endif
			#ifdef WM_KEYLAST
				case WM_KEYLAST: return "WM_KEYLAST";
			#endif
			#ifdef WM_SYNCPAINT
				case WM_SYNCPAINT: return "WM_SYNCPAINT";
			#endif
			#ifdef WM_MOUSEACTIVATE
				case WM_MOUSEACTIVATE: return "WM_MOUSEACTIVATE";
			#endif
			#ifdef WM_MOUSEMOVE
				case WM_MOUSEMOVE: return "WM_MOUSEMOVE";
			#endif
			#ifdef WM_LBUTTONDOWN
				case WM_LBUTTONDOWN: return "WM_LBUTTONDOWN";
			#endif
			#ifdef WM_LBUTTONUP
				case WM_LBUTTONUP: return "WM_LBUTTONUP";
			#endif
			#ifdef WM_LBUTTONDBLCLK
				case WM_LBUTTONDBLCLK: return "WM_LBUTTONDBLCLK";
			#endif
			#ifdef WM_RBUTTONDOWN
				case WM_RBUTTONDOWN: return "WM_RBUTTONDOWN";
			#endif
			#ifdef WM_RBUTTONUP
				case WM_RBUTTONUP: return "WM_RBUTTONUP";
			#endif
			#ifdef WM_RBUTTONDBLCLK
				case WM_RBUTTONDBLCLK: return "WM_RBUTTONDBLCLK";
			#endif
			#ifdef WM_MBUTTONDOWN
				case WM_MBUTTONDOWN: return "WM_MBUTTONDOWN";
			#endif
			#ifdef WM_MBUTTONUP
				case WM_MBUTTONUP: return "WM_MBUTTONUP";
			#endif
			#ifdef WM_MBUTTONDBLCLK
				case WM_MBUTTONDBLCLK: return "WM_MBUTTONDBLCLK";
			#endif
			#ifdef WM_MOUSEWHEEL
				case WM_MOUSEWHEEL: return "WM_MOUSEWHEEL";
			#endif
			#ifdef WM_XBUTTONDOWN
				case WM_XBUTTONDOWN: return "WM_XBUTTONDOWN";
			#endif
			#ifdef WM_XBUTTONUP
				case WM_XBUTTONUP: return "WM_XBUTTONUP";
			#endif
			#ifdef WM_MOUSELAST
				case WM_MOUSELAST: return "WM_MOUSELAST";
			#endif
			#ifdef WM_MOUSEHOVER
				case WM_MOUSEHOVER: return "WM_MOUSEHOVER";
			#endif
			#ifdef WM_MOUSELEAVE
				case WM_MOUSELEAVE: return "WM_MOUSELEAVE";
			#endif
			#ifdef WM_TOUCHMOVE
				case WM_TOUCHMOVE: return "WM_TOUCHMOVE";
			#endif
			#ifdef WM_TOUCHDOWN
				case WM_TOUCHDOWN: return "WM_TOUCHDOWN";
			#endif
			#ifdef WM_TOUCHUP
				case WM_TOUCHUP: return "WM_TOUCHUP";
			#endif
		}
		char buf[200];
		sprintf(buf,"Unkown Message: %d",msg);
		return buf;
	}

};

#endif
