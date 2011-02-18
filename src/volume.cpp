

#include <AoTK/volume.h>
#include <AoTK/aotk.h>

namespace AoTK{

template<typename T> Volume<T>::Volume(unsigned int w,unsigned int h,unsigned int d):
width(w),
height(h),
depth(d){
    data = new T[width*height*depth];
}
template<typename T> Volume<T>::Volume(const Volume<T> &v):
width(v.width),
height(v.height),
depth(v.depth)
{
    data = new T[width*height*depth];
    for(unsigned int i = 0;i<width*height*depth;i++)
        data[i] = v.data[i];
}

template<typename T> Volume<T>& Volume<T>::operator=(const Volume<T> &v){
    if(this == &v)
        return *this;
    width = v.width;
    height = v.height;
    depth = v.depth;
    data = new T[width*height*depth];
    for(unsigned int i = 0;i<width*height*depth;i++)
        data[i] = v.data[i];
}


template<> Volume<bool> Volume<bool>::toBinary(bool threshold)const{
    assert(false && "Trying to make a binary volume of a binary volume");
    std::cerr << "Trying to make a binary volume of a binary volume" << std::endl;
    return Volume(0,0,0);
}
template<typename T> Volume<bool> Volume<T>::toBinary(T threshold)const{
    Volume<bool> v(width,height,depth);
    for(unsigned int x = 0; x < width; x++)for(unsigned int y = 0; y < height; y++)for(unsigned int z = 0; z < depth; z++){
        unsigned int i = index(x,y,z);
        if(data[i] >= threshold)
            v.data[i] = true;
        else
            v.data[i] = false;
    }

    return v;
}

template class Volume<double>;
template class Volume<float>;
template class Volume<uint8_t>;
template class Volume<uint16_t>;
template class Volume<bool>;
template class Volume<HITANDMISS_BOOLEAN>;

};


