#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <AoTK/aotk.h>
#include "listeners.h"
#include "scene.h"
#include "camera.h"

namespace AoTK{
    class Viewport: public ResizeListener{
    friend class AOTK;
        std::string name;
        int vp_params[4];
        Size2D<> size;
        Position<> pos;

        Camera *cam;
        Scene *scene;


    public:
        Viewport(Scene *scene,Camera *cam,std::string name = "");
        Viewport(const Viewport&) = delete;
        Viewport& operator=(const Viewport&) = delete;
        ~Viewport();

        void setViewport();
        void resize(unsigned int w,unsigned int h);


    };
};


#endif

