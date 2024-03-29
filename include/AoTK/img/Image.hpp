
#include <type_traits>
#include <limits>

namespace AoTK{
namespace IMG{

template<typename T>
Image<T>::Image(const Image<T>& img):
    width(img.width),
    height(img.height),
    channels(img.channels),
    data(0)
{
//    static_assert( std::is_same<T,T2>::value  , "Implementation for converting from T to T2 is not defined");

    data = new T*[channels]();
    for(int i = 0;i<channels;i++){
        data[i] = new T[width*height]();
        for(int j = 0;j<width*height;j++){
            data[i][j]= img.data[i][j];
        }
    }
}
template<typename T>
Image<T>& Image<T>::operator=(const Image<T> &img){
//    static_assert( std::is_same<T,T2>::value  , "Implementation for converting from T to T2 is not defined");
    if(this == &img)
        return *this;

    delete data;

    width = img.width;
    height = img.height;
    channels = img.channels;

    data = new T*[channels]();
    for(int i = 0;i<channels;i++){
        data[i] = new T[width*height]();
        for(int j = 0;j<width*height;j++){
            data[i][j]= img.data[i][j];
        }
    }

    return *this;
}

template<typename T>
Image<T>::Image(uint16_t _w,uint16_t _h,uint16_t _c):
    width(_w),
    height(_h),
    channels(_c),
    data(0)
{
    data = new T*[channels]();
    for(int i = 0;i<channels;i++){
        data[i] = new T[width*height]();
    }

}

template<typename T> Image<T>::~Image(){
    for(int i = 0;i<channels;i++){
        delete data[i];
    }
    delete data;
}


template<typename T>
Image<T>::Image():
    width(1),
    height(1),
    channels(1),
    data(0)
{
    data = new T*[channels]();
    for(int i = 0;i<channels;i++){
        data[i] = new T[width*height]();
    }
}

template<typename T> T cubicInterpolation(float x,T a,T b,T c,T d){
//	T p;
//	p = (1-x)*(1-x)*(1-x)*a;
//	p += 3*(1-x)*(1-x)*x*b;
//	p += 3*(1-x)*x*x*c;
//	p += x*x*x*d;
//	p = b;
//	p += ((-a + 3.0 * b - 3.0 * c + d)*0.5) * x*x*x;
//	p += (a-5.0/2.0*b+2.0*c-0.5*d)*x*x;
//	p += (0.5*(-a+c))*x;
//	return p;
    return b + 0.5 * x*(c - a + x*(2.0*a - 5.0*b + 4.0*c - d + x*(3.0*(b - c) + d - a)));
}

//p[1] +
//0.5 * x*(p[2] - p[0] + x*(2.0*p[0] - 5.0*p[1] + 4.0*p[2] - p[3] + x*(3.0*(p[1] - p[2]) + p[3] - p[0])));


template<typename T>
T Image<T>::getInterpolatedPixel(float x,float y, int16_t _c,INTERPOLATION interpolation,_FILTER_WRAP wrap)const{
    if(_c>=channels){
        std::cerr << "Channel outside image"<< std::endl;
        assert(false && "Channel outside image");
        return T(0);
    }
//    if(x>(width-1)||y>(height-1)||x<0||y<0){
//        switch(wrap){
//                break;
//            case ONE_PADDING:
//                return upperLimit();
//                break;
//            case CLAMP:
//                x = clamp(x,0,width-1);
//                y = clamp(y,0,height-1);
//                break;
//            case MIRROR:
//                if(x<0)x = -x;
//                if(y<0)y = -y;
//                if(x>(width-1)) x = (width-1)-(x-(width-1));
//                if(y>(height-1)) y = (height-1)-(y-(height-1));
//                break;
//            case REPEAT:
//                while(x<0) x += (width-1);
//                while(y<0) y += (height-1);
//                while(x>(width-1)) x -= (width-1);
//                while(y>(height-1))y -= (height-1);
//                break;
//            case WARNING:
//                std::cerr << "Warning: Trying to get a pixel outside the image" << std::endl;
//            case _ZERO_PADDING:
//            default:
//                return 0;
//        }
//    }


    float a,b,c,d;
    int16_t _x,_y;
    T value = 0;
    switch(interpolation){
        case NEAREST_NEIGHBOUR:
            x = round(x);
            y = round(y);
            value = getPixel((int16_t)x,(int16_t)y,_c,wrap);
            break;
	case CUBIC:
            a = x - floor(x);
            b = y - floor(y);
            _x = floor(x)-1;
            _y = floor(y)-1;

//            a += 1.0;
//            a /= 3.0;
//            b += 1.0;
//            b /= 3.0;

            value += cubicInterpolation(b,
					cubicInterpolation(a,getPixel(_x+0,_y+0,_c,wrap),getPixel(_x+1,_y+0,_c,wrap),getPixel(_x+2,_y+0,_c,wrap),getPixel(_x+3,_y+0,_c,wrap)),
					cubicInterpolation(a,getPixel(_x+0,_y+1,_c,wrap),getPixel(_x+1,_y+1,_c,wrap),getPixel(_x+2,_y+1,_c,wrap),getPixel(_x+3,_y+1,_c,wrap)),
					cubicInterpolation(a,getPixel(_x+0,_y+2,_c,wrap),getPixel(_x+1,_y+2,_c,wrap),getPixel(_x+2,_y+2,_c,wrap),getPixel(_x+3,_y+2,_c,wrap)),
					cubicInterpolation(a,getPixel(_x+0,_y+3,_c,wrap),getPixel(_x+1,_y+3,_c,wrap),getPixel(_x+2,_y+3,_c,wrap),getPixel(_x+3,_y+3,_c,wrap))
					);

            break;
        case LINEAR:
        default:
            b = x - floor(x);
            a = 1-b;
            d = y - floor(y);
            c = 1-d;

            value += a*c*getPixel((int16_t)floor(x)+0,(int16_t)floor(y)+0,_c,wrap);
            value += b*c*getPixel((int16_t)floor(x)+1,(int16_t)floor(y)+0,_c,wrap);
            value += a*d*getPixel((int16_t)floor(x)+0,(int16_t)floor(y)+1,_c,wrap);
            value += b*d*getPixel((int16_t)floor(x)+1,(int16_t)floor(y)+1,_c,wrap);
            break;
    }
    return value;
}

template<typename T>
T Image<T>::getPixel(int16_t x, int16_t y, int16_t _c,_FILTER_WRAP wrap)const{
    if(_c>=channels){
        std::cerr << "Channel outside image"<< std::endl;
        assert(false && "Channel outside image");
        return T(0);
    }
    if(x>(width-1)||y>(height-1)||x<0||y<0){
        switch(wrap){
            case ONE_PADDING:
                return upperLimit();
            case CLAMP:
                x = clamp(x,0,width-1);
                y = clamp(y,0,height-1);
                break;
            case MIRROR:
                if(x<0)x = -x;
                if(y<0)y = -y;
                if(x>(width-1)) x = (width-1)-(x-(width-1));
                if(y>(height-1)) y = (height-1)-(y-(height-1));
                break;
            case REPEAT:
                while(x<0) x += (width-1);
                while(y<0) y += (height-1);
                while(x>(width-1)) x -= (width-1);
                while(y>(height-1))y -= (height-1);
                break;
            case WARNING:
                std::cerr << "Warning: Trying to get a pixel outside the image" << std::endl;
            case _ZERO_PADDING:
            default:
                return 0;
        }
    }
    return data[_c][x+y*width];
}
template<typename T>
void Image<T>::setPixel(int16_t x, int16_t y, int16_t c,T t){
    if(c>=channels){
        std::cerr << "Channel outside image"<< std::endl;
        assert(false && "Channel outside image");
        return;
    }
    if(x>(width-1)||y>(height-1)||x<0||y<0){
        std::cerr << "Coordinates outside image"<< std::endl;
        assert(false && "Coordinates outside image");
        return;
    }
    data[c][x+y*width] = t;
}

template<typename T>
T Image<T>::getMax(int16_t c)const{
    T m = data[c][0];
    for(int i = 1;i<width*height;i++){
        if(data[c][i] > m) m = data[c][i];
    }
    return m;
}
template<typename T>
T Image<T>::getMin(int16_t c)const{
    T min = data[c][0];
    for(int i = 1;i<width*height;i++){
        if(data[c][i] < min) min = data[c][i];
    }
    return min;
}

template<typename T>
Image<T> Image<T>::getChannel(uint8_t c)const{
    if(c>=channels){
        std::cerr << "Channel outside image"<< std::endl;
        assert(false && "Channel outside image");
        return Image<T>();
    }
    Image<T> img(width,height,1);
    for(int i =0;i< width*height;i++)
        img.data[0][i] = data[c][i];

    return img;
}


template<typename T>
Image<T> Image<T>::getGreyscale()const{
    if(channels!=3){
        std::cerr << "Not an RGB image, cant creat greyscale"<< std::endl;
        assert(false && "Not an RGB image, cant creat greyscale");
        return Image<T>();
    }
    Image<T> img(width,height,1);
    for(int i =0;i< width*height;i++){
        img.data[0][i] = 0.2989 *data[0][i];
        img.data[0][i] += 0.5870 *data[1][i];
        img.data[0][i] += 0.1140 *data[2][i];
    }
    return img;
}

template<typename T>
void Image<T>::normalize(){
    for(int c = 0;c<channels;c++){
        T m = getMax(c);
        T _min = getMin(c);
        m -= _min;
		m /= (T)upperLimit();
        for(int i = 0;i<width*height;i++){
            T d = data[c][i];
            d -= _min;
            d /= m;
            data[c][i] = d;
        }

    }
}

template<typename T> Image<T> Image<T>::scale(float sx,float sy,INTERPOLATION interpolation,_FILTER_WRAP wrap)const{
	Image<T> img(std::ceil(width*sx),std::ceil(height*sy),channels);
	sx = float(width - 1) / (img.width-1);
	sy = float(height -1) / (img.height-1);
	for(int x = 0;x<img.width;x++)for(int y = 0;y<img.height;y++)for(int c = 0;c<img.channels;c++){
		img.setPixel(x,y,c,getInterpolatedPixel(x*sx,y*sy,c,interpolation,wrap));
		if(x==img.width-1){
            img.setPixel(x,y,c,255);
		}
	}
	return img;
}

template<typename T> Image<T> Image<T>::resize(unsigned int neww,unsigned int newh,INTERPOLATION interpolation,_FILTER_WRAP wrap)const{
	return scale(float(neww)/width,float(newh)/height,interpolation,wrap);
}

template<typename T>
Image<T> Image<T>::rotate(float deg)const{
    while(deg >= 360) deg -= 360;
    while(deg < 0) deg += 360;
    if(fabs(deg - 0) < 0.01){
        return Image<T>(*this);
    }else if(fabs(deg - 90) < 0.01 ||fabs(deg - 270) < 0.01){
        Image<T> img(height,width,channels);
        for(uint16_t x = 0;x<height;x++)for(uint16_t y = 0;y<width;y++){
            if(fabs(deg - 90) < 0.01){
                for(int c = 0;c<channels;c++)
                    img.setPixel(x,y,c,getPixel(y,height-1-x,c,_ZERO_PADDING));
            }else{
                for(int c = 0;c<channels;c++)
                    img.setPixel(x,y,c,getPixel(width-1-y,x,c,_ZERO_PADDING));
            }
        }
        return img;
    }else if(fabs(deg - 180) < 0.01){
        Image<T> img(width,height,channels);
        for(uint16_t x = 0;x<width;x++)for(uint16_t y = 0;y<height;y++){
            for(int c = 0;c<channels;c++)
                img.setPixel(x,y,c,getPixel(width-1-x,height-1-y,c,_ZERO_PADDING));
        }
        return img;
    }
    int16_t newW,newH;
    float oldx,oldy;

    deg *= (M_PI / 180);

    newW = fabs((width * cos(deg))) + fabs((height * sin(deg)));
    newH = fabs((width * sin(deg))) + fabs((height * cos(deg)));


    Image<T> rotated_img(newW,newH,channels);
    for(uint16_t x = 0;x<newW;x++)for(uint16_t y = 0;y<newH;y++){
        oldx = (x-newW/2.0)*cos(deg) + (y-newH/2.0)*sin(deg) + width/2.0;
        oldy = (y-newH/2.0)*cos(deg) - (x-newW/2.0)*sin(deg) + height/2.0;
        for(int c = 0;c<channels;c++){
            T p = getInterpolatedPixel(oldx,oldy,c,LINEAR,_ZERO_PADDING);
            rotated_img.setPixel(x,y,c,p);
        }
    }

    return rotated_img;
}



template<typename T>
Image<T> Image<T>::operator+(const Image<T> img)const{
	
	assert(img.width == width);
	assert(img.height == height);
	assert(img.channels == channels);

	if(img.width != width || img.height != height || img.channels != channels)
		return Image<T>(1,1,1);

	Image<T> i = *this;
	i += img;
	return i;
}

template<typename T>
Image<T> Image<T>::operator-(const Image<T> img)const{
	
	assert(img.width == width);
	assert(img.height == height);
	assert(img.channels == channels);

	if(img.width != width || img.height != height || img.channels != channels)
		return Image<T>(1,1,1);

	Image<T> i = *this;
	i += img;
	return i;
}

template<typename T>
Image<T> Image<T>::operator*(const Image<T> img)const{
	
	assert(img.width == width);
	assert(img.height == height);
	assert(img.channels == channels);

	if(img.width != width || img.height != height || img.channels != channels)
		return Image<T>(1,1,1);

	Image<T> i = *this;
	i *= img;
	return i;
}

template<typename T>
Image<T> Image<T>::operator/(const Image<T> img)const{
	
	assert(img.width == width);
	assert(img.height == height);
	assert(img.channels == channels);

	if(img.width != width || img.height != height || img.channels != channels)
		return Image<T>(1,1,1);

	Image<T> i = *this;
	i /= img;
	return i;
}

template<typename T>
Image<T> &Image<T>::operator+=(const Image<T> img){
	assert(img.width == width);
	assert(img.height == height);
	assert(img.channels == channels);

	if(img.width != width || img.height != height || img.channels != channels)
		return Image<T>(1,1,1);
	for(int i = 0;i<width*height;i++)	for(int c = 0;c<channels;c++){
		data[c][i] += img.data[c][i];
	}
}

template<typename T>
Image<T> &Image<T>::operator-=(const Image<T> img){
	assert(img.width == width);
	assert(img.height == height);
	assert(img.channels == channels);

	if(img.width != width || img.height != height || img.channels != channels)
		return Image<T>(1,1,1);
	for(int i = 0;i<width*height;i++)	for(int c = 0;c<channels;c++){
		data[c][i] -= img.data[c][i];
	}
}

template<typename T>
Image<T> &Image<T>::operator*=(const Image<T> img){
	assert(img.width == width);
	assert(img.height == height);
	assert(img.channels == channels);

	if(img.width != width || img.height != height || img.channels != channels)
		return Image<T>(1,1,1);
	for(int i = 0;i<width*height;i++)	for(int c = 0;c<channels;c++){
		data[c][i] *= img.data[c][i];
	}
}

template<typename T>
Image<T> &Image<T>::operator/=(const Image<T> img){
	assert(img.width == width);
	assert(img.height == height);
	assert(img.channels == channels);

	if(img.width != width || img.height != height || img.channels != channels)
		return Image<T>(1,1,1);
	for(int i = 0;i<width*height;i++)	for(int c = 0;c<channels;c++){
		data[c][i] /= img.data[c][i];
	}
}


template<typename T>
bool Image<T>::operator==(const Image<T> img)const{	
	if(img.width != width || img.height != height || img.channels != channels)
		return false;

	for(int x = 0;x<width;x++)	for(int y = 0;y<height;y++)	for(int c = 0;c<channels;c++){
		if(getPixel(x,y,c) != img.getPixel(x,y,c))
			return false;
	}
	return true;
}

template<typename T>
bool Image<T>::operator!=(const Image<T> img)const{	
	if(img.width != width || img.height != height || img.channels != channels)
		return true;

	for(int x = 0;x<width;x++)	for(int y = 0;y<height;y++)	for(int c = 0;c<channels;c++){
		if(getPixel(x,y,c) != img.getPixel(x,y,c))
			return true;
	}
	return false;
}


};
};

