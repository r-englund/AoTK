#ifndef _AOTK_MATRIX4X4_HPP_
#define _AOTK_MATRIX4x4_HPP_

namespace AoTK{
namespace Math{

template<typename T> struct mat16{
    T _1d[16];
};
template<typename T> struct mat4x4{
    T _2d[4][4];
};

/*********
*
*
*
* _2d[col][row]
*
* _1d[id]
*
*
**********/
    template<typename T>
    struct Matrix4x4{
        union{
            T _1d[16];
            struct{
                T _2d[4][4];
            };
            mat4x4<T> _mat4x4;
            mat16<T> _mat16;
        };


        Matrix4x4(mat4x4<T> _mat4x4):_mat4x4(_mat4x4){}
        Matrix4x4(mat16<T> _mat16):_mat16(_mat16){}
        Matrix4x4(T a,T b,T c,T d,
                  T e,T f,T g,T h,
                  T i,T j,T k,T l,
                  T m,T n,T o,T p){
            _1d[0] = a;
            _1d[1] = b;
            _1d[2] = c;
            _1d[3] = d;
            _1d[4] = e;
            _1d[5] = f;
            _1d[6] = g;
            _1d[7] = h;
            _1d[8] = i;
            _1d[9] = j;
            _1d[10] = k;
            _1d[11] = l;
            _1d[12] = m;
            _1d[13] = n;
            _1d[14] = o;
            _1d[15] = p;
        }
        Matrix4x4(T a[16]){
            for(int i = 0;i<16;i++)
                _1d[i] = a[i];
        }
        Matrix4x4(T a[4][4]){
            for(int i = 0;i<4;i++)for(int j = 0;j<4;j++)
                _2d[i][j] = a[i][j];
        }
        Matrix4x4(){
            for(int i = 0;i<16;i++)
                _1d[i] = 0;
            _2d[0][0] = 1;
            _2d[1][1] = 1;
            _2d[2][2] = 1;
            _2d[3][3] = 1;
        }
        Matrix4x4(const Matrix4x4 &m){
            for(int i = 0;i<16;i++)
                _1d[i] = m._1d[i];
        }
        virtual ~Matrix4x4(){}

        Matrix4x4 transpose(){
            return {toOpenGLMatrix()};
        }

        mat16<T> toOpenGLMatrix()const{
            mat16<T> t = {_1d[0],_1d[4],_1d[8],_1d[12],
                       _1d[1],_1d[5],_1d[9],_1d[13],
                       _1d[2],_1d[6],_1d[10],_1d[14],
                       _1d[3],_1d[7],_1d[11],_1d[15]};
            return t;
        }

        T det(){
            return determinant();
        }

        T determinant(){
            T d = 0.0;
            for(int i = 0;i<4;i++){
                T p[9];
                int j = 0;
                for(int row = 1;row<4;row++)for(int col = 0;col<4;col++)if(col!=i){
                    p[j++] = _2d[row][col];
                }
                d+=((p[0]*p[4]*p[8])
                   +(p[1]*p[5]*p[6])
                   +(p[2]*p[3]*p[7])
                   -(p[2]*p[4]*p[6])
                   -(p[5]*p[7]*p[0])
                   -(p[1]*p[3]*p[8])
                   )*_2d[0][i]*((i%2)?1:-1);
            }
            //TODO test this
            return d;
        }

        Matrix4x4 operator+(const Matrix4x4  &m) const{
            auto M = *this;
            for(int i = 0;i<16;i++)
                M._1d[i] += m._1d[i];
            return M;
        }
        Matrix4x4 operator-(const Matrix4x4  &m) const{
            auto M = *this;
            for(int i = 0;i<16;i++)
                M._1d[i] -= m._1d[i];
            return M;
        }
        Matrix4x4 operator*(const Matrix4x4  &m) const{
            Matrix4x4 M;
            for(int row = 0;row < 4;row++)for(int col = 0;col < 4;col++){
                M._2d[row][col] = 0;
                for(int i = 0;i<4;i++){
                    M._2d[row][col] = this->_2d[row][i] * m._2d[i][col];
                }
            }
            return M;
        }
        Matrix4x4 operator+(T f) const{
            auto M = *this;
            for(int i = 0;i<16;i++)
                M._1d[i] += f;
            return M;
        }
        Matrix4x4 operator-(T f) const{
            auto M = *this;
            for(int i = 0;i<16;i++)
                M._1d[i] -= f;
            return M;
        }
        Matrix4x4 operator*(T f) const{
            auto M = *this;
            for(int i = 0;i<16;i++)
                M._1d[i] *= f;
            return M;
        }
        Matrix4x4 operator/(T f) const{
            auto M = *this;
            for(int i = 0;i<16;i++)
                M._1d[i] /= f;
            return M;
        }

        Matrix4x4 &operator=(const Matrix4x4  &m){
            for(int i = 0;i<16;i++)
                _1d[i] = m._1d[i];
            return *this;
        }

        Matrix4x4 &operator+=(const Matrix4x4  &m){
            for(int i = 0;i<16;i++)
                _1d[i] += m._1d[i];
            return *this;
        }
        Matrix4x4 &operator-=(const Matrix4x4  &m){
            for(int i = 0;i<16;i++)
                _1d[i] -= m._1d[i];
            return *this;
        }
        Matrix4x4 &operator*=(const Matrix4x4  &m){
            *this = *this * m;
        }
        Matrix4x4 &operator+=(T f){
            for(int i = 0;i<16;i++)
                _1d[i] += f;
            return *this;
        }
        Matrix4x4 &operator-=(T f){
            for(int i = 0;i<16;i++)
                _1d[i] -= f;
            return *this;
        }
        Matrix4x4 &operator*=(T f){
            for(int i = 0;i<16;i++)
                _1d[i] *= f;
            return *this;
        }
        Matrix4x4 &operator/=(T f){
            for(int i = 0;i<16;i++)
                _1d[i] /= f;
            return *this;
        }

