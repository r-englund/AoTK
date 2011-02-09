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
