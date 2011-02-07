#ifndef SCENE_H
#define SCENE_H

#include "aotk.h"
#include "camera.h"

namespace AoTK{
    class Scene{
        friend class AOTK;

        std::string name;
        std::vector<Object *> objects;
    public:
        Scene(std::string name = "");
        virtual ~Scene();
        Scene() = delete;
        Scene(const Scene &o) = delete;
        Scene &operator=(const Scene &o) = delete;

        void addObject(Object *o);
        void removeObject(Object *o);

        void doLogic(unsigned int frame);
        void doGraphics(unsigned int frame);
        void doPrepare(unsigned int frame);
        void render();



    };
};


#endif
