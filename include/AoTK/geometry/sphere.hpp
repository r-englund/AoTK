#ifndef AOTK_SPHERE_HPP
#define AOTK_SPHERE_HPP

namespace AoTK{
namespace Geometry{
    template<typename T>
    class Sphere{
    public:
        Math::Vector3<T> center;
        T radius;
    public:
        Sphere(Math::Vector3<T> _center,T _radius):
        center(center),
        radius(radius)
        {}

        inline bool inside(Math::Vector3<T> p){
            return((p-center).getLength()<radius);
        }
        inline bool outside(Math::Vector3<T> p){
            return((p-center).getLength()>radius);
        }
        inline bool on(Math::Vector3<T> p){
            return((p-center).getLength()==radius);
        }
        inline bool insideOn(Math::Vector3<T> p){
            return((p-center).getLength()<=radius);
        }
        inline bool outsideOn(Math::Vector3<T> p){
            return((p-center).getLength()>=radius);
        }

        void addVertex(Math::Vector3<T> point){
            if(insideOn(point))
                return;
            float l;
            auto dir = center - point;
            l = dir.getLength();
            center += dir*(l-radius)/2.0;
            radius = (l+radius)/2.0;
        }

        static Sphere<T> fromPoints(std::vector<Math::Vector3<T>> points){
            assert(points.size()>=4 && "Cant create a sphere with less than four points");
            T r = 0,l;
            Math::Vector3<T> min =points[0];
            Math::Vector3<T> m = points[0];
            Math::Vector3<T> center;
            for(auto it = points.begin();it!=points.end();++it){
                if(min.x>it->x) min.x=it->x;
                if(min.y>it->y) min.y=it->y;
                if(min.z>it->z) min.z=it->z;

                if(m.x<it->x) m.x=it->x;
                if(m.y<it->y) m.y=it->y;
                if(m.z<it->z) m.z=it->z;
            }
            center = min + m;
            center *= 0.5;
            r = (m-min).getLength()*0.5;
            Sphere<T> s(center,r);
            bool moved = false;
            do{
                moved = false;
                for(auto it = points.begin();it!=points.end();++it){
                    if(s.outside(*it)){
                        auto dir = s.center - *it;
                        l = dir.getLength();
                        dir.normalize();
                        s.center += dir*(l-r)/2.0;
                        s.radius = r = (l+r)/2.0;
                        moved = true;
                    }
                }
            }while(moved);
            return s;
        }
    };
};
};

#endif
