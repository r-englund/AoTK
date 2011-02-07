#ifndef MATH_H
#define MATH_H

namespace AoTK{

#define Size2D Vector2

#define Size3D Vector3
#define Direction Vector3

#define Position Vector4
#define Color Vector4


struct Vector2{
    union{
        float f[2];
        struct{
            float x,y;
        };
        struct{
            float u,v;
        };
        struct{
            float w,h;
        };
    };
    Vector2(float _x = 0.0f,float _y = 0.0f):x(_x),y(_y){}
};
struct Vector3{
    union{
        float f[3];
        struct{
            float x,y,z;
        };
        struct{
            float u,v,s;
        };
        struct{
            float w,h,d;
        };
        struct{
            float r,g,b;
        };
    };
    Vector3(float _x = 0.0f,float _y = 0.0f,float _z = 0.0f):x(_x),y(_y),z(_z){}
};
struct Vector4{
    Vector4(float _x = 0.0f,float _y = 0.0f,float _z = 0.0f,float _w = 1.0f):x(_x),y(_y),z(_z),w(_w){}
    union{
        float f[4];
        struct{
            float x,y,z,w;
        };
        struct{
            float r,g,b,a;
        };
    };
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

    static Matrix rotateX(float deg);
    static Matrix rotateY(float deg);
    static Matrix rotateZ(float deg);
    static Matrix rotateAxis(float deg,float x,float y,float z);
    static Matrix rotateAxis(float deg,const Vector3 &v);

    static Matrix translate(float x,float y,float z);
    static Matrix scale(float x,float y,float z);

    friend std::ostream &operator<<(std::ostream &os,const Matrix &m);
};

};
#endif
