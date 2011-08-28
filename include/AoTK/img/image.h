#ifndef AOTK_IMAGE_H
#define AOTK_IMAGE_H

#define implement std::cout << "Implement this in: " << __FILE__ << " at line " << __LINE__ << std::endl;


#include <stdint.h>
#include <typeinfo>
#include <string>
#include <assert.h>
#include <stdio.h>
#include <cmath>
#include <iostream>

#ifdef __GXX_EXPERIMENTAL_CXX0X__
#include <cxxabi.h> //to get better output from typeid().name()
#endif

#include <stdlib.h>
#include <time.h>

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

#ifndef clamp
#define clamp(a,b,c) (((a) > (c)) ? (c) : (((a) < (b)) ? (b) : (a)))
#endif



namespace AoTK{
namespace IMG{
    enum INTERPOLATION{
        NEAREST_NEIGHBOUR,
        LINEAR,
        CUBIC
    };

    enum HITANDMISS_BOOLEAN : signed int{
        SKIP = -1,
        ONE = 1,
        ZERO = 0
    };

    enum _FILTER_WRAP{
        _ZERO_PADDING, // all elements outside equal to zero
        ONE_PADDING, // all elements outside equal to one ( or maximum)
        CLAMP, //cpoy the closest element
        MIRROR,  //miror along the axis eg : -3 = 3 and max + 3 = max - 3
        REPEAT, //max + 3 = 3 and -3 = max -3
        WARNING //Warn user and return 0(assert if possible)
    };

    template<typename T>
    class Image{
    public:
        Image();
        Image(uint16_t width,uint16_t height,uint16_t channels = 1);
        template <typename T2> Image(const Image<T2> &t);
        Image(const Image &t);
        template <typename T2> Image &operator=(const Image<T2> &t);
        Image &operator=(const Image &t);

        virtual ~Image();
        Image resized(uint16_t new_width,uint16_t new_height) const;
        template<typename T2> Image convolution(const Image<T2> &img,_FILTER_WRAP wrap = _ZERO_PADDING)const;
        template<typename T2> Image correlation(const Image<T2> &img,_FILTER_WRAP wrap = _ZERO_PADDING)const;
        Image rotate(float deg)const;
		Image scale(float sx,float sy,INTERPOLATION interpolation = LINEAR,_FILTER_WRAP wrap = _ZERO_PADDING)const;
		Image resize(unsigned int neww,unsigned int newH,INTERPOLATION interpolation = LINEAR,_FILTER_WRAP wrap = _ZERO_PADDING)const;

        T getInterpolatedPixel(float x,float y, int16_t c,INTERPOLATION interpolation = LINEAR,_FILTER_WRAP wrap = WARNING)const;
        T getPixel(int16_t x, int16_t y, int16_t c,_FILTER_WRAP wrap = WARNING)const;
        void setPixel(int16_t x, int16_t y, int16_t c,T t);
        T getInterpolatedPixel(float x,float y,INTERPOLATION interpolation = LINEAR,_FILTER_WRAP wrap = WARNING)const{return getInterpolatedPixel(x,y,0,interpolation,wrap);}
        T getPixel(int16_t x, int16_t y,_FILTER_WRAP wrap = WARNING)const{return getPixel(x,y,0,wrap);}
        void setPixel(int16_t x, int16_t y,T t){setPixel(x,y,0,t);}

        T getMax(int16_t c = 0)const;
        T getMin(int16_t c = 0)const;

        void setData(T* t){data = t;}
        T** getData()const{return data;}
        Image<T> getChannel(uint8_t channel)const;

        Image<T> getGreyscale()const;
        Image<T> rgb2hsv()const;
        Image<T> hsv2rgb()const;

        void normalize();

		Image<T> operator+(const Image<T> img)const;
		Image<T> operator-(const Image<T> img)const;
		Image<T> operator*(const Image<T> img)const;
		Image<T> operator/(const Image<T> img)const;
		Image<T> &operator+=(const Image<T> img);
		Image<T> &operator-=(const Image<T> img);
		Image<T> &operator*=(const Image<T> img);
		Image<T> &operator/=(const Image<T> img);
		
		bool operator==(const Image<T> img)const;
		bool operator!=(const Image<T> img)const;
		
#ifdef GL_VERSION_1_1
        static Image FromGLTexture(GLuint tex);
        static Image FromCurrentGLContext();
        static Image FromCurrentGLContextDepth();
        GLuint toGLTexture();

#endif

        unsigned int getWidth()const{return width;}
        unsigned int getHeight()const{return height;}

        void saveBMP(std::string filename);
        void saveJSON(std::string filename,std::string name = "image");
        void savePNG(std::string filename);
        void saveJPG(std::string filename);
        void saveGIF(std::string filename);

		static T upperLimit();
		static T lowerLimit();

        static Image SobelXKernel(uint16_t size = 3);
        static Image SobelYKernel(uint16_t size = 3);
        static Image LaplaceKernel(uint16_t size = 3);
        static Image AverageKernel(uint16_t size = 3);
        static Image GaussianKernel(float r = 1.0,uint16_t size = 3);

        static Image AverageKernel(uint16_t width,uint16_t height);
        static Image GaussianKernel(float r,uint16_t width,uint16_t height);

        static Image random(uint16_t w,uint16_t h,uint16_t c);

        static Image LoadBMP(std::string filename);
        static Image LoadPNG(std::string filename);
        static Image LoadJPG(std::string filename);
        static Image LoadGIF(std::string filename);

        void clear();

    private:
        template<typename X> friend class Image;
        uint16_t width,height,channels;
        T **data;


    };

};
};

#include "Image.hpp"
#include "Image_GIF.hpp"
#include "Image_JPG.hpp"
#include "Image_PNG.hpp"
#include "Image_Static_Functions.hpp"
#include "Image_Filters.hpp"


#endif
