#ifndef _AOTK_VECTOR3_HPP_
#define _AOTK_VECTOR3_HPP_
namespace AoTK{
namespace Math{

template<typename T> Vector3<T>::Vector3(T _x,T _y, T _z):x(_x),y(_y),z(_z){}
template<typename T> Vector3<T>::Vector3():x(0),y(0),z(0){}
template<typename T> template<typename T2> Vector3<T>::Vector3(const Vector3<T2> &V):x(V.x),y(V.y),z(V.z){}

template<typename T>
template<typename T2>
T Vector3<T>::dot(const Vector3<T2> &V)const{
    return x*V.x+y*V.y+z*V.z;
}

template<typename T>
template<typename T2>
Vector3<T> Vector3<T>::cross(const Vector3<T2> &V)const{
    Vector3<T> _v;
    _v.x = y*V.z-z*V.y;
    _v.y = 0-x*V.z+z*V.x;
    _v.z = x*V.y-y*V.x;
    return _v;
}
#include <assert.h>
template<typename T> inline void Vector3<T>::normalize(){
    float l = sqrt(x*x+y*y+z*z);
    if(floatCMP(l,0)||floatCMP(l,1))
        return;
    x /= l;
    y /= l;
    z /= l;
}

template<typename T> inline T Vector3<T>::getLength()const{
    return sqrt(x*x+y*y+z*z);
}

template<typename T>
template<typename T2> inline Vector3<T> Vector3<T>::operator+(const Vector3<T2> &V)const{
    Vector3<T> _v(V);
    _v.x += x;
    _v.y += y;
    _v.z += z;
    return _v;
}
template<typename T>
template<typename T2> inline Vector3<T> Vector3<T>::operator-(const Vector3<T2> &V)const{
    Vector3<T> _v(V);
    _v.x -= x;
    _v.y -= y;
    _v.z -= z;
    return _v;
}
template<typename T>
template<typename T2> inline Vector3<T> Vector3<T>::operator+(T2 t)const{
    Vector3<T> _v(*this);
    _v.x += t;
    _v.y += t;
    _v.z += t;
    return _v;
}
template<typename T>
template<typename T2> inline Vector3<T> Vector3<T>::operator-(T2 t)const{
    Vector3<T> _v(*this);
    _v.x -= t;
    _v.y -= t;
    _v.z -= t;
    return _v;
}
template<typename T>
template<typename T2> inline Vector3<T> Vector3<T>::operator*(T2 t)const{
    Vector3<T> _v(*this);
    _v.x *= t;
    _v.y *= t;
    _v.z *= t;
    return _v;
}
template<typename T>
template<typename T2> inline Vector3<T> Vector3<T>::operator/(T2 t)const{
    Vector3<T> _v(*this);
    _v.x /= t;
    _v.y /= t;
    _v.z /= t;
    return _v;
}

template<typename T>
template<typename T2> inline Vector3<T>& Vector3<T>::operator+=(const Vector3<T2> &V){
    x+=V.x;
    y+=V.y;
    z+=V.z;
    return *this;
}
template<typename T>
template<typename T2> inline Vector3<T>& Vector3<T>::operator-=(const Vector3<T2> &V){
    x-=V.x;
    y-=V.y;
    z-=V.z;
    return *this;
}
template<typename T>
template<typename T2> inline Vector3<T>& Vector3<T>::operator+=(T2 t){
    x+=t;
    y+=t;
    z+=t;
    return *this;
}
template<typename T>
template<typename T2> inline Vector3<T>& Vector3<T>::operator-=(T2 t){
    x-=t;
    y-=t;
    z-=t;
    return *this;
}
template<typename T>
template<typename T2> inline Vector3<T>& Vector3<T>::operator*=(T2 t){
    x*=t;
    y*=t;
    z*=t;
    return *this;
}
template<typename T>
template<typename T2> inline Vector3<T>& Vector3<T>::operator/=(T2 t){
    x/=t;
    y/=t;
    z/=t;
    return *this;
}

template<typename T>
template<typename T2> inline bool Vector3<T>::operator==(const Vector3<T2> &V)const{return x==V.x && y ==V.y && z ==V.z;}
template<typename T>
template<typename T2> inline bool Vector3<T>::operator!=(const Vector3<T2> &V)const{return x!=V.x || y !=V.y || z !=V.z;}


template<typename T>
template<typename T2> inline bool Vector3<T>::operator>(const Vector3<T2> &m)const{
    return getLength() > m.getLength();
}
template<typename T>
template<typename T2> inline bool Vector3<T>::operator<(const Vector3<T2> &m)const{
    return getLength() < m.getLength();
}
template<typename T>
template<typename T2> inline bool Vector3<T>::operator<=(const Vector3<T2> &m)const{
    return getLength() <= m.getLength();
}
template<typename T>
template<typename T2> inline bool Vector3<T>::operator>=(const Vector3<T2> &m)const{
    return getLength() >= m.getLength();
}


//template<typename T>
//std::ostream &operator<<(std::ostream &os,const Vector3<T> &V){
//    os <<"["<< V.x << " " << V.y << " " << V.z << "]";
//    return os;
//}
//
//template<>
//std::ostream &operator<<(std::ostream &os,const Vector3<int8_t> &V){
//    os <<"["<< (int)V.x << " " << (int)V.y << " " << (int)V.z << "]";
//    return os;
//}
//
//template<>
//std::ostream &operator<<(std::ostream &os,const Vector3<uint8_t> &V){
//    os <<"["<< (int)V.x << " " << (int)V.y << " " << (int)V.z << "]";
//    return os;
//}

//
//template<typename T,typename T2> Vector3<T> operator*(T2 t,const Vector3<T> &v){
//    Vector3<T> V(v);
//    V*=t;
//    return V;
//}
//template<typename T,typename T2> Vector3<T> operator+(T2 t,const Vector3<T> &v){
//    Vector3<T> V(v);
//    V+=t;
//    return V;
//}
//template<typename T,typename T2> Vector3<T> operator-(T2 t,const Vector3<T> &v){
//    Vector3<T> V(v);
//    V-=t;
//    return V;
//}
//template<typename T,typename T2> Vector3<T> operator/(T2 t,const Vector3<T> &v){
//    Vector3<T> V(v);
//    V/=t;
//    return V;
//}


};
};
#endif
