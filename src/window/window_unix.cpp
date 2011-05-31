
#include <AoTK/window_handler.h>

#ifdef AoTK_UNIX


#include <assert.h>

namespace AoTK{

    Window* Window::createWindow(uint16_t width,uint16_t height,std::string title,bool force32){
        __window = new Window();
        __window->width = width;
        __window->height = height;

        if(force32)
            std::cerr << "force32 not yet supported " << __FILE__ << " " << __LINE__<<std::endl;

        Display *display = XOpenDisplay(0);
        assert(display);

        static int visual_attribs[] =
        {
                GLX_X_RENDERABLE    , True,
                GLX_DRAWABLE_TYPE   , GLX_WINDOW_BIT,
                GLX_RENDER_TYPE     , GLX_RGBA_BIT,
                GLX_X_VISUAL_TYPE   , GLX_TRUE_COLOR,
                GLX_RED_SIZE        , 8,
                GLX_GREEN_SIZE      , 8,
                GLX_BLUE_SIZE       , 8,
                GLX_ALPHA_SIZE      , 8,
                GLX_DEPTH_SIZE      , 32,
                GLX_STENCIL_SIZE    , 8,
                GLX_DOUBLEBUFFER    , True,
                //GLX_SAMPLE_BUFFERS  , 1,
                //GLX_SAMPLES         , 4,
                None
        };

        int glx_major, glx_minor;

        // FBConfigs were added in GLX version 1.3.
        if ( !glXQueryVersion( display, &glx_major, &glx_minor ) ||
            ( ( glx_major == 1 ) && ( glx_minor < 3 ) ) || ( glx_major < 1 ) )
            {
                printf( "Invalid GLX version" );
                exit(1);
            }

        std::cerr << "createWindow not yet implemented " << __FILE__ << " " << __LINE__<<std::endl;

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



        return __window;
    }

    void Window::checkForMessages(){
        std::cerr << "checkForMessages not yet implemented " << __FILE__ << " " << __LINE__<<std::endl;
    }
    void Window::swapBuffers(){
        std::cerr << "swapBuffers not yet implemented " << __FILE__ << " " << __LINE__<<std::endl;
    }

};


#endif
