
#include <AoTK/aotk.h>

namespace AoTK{
namespace IMG{

template<> template<> Image<uint8_t>::Image(const Image<float> &img):
    width(img.width),
    height(img.height),
    channels(img.channels),
    data(0)
{
    data = new uint8_t*[channels]();
    for(int i = 0;i<channels;i++){
        data[i] = new uint8_t[width*height]();
        for(int j = 0;j<width*height;j++){
            data[i][j]= img.data[i][j]*255;
        }
    }
}
template<> template<> Image<uint8_t>::Image(const Image<double> &img):
    width(img.width),
    height(img.height),
    channels(img.channels),
    data(0)
{
    data = new uint8_t*[channels]();
    for(int i = 0;i<channels;i++){
        data[i] = new uint8_t[width*height]();
        for(int j = 0;j<width*height;j++){
            data[i][j]= img.data[i][j]*255;
        }
    }
}

};
};
