#ifndef IMAGE_H
#define IMAGE_H

#include <AoTK/aotk.h>

namespace AoTK{
class Image{
private:
    float *data;
    unsigned int w; //Width
    unsigned int h; //Height
    IMG_MODE mode;


    void RGB2RGBA();
    void RGB2GREY();
    void RGBA2RGB(bool alphascale = false);
    void RGBA2GREY(bool alphascale = false);
    void GREY2RGBA();
    void GREY2RGB();
public:
    Image(unsigned int w,unsigned int h,IMG_MODE mode = RGBA);
    Image();
    ~Image();
    Image(const Image&);
    Image& operator=(const Image&);

    float getGreyscale(unsigned int w,unsigned int h);
    Color<> getColor(unsigned int w,unsigned int h);
    void setColor(unsigned int w,unsigned int h,Color<> rgb);
    void setColor(unsigned int w,unsigned int h,float grey);

    float* getData()const{return data;}
    void setData(float *_data){data = _data;}

    unsigned int getWidth()const{return w;}
    unsigned int getHeight()const{return h;}

    float* getRow(unsigned int row);
    float* getCol(unsigned int col);

    IMG_MODE getMode(){return mode;}

    void convolution(const Image &filter,FILTER_WRAP padding = ZERO_PADDING); //TODO implement

    void setSize(unsigned int w,unsigned int h,bool keep = true);
    void setMode(IMG_MODE m);
    void normalize(float min = 0,float max = 1);
    void toGreyscale();

    void clear(float i = 0);

    void saveBMP(std::string filename);
    void savePNG(std::string filename);
    void saveJPG(std::string filename);
    void saveGIF(std::string filename);

    static Image random(unsigned int w,unsigned int h, IMG_MODE mode = RGB);

    static Image LoadBMP(std::string filename);
    static Image LoadPNG(std::string filename);
    static Image LoadJPG(std::string filename);
    static Image LoadGIF(std::string filename);
};
};

#endif
