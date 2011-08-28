
#include <AoTK/aotk.h>

namespace AoTK{
namespace IMG{

template<> template<> Image<double>::Image(const Image<uint8_t> &img):
    width(img.width),
    height(img.height),
    channels(img.channels),
    data(0)
{
    data = new double*[channels]();
    for(int i = 0;i<channels;i++){
        data[i] = new double[width*height]();
        for(int j = 0;j<width*height;j++){
            data[i][j]= img.data[i][j]/255.0;
        }
    }
}
template<> template<> Image<double>::Image(const Image<float> &img):
    width(img.width),
    height(img.height),
    channels(img.channels),
    data(0)
{
    data = new double*[channels]();
    for(int i = 0;i<channels;i++){
        data[i] = new double[width*height]();
        for(int j = 0;j<width*height;j++){
            data[i][j]= (double)img.data[i][j];
        }
    }
}

};
};
