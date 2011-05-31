#ifndef _AOTK_VECTOR4_HPP_
#define _AOTK_VECTOR4_HPP_

namespace AoTK{
namespace Math{

template<typename T> Vector4<T>::Vector4(T _x,T _y,T _z,T _w){
    x = _x;
    y = _y;
    z = _z;
    w = _w;
};
template<typename T> Vector4<T>::Vector4(){
    x = 0;
    y = 0;
    z = 0;
    w = 0;
}
template<typename T> template<typename T2> Vector4<T>::Vector4(const Vector4<T2> &v){
    x = v.x;
    y = v.y;
    z = v.z;
    w = v.w;
}

template<typename T>
template<typename T2>
T Vector4<T>::dot(const Vector4<T2> &v)const{
    return x*v.x+y*v.y+z*v.z+w*v.w;
}

template<typename T> inline void Vector4<T>::normalize(){
    float l = sqrt(x*x+y*y+z*z+w*w);
    x /= l;
    y /= l;
    z /= l;
    w /= l;
}

template<typename T> inline T Vector4<T>::getLength()const{
    return sqrt(x*x+y*y+z*z+w*w);
}

template<typename T>
template<typename T2> inline Vector4<T> Vector4<T>::operator+(const Vector4<T2> &v)const{
    Vector4<T> _v(v);
    _v.x += x;
    _v.y += y;
    _v.z += z;
    _v.w += w;
    return _v;
}
template<typename T>
template<typename T2> inline Vector4<T> Vector4<T>::operator-(const Vector4<T2> &v)const{
    Vector4<T> _v(v);
    _v.x -= x;
    _v.y -= y;
    _v.z -= z;
    _v.w -= w;
    return _v;
}
template<typename T>
template<typename T2> inline Vector4<T> Vector4<T>::operator+(T2 t)const{
    Vector4<T> _v(*this);
    _v.x += t;
    _v.y += t;
    _v.z += t;
    _v.w += t;
    return _v;
}
template<typename T>
template<typename T2> inline Vector4<T> Vector4<T>::operator-(T2 t)const{
    Vector4<T> _v(*this);
    _v.x -= t;
    _v.y -= t;
    _v.z -= t;
    _v.w -= t;
    return _v;
}
template<typename T>
template<typename T2> inline Vector4<T> Vector4<T>::operator*(T2 t)const{
    Vector4<T> _v(*this);
    _v.x *= t;
    _v.y *= t;
    _v.z *= t;
    _v.w *= t;
    return _v;
}
template<typename T>
template<typename T2> inline Vector4<T> Vector4<T>::operator/(T2 t)const{
    Vector4<T> _v(*this);
    _v.x /= t;
    _v.y /= t;
    _v.z /= t;
    _v.w /= t;
    return _v;
}

template<typename T>
template<typename T2> inline Vector4<T>& Vector4<T>::operator+=(const Vector4<T2> &v){
    x+=v.x;
    y+=v.y;
    z+=v.z;
    w+=v.w;
    return *this;
}
template<typename T>
template<typename T2> inline Vector4<T>& Vector4<T>::operator-=(const Vector4<T2> &v){
    x-=v.x;
    y-=v.y;
    z-=v.z;
    w-=v.w;
    return *this;
}
template<typename T>
template<typename T2> inline Vector4<T>& Vector4<T>::operator+=(T2 t){
    x+=t;
    y+=t;
    z+=t;
    w+=t;
    return *this;
}
template<typename T>
template<typename T2> inline Vector4<T>& Vector4<T>::operator-=(T2 t){
    x-=t;
    y-=t;
    z-=t;
    w-=t;
    return *this;
}
//template<typename T>
//template<typename T2> inline Vector4<T>& Vector4<T>::operator*=(T2 t){
//    x*=t;
//    y*=t;
//    z*=t;
//    w*=t;
//    return *this;
//}
template<typename T>
template<typename T2> inline Vector4<T>& Vector4<T>::operator/=(T2 t){
    x/=t;
    y/=t;
    z/=t;
    w/=t;
    return *this;
}

template<typename T>
template<typename T2> inline bool Vector4<T>::operator==(const Vector4<T2> &v)const{return x==v.x && y ==v.y && z ==v.z && w ==v.w;}
template<typename T>
template<typename T2> inline bool Vector4<T>::operator!=(const Vector4<T2> &v)const{return x!=v.x || y !=v.y || z !=v.z|| w !=v.w;}


//
//template<typename T>
//template<typename T2> inline bool Vector4<T>::operator>(const Vector4<T2> &m)const{
//    return getLength() > m.getLength();
//}
//template<typename T>
//template<typename T2> inline bool Vector4<T>::operator<(const Vector4<T2> &m)const{
//    return getLength() < m.getLength();
//}
//template<typename T>
//template<typename T2> inline bool Vector4<T>::operator<=(const Vector4<T2> &m)const{
//    return getLength() <= m.getLength();
//}
//template<typename T>
//template<typename T2> inline bool Vector4<T>::operator>=(const Vector4<T2> &m)const{
//    return getLength() >= m.getLength();
//}


//template<typename T>
//std::ostream &operator<<(std::ostream &os,const Vector4<T> &v){
//    os <<"["<< v.x << " " << v.y << " " << v.z << " " << v.w << "]";
//    return os;
//}
//
//
//template<>
//std::ostream &operator<<(std::ostream &os,const Vector4<int8_t> &V){
//    os <<"["<< (int)V.x << " " << (int)V.y << " " << (int)V.z << " " << (int)V.w << "]";
//    return os;
//}
//
//template<>
//std::ostream &operator<<(std::ostream &os,const Vector4<uint8_t> &V){
//    os <<"["<< (int)V.x << " " << (int)V.y << " " << (int)V.z << " " << (int)V.w << "]";
//    return os;
//}

//
//template<typename T,typename T2> Vector4<T> operator*(T2 t,const Vector4<T> &v){
//    Vector4<T> V(v);
//    V*=t;
//    return V;
//}
//template<typename T,typename T2> Vector4<T> operator+(T2 t,const Vector4<T> &v){
//    Vector4<T> V(v);
//    V+=t;
//    return V;
//}
//template<typename T,typename T2> Vector4<T> operator-(T2 t,const Vector4<T> &v){
//    Vector4<T> V(v);
//    V-=t;
//    return V;
//}
//template<typename T,typename T2> Vector4<T> operator/(T2 t,const Vector4<T> &v){
//    Vector4<T> V(v);
//    V/=t;
//    return V;
//}
};
};
#endif
