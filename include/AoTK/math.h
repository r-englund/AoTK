#ifndef AOTK_MATH_H
#define AOTK_MATH_H


#include <stdint.h>
#include <string.h>
#include <cmath>
#include <cstdlib>
#include <iostream>

#include <assert.h>

#ifndef M_E
#define M_E		    2.7182818284590452354
#endif
#ifndef M_LOG2E
#define M_LOG2E		1.4426950408889634074
#endif
#ifndef M_LOG10E
#define M_LOG10E	0.43429448190325182765
#endif
#ifndef M_LN2
#define M_LN2		0.69314718055994530942
#endif
#ifndef M_LN10
#define M_LN10		2.30258509299404568402
#endif
#ifndef M_PI
#define M_PI		3.14159265358979323846
#endif
#ifndef M_PI_2
#define M_PI_2		1.57079632679489661923
#endif
#ifndef M_PI_4
#define M_PI_4		0.78539816339744830962
#endif
#ifndef M_1_PI
#define M_1_PI		0.31830988618379067154
#endif
#ifndef M_2_PI
#define M_2_PI		0.63661977236758134308
#endif
#ifndef M_2_SQRTPI
#define M_2_SQRTPI	1.12837916709551257390
#endif
#ifndef M_SQRT2
#define M_SQRT2		1.41421356237309504880
#endif
#ifndef M_SQRT1_2
#define M_SQRT1_2	0.70710678118654752440
#endif

#ifndef round
template<class T> int round(T t){
	T d = t - (int)t;
	if(d>0.5)
		return t+1;
	return t;
}
#endif

#ifndef abs
//template<typename T> inline T abs( T a){return ((a<0) ? -a : a);}
#endif

inline bool floatCMP(float a,float b,float e = 0.001){return abs(a-b)<e;}

#ifndef clamp
#define clamp(a,b,c) (((a) > (c)) ? (c) : (((a) < (b)) ? (b) : (a)))
#endif

namespace AoTK{
namespace Math{
    template<int,int,typename T> struct Matrix;
    template<typename T = float> struct Matrix4x4;
    template<typename T = float> struct Vector2;
    template<typename T = float> struct Vector3;
    template<typename T = float> struct Vector4;

    template<typename T>
    struct Vector2{
        union{
            T arr[2];
            struct{
                T x,y;
            };
            struct{
                T u,v;
            };
            struct{
                T w,h;
            };
        };
        Vector2(T x,T y = 0);
        Vector2();
        template<typename T2> Vector2(const Vector2<T2> &v);
        ~Vector2(){}

        template<typename T2> T dot(const Vector2<T2> &v) const;

        void normalize();
        T getLength()const;
        template<typename T2> Vector2 operator+(const Vector2<T2> &v)const;
        template<typename T2> Vector2 operator-(const Vector2<T2> &v)const;
        template<typename T2> Vector2 operator+(T2 t)const;
        template<typename T2> Vector2 operator-(T2 t)const;
        template<typename T2> Vector2 operator*(T2 t)const;
        template<typename T2> Vector2 operator/(T2 t)const;

        template<typename T2> Vector2 &operator+=(const Vector2<T2> &v);
        template<typename T2> Vector2 &operator-=(const Vector2<T2> &v);
        template<typename T2> Vector2 &operator+=(T2 t);
        template<typename T2> Vector2 &operator-=(T2 t);
        template<typename T2> Vector2 &operator*=(T2 t);
        template<typename T2> Vector2 &operator/=(T2 t);

        template<typename T2> bool operator==(const Vector2<T2> &v)const;
        template<typename T2> bool operator!=(const Vector2<T2> &v)const;

        template<typename T2> bool operator>(const Vector2<T2> &m)const;
        template<typename T2> bool operator<(const Vector2<T2> &m)const;
        template<typename T2> bool operator<=(const Vector2<T2> &m)const;
        template<typename T2> bool operator>=(const Vector2<T2> &m)const;

    };


    template<typename T>
    struct Vector3{
        union{
            T arr[3];
            struct{
                T x,y,z;
            };
            struct{
                T u,v,s;
            };
            struct{
                T w,h,d;
            };
            struct{
                T r,g,b;
            };
        };
        Vector3();
        Vector3(T x,T y = 0,T z = 0);
        template<typename T2> Vector3(const Vector3<T2> &v);
        ~Vector3(){}

        template<typename T2> T dot(const Vector3<T2> &v) const;
        template<typename T2> Vector3 cross(const Vector3<T2> &v) const;

