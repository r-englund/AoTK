


namespace AoTK{


template<typename T> Image<T> Image<T>::SobelXKernel(uint16_t size){
    Image<T> img(size,3);
    for(uint16_t i = 0;i<size;i++){
        img.setPixel(i,0,0,-1);
        img.setPixel(i,1,0,0);
        img.setPixel(i,2,0,1);
    }
    return img;
}
template<typename T> Image<T> Image<T>::SobelYKernel(uint16_t size){
    Image<T> img(3,size);
    for(uint16_t i = 0;i<size;i++){
        img.setPixel(0,i,0,-1);
        img.setPixel(1,i,0,0);
        img.setPixel(2,i,0,1);
    }
    return img;

}
template<typename T> Image<T> Image<T>::LaplaceKernel(uint16_t size){
    Image<T> img(size,size);
    int v = size*size - 1;
    for(uint16_t x = 0;x<size;x++)for(uint16_t y = 0;y<size;y++){
        img.setPixel(x,y,-1);
    }
    img.setPixel(size/2,size/2,v);
    return img;
}
template<typename T> Image<T> Image<T>::AverageKernel(uint16_t size){return AverageKernel(size,size);}
template<typename T> Image<T> Image<T>::GaussianKernel(float r,uint16_t size){return GaussianKernel(r,size,size);}

template<typename T> Image<T> Image<T>::AverageKernel(uint16_t width,uint16_t height){
    static_assert(std::is_same<T,float>::value || std::is_same<T,double>::value  , "Averege Kernel should be either float or double");
    Image<T> img(width,height);
    T v = 1.0/(width*height);
    for(int i = 0;i<width*height;i++)
        img.data[0][i] = v;
    return img;
}
template<typename T> Image<T> Image<T>::GaussianKernel(float r,uint16_t width,uint16_t height){
    Image<T> img(width,height);
    double tot = 0;
    for(uint16_t x = 0;x<width;x++)for(uint16_t y = 0;y<height;y++){
        float v = 0;
        v = exp( ((x-width/2.0)*(x-width/2.0)+(y-height/2.0)*(y-height/2.0))/(-2*r*r));
        tot += v;
        if(!(std::is_same<T,float>::value || std::is_same<T,double>::value)){
            v *= std::numeric_limits<T>::max();
        }
        img.setPixel(x,y,0,v);
    }
    for(uint16_t x = 0;x<width;x++)for(uint16_t y = 0;y<height;y++){
        img.setPixel(x,y,img.getPixel(x,y)/tot);
    }

    return img;
}


template<typename T> Image<T> Image<T>::random(uint16_t w,uint16_t h,uint16_t c){
    Image<T> img(w,h,c);
    for(int i = 0;i<c;i++){
        for(int j = 0;j < w*h;j++){
            if((std::is_same<T,float>::value || std::is_same<T,double>::value)){
                img.data[i][j] = float(rand()) / float(RAND_MAX);
            }else{
                img.data[i][j] = (float(rand()) / float(RAND_MAX) ) * std::numeric_limits<T>::max();

            }
        }
    }
    return img;
}




};
