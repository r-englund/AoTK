#ifndef AOTK_MATH_H
#define AOTK_MATH_H


#include <stdint.h>
#include <string.h>
#include <cmath>
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

#ifndef clamp
#define clamp(a,b,c) (((a) > (c)) ? (c) : (((a) < (b)) ? (b) : (a)))
#endif

namespace AoTK{
    template<int,int,typename T> struct Matrix;
    template<typename T = float> struct Matrix4x4;
    template<typename T = float> struct Vector2;
    template<typename T = float> struct Vector3;
    template<typename T = float> struct Vector4;



/*********
*
* xx yx zx wx
* xy yy zy wy
* xz yz zz wz
* xw yw zw ww
*
*
* _2d[col][row]
*
* _1d[id]
*
* id is asigned as:
*
* 1 5 9  13
* 2 6 10 14
* 3 7 11 15
* 4 8 12 16
*
**********/
    template<typename T>
    struct Matrix4x4{
        union{
            T _1d[16];
            struct{
                T _2d[4][4];
            };
            struct{
                T xx,xy,xz,xw,
                  yx,yy,yz,yw,
                  zx,zy,zz,zw,
                  wx,wy,wz,ww;
            };
        };

        Matrix4x4(T a[16]);
        Matrix4x4(T a[4][4]);
        Matrix4x4();
        Matrix4x4(const Matrix4x4 &m);
//        template<typename T2> Matrix4x4(const Matrix4x4<T2> &m);
        virtual ~Matrix4x4(){}

        Matrix4x4 operator+(const Matrix4x4  &m) const;
        Matrix4x4 operator-(const Matrix4x4  &m) const;
        Matrix4x4 operator*(const Matrix4x4  &m) const;
        Matrix4x4 operator+(T f) const;
        Matrix4x4 operator-(T f) const;
        Matrix4x4 operator*(T f) const;
        Matrix4x4 operator/(T f) const;

        Matrix4x4 &operator=(const Matrix4x4  &m);

        Matrix4x4 &operator+=(const Matrix4x4  &m);
        Matrix4x4 &operator-=(const Matrix4x4  &m);
        Matrix4x4 &operator*=(const Matrix4x4  &m);
        Matrix4x4 &operator+=(T f);
        Matrix4x4 &operator-=(T f);
        Matrix4x4 &operator*=(T f);
        Matrix4x4 &operator/=(T f);

        template<typename T2> bool operator==(const Matrix4x4<T2>  &m);
        template<typename T2> bool operator!=(const Matrix4x4<T2> &m);

        static Matrix4x4 perspectiveProjection(T fovy,T aspc,T near,T far);
        static Matrix4x4 orthogonalProjection(T left, T right, T bottom, T top, T near, T far);
        static Matrix4x4 lookAt(Vector3<T> pos,Vector3<T> at,Vector3<T> up);

        static Matrix4x4 rotateX(T deg);
        static Matrix4x4 rotateY(T deg);
        static Matrix4x4 rotateZ(T deg);
        static Matrix4x4 rotateAxis(T deg,T x,T y,T z);
        static Matrix4x4 rotateAxis(T deg,const Vector3<T> &_v);

        static Matrix4x4 translate(T x,T y,T z);
        static Matrix4x4 scale(T x,T y,T z);
        static Matrix4x4 scale(T x){
            return scale(x,x,x);
        }

        template<typename M> friend std::ostream &operator<<(std::ostream &os,const Matrix4x4<M> &m);
    };

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

//    template<typename V> std::ostream &operator<<(std::ostream &os,const Vector2<V> &v){}
//    template<typename V> std::ostream &operator<<(std::ostream &os,const Vector3<V> &v){}
//    template<typename V> std::ostream &operator<<(std::ostream &os,const Vector4<V> &v){}

//    template<typename T,typename T2> Vector2<T> operator*(T2 t,const Vector2<T> &v);
//    template<typename T,typename T2> Vector2<T> operator+(T2 t,const Vector2<T> &v);
//    template<typename T,typename T2> Vector2<T> operator-(T2 t,const Vector2<T> &v);
//    template<typename T,typename T2> Vector2<T> operator/(T2 t,const Vector2<T> &v);
//
//    template<typename T,typename T2> Vector3<T> operator*(T2 t,const Vector3<T> &v);
////    template<typename T,typename T2> Vector3<T> operator+(T2 t,const Vector3<T> &v);
//    template<typename T,typename T2> Vector3<T> operator-(T2 t,const Vector3<T> &v);
//    template<typename T,typename T2> Vector3<T> operator/(T2 t,const Vector3<T> &v);
//
//    template<typename T,typename T2> Vector4<T> operator*(T2 t,const Vector4<T> &v);
//    template<typename T,typename T2> Vector4<T> operator+(T2 t,const Vector4<T> &v);
//    template<typename T,typename T2> Vector4<T> operator-(T2 t,const Vector4<T> &v);
//    template<typename T,typename T2> Vector4<T> operator/(T2 t,const Vector4<T> &v);
};

//#ifndef AOTK_MATH_ONLY_TYPES

#include "math/matrix.hpp"
#include "math/matrix4x4.hpp"
#include "math/vector2.hpp"
#include "math/vector3.hpp"
#include "math/vector4.hpp"

//#endif
#endif
