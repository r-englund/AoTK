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
namespace Math{
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
                T xx,xy,xz,xw, //column 1
                  yx,yy,yz,yw, //column 2
                  zx,zy,zz,zw, //column 3
                  wx,wy,wz,ww; //column 4
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

        bool operator==(const Matrix4x4<T>  &m);
        bool operator!=(const Matrix4x4<T> &m);

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
        #ifdef GL_MODELVIEW_MATRIX
        static Matrix4x4 fromCurrentModelViewGLMatrix();
        static Matrix4x4 fromCurrentProjectionGLMatrix();
        static Matrix4x4 fromCurrentTextureGLMatrix();
        #endif
    };

    #ifdef GL_MODELVIEW_MATRIX

    template< > Matrix4x4<float> Matrix4x4<float>::fromCurrentModelViewGLMatrix(){
        Matrix4x4<float> m;
        glGetFloatv(GL_MODELVIEW_MATRIX,m._1d);
        return m;
    }
    template< > Matrix4x4<double> Matrix4x4<double>::fromCurrentModelViewGLMatrix(){
        Matrix4x4<double> m;
        glGetDoublev(GL_MODELVIEW_MATRIX,m._1d);
        return m;
    }



    template< > Matrix4x4<float> Matrix4x4<float>::fromCurrentProjectionGLMatrix(){
        Matrix4x4<float> m;
        glGetFloatv(GL_PROJECTION_MATRIX,m._1d);
        return m;
    }
    template< > Matrix4x4<double> Matrix4x4<double>::fromCurrentProjectionGLMatrix(){
        Matrix4x4<double> m;
        glGetDoublev(GL_PROJECTION_MATRIX,m._1d);
        return m;
    }

    template< > Matrix4x4<float> Matrix4x4<float>::fromCurrentTextureGLMatrix(){
        Matrix4x4<float> m;
        glGetFloatv(GL_TEXTURE_MATRIX,m._1d);
        return m;
    }
    template< > Matrix4x4<double> Matrix4x4<double>::fromCurrentTextureGLMatrix(){
        Matrix4x4<double> m;
        glGetDoublev(GL_TEXTURE_MATRIX,m._1d);
        return m;
    }
    #endif

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
//    template<typename T> Vector4<T> &operator*=(const Matrix4x4<T> m,Vector4<T> &v){
//        Vector4<T> out;
//        out.x = v.x*m.xx + v.y*m.yx + v.z*m.zx + v.w*m.wx;
//        out.y = v.x*m.xy + v.y*m.yy + v.z*m.zy + v.w*m.wy;
//        out.z = v.x*m.xz + v.y*m.yz + v.z*m.zz + v.w*m.wz;
//        out.w = v.x*m.xw + v.y*m.yw + v.z*m.zw + v.w*m.ww;
//        v = out;
//        return v;
//    }
//
//    template<typename T> Vector4<T>  operator*(const Matrix4x4<T> m,const Vector4<T> v){
//        Vector4<T> out;
//        out.x = v.x*m.xx + v.y*m.yx + v.z*m.zx + v.w*m.wx;
//        out.y = v.x*m.xy + v.y*m.yy + v.z*m.zy + v.w*m.wy;
//        out.z = v.x*m.xz + v.y*m.yz + v.z*m.zz + v.w*m.wz;
//        out.w = v.x*m.xw + v.y*m.yw + v.z*m.zw + v.w*m.ww;
//        return out;
//    }

    template<typename T> Vector4<T>  operator*(const Matrix4x4<T> m,const Vector4<T> v){
        Vector4<T> out;
        out.x = v.x*m.xx + v.y*m.xy + v.z*m.xz + v.w*m.xw;
        out.y = v.x*m.yx + v.y*m.yy + v.z*m.yz + v.w*m.yw;
        out.z = v.x*m.zx + v.y*m.zy + v.z*m.zz + v.w*m.zw;
        out.w = v.x*m.wx + v.y*m.wy + v.z*m.wz + v.w*m.ww;
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
