#include <AoTK/aotk.h>




namespace AoTK{

Matrix::Matrix(const Matrix &m){
    for(int i = 0; i<16;i++)
        _1d[i] = m._1d[i];
}
Matrix::Matrix(){
    for(int i = 0;i<16;i++)
        _1d[i] = 0;
    xx=1;
    yy=1;
    zz=1;
    ww=1;
}

Matrix::Matrix(float _a[4][4]){
    for(int x = 0;x<4;x++)for(int y = 0;y<4;y++)
        _2d[x][y] = _a[x][y];
}

Matrix& Matrix::operator=(const Matrix &m){
    if(&m == this)
        return *this;
    for(int i = 0; i<16;i++)
        _1d[i] = m._1d[i];
    return *this;
}


Matrix::Matrix(float _a[16]){
    for(int x = 0;x<16;x++)
        _1d[x] = _a[x];
}


bool Matrix::operator==(const Matrix &m){
    for(int i = 0;i<16;i++)
        if(abs(_1d[i] - m._1d[i]) > 0.01)
            return false;
    return true;
}
bool Matrix::operator!=(const Matrix &m){
    for(int i = 0;i<16;i++)
        if(abs(_1d[i] - m._1d[i]) > 0.01)
            return true;
    return false;

}
Matrix &Matrix::operator*=(float f){
    for(int i = 0;i<16;i++)
        _1d[i] *= f;
    return *this;
}

Matrix &Matrix::operator/=(float f){
    for(int i = 0;i<16;i++)
        _1d[i] /= f;
    return *this;
}

Matrix &Matrix::operator+=(float f){
    for(int i = 0;i<16;i++)
        _1d[i] += f;
    return *this;
}

Matrix &Matrix::operator-=(float f){
    for(int i = 0;i<16;i++)
        _1d[i] -= f;
    return *this;
}

Matrix &Matrix::operator*=(const Matrix &m){
    Matrix tmp = *this;
    for(int row = 0;row<4;row++)for(int col = 0;col<4;col++){
        _2d[col][row] = 0;
        for(int i = 0;i<4;i++){
            _2d[col][row] += tmp._2d[i][row] * m._2d[col][i];
        }
    }
    return *this;
}
Matrix &Matrix::operator-=(const Matrix &m){
    for(int i = 0; i<16;i++)
        _1d[i] -= m._1d[i];
    return *this;
}
Matrix &Matrix::operator+=(const Matrix &m){
    for(int i = 0; i<16;i++)
        _1d[i] += m._1d[i];
    return *this;
}
Matrix Matrix::operator/(float f)const{
    Matrix m(*this);
    m /= f;
    return m;
}
Matrix Matrix::operator*(float f)const{
    Matrix m(*this);
    m *= f;
    return m;
}
Matrix Matrix::operator-(float f)const{
    Matrix m(*this);
    m -= f;
    return m;
}
Matrix Matrix::operator+(float f)const{
    Matrix m(*this);
    m += f;
    return m;
}

Matrix Matrix::operator*(const Matrix &_m)const{
    Matrix m(*this);
    m *= _m;
    return m;
}
Matrix Matrix::operator-(const Matrix &_m)const{
    Matrix m(*this);
    m -= _m;
    return m;
}
Matrix Matrix::operator+(const Matrix &_m)const{
    Matrix m(*this);
    m += _m;
    return m;
}

Matrix Matrix::lookAt(Position<> pos,Position<> at,Direction<> up){
    Vector3<> center(pos.x,pos.y,pos.z);
    Vector3<> view_dir;
    view_dir.x = at.x - pos.x;
    view_dir.y = at.y - pos.y;
    view_dir.z = at.z - pos.z;
    view_dir.normalize();

    Vector3<> side = up.cross(view_dir);
    side.normalize();
    up = view_dir.cross(side);
    Matrix m;
    m._2d[0][0] = side.x;
    m._2d[1][0] = side.y;
    m._2d[2][0] = side.z;

    m._2d[0][1] = up.x;
    m._2d[1][1] = up.y;
    m._2d[2][1] = up.z;

    m._2d[0][2]  = -view_dir.x;
    m._2d[1][2]  = -view_dir.y;
    m._2d[2][2]  = -view_dir.z;

    m._2d[3][0]  = -side.dot(center);
    m._2d[3][1]  = -up.dot(center);
    m._2d[3][2]  = view_dir.dot(center);

    return m;
}

Matrix Matrix::perspectiveProjection(float fovy,float asp,float nearPlane,float farPlane){
    float e = 1.0/tan((fovy*0.0174532925/2));
    Matrix m;
    m._2d[0][0] = e;
    m._2d[1][1] = e*asp;
    m._2d[2][2] = -(farPlane+nearPlane)/(farPlane-nearPlane);
    m._2d[3][2] = -(2*farPlane*nearPlane)/(farPlane-nearPlane);
    m._2d[2][3] = -1;
    m._2d[3][3] = 0;
    return m;
}

Matrix Matrix::orthogonalProjection(float left, float right, float bottom, float top, float nearPlane, float farPlane){
    Matrix m;
    m._2d[0][0] = 2.0/(right-left);
    m._2d[1][1] = 2.0/(top-bottom);
    m._2d[2][2] = -2.0/(farPlane-nearPlane);

    m._2d[3][0] = -(right+left)/(right-left);
    m._2d[3][1] = -(top+bottom)/(top-bottom);
    m._2d[3][2] = -(farPlane+nearPlane)/(farPlane-nearPlane);
    return m;
}
Matrix Matrix::rotateX(float deg){
    Matrix m;
    m.yy = cos(deg);
    m.zz = cos(deg);
    m.zy = -sin(deg);
    m.yz = sin(deg);
    return m;
}
Matrix Matrix::rotateY(float deg){
    Matrix m;
    m.xx = cos(deg);
    m.zz = cos(deg);
    m.xz = -sin(deg);
    m.zx = sin(deg);
    return m;
}
Matrix Matrix::rotateZ(float deg){
    Matrix m;
    m.xx = cos(deg);
    m.yy = cos(deg);
    m.yx = -sin(deg);
    m.xy = sin(deg);
    return m;
}
Matrix Matrix::rotateAxis(float deg,float x,float y,float z){
    Matrix m;
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
Matrix Matrix::rotateAxis(float deg,const Vector3<> &v){
    return rotateAxis(deg,v.x,v.y,v.z);
}

Matrix Matrix::translate(float x,float y,float z){
    Matrix m;
    m.wx = x;
    m.wy = y;
    m.wz = z;

    return m;
}
Matrix Matrix::scale(float x,float y,float z){
    Matrix m;
    m.xx = x;
    m.yy = y;
    m.zz = z;
    return m;
}


std::ostream &operator<<(std::ostream &os,const Matrix &m){
    for(int row = 0;row < 4;row++){
        for(int col = 0;col < 4;col++){
            os << m._2d[col][row] << " ";
        }
        os << std::endl;
    }
    return os;
}
Vector4<> operator*(const Matrix &m,const Vector4<> &v){
    Vector4<> V;
    V.x = v.x*m.xx + v.y*m.yx + v.z*m.zx + v.w*m.wx;
    V.y = v.x*m.xy + v.y*m.yy + v.z*m.zy + v.w*m.wy;
    V.z = v.x*m.xz + v.y*m.yz + v.z*m.zz + v.w*m.wz;
    V.w = v.x*m.xw + v.y*m.yw + v.z*m.zw + v.w*m.ww;
    return V;
}
Vector3<> operator*(const Matrix &m,const Vector3<> &v){
    Vector4<> V;
    V.x = v.x;
    V.y = v.y;
    V.z = v.z;
    V.w = 1.0;
    Vector4<> a = m*V;
    return Vector3<>(a.x/a.w,a.y/a.w,a.z/a.w);
}


std::ostream &operator<<(std::ostream &os,const Vector3<> &v){
    os << "[" << v.x << " " << v.y << " " << v.z << "]";
    return os;
}
std::ostream &operator<<(std::ostream &os,const Vector4<> &v){
    os << "[" << v.x << " " << v.y << " " << v.z <<  " " << v.w << "]";
    return os;
}


};
