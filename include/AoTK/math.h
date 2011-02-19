#ifndef MATH_H
#define MATH_H

#include <cmath>
#include <iostream>

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

#define clamp(a,b,c) (((a) > (c)) ? (c) : (((a) < (b)) ? (b) : (a)))


namespace AoTK{

#define Size2D Vector2

#define Size3D Vector3
#define Direction Vector3

#define Position Vector4
#define Color Vector4

template <typename T = float>
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
    Vector2(T _x = 0.0f,T _y = 0.0f):x(_x),y(_y){}
    void normalize(){
        float l = sqrt(x*x+y*y);
        x /= l;
        y /= l;
    }
};

template <typename T = float>
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
    Vector3<T>(T _x = 0.0f,T _y = 0.0f,T _z = 0.0f):x(_x),y(_y),z(_z){}

    T dot(const Vector3<T> &_v)const{
        return x*_v.x + y*_v.y + z*_v.z;
    }

    Vector3 cross(const Vector3 &_v){
        Vector3 V;
        V.x =  y*_v.z - z*_v.y;
        V.y =-(x*_v.z - z*_v.x);
        V.z =  x*_v.y - y*_v.x;
        return V;
    }

    void normalize(){
        float l = sqrt(x*x+y*y+z*z);
        x /= l;
        y /= l;
        z /= l;
    }
    Vector3 &operator=(Vector3 const &_v){
        if(this == &_v)
            return *this;
        x = _v.x;
        y = _v.y;
        z = _v.z;
        return *this;
    }

    Vector3 &operator+=(Vector3 const &_v){
        x += _v.x;
        y += _v.y;
        z += _v.z;
        return *this;
    }
    Vector3 &operator-=(Vector3 const &_v){
        x -= _v.x;
        y -= _v.y;
        z -= _v.z;
        return *this;
    }
    Vector3 &operator+=(float f){
        x += f;
        y += f;
        z += f;
        return *this;
    }
    Vector3 &operator-=(float f){
        x -= f;
        y -= f;
        z -= f;
        return *this;
    }
    Vector3 &operator*=(float f){
        x *= f;
        y *= f;
        z *= f;
        return *this;
    }
    Vector3 &operator/=(float f){
        x /= f;
        y /= f;
        z /= f;
        return *this;
    }

    Vector3 operator+(Vector3 const &_v)const{
        Vector3 V(v);
        V += *this;
        return V;
    }
    Vector3 operator-(Vector3 const &_v)const{
        Vector3 V(v);
        V -= *this;
        return V;
    }
    Vector3 operator+(float f)const{
        Vector3 V(*this);
        V += f;
        return V;
    }
    Vector3 operator-(float f)const{
        Vector3 V(*this);
        V -= f;
        return V;
    }
    Vector3 operator*(float f)const{
        Vector3 V(*this);
        V *= f;
        return V;
    }
    Vector3 operator/(float f)const{
        Vector3 V(*this);
        V /= f;
        return V;
    }

    bool operator==(Vector3 const &_v)const{
        return (abs(this->x - _v.x) < 0.001 && abs(this->y - _v.y) < 0.001 && abs(this->z - _v.z) < 0.001);
    }
    bool operator!=(Vector3 const &_v)const{
        return !(*this==v);
    }
};

template <typename T = float>
struct Vector4{
    Vector4(T _x = 0.0f,T _y = 0.0f,T _z = 0.0f,T _w = 1.0f):x(_x),y(_y),z(_z),w(_w){}
    union{
        T arr[4];
        struct{
            T x,y,z,w;
        };
        struct{
            T r,g,b,a;
        };
    };
    void normalize3(){
        T l = sqrt(x*x+y*y+z*z);
        x /= l;
        y /= l;
        z /= l;
    }
    void normalize(){
        T l = sqrt(x*x+y*y+z*z+w*w);
        x /= l;
        y /= l;
        z /= l;
        w /= l;
    }
    Vector4<T> &operator=(Vector3<T> const &_v){
        x = _v.x;
        y = _v.y;
        z = _v.z;
        w = _v.w;
    }

