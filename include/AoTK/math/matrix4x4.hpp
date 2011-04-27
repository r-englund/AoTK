
namespace AoTK{

template<typename T> Matrix4x4<T>::Matrix4x4(T a[16]){
    for(int i = 0;i<16;i++){
        _1d[i] = a[i];
    }
}
template<typename T> Matrix4x4<T>::Matrix4x4(T _a[4][4]){
    for(int a = 0;a<4;a++)for(int b = 0;b<4;b++){
        _2d[a][b] = _a[a][b];
    }
}
template<typename T> Matrix4x4<T>::Matrix4x4(){
    for(int i = 0;i<16;i++){
        _1d[i] = 0;
    }
    _2d[0][0] = 1;
    _2d[1][1] = 1;
    _2d[2][2] = 1;
    _2d[3][3] = 1;
}

template<typename T> /*template<typename T2>*/ Matrix4x4<T>::Matrix4x4(const Matrix4x4<T>  &m)
//    :_1d(_1d)
{
    for(int i = 0;i<16;i++){
        _1d[i] = m._1d[i];
    }
}

template<typename T> Matrix4x4<T> Matrix4x4<T>::operator+(const Matrix4x4<T> &_m) const{
    Matrix4x4<T> m(*this);
    for(int i = 0;i<16;i++){
        m._1d[i] += _m._1d[i];
    }
    return m;
}
template<typename T> Matrix4x4<T> Matrix4x4<T>::operator-(const Matrix4x4<T> &_m) const{
    Matrix4x4<T> m(*this);
    for(int i = 0;i<16;i++){
        m._1d[i] -= _m._1d[i];
    }
    return m;
}
template<typename T> Matrix4x4<T> Matrix4x4<T>::operator*(const Matrix4x4<T> &_m) const{
    Matrix4x4 m(*this);
    m *= _m;
    return m;
}
template<typename T> Matrix4x4<T> Matrix4x4<T>::operator+(T f) const{
    Matrix4x4<T> m(*this);
    for(int i = 0;i<16;i++){
        m._1d[i] += f;
    }
    return m;
}
template<typename T> Matrix4x4<T> Matrix4x4<T>::operator-(T f) const{
    Matrix4x4<T> m(*this);
    for(int i = 0;i<16;i++){
        m._1d[i] -= f;
    }
    return m;
}
template<typename T> Matrix4x4<T> Matrix4x4<T>::operator*(T f) const{
    Matrix4x4<T> m(*this);
    for(int i = 0;i<16;i++){
        m._1d[i] *= f;
    }
    return m;
}
template<typename T> Matrix4x4<T> Matrix4x4<T>::operator/(T f) const{
    Matrix4x4<T> m(*this);
    for(int i = 0;i<16;i++){
        m._1d[i] /= f;
    }
    return m;
}

template<typename T> Matrix4x4<T>& Matrix4x4<T>::operator=(const Matrix4x4<T> &m){
    for(int i = 0;i<16;i++){
        _1d[i] = m._1d[i];
    }
    return *this;
}

template<typename T> Matrix4x4<T>& Matrix4x4<T>::operator+=(const Matrix4x4<T> &m){
    for(int i = 0;i<16;i++){
        _1d[i] += m._1d[i];
    }
    return *this;
}
template<typename T> Matrix4x4<T>& Matrix4x4<T>::operator-=(const Matrix4x4<T> &m){
    for(int i = 0;i<16;i++){
        _1d[i] -= m._1d[i];
    }
    return *this;
}
template<typename T> Matrix4x4<T>& Matrix4x4<T>::operator*=(const Matrix4x4<T> &m){
    Matrix4x4 tmp(*this);
    for(int row = 0;row<4;row++)for(int col = 0;col<4;col++){
        _2d[col][row] = 0;
        for(int i = 0;i<4;i++){
            _2d[col][row] += tmp._2d[i][row] * m._2d[col][i];
        }
    }
    return *this; //TODO test this
}
template<typename T> Matrix4x4<T>& Matrix4x4<T>::operator+=(T f){
    for(int i = 0;i<16;i++){
        _1d[i] +=f;
    }
    return *this;
}
template<typename T> Matrix4x4<T>& Matrix4x4<T>::operator-=(T f){
    for(int i = 0;i<16;i++){
        _1d[i] -=f;
    }
    return *this;
}
template<typename T> Matrix4x4<T>& Matrix4x4<T>::operator*=(T f){
    for(int i = 0;i<16;i++){
        _1d[i] *=f;
    }
    return *this;
}
template<typename T> Matrix4x4<T>& Matrix4x4<T>::operator/=(T f){
    for(int i = 0;i<16;i++){
        _1d[i] /=f;
    }
    return *this;
}

template<typename T> bool Matrix4x4<T>::operator==(const Matrix4x4<T> &m){
    for(int i = 0;i<16;i++){
        if(_1d[i] != m._1d[i])
            return false;
    }
    return true;
}
template<typename T> bool Matrix4x4<T>::operator!=(const Matrix4x4<T> &m){return !(*this == m);}

template<typename T> Matrix4x4<T> Matrix4x4<T>::perspectiveProjection(T fovy,T aspc,T nearPlane,T farPlane){
    T e = 1.0/tan((fovy*0.0174532925/2));
    Matrix4x4<T> m;
    m._2d[0][0] = e;
    m._2d[1][1] = e*aspc;
    m._2d[2][2] = -(farPlane+nearPlane)/(farPlane-nearPlane);
    m._2d[3][2] = -(2*farPlane*nearPlane)/(farPlane-nearPlane);
    m._2d[2][3] = -1;
    m._2d[3][3] = 0;
    return m;
}

template<typename T> Matrix4x4<T> Matrix4x4<T>::orthogonalProjection(T left, T right, T bottom, T top, T nearPlane, T farPlane){
    Matrix4x4<T> m;
    m._2d[0][0] = 2.0/(right-left);
    m._2d[1][1] = 2.0/(top-bottom);
    m._2d[2][2] = -2.0/(farPlane-nearPlane);

    m._2d[3][0] = -(right+left)/(right-left);
    m._2d[3][1] = -(top+bottom)/(top-bottom);
    m._2d[3][2] = -(farPlane+nearPlane)/(farPlane-nearPlane);
    return m;
}

template<typename T> Matrix4x4<T> Matrix4x4<T>::lookAt(Vector3<T> pos,Vector3<T> at,Vector3<T> up){
    Vector3<T> center(pos);
    Vector3<T> view_dir = at - pos;
    view_dir.normalize();

    Vector3<T> side = up.cross(view_dir);
    side.normalize();
    up = view_dir.cross(side);
    Matrix4x4<T> m;

    m._2d[0][0] = side.x;
    m._2d[1][0] = side.y;
    m._2d[2][0] = side.z;

    m._2d[0][1] = up.x;
    m._2d[1][1] = up.y;
    m._2d[2][1] = up.z;

    m._2d[0][2]  = view_dir.x;
    m._2d[1][2]  = view_dir.y;
    m._2d[2][2]  = view_dir.z;

    m._2d[3][0]  = -side.dot(center);
    m._2d[3][1]  = -up.dot(center);
    m._2d[3][2]  = -view_dir.dot(center);

    return m;
}

template<typename T> Matrix4x4<T> Matrix4x4<T>::rotateX(T deg){
    Matrix4x4<T> m;
    m.yy = cos(deg);
    m.zz = cos(deg);
    m.zy = -sin(deg);
    m.yz = sin(deg);
    return m;
}

template<typename T> Matrix4x4<T> Matrix4x4<T>::rotateY(T deg){
    Matrix4x4<T> m;
    m.xx = cos(deg);
    m.zz = cos(deg);
    m.xz = -sin(deg);
    m.zx = sin(deg);
    return m;
}

template<typename T> Matrix4x4<T> Matrix4x4<T>::rotateZ(T deg){
    Matrix4x4<T> m;
    m.xx = cos(deg);
    m.yy = cos(deg);
    m.yx = -sin(deg);
    m.xy = sin(deg);
    return m;
}
template<typename T> Matrix4x4<T> Matrix4x4<T>::rotateAxis(T deg,T x,T y,T z){
    Matrix4x4<T> m;
    float c = cos(deg);
    float s = sin(deg);
    m.xx = c+x*x*(1-c);
    m.yx = x*y*(1-c)-z*s;
    m.zx = x*z*(1-c)-y*s;

    m.xy = y*x*(1-c)+z*s;
    m.yy = c+y*y*(1-c);
    m.zy = y*z*(1-c)-x*s;

    m.xz = z*x*(1-c)-y*s;
    m.yz = z*y*(1-c)+z*s;
    m.zz = c+z*z*(1-c);

    return m;
}
template<typename T> Matrix4x4<T> Matrix4x4<T>::rotateAxis(T deg,const Vector3<T> &_v){
    return rotateAxis(deg,_v.x,_v.y,_v.z);
}

template<typename T> Matrix4x4<T> Matrix4x4<T>::translate(T x,T y,T z){
    Matrix4x4<T> m;
    m.wx = x;
    m.wy = y;
    m.wz = z;

    return m;
}
template<typename T> Matrix4x4<T> Matrix4x4<T>::scale(T x,T y,T z){
    Matrix4x4<T> m;
    m.xx = x;
    m.yy = y;
    m.zz = z;
    return m;
}

template<typename T> std::ostream &operator<<(std::ostream &os,const Matrix4x4<T> &m){
    for(int row = 0;row < 4;row++){
        for(int col = 0;col < 4;col++){
            os << m._2d[col][row] << " ";
        }
        os << std::endl;
    }
    return os;
}














};
