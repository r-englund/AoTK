#ifndef WINDOW_H
#define WINDOW_H

#include "viewport.h"

#include <vector>

namespace AoTK{
    class Window{
        Size2D<unsigned int> size;
        std::string title;
        std::vector<Viewport *> viewports;

        void createWindow();

    friend class AOTK;
        Window(Size2D<unsigned int> size,std::string title);
        Window() = delete;
        Window(const Window &w) = delete;
        Window& operator=(const Window &w) = delete;
        ~Window();

        void checkForMessages();
        void swapBuffers();

        void createSubWindow(Size2D<unsigned int> size);

    public:

        Size2D<unsigned int> getSize(){return size;}
    };
};

#endif
