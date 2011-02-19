
#include <AoTK/aotk.h>

namespace AoTK{

template<typename T> Volume<T>::Volume(unsigned int w,unsigned int h,unsigned int d):
width(w),
height(h),
depth(d){
    data = new T[width*height*depth]();
}

template<typename T> Volume<T>::Volume(const Volume<T> &v):
width(v.width),
height(v.height),
depth(v.depth)
{
    data = new T[width*height*depth]();
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
    return *this;
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

template<> Volume<Vector3<uint8_t>> Volume<uint8_t>::getGradientVolume(bool normalize)const{
    Volume<Vector3<uint8_t>> v(width,height,depth);
    int16_t gx,gy,gz;
    uint8_t mean = 0xff / 2;
    for(uint16_t x = 0; x < width;x++)for(uint16_t y = 0; y < height;y++)for(uint16_t z = 0; z < depth;z++){
        if(x == 0||y==0||z==0||x==width-1||y==height-1||z==depth-1){
            v.data[index(x,y,z)] = Vector3<uint8_t>(mean,mean,mean);
        }else{
            gx = data[index(x+1,y,z)]-data[index(x-1,y,z)];
            gy = data[index(x,y+1,z)]-data[index(x,y-1,z)];
            gz = data[index(x,y,z+1)]-data[index(x,y,z-1)];
            if(normalize){
                float l = sqrt(gx*gx+gy*gy+gz*gz) / 0xff;
                if(l>0.001){
                    gx /= l;
                    gy /= l;
                    gz /= l;
                    //TODO test this
                }
            }
            v.data[index(x,y,z)] = Vector3<uint8_t>(gx*0.5 + mean,
                                                    gy*0.5 + mean,
                                                    gz*0.5 + mean);
        }
    }
    return v;
}


template<> Volume<Vector4<uint8_t>> Volume<uint8_t>::getGradientDensityVolume(bool normalize)const{
    Volume<Vector4<uint8_t>> v(width,height,depth);
    int16_t gx,gy,gz;
    uint8_t mean = 0xff / 2;
    for(uint16_t x = 0; x < width;x++)for(uint16_t y = 0; y < height;y++)for(uint16_t z = 0; z < depth;z++){
        if(x == 0||y==0||z==0||x==width-1||y==height-1||z==depth-1){
            v.data[index(x,y,z)] = Vector4<uint8_t>(mean,mean,mean,data[index(x,y,z)]);
        }else{
            gx = data[index(x+1,y,z)]-data[index(x-1,y,z)];
            gy = data[index(x,y+1,z)]-data[index(x,y-1,z)];
            gz = data[index(x,y,z+1)]-data[index(x,y,z-1)];
            if(normalize){
                float l = sqrt(gx*gx+gy*gy+gz*gz) / 0xff;
                if(l>0.001){
                    gx /= l;
                    gy /= l;
                    gz /= l;
                    //TODO test this
                }
            }
            v.data[index(x,y,z)] = Vector4<uint8_t>(gx*0.5 + mean,
                                                    gy*0.5 + mean,
                                                    gz*0.5 + mean,
                                                    data[index(x,y,z)]);
        }
    }
    return v;
}

template<> Volume<Vector3<uint16_t>> Volume<uint16_t>::getGradientVolume(bool normalize)const{
    Volume<Vector3<uint16_t>> v(width,height,depth);
    int32_t gx,gy,gz;
    uint16_t mean = 0xffff / 2;
    for(uint16_t x = 0; x < width;x++)for(uint16_t y = 0; y < height;y++)for(uint16_t z = 0; z < depth;z++){
        if(x == 0||y==0||z==0||x==width-1||y==height-1||z==depth-1){
            v.data[index(x,y,z)] = Vector3<uint16_t>(mean,mean,mean);
        }else{
            gx = data[index(x+1,y,z)]-data[index(x-1,y,z)];
            gy = data[index(x,y+1,z)]-data[index(x,y-1,z)];
            gz = data[index(x,y,z+1)]-data[index(x,y,z-1)];
            if(normalize){
                float l = sqrt(gx*gx+gy*gy+gz*gz) / 0xffff;
                if(l>0.001){
                    gx /= l;
                    gy /= l;
                    gz /= l;
                    //TODO test this
                }
            }
            v.data[index(x,y,z)] = Vector3<uint16_t>(gx*0.5 + mean,
                                                     gy*0.5 + mean,
                                                     gz*0.5 + mean);
        }
    }
    return v;
}

template<> Volume<Vector4<uint16_t>> Volume<uint16_t>::getGradientDensityVolume(bool normalize)const{
    Volume<Vector4<uint16_t>> v(width,height,depth);
    int32_t gx,gy,gz;
    uint16_t mean = 0xffff / 2;
    for(uint16_t x = 0; x < width;x++)for(uint16_t y = 0; y < height;y++)for(uint16_t z = 0; z < depth;z++){
        if(x == 0||y==0||z==0||x==width-1||y==height-1||z==depth-1){
            v.data[index(x,y,z)] = Vector4<uint16_t>(mean,mean,mean,data[index(x,y,z)]);
        }else{
            gx = data[index(x+1,y,z)]-data[index(x-1,y,z)];
            gy = data[index(x,y+1,z)]-data[index(x,y-1,z)];
            gz = data[index(x,y,z+1)]-data[index(x,y,z-1)];
            if(normalize){
                float l = sqrt(gx*gx+gy*gy+gz*gz) / 0xffff;
                if(l>0.001){
                    gx /= l;
                    gy /= l;
                    gz /= l;
                    //TODO test this
                }
            }
            v.data[index(x,y,z)] = Vector4<uint16_t>(gx*0.5 + mean,
                                                     gy*0.5 + mean,
                                                     gz*0.5 + mean,
                                                     data[index(x,y,z)]);
        }
    }
    return v;
}



template<> Volume<Vector3<float>> Volume<float>::getGradientVolume(bool normalize)const{//TODO normalize
    Volume<Vector3<float>> v(width,height,depth);
    int32_t gx,gy,gz;
    for(uint16_t x = 0; x < width;x++)for(uint16_t y = 0; y < height;y++)for(uint16_t z = 0; z < depth;z++){
        if(x == 0||y==0||z==0||x==width-1||y==height-1||z==depth-1){
            v.data[index(x,y,z)] = Vector3<float>(0,0,0);
        }else{
            gx = data[index(x+1,y,z)]-data[index(x-1,y,z)];
            gy = data[index(x,y+1,z)]-data[index(x,y-1,z)];
            gz = data[index(x,y,z+1)]-data[index(x,y,z-1)];
            v.data[index(x,y,z)] = Vector3<float>(gx,gy,gz);
        }
    }
    return v;
}

template<> Volume<Vector4<float>> Volume<float>::getGradientDensityVolume(bool normalize)const{ //TODO normalize
    Volume<Vector4<float>> v(width,height,depth);
    int32_t gx,gy,gz;
    for(uint16_t x = 0; x < width;x++)for(uint16_t y = 0; y < height;y++)for(uint16_t z = 0; z < depth;z++){
        if(x == 0||y==0||z==0||x==width-1||y==height-1||z==depth-1){
            v.data[index(x,y,z)] = Vector4<float>(0,0,0,data[index(x,y,z)]);
        }else{
            gx = data[index(x+1,y,z)]-data[index(x-1,y,z)];
            gy = data[index(x,y+1,z)]-data[index(x,y-1,z)];
            gz = data[index(x,y,z+1)]-data[index(x,y,z-1)];
            v.data[index(x,y,z)] = Vector4<float>(gx,gy,gz,data[index(x,y,z)]);
        }
    }
    return v;
}

template<typename T> Volume<T> Volume<T>::loadRawVolume(unsigned int width,unsigned int height,unsigned int depth,char *filename){
    Volume<T> v(width,height,depth);
    FILE *f = fopen(filename,"rb");
    assert(f != NULL);

    fread(v.data,sizeof(T),width*height*depth,f);
    assert(ferror(f)==0);
    fclose(f);

    return v;
}


template<> Volume<HITANDMISS_BOOLEAN> Volume<HITANDMISS_BOOLEAN>::convolution(const Volume<float> kernel,FILTER_WRAP wrap)const{
    std::cerr << "Cant do convolution on a HITANDMISS_BOOLEAN volume" << std::endl;
    assert(false);
    return Volume<HITANDMISS_BOOLEAN>(0,0,0);
}
template<> Volume<bool> Volume<bool>::convolution(const Volume<float> kernel,FILTER_WRAP wrap)const{
    std::cerr << "Cant do convolution on a binary volume" << std::endl;
    assert(false);
    return Volume<bool>(0,0,0);
}

template<typename T> Volume<T> Volume<T>::convolution(const Volume<float> kernel,FILTER_WRAP wrap)const{
    int16_t hw,hh,hd,xx,yy,zz;
    hw = kernel.width / 2;
    hh = kernel.height / 2;
    hd = kernel.depth / 2;
    Volume<T> v(width,height,depth);
    for(uint16_t x = 0; x < width;x++)for(uint16_t y = 0; y < height;y++)for(uint16_t z = 0; z < depth;z++){
        float res = 0;
        for(uint16_t a = 0; a < kernel.width;a++)for(uint16_t b = 0; b < kernel.height;b++)for(uint16_t c = 0; c < kernel.height;c++){
            xx = a+x-hw;
            yy = b+y-hh;
            zz = c+z-hd;
            if(xx < 0 || yy < 0 || zz < 0 || xx < (int)width || yy < (int)height || zz < (int)depth ){
                switch(wrap){
                    case ZERO_PADDING:
                        break;
                    case ONE_PADDING:
                        res += MAX()*kernel.data[kernel.index(a,b,c)];
                        break;
                    case CLAMP:
                        xx = clamp(xx,0,(int)width-1);
                        yy = clamp(yy,0,(int)height-1);
                        zz = clamp(zz,0,(int)depth-1);
                        res += data[index(xx,yy,zz)]*kernel.data[kernel.index(a,b,c)];
                        break;
                    case MIRROR:
                        if(xx < 0) xx = -xx;
                        while(xx>=(int)width) xx -= width;
                        if(yy < 0) yy = -yy;
                        while(yy>=(int)height) yy -= height;
                        if(zz < 0) zz = -zz;
                        while(zz>=(int)depth) zz -= depth;
                        res += data[index(xx,yy,zz)]*kernel.data[kernel.index(a,b,c)];
                        break;
                    case REPEAT:
                        if(xx < 0) xx = width+xx;
                        else if(xx>(int)width) xx = xx % width;
                        if(yy < 0) yy = height+yy;
                        else if(yy>(int)height) yy = yy % height;
                        if(zz < 0) zz = depth+zz;
                        else if(zz>(int)depth) zz = zz % depth;

                        res += data[index(xx,yy,zz)]*kernel.data[kernel.index(a,b,c)];
                        break;
                    case SHRINK:
                    default:
                        std::cerr << "Unsupported filter wrap used" << std::endl;
                        return Volume<T>(0,0,0);
                }
            }else{
                res += data[index(xx,yy,zz)]*kernel.data[kernel.index(a,b,c)];
            }
        }
        v.data[index(x,y,z)] = res;
    }
    return v;
}

template<> Volume<bool> Volume<bool>::erode(const Volume<bool> &kernel,FILTER_WRAP wrap)const{
    int16_t hw,hh,hd;
    hw = kernel.width / 2;
    hh = kernel.height / 2;
    hd = kernel.depth / 2;
    Volume<bool> v(width,height,depth);
    for(uint16_t x = 0; x < width;x++)for(uint16_t y = 0; y < height;y++)for(uint16_t z = 0; z < depth;z++){
        bool res = true;
        for(uint16_t a = 0; a < kernel.width && res;a++)for(uint16_t b = 0; b < kernel.height && res;b++)for(uint16_t c = 0; c < kernel.height && res;c++)if(kernel.data[kernel.index(a,b,c)]){
            uint16_t xx,yy,zz;
            xx = a+x-hw;
            yy = b+y-hh;
            zz = c+z-hd;

            if(xx < 0 || yy < 0 || zz < 0 || xx < width || yy < height || zz < depth ){
                switch(wrap){
                    case ZERO_PADDING:
                        res = false;
                        break;
                    case ONE_PADDING:
                        res = true;
                        break;
                    case CLAMP:
                        xx = clamp(xx,0,width-1);
                        yy = clamp(yy,0,height-1);
                        zz = clamp(zz,0,depth-1);
                        res = data[index(xx,yy,zz)];
                        break;
                    case MIRROR:
                        if(xx < 0) xx = -xx;
                        while(xx>=width) xx -= width;
                        if(yy < 0) yy = -yy;
                        while(yy>=height) yy -= height;
                        if(zz < 0) zz = -zz;
                        while(zz>=depth) zz -= depth;
                        res = data[index(xx,yy,zz)];
                        break;
                    case REPEAT:
                        if(xx < 0) xx = width+xx;
                        else if(xx>width) xx = xx % width;
                        if(yy < 0) yy = height+yy;
                        else if(yy>height) yy = yy % height;
                        if(zz < 0) zz = depth+zz;
                        else if(zz>depth) zz = zz % depth;

                        res = data[index(xx,yy,zz)];
                        break;
                    case SHRINK:
                    default:
                        std::cerr << "Unsupported filter wrap used" << std::endl;
                        return Volume<bool>(0,0,0);
                }
            }else{
                res = data[index(xx,yy,zz)];
            }
        }
        v.data[index(x,y,z)] = res;
    }
    return v;
}

template<> Volume<bool> Volume<bool>::dilate(const Volume<bool> &kernel,FILTER_WRAP wrap)const{
    int16_t hw,hh,hd;
    hw = kernel.width / 2;
    hh = kernel.height / 2;
    hd = kernel.depth / 2;
    Volume<bool> v(width,height,depth);
    for(uint16_t x = 0; x < width;x++)for(uint16_t y = 0; y < height;y++)for(uint16_t z = 0; z < depth;z++){
        bool res = false;
        for(uint16_t a = 0; a < kernel.width && !res;a++)for(uint16_t b = 0; b < kernel.height && !res;b++)for(uint16_t c = 0; c < kernel.height && !res;c++)if(kernel.data[kernel.index(a,b,c)]){
            uint16_t xx,yy,zz;
            xx = a+x-hw;
            yy = b+y-hh;
            zz = c+z-hd;

            if(xx < 0 || yy < 0 || zz < 0 || xx < width || yy < height || zz < depth ){
                switch(wrap){
                    case ZERO_PADDING:
                        res = false;
                        break;
                    case ONE_PADDING:
                        res = true;
                        break;
                    case CLAMP:
                        xx = clamp(xx,0,width-1);
                        yy = clamp(yy,0,height-1);
                        zz = clamp(zz,0,depth-1);
                        res = data[index(xx,yy,zz)];
                        break;
                    case MIRROR:
                        if(xx < 0) xx = -xx;
                        while(xx>=width) xx -= width;
                        if(yy < 0) yy = -yy;
                        while(yy>=height) yy -= height;
                        if(zz < 0) zz = -zz;
                        while(zz>=depth) zz -= depth;
                        res = data[index(xx,yy,zz)];
                        break;
                    case REPEAT:
                        if(xx < 0) xx = width+xx;
                        else if(xx>width) xx = xx % width;
                        if(yy < 0) yy = height+yy;
                        else if(yy>height) yy = yy % height;
                        if(zz < 0) zz = depth+zz;
                        else if(zz>depth) zz = zz % depth;

                        res = data[index(xx,yy,zz)];
                        break;
                    case SHRINK:
                    default:
                        std::cerr << "Unsupported filter wrap used" << std::endl;
                        return Volume<bool>(0,0,0);
                }
            }else{
                res = data[index(xx,yy,zz)];
            }
        }
        v.data[index(x,y,z)] = res;
    }
    return v;
}

template<> double Volume<double>::MAX()const{return 1.0;}
template<> float Volume<float>::MAX()const{return 1.0f;}
template<> uint8_t Volume<uint8_t>::MAX()const{return 0xff;}
template<> uint16_t Volume<uint16_t>::MAX()const{return 0xffff;}

template class Volume<double>;
template class Volume<float>;
template class Volume<uint8_t>;
template class Volume<uint16_t>;
template class Volume<bool>;
template class Volume<HITANDMISS_BOOLEAN>;

};


