#ifndef AOTK_SPHERE_HPP
#define AOTK_SPHERE_HPP

namespace AoTK{
namespace Geometry{
    template<typename T>
    class Sphere{
        Math::Vector3<T> center;
        T radius;
    public:
        Sphere(Math::Vector3<T> center,T radius):
        center(center),
        radius(radius)
        {}

        inline bool inside(Math::Vector3<T> p){return((p-center).length()<radius);}
        inline bool outside(Math::Vector3<T> p){return((p-center).length()>radius);}
        inline bool on(Math::Vector3<T> p){return((p-center).length()==radius);}
        inline bool insideOn(Math::Vector3<T> p){return((p-center).length()<=radius);}
        inline bool outsideOn(Math::Vector3<T> p){return((p-center).length()>=radius);}

        static Sphere<T> fromPoints(std::vector<Math::Vector3<T>> points){
            assert(points.size()>=4 && "Cant create a sphere with less than four points");
            T r = 0,l;
            Math::Vector3<T> min =points[0];
            Math::Vector3<T> max = points[0];
            Math::Vector3<T> center;
            for(auto it = points.begin();it!=points.end();++it){
                if(min.x>it->x) min.x=it->x;
                if(min.y>it->y) min.y=it->y;
                if(min.z>it->z) min.z=it->z;

                if(max.x<it->x) max.x=it->x;
                if(max.y<it->y) max.y=it->y;
                if(max.z<it->z) max.z=it->z;
            }
            center = min + max;
            center *= 0.5;
            r = (max-min).getLenth()*0.5;
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
            //TODO test this..
        }
    };
};
};

#endif
