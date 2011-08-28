#ifndef AOTK_PLANE_HPP
#define AOTK_PLANE_HPP

#include <exception>

namespace AoTK{
namespace Geometry{
    template<typename T>
    class Plane{
        Math::Vector4<T> __normal; //w = d in ax+by+cx+d = 0

        public:
            Plane(Math::Vector4<T> normal):__normal(normal){}
            Plane(Math::Vector3<T> dir1,Math::Vector3<T> dir2){
                __normal = dir1.cross(dir2);
            }
            Plane(Math::Vector3<T> points[3]){
                auto e1 = points[1] - points[0];
                auto e2 = points[2] - points[0];
                __normal = e1.cross(e2);
            }

            static Plane LeastSquarePlane(std::vector<Math::Vector3<T>> points){
                std::exception e = new std::exception();
                throw e;
            }
    };
};
};

#endif
