
#include <AoTK/aotk.h>




namespace AoTK{

Image::Image(const Image& img):
    data(0),
    w(img.w),
    h(img.h),
    mode(img.mode)
{
    unsigned int c =0;
    switch(mode){
        case RGB:
            c = 3;
            break;
        case RGBA:
            c = 4;
            break;
        case GREYSCALE:
            c = 1;
            break;
        default:
            break;
    }
    memcpy(data,img.data,w*h*c);
}
Image& Image::operator=(const Image &img){
    if(this == &img)
        return *this;

    delete data;

    w = img.w;
    h = img.h;
    mode = img.mode;

    unsigned int c =0;
    switch(mode){
        case RGB:
            c = 3;
            break;
        case RGBA:
            c = 4;
            break;
        case GREYSCALE:
            c = 1;
            break;
        default:
            break;
    }
    memcpy(data,img.data,w*h*c);

    return *this;
}

Image::Image(unsigned int _w,unsigned int _h,IMG_MODE _mode):
    data(0),
    w(_w),
    h(_h),
    mode(_mode){
    setSize(w,h,0);
}
Image::Image():
    data(0),
    w(0),
    h(0),
    mode(RGBA){
}
Image::~Image(){
    delete data;
}

float Image::getGreyscale(unsigned int x,unsigned int y){
    assert(mode == GREYSCALE);
    assert(x<w && y<h && "Index outside of image");
    unsigned int index = (x+y*w);
    return data[index];
}
Color<> Image::getColor(unsigned int x,unsigned int y){
    Color<> col;
    col.a = 1;
    switch(mode){
        case GREYSCALE:
            col.r = col.g = col.b = data[x+y*w];
            break;
        case RGB:
            col.r = data[(x+y*w)*3+0];
            col.g = data[(x+y*w)*3+1];
            col.b = data[(x+y*w)*3+2];
            break;
        case RGBA:
            col.r = data[(x+y*w)*4+0];
            col.g = data[(x+y*w)*4+1];
            col.b = data[(x+y*w)*4+2];
            col.a = data[(x+y*w)*4+3];
            break;
        default:
            assert(false && "Unsuported mode __FILE__ : __LINE__");
    }

    return col;
}

void Image::setColor(unsigned int x,unsigned int y,Color<> rgb){
    assert(x<w && y<h && "Index outside of image");
    unsigned int c = 0;
    switch(mode){
        case RGB:
            c = 3;
            break;
        case RGBA:
            c = 4;
            break;
        case GREYSCALE:
        default:
            assert(false && "Unsupported mode for setColor");
    }
    unsigned int index = (x+y*w) *c;
    data[index] = rgb.r;
    data[index+1] = rgb.g;
    data[index+2] = rgb.b;
    if(c == 4)
        data[index+3] = rgb.a;

}
void Image::setColor(unsigned int x,unsigned int y,float grey){
    assert(mode == GREYSCALE);
    assert(x<w && y<h && "Index outside of image");
    unsigned int index = (x+y*w);
    data[index] = grey;
}

void Image::setMode(IMG_MODE m){
    switch(mode){
        case GREYSCALE:
            switch(m){
                case RGB:
                    GREY2RGB();
                    break;
                case RGBA:
                    GREY2RGBA();
                    break;
                case GREYSCALE:
                default:break;
            }
            break;
        case RGB:
            switch(m){
                case RGB:
                    break;
                case RGBA:
                    RGB2RGBA();
                    break;
                case GREYSCALE:
                    RGB2GREY();
                    break;
                default:break;
            }
            break;
        case RGBA:
            switch(m){
                case RGB:
                    RGBA2RGB();
                    break;
                case RGBA:
                    break;
                case GREYSCALE:
                    RGBA2GREY();
                    break;
                default:
                    break;
            }
            break;
        default: break;
    }
}

void Image::setSize(unsigned int _w,unsigned int _h,bool keep){
    if(keep){
        assert(false && "Parts of setsize not yet implemented");
    }else{
        if(data)
            delete data;
        unsigned int c;
        if(mode == RGB)
            c = 3;
        else if(mode == RGBA)
            c = 4;
        else
            c = 1;
        this->w = _w;
        this->h = _h;
        data = new float[w*h*c]();
        clear();
    }
}

void Image::RGB2RGBA(){
    float *tmp = data;
    data = new float[w*h*4]();
    for(unsigned int i = 0;i<w*h;i++){
        data[i*4+0] = tmp[i*3+0];
        data[i*4+1] = tmp[i*3+1];
        data[i*4+2] = tmp[i*3+2];
        data[i*4+3] = 1;
    }
    mode = RGBA;
    delete tmp;
}
void Image::RGB2GREY(){ //0.2989 * R + 0.5870 * G + 0.1140 * B
    float *tmp = data;
    data = new float[w*h]();
    for(unsigned int i = 0;i<w*h;i++){
        data[i]  = 0.298933*tmp[i*3+0];
        data[i] += 0.587033*tmp[i*3+1];
        data[i] += 0.114033*tmp[i*3+2];
    }
    mode = GREYSCALE;
    delete tmp;
}
void Image::RGBA2GREY(bool alphascale){ //   ( 0.2989 * R + 0.5870 * G + 0.1140 * B ) * A
    float *tmp = data;
    data = new float[w*h]();
    for(unsigned int i = 0;i<w*h;i++){
        data[i]  = 0.298933*tmp[i*4+0];
        data[i] += 0.587033*tmp[i*4+1];
        data[i] += 0.114033*tmp[i*4+2];
        if(alphascale)
            data[i] *= tmp[i*4+3];
    }
    mode = GREYSCALE;
    delete tmp;
}
void Image::RGBA2RGB(bool alphascale){ //
    float *tmp = data;
    data = new float[w*h*3]();
    for(unsigned int i = 0;i<w*h;i++){
        data[i*3+0]  = tmp[i*4+0];
        data[i*3+1] += tmp[i*4+1];
        data[i*3+2] += tmp[i*4+2];
        if(alphascale){
            data[i*3+0] *= tmp[i*4+3];
            data[i*3+1] *= tmp[i*4+3];
            data[i*3+2] *= tmp[i*4+3];
        }
    }
    mode = RGB;
    delete tmp;
}
void Image::GREY2RGBA(){
    float *tmp = data;
    data = new float[w*h*4]();
    for(unsigned int i = 0;i<w*h;i++){
        data[i*4+0] = tmp[i];
        data[i*4+1] = tmp[i];
        data[i*4+2] = tmp[i];
        data[i*4+3] = 1;
    }
    mode = RGBA;
    delete tmp;
}

void Image::GREY2RGB(){
    float *tmp = data;
    data = new float[w*h*3]();
    for(unsigned int i = 0;i<w*h;i++){
        data[i*3+0] = tmp[i];
        data[i*3+1] = tmp[i];
        data[i*3+2] = tmp[i];
    }
    mode = RGB;
    delete tmp;
}

void Image::clear(float _i){
    unsigned int c =0;
    switch(mode){
        case RGB:
            c = 3;
            break;
        case RGBA:
            c = 4;
            break;
        case GREYSCALE:
            c = 1;
            break;
        default:
            assert(false && "Unsupported mode in clear()");
    }
    for(unsigned int i = 0; i< w*h*c;i++){
        data[i] = _i;
    }
}
void Image::normalize(float min,float max){
    assert(max<=min);
    if(w == 0|| h==0)
        return;
    if(mode == GREYSCALE){
        float _min = data[0];
        float _max = data[0];
        for(unsigned int i = 0; i< w*h;i++){
            if(data[i] < _min) _min = data[i];
            if(data[i] > _min) _max = data[i];
        }
        for(unsigned int i = 0; i< w*h;i++){
            data[i] = (data[i] - _min) / (_max-_min); //map between 0 and 1
            data[i] = (data[i] * (max-min)) + min; //map to min and max
        }
    }
    assert(false && "Not yet implemented");

}
void Image::toGreyscale(){assert(false && "toGreyScale not yet implemented");}

Image Image::random(unsigned int w,unsigned int h, IMG_MODE mode){
    Image img(w,h,mode);
    unsigned int c = 0;
    switch(mode){
        case RGB:
            c = 3;
            break;
        case RGBA:
            c = 4;
            break;
        case GREYSCALE:
            c = 1;
            break;
        default:
            assert(false && "Unsupported mode in clear()");
    }
    for(unsigned int i = 0;i<w*h*c;i++){
        if(c == 4 && i%4 == 3)
            img.data[i] = 1;
        else
            img.data[i] = rand()/float(RAND_MAX);

    }

    return img;
}
};