        void normalize();
        T getLength()const;
        template<typename T2> Vector3 operator+(const Vector3<T2> &v)const;
        template<typename T2> Vector3 operator-(const Vector3<T2> &v)const;
        template<typename T2> Vector3 operator+(T2 t)const;
        template<typename T2> Vector3 operator-(T2 t)const;
        template<typename T2> Vector3 operator*(T2 t)const;
        template<typename T2> Vector3 operator/(T2 t)const;

        template<typename T2> Vector3 &operator+=(const Vector3<T2> &v);
        template<typename T2> Vector3 &operator-=(const Vector3<T2> &v);
        template<typename T2> Vector3 &operator+=(T2 t);
        template<typename T2> Vector3 &operator-=(T2 t);
        template<typename T2> Vector3 &operator*=(T2 t);
        template<typename T2> Vector3 &operator/=(T2 t);

        template<typename T2> bool operator==(const Vector3<T2> &v)const;
        template<typename T2> bool operator!=(const Vector3<T2> &v)const;

        template<typename T2> bool operator>(const Vector3<T2> &m)const;
        template<typename T2> bool operator<(const Vector3<T2> &m)const;
        template<typename T2> bool operator<=(const Vector3<T2> &m)const;
        template<typename T2> bool operator>=(const Vector3<T2> &m)const;

    };
    template<typename T>
    struct Vector4{
        union{
            T arr[4];
            struct{
                T x,y,z,w;
            };
            struct{
                T r,g,b,a;
            };
        };
        Vector4();
        Vector4(T x,T y = 0,T z = 0,T w = 1);
        template<typename T2> Vector4(const Vector4<T2> &v);
        ~Vector4(){}

        template<typename T2> T dot(const Vector4<T2> &v) const;

        void normalize();
        T getLength()const;
        template<typename T2> Vector4 operator+(const Vector4<T2> &v)const;
        template<typename T2> Vector4 operator-(const Vector4<T2> &v)const;
        template<typename T2> Vector4 operator+(T2 t)const;
        template<typename T2> Vector4 operator-(T2 t)const;
        template<typename T2> Vector4 operator*(T2 t)const;
        template<typename T2> Vector4 operator/(T2 t)const;

        template<typename T2> Vector4 &operator+=(const Vector4<T2> &v);
        template<typename T2> Vector4 &operator-=(const Vector4<T2> &v);
        template<typename T2> Vector4 &operator+=(T2 t);
        template<typename T2> Vector4 &operator-=(T2 t);
        template<typename T2> Vector4 &operator*=(T2 t);
        template<typename T2> Vector4 &operator/=(T2 t);

        template<typename T2> bool operator==(const Vector4<T2> &v)const;
        template<typename T2> bool operator!=(const Vector4<T2> &v)const;

        template<typename T2> bool operator>(const Vector4<T2> &m)const;
        template<typename T2> bool operator<(const Vector4<T2> &m)const;
        template<typename T2> bool operator<=(const Vector4<T2> &m)const;
        template<typename T2> bool operator>=(const Vector4<T2> &m)const;


    };
    template<typename T> Vector4<T> &operator*=(const Matrix4x4<T> m,Vector4<T> &v){
        v = m * v;
        return v;
    }

    template<typename T> Vector4<T>  operator*(const Matrix4x4<T> m,const Vector4<T> v){
        Vector4<T> out;
        out.x = v.x * m._2d[0][0] +  v.y * m._2d[0][1] +  v.z * m._2d[0][2] +  v.w * m._2d[0][3];
        out.y = v.x * m._2d[1][0] +  v.y * m._2d[1][1] +  v.z * m._2d[1][2] +  v.w * m._2d[1][3];
        out.z = v.x * m._2d[2][0] +  v.y * m._2d[2][1] +  v.z * m._2d[2][2] +  v.w * m._2d[2][3];
        out.w = v.x * m._2d[3][0] +  v.y * m._2d[3][1] +  v.z * m._2d[3][2] +  v.w * m._2d[3][3];

        return out;
    }


template<typename T> std::ostream &operator<<(std::ostream &os,const Vector4<T> &v){
    os << "[" << v.x << " " << v.y << " " << v.z << " " << v.w << "]" << std::endl;
    return os;
}

template<typename T> std::ostream &operator<<(std::ostream &os,const Vector3<T> &v){
    os << "[" << v.x << " " << v.y << " " << v.z << "]" << std::endl;
    return os;
}

template<typename T> std::ostream &operator<<(std::ostream &os,const Vector2<T> &v){
    os << "[" << v.x << " " << v.y << "]" << std::endl;
    return os;
}
};
};

//#ifndef AOTK_MATH_ONLY_TYPES

#include "math/matrix.hpp"
#include "math/matrix4x4.hpp"
#include "math/vector2.hpp"
#include "math/vector3.hpp"
#include "math/vector4.hpp"

//#endif
#endif
