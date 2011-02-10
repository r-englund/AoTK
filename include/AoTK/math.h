#ifndef MATH_H
#define MATH_H

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



namespace AoTK{

#define Size2D Vector2

#define Size3D Vector3
#define Direction Vector3

#define Position Vector4
#define Color Vector4


struct Vector2{
    union{
        float arr[2];
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
    void normalize(){
        float l = sqrt(x*x+y*y);
        x /= l;
        y /= l;
    }
};
struct Vector3{
    union{
        float arr[3];
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

    float dot(const Vector3 &v)const{
        return x*v.x + y*v.y + z*v.z;
    }

    Vector3 cross(const Vector3 &v){
        Vector3 V;
        V.x =  y*v.z - z*v.y;
        V.y =-(x*v.z - z*v.x);
        V.z =  x*v.y - y*v.x;
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

    Vector3 &operator+=(Vector3 const &v){
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }
    Vector3 &operator-=(Vector3 const &v){
        x -= v.x;
        y -= v.y;
        z -= v.z;
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

    Vector3 operator+(Vector3 const &v)const{
        Vector3 V(v);
        V += *this;
        return V;
    }
    Vector3 operator-(Vector3 const &v)const{
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

    bool operator==(Vector3 const &v)const{
        return (this->x == v.x && this->y == v.y && this->z == v.z);
    }
    bool operator!=(Vector3 const &v)const{
        return !(*this==v);
    }
};
struct Vector4{
    Vector4(float _x = 0.0f,float _y = 0.0f,float _z = 0.0f,float _w = 1.0f):x(_x),y(_y),z(_z),w(_w){}
    union{
        float arr[4];
        struct{
            float x,y,z,w;
        };
        struct{
            float r,g,b,a;
        };
    };
    void normalize3(){
        float l = sqrt(x*x+y*y+z*z);
        x /= l;
        y /= l;
        z /= l;
    }
    void normalize(){
        float l = sqrt(x*x+y*y+z*z+w*w);
        x /= l;
        y /= l;
        z /= l;
        w /= l;
    }
    Vector4 &operator=(Vector3 const &v){
        x = v.x;
        y = v.y;
        z = v.z;
        w = v.w;
    }

    Vector4 operator+(Vector4 const &v)const{
        Vector4 V(*this);
        V.x += v.x;
        V.y += v.y;
        V.z += v.z;
        V.w += v.w;
        return V;
    }
    Vector4 operator-(Vector4 const &v)const{
        Vector4 V(*this);
        V.x -= v.x;
        V.y -= v.y;
        V.z -= v.z;
        V.w -= v.w;
        return V;
    }
    Vector4 operator+(float f)const{
        Vector4 V(*this);
        V += f;
        return V;
    }
    Vector4 operator-(float f)const{
        Vector4 V(*this);
        V -= f;
        return V;
    }
    Vector4 operator*(float f)const{
        Vector4 V(*this);
        V *= f;
        return V;
    }
    Vector4 operator/(float f)const{
        Vector4 V(*this);
        V /= f;
        return V;
    }

    Vector4 &operator+=(Vector4 const &v){
        x += v.x;
        y += v.y;
        z += v.z;
        w += v.w;
        return *this;
    }
    Vector4 &operator-=(Vector4 const &v){
        x -= v.x;
        y -= v.y;
        z -= v.z;
        w -= v.w;
        return *this;
    }
    Vector4 &operator+=(float f){
        x += f;
        y += f;
        z += f;
        w += f;
        return *this;
    }
    Vector4 &operator-=(float f){
        x -= f;
        y -= f;
        z -= f;
        w -= f;
        return *this;
    }
    Vector4 &operator*=(float f){
        x *= f;
        y *= f;
        z *= f;
        w *= f;
        return *this;
    }
    Vector4 &operator/=(float f){
        x /= f;
        y /= f;
        z /= f;
        w /= f;
        return *this;
    }

    bool operator==(Vector4 const &v)const{ return (this->x == v.x && this->y == v.y && this->z == v.z && this->w == v.w);}
    bool operator!=(Vector4 const &v)const{ return !(*this == v);};
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
    static Matrix lookAt(Position pos,Position at,Direction up);

    static Matrix rotateX(float deg);
    static Matrix rotateY(float deg);
    static Matrix rotateZ(float deg);
    static Matrix rotateAxis(float deg,float x,float y,float z);
    static Matrix rotateAxis(float deg,const Vector3 &v);

    static Matrix translate(float x,float y,float z);
    static Matrix scale(float x,float y,float z);

    friend std::ostream &operator<<(std::ostream &os,const Matrix &m);
};

Vector4 operator*(const Matrix &m,const Vector4 &v);
Vector3 operator*(const Matrix &m,const Vector3 &v);

std::ostream &operator<<(std::ostream &os,const Vector3 &v);
std::ostream &operator<<(std::ostream &os,const Vector4 &v);

};
#endif