        bool operator==(const Matrix4x4<T>  &m){
            for(int i = 0;i<16;i++)
                if(_1d[i] != m._1d[i])
                    return false;
            return true;
        }
        bool operator!=(const Matrix4x4<T> &m){
            return !(*this==m);
        }

        static Matrix4x4 perspectiveProjection(T fovy,T aspc,T nearPlane,T farPlane){
                T e = 1.0/tan((fovy*0.0174532925/2));
                Matrix4x4<T> m;
                m._2d[0][0] = e;
                m._2d[1][1] = e*aspc;
                m._2d[2][2] = -(farPlane+nearPlane)/(farPlane-nearPlane);
                m._2d[2][3] = -(2*farPlane*nearPlane)/(farPlane-nearPlane);
                m._2d[3][2] = -1;
                m._2d[3][3] = 0;
                return m;
        }
        static Matrix4x4 orthogonalProjection(T left, T right, T bottom, T top, T nearPlane, T farPlane){
                Matrix4x4<T> m;
                m._2d[0][0] = 2.0/(right-left);
                m._2d[1][1] = 2.0/(top-bottom);
                m._2d[2][2] = -2.0/(farPlane-nearPlane);

                m._2d[0][3] = -(right+left)/(right-left);
                m._2d[1][3] = -(top+bottom)/(top-bottom);
                m._2d[2][3] = -(farPlane+nearPlane)/(farPlane-nearPlane);
                return m;
        }
        static Matrix4x4 lookAt(Vector3<T> pos,Vector3<T> at,Vector3<T> up){
            Vector3<T> center(pos);
            Vector3<T> view_dir = at - pos;
            view_dir.normalize();

            Vector3<T> side = up.cross(view_dir);
            side.normalize();
            up = view_dir.cross(side);
            Matrix4x4<T> m;

            m._2d[0][0] = side.x;
            m._2d[0][1] = side.y;
            m._2d[0][2] = side.z;

            m._2d[1][0] = up.x;
            m._2d[1][1] = up.y;
            m._2d[1][2] = up.z;

            m._2d[2][0]  = view_dir.x;
            m._2d[2][1]  = view_dir.y;
            m._2d[2][2]  = view_dir.z;

            m._2d[0][3]  = -side.dot(center);
            m._2d[1][3]  = -up.dot(center);
            m._2d[2][3]  = -view_dir.dot(center);

            return m;
        }

        static Matrix4x4 rotateX(T deg){
            Matrix4x4 m;
            m._2d[1][1] = cos(deg);
            m._2d[1][2] = sin(deg);
            m._2d[2][1] = -sin(deg);
            m._2d[2][2] = cos(deg);
            return m;
        }
        static Matrix4x4 rotateY(T deg){
            Matrix4x4 m;
            m._2d[0][0] = cos(deg);
            m._2d[0][2] = -sin(deg);
            m._2d[2][0] = sin(deg);
            m._2d[2][2] = cos(deg);
            return m;
        }
        static Matrix4x4 rotateZ(T deg){
            Matrix4x4 m;
            m._2d[0][0] = cos(deg);
            m._2d[0][1] = sin(deg);
            m._2d[1][0] = -sin(deg);
            m._2d[1][1] = cos(deg);
            return m;
        }
        static Matrix4x4 rotateAxis(T deg,T x,T y,T z){
        Matrix4x4<T> m;
        float c = cos(deg);
        float s = sin(deg);
        float t = 1.0- c;

        m._2d[0][0] = t*x*x+c;      m._2d[0][1] = t*x*y+s*z;    m._2d[0][2] = t*x*z-s*y;    m._2d[0][3] = 0;
        m._2d[1][0] = t*x*y-s*z;    m._2d[1][1] = t*y*y+c;      m._2d[1][2] = t*y*z+s*x;    m._2d[1][3] = 0;
        m._2d[2][0] = t*x*y+s*y;    m._2d[2][1] = t*y*z-s*x;     m._2d[2][2] = t*z*z+c;     m._2d[2][3] = 0;
        m._2d[3][0] = 0;m._2d[3][1] = 0;m._2d[3][2] = 0;m._2d[3][3] = 1;



        return m;
}
        static Matrix4x4 rotateAxis(T deg,const Vector3<T> &_v){
            return rotateAxis(deg,_v.x,_v.y,_v.z);
        }

        static Matrix4x4 translate(T x,T y,T z){
            Matrix4x4 m;
            m._2d[0][3] = x;
            m._2d[1][3] = y;
            m._2d[2][3] = z;
            return m;
        }
        static Matrix4x4 scale(T x,T y,T z){
            Matrix4x4 m;
            m._2d[0][0] = x;
            m._2d[1][1] = y;
            m._2d[2][2] = z;
            return m;
        }
        static Matrix4x4 scale(T x){
            return scale(x,x,x);
        }
        #ifdef GL_MODELVIEW_MATRIX
        static Matrix4x4 fromCurrentModelViewGLMatrix();
        static Matrix4x4 fromCurrentProjectionGLMatrix();
        static Matrix4x4 fromCurrentTextureGLMatrix();
        #endif
    };

template<typename T> std::ostream &operator<<(std::ostream &os,const Matrix4x4<T> &m){
    for(int row = 0;row < 4;row++){
        for(int col = 0;col < 4;col++){
            os << m._2d[row][col] << " ";
        }
        os << std::endl;
    }
    return os;
}
















};
};

#endif
