#ifndef GLSL_H
#define GLSL_H

#include "math.h"
#include "enums.h"
#include <assert.h>
#include <GL/glew.h>

namespace AoTK{

template <typename T >
class Volume{
    unsigned int width;
    unsigned int height;
    unsigned int depth;
    T *data;

    inline unsigned int index(unsigned int x,unsigned int y,unsigned int z)const{
        #ifdef DEBUG
        assert(x<width);
        assert(y<height);
        assert(z<depth);
        #endif
        return x + y*width + x*width*height;
    }

public:
    Volume(unsigned int width,unsigned int height,unsigned int depth);
    Volume(const Volume<T> &v);
    Volume &operator=(const Volume<T> &v);
    ~Volume(){delete data;}

    inline T getVoxel(unsigned int x,unsigned int y,unsigned int z)const{
        return data[index(x,y,z)];
    }
    inline void setVoxel(unsigned int x,unsigned int y,unsigned int z,T t){
        data[index(x,y,z)] = t;
    }

    void convolution(const Volume<float> kernel,FILTER_WRAP pad = zero_padding);
    void erode(const Volume<bool> &kernel,FILTER_WRAP pad = zero_padding);
    void dialte(const Volume<bool> &kernel,FILTER_WRAP pad = zero_padding);
    void hitAndMiss(const Volume<HITANDMISS_BOOLEAN> &kernel);


    Volume<Vector3<T>> getGradientVolume(bool normalize = false)const;
    Volume<Vector4<T>> getGradientDensityVolume(bool normalize = false)const;

    Volume<bool> toBinary(T threshold)const;

    GLuint toGLtexture()const;

    static Volume<T> loadRawVolume(unsigned int width,unsigned int height,unsigned int depth);


private:
    friend class Volume<double>;
    friend class Volume<float>;
    friend class Volume<uint8_t>;
    friend class Volume<uint16_t>;
    friend class Volume<bool>;
    friend class Volume<HITANDMISS_BOOLEAN>;
};

};

#endif
