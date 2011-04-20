
namespace AoTK{
template<typename T>
template<typename T2> Image<T> Image<T>::convolution(const Image<T2> &img,_FILTER_WRAP wrap)const{
    if(!(std::is_same<T,float>::value || std::is_same<T,double>::value)){
        int status;
        std::cerr << "Warning, running convolution on a image thats not float or double, wrapping error might happen, cossider casting image to float or double before convoltution. Using("  << abi::__cxa_demangle(typeid(data[0][0]).name(),0,0,&status) << ")" << std::endl;
    }
    Image<T> out(width,height,channels);
    for(int c = 0;c<channels;c++){
        for(int x = 0;x<width;x++)for(int y = 0;y<height;y++){
            T v(0);
            for(int a = 0;a<img.width;a++)for(int b = 0;b<img.height;b++){
                v += img.getPixel(a,b,WARNING) * getPixel(x-(a-img.width/2),y-(b-img.height/2),c,wrap);
            }
            out.setPixel(x,y,c,v);
        }
    }
    return out;
}

template<typename T>
template<typename T2> Image<T> Image<T>::correlation(const Image<T2> &img,_FILTER_WRAP wrap)const{
    if(!(std::is_same<T,float>::value || std::is_same<T,double>::value)){
        int status;
        std::cerr << "Warning, running convolution on a image thats not float or double, wrapping error might happen, cossider casting image to float or double before convoltution. Using("  << abi::__cxa_demangle(typeid(data[0][0]).name(),0,0,&status) << ")" << std::endl;
    }
    Image<T> out(width,height,channels);
    for(int c = 0;c<channels;c++){
        for(int x = 0;x<width;x++)for(int y = 0;y<height;y++){
            T v(0);
            for(int a = 0;a<img.width;a++)for(int b = 0;b<img.height;b++){
                v += img.getPixel(a,b,WARNING) * getPixel(x+(a-img.width/2),y+(b-img.height/2),c,wrap);
            }
            out.setPixel(x,y,c,v);
        }
    }
    return out;
}




};
