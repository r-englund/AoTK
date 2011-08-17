#include <AoTK/window_handler.h>
#include <AoTK/math.h>

#ifdef AoTK_GLUT

#include <assert.h>
#include <string.h>

namespace AoTK{

    void Window::start(){
    std::cout << "starting" << std::endl;
    __start = clock();
    glutMainLoop();
//    __run = true;
//    while(__run){
//        checkForMessages();
//        idleEvent();
//        if(redisplay){
//            if(__dispFunc != NULL){
//            __dispFunc();
//        }
////        getAllError("Main Loop",-1);
//        swapBuffers();
//        redisplay = false;
//        }
//    }

}

    void display(){
        if(Window::getWindow()->redisplay){
            if(Window::getWindow()->__dispFunc != NULL)
                Window::getWindow()->__dispFunc();
            Window::getWindow()->redisplay = false;
            Window::getWindow()->swapBuffers();
        }
    }

    void idle(){
        Window::getWindow()->idleEvent();
        glutPostRedisplay();
    }

    void resize(int w, int h){Window::getWindow()->resizeEvent();}
    AoTK::Math::Vector2<float> oldPassive(-1,-1),oldActive(-1,-1);

    void mouseClick(int button, int state, int x, int y){
        if(state == GLUT_DOWN){
            switch(button){
                case GLUT_LEFT_BUTTON:
                    Window::getWindow()->mousePressEvent(AoTK::MOUSE_BUTTON::LEFT_BUTTON,x,y);
                    break;
                case GLUT_RIGHT_BUTTON:
                    Window::getWindow()->mousePressEvent(AoTK::MOUSE_BUTTON::RIGHT_BUTTON,x,y);
                    break;
                case GLUT_MIDDLE_BUTTON:
                    Window::getWindow()->mousePressEvent(AoTK::MOUSE_BUTTON::MIDDLE_BUTTON,x,y);
                    break;
            }
            oldActive.x = x;
            oldActive.y = y;
        }else{
            switch(button){
                case GLUT_LEFT_BUTTON:
                    Window::getWindow()->mouseReleaseEvent(AoTK::MOUSE_BUTTON::LEFT_BUTTON,x,y);
                    break;
                case GLUT_RIGHT_BUTTON:
                    Window::getWindow()->mouseReleaseEvent(AoTK::MOUSE_BUTTON::RIGHT_BUTTON,x,y);
                    break;
                case GLUT_MIDDLE_BUTTON:
                    Window::getWindow()->mouseReleaseEvent(AoTK::MOUSE_BUTTON::MIDDLE_BUTTON,x,y);
                    break;
            }
            oldPassive.x = x;
            oldPassive.y = y;
        }
    }
    void passiveMotion(int x, int y){
        if(oldPassive.x == -1 || oldPassive.y == -1){
            oldPassive.x = x;
            oldPassive.y = y;
        }
        int dx,dy;
        dx = oldPassive.x - x;
        dy = oldPassive.y - y;
        Window::getWindow()->passiveMousemotionEvent(-dx,-dy);
        //std::cout << "Passive motion not yet supported" << std::endl;
    }
    void motion(int x, int y){
        int dx,dy;
        dx = oldActive.x - x;
        dy = oldActive.y - y;
        Window::getWindow()->mousemotionEvent(-dx,-dy);
    }

    void keyboard(unsigned char key,int x, int y){
        std::cout << "to do, implement";
        __window->keyImpulseEvent(key);


    }
    void keyboardUp(unsigned char key,int x, int y){
        std::cout << "to do, implement";
        __window->keyImpulseEvent(key);

    }

    Window* Window::createWindow(uint16_t width,uint16_t height,std::string title,bool force32){
        __window = new Window();
        __window->window_width = width;
        __window->window_height = height;
        __window->client_width = width;
        __window->client_height = height;

        int i;
        char *c[1];
        c[0] = new char[title.length()];
        for(int i=0;i<title.length();i++){
            c[0][i] = title[i];
        }
        glutInit(&i,c);

        glutInitWindowSize(width,height);
        glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

        glutCreateWindow(title.c_str());

        GLenum err = glewInit();
        assert(err == GLEW_OK && glewGetErrorString(err));

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


        glutDisplayFunc(display);
        glutIdleFunc(idle);
        glutReshapeFunc(resize);
        glutMouseFunc(mouseClick);
        glutPassiveMotionFunc(passiveMotion);
        glutMotionFunc(motion);
        glutKeyboardFunc(keyboard);
        glutKeyboardUpFunc(keyboardUp);

        __window->setSizes();

        return __window;
    }



    void Window::setSizes(){}

    void Window::checkForMessages(){ }


    void Window::swapBuffers(){
        glutSwapBuffers();
    }

};

#endif
