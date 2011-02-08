namespace AoTK{

#include "../object.h"

    class Sphere : public Object{
        void logic();
        void graphic();
        void prepare();
        void render();
        public:
            Sphere(float radius = 1.0,unsigned int subdivision = 16, unsigned int slices = 8 std::string name="");
            ~Sphere();
    }
};
