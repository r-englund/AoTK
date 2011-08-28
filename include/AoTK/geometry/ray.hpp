#ifndef AOTK_RAY_HPP
#define AOTK_RAY_HPP

namespace AoTK{
namespace Geometry{
    template<typename T>
    class Ray{
        Math::Vector3<T> start;
        Math::Vector3<T> dir;

    public:
        Ray(Math::Vector3<T> _start,Math::Vector3<T> _dir):
        start(start),
        dir(dir){}

        void normalizeDirection(){
            dir.normalize();
        }

        Math::Vector3<T> getPoint(T t){
            return start + dir*t;
        }
    };
};
};

#endif