    Vector4<T> operator+(Vector4<T> const &_v)const{
        Vector4<T> V(*this);
        V.x += _v.x;
        V.y += _v.y;
        V.z += _v.z;
        V.w += _v.w;
        return V;
    }
    Vector4<T> operator-(Vector4<T> const &_v)const{
        Vector4<T> V(*this);
        V.x -= _v.x;
        V.y -= _v.y;
        V.z -= _v.z;
        V.w -= _v.w;
        return V;
    }
    Vector4<T> operator+(T f)const{
        Vector4<T> V(*this);
        V += f;
        return V;
    }
    Vector4<T> operator-(T f)const{
        Vector4<T> V(*this);
        V -= f;
        return V;
    }
    Vector4<T> operator*(T f)const{
        Vector4<T> V(*this);
        V *= f;
        return V;
    }
    Vector4<T> operator/(T f)const{
        Vector4<T> V(*this);
        V /= f;
        return V;
    }

    Vector4<T> &operator+=(Vector4<T> const &_v){
        x += _v.x;
        y += _v.y;
        z += _v.z;
        w += _v.w;
        return *this;
    }
    Vector4<T> &operator-=(Vector4<T> const &_v){
        x -= _v.x;
        y -= _v.y;
        z -= _v.z;
        w -= _v.w;
        return *this;
    }
    Vector4<T> &operator+=(float f){
        x += f;
        y += f;
        z += f;
        w += f;
        return *this;
    }
    Vector4<T> &operator-=(float f){
        x -= f;
        y -= f;
        z -= f;
        w -= f;
        return *this;
    }
    Vector4<T> &operator*=(float f){
        x *= f;
        y *= f;
        z *= f;
        w *= f;
        return *this;
    }
    Vector4<T> &operator/=(float f){
        x /= f;
        y /= f;
        z /= f;
        w /= f;
        return *this;
    }

    bool operator==(Vector4<T> const &_v)const{ return (abs(this->x - _v.x) < 0.001 && abs(this->y - _v.y) < 0.001 && abs(this->z - _v.z) < 0.001 && abs(this->w - _v.w) < 0.001);}
    bool operator!=(Vector4<T> const &_v)const{ return !(*this == _v);};
};


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

class Matrix{
public:
    union{
        float _1d[16];
        struct{
            float _2d[4][4];
        };
        struct{
            float xx,xy,xz,xw,
                  yx,yy,yz,yw,
                  zx,zy,zz,zw,
                  wx,wy,wz,ww;
        };
    };

    Matrix(float a[16]);
    Matrix(float a[4][4]);
    Matrix();
    Matrix(const Matrix &m);
    virtual ~Matrix(){}

    Matrix operator+(const Matrix &m) const;
    Matrix operator-(const Matrix &m) const;
    Matrix operator*(const Matrix &m) const;
    Matrix operator+(float f) const;
    Matrix operator-(float f) const;
    Matrix operator*(float f) const;
    Matrix operator/(float f) const;

    Matrix &operator=(const Matrix &m);

    Matrix &operator+=(const Matrix &m);
    Matrix &operator-=(const Matrix &m);
    Matrix &operator*=(const Matrix &m);
    Matrix &operator+=(float f);
    Matrix &operator-=(float f);
    Matrix &operator*=(float f);
    Matrix &operator/=(float f);

    bool operator==(const Matrix &m);
    bool operator!=(const Matrix &m);


    static Matrix perspectiveProjection(float fovy,float aspc,float near,float far);
    static Matrix orthogonalProjection(float left, float right, float bottom, float top, float near, float far);
    static Matrix lookAt(Position<> pos,Position<> at,Direction<> up);

    static Matrix rotateX(float deg);
    static Matrix rotateY(float deg);
    static Matrix rotateZ(float deg);
    static Matrix rotateAxis(float deg,float x,float y,float z);
    static Matrix rotateAxis(float deg,const Vector3<> &_v);

    static Matrix translate(float x,float y,float z);
    static Matrix scale(float x,float y,float z);

    friend std::ostream &operator<<(std::ostream &os,const Matrix &m);
};

Vector4<> operator*(const Matrix &m,const Vector4<> &_v);
Vector3<> operator*(const Matrix &m,const Vector3<> &_v);

std::ostream &operator<<(std::ostream &os,const Vector3<> &_v);
std::ostream &operator<<(std::ostream &os,const Vector4<> &_v);

};
#endif
