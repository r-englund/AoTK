


namespace AoTK{
namespace IMG{

template<> template<> Image<float>::Image(const Image<uint8_t> &img):
    width(img.width),
    height(img.height),
    channels(img.channels),
    data(0)
{
    data = new float*[channels]();
    for(int i = 0;i<channels;i++){
        data[i] = new float[width*height]();
        for(int j = 0;j<width*height;j++){
            data[i][j]= img.data[i][j]/255.0;
        }
    }
}
template<> template<> Image<float>::Image(const Image<double> &img):
    width(img.width),
    height(img.height),
    channels(img.channels),
    data(0)
{
    data = new float*[channels]();
    for(int i = 0;i<channels;i++){
        data[i] = new float[width*height]();
        for(int j = 0;j<width*height;j++){
            data[i][j]= (float)img.data[i][j];
        }
    }
}

};
};
