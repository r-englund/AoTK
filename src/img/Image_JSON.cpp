
#include <AoTK/aotk.h>

#include <fstream>

namespace AoTK{
namespace IMG{

template<>
void Image<uint8_t>::saveJSON(std::string filename,std::string name){
    std::ofstream f;
    f.open(filename);

    f << name << " = { " << std::endl;
    f << '"'<< "name" << '"' << ":" << '"' << name  << std::endl;
    f << '"'<< ",channels" << '"' << ":" << '"' << this->channels  << '"'<< std::endl;
    f << '"'<< ",width" << '"' << ":" << '"' << this->width  << '"'<< std::endl;
    f << '"'<< ",height" << '"' << ":" << '"' << this->height  << '"'<< std::endl;
    f << '"'<< ",pixels : [" << std::endl;
    for(int y = 0;y<this->height;y++)for(int x = 0;x<this->width;x++){
        if(this->channels == 1){
            f << "[" << (int)this->getPixel(x,y,0) << "]," << std::endl;
        }else if(this->channels == 3){
            f << "[" << (int)this->getPixel(x,y,0) << "," << (int)this->getPixel(x,y,1) << "," << (int)this->getPixel(x,y,2) << "]," << std::endl;
        }else if(this->channels == 4){
            f << "[" << (int)this->getPixel(x,y,0) << "," << (int)this->getPixel(x,y,1) << "," << (int)this->getPixel(x,y,2) << "," << (int)this->getPixel(x,y,3) << "]," << std::endl;
        }else{
            std::cout << "fuck" << std::endl;
        }
    }
    f << "]" << '"' << std::endl;


    f << "};" << std::endl;
    f.close();

}

};
};
