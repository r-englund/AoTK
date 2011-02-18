#include <AoTK/aotk.h>


namespace AoTK{
    Window::Window(Size2D<unsigned int> _size,std::string _title):size(_size),title(_title){
        createWindow();
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


        viewports.push_back(new Viewport(new Scene("main_scene"),new Camera(Position<>(0,0,3),Direction<>(0,0,-1),60,"main_camera"),"main_viewport"));
    }















};

