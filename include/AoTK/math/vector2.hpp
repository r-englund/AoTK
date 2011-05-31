


namespace AoTK{
namespace Math{

template<typename T> Vector2<T>::Vector2(T _x,T _y){
    x = _x;
    y = _y;
};
template<typename T> Vector2<T>::Vector2(){
    x = 0;
    y = 0;
}
template<typename T> template<typename T2> Vector2<T>::Vector2(const Vector2<T2> &_v){
    x = _v.x;
    y = _v.y;
}

template<typename T>
template<typename T2>
inline T Vector2<T>::dot(const Vector2<T2> &_v)const{
    return x*_v.x+y*_v.y;
}

template<typename T> inline void Vector2<T>::normalize(){
    float l = sqrt(x*x+y*y);
    x /= l;
    y /= l;
}

template<typename T> inline T Vector2<T>::getLength()const{
    return sqrt(x*x+y*y);
}

template<typename T>
template<typename T2> inline Vector2<T> Vector2<T>::operator+(const Vector2<T2> &V)const{
    Vector2<T> _v(V);
    _v.x += x;
    _v.y += y;
    return _v;
}
template<typename T>
template<typename T2> inline Vector2<T> Vector2<T>::operator-(const Vector2<T2> &V)const{
    Vector2<T> _v(V);
    _v.x -= x;
    _v.y -= y;
    return _v;
}
template<typename T>
template<typename T2> inline Vector2<T> Vector2<T>::operator+(T2 t)const{
    Vector2<T> _v(*this);
    _v.x += t;
    _v.y += t;
    return _v;
}
template<typename T>
template<typename T2> inline Vector2<T> Vector2<T>::operator-(T2 t)const{
    Vector2<T> _v(*this);
    _v.x -= t;
    _v.y -= t;
    return _v;
}
template<typename T>
template<typename T2> inline Vector2<T> Vector2<T>::operator*(T2 t)const{
    Vector2<T> _v(*this);
    _v.x *= t;
    _v.y *= t;
    return _v;
}
template<typename T>
template<typename T2> inline Vector2<T> Vector2<T>::operator/(T2 t)const{
    Vector2<T> _v(*this);
    _v.x /= t;
    _v.y /= t;
    return _v;
}

template<typename T>
template<typename T2> inline Vector2<T>& Vector2<T>::operator+=(const Vector2<T2> &V){
    x+=V.x;
    y+=V.y;
    return *this;
}
template<typename T>
template<typename T2> inline Vector2<T>& Vector2<T>::operator-=(const Vector2<T2> &V){
    x-=V.x;
    y-=V.y;
    return *this;
}
template<typename T>
template<typename T2> inline Vector2<T>& Vector2<T>::operator+=(T2 t){
    x+=t;
    y+=t;
    return *this;
}
template<typename T>
template<typename T2> inline Vector2<T>& Vector2<T>::operator-=(T2 t){
    x-=t;
    y-=t;
    return *this;
}
template<typename T>
template<typename T2> inline Vector2<T>& Vector2<T>::operator*=(T2 t){
    x*=t;
    y*=t;
    return *this;
}
template<typename T>
template<typename T2> inline Vector2<T>& Vector2<T>::operator/=(T2 t){
    x/=t;
    y/=t;
    return *this;
}

template<typename T>
template<typename T2> inline bool Vector2<T>::operator==(const Vector2<T2> &V)const{return x==V.x && y ==V.y;}
template<typename T>
template<typename T2> inline bool Vector2<T>::operator!=(const Vector2<T2> &V)const{return x!=V.x || y !=V.y;}



template<typename T>
template<typename T2> inline bool Vector2<T>::operator>(const Vector2<T2> &m)const{
    return getLength() > m.getLength();
}
template<typename T>
template<typename T2> inline bool Vector2<T>::operator<(const Vector2<T2> &m)const{
    return getLength() < m.getLength();
}
template<typename T>
template<typename T2> inline bool Vector2<T>::operator<=(const Vector2<T2> &m)const{
    return getLength() <= m.getLength();
}
template<typename T>
template<typename T2> inline bool Vector2<T>::operator>=(const Vector2<T2> &m)const{
    return getLength() >= m.getLength();
}


//template<typename T>
//std::ostream &operator<<(std::ostream &os,const Vector2<T> &V){
//    os <<"[" << V.x << " " << V.y << "]";
//    return os;
//}
//
//template<>
//std::ostream &operator<<(std::ostream &os,const Vector2<int8_t> &V){
//    os <<"["<< (int)V.x << " " << (int)V.y << "]";
//    return os;
//}
//
//template<>
//std::ostream &operator<<(std::ostream &os,const Vector2<uint8_t> &V){
//    os <<"["<< (int)V.x << " " << (int)V.y << "]";
//    return os;
//}

template<typename T,typename T2> Vector2<T> operator*(T2 t,const Vector2<T> &v){
    Vector2<T> V(v);
    V*=t;
    return V;
}
template<typename T,typename T2> Vector2<T> operator+(T2 t,const Vector2<T> &v){
    Vector2<T> V(v);
    V+=t;
    return V;
}
template<typename T,typename T2> Vector2<T> operator-(T2 t,const Vector2<T> &v){
    Vector2<T> V(v);
    V-=t;
    return V;
}
template<typename T,typename T2> Vector2<T> operator/(T2 t,const Vector2<T> &v){
    Vector2<T> V(v);
    V/=t;
    return V;
}



};
};
