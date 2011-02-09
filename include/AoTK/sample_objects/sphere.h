#ifndef SPHERE_H
#define SPHERE_H

#include "../aotk.h"

namespace AoTK{

    class Sphere : public Object , public ScrollListener{
        void logic();
        void graphic();
        void prepare();
        void render();

        std::vector<Vertex> vertices;
        std::vector<unsigned short> indices;

        float radius;
        unsigned int subdivisions;
        void tesselate();

        public:
            void scroll(int p){
                if(subdivisions == 0 && p == -1)
                    return;
                subdivisions += p;
                if(subdivisions<0) subdivisions = 0;
                else if(subdivisions>5) subdivisions = 5;
                tesselate();
                std::cout << subdivisions <<" " << p <<std::endl;
            }
            Sphere(float radius = 1.0,Matrix toWorld = Matrix(),unsigned int subdivision = 3, std::string name="");
            ~Sphere();
    };
};



#endif
