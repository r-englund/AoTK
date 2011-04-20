

namespace AoTK{
struct BMPMAGIC{
    unsigned char magic[2];
};

struct BMPHEADER{
    uint32_t size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offset;
};

struct BITMAPINFOHEADER40{
    uint32_t size;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bpp;
    uint32_t compress_type;
    uint32_t bmp_bytesz;
    int32_t hres;
    int32_t vres;
    uint32_t ncolors;
    uint32_t nimpcolors;
};

enum BMP_COMPRESS_TYPE{
  BMP_RGB = 0,
  BMP_RLE8,
  BMP_RLE4,
  BMP_BITFIELDS,
  BMP_JPEG,
  BMP_PNG,
};

struct PIXEL24BIT{
    uint8_t blue;
    uint8_t green;
    uint8_t red;
};

template<>
void Image<uint8_t>::saveBMP(std::string filename){
    BMPMAGIC mp;
    BMPHEADER bmpheader;
    BITMAPINFOHEADER40 infoheader;
    mp.magic[0] = 'B';
    mp.magic[1] = 'M';
    bmpheader.size = sizeof(BMPMAGIC) * sizeof(BMPHEADER) * sizeof(BITMAPINFOHEADER40) * width*height*3;
    bmpheader.reserved1 = 0;
    bmpheader.reserved1 = 0;
    bmpheader.offset = 54;


    infoheader.size = 40;
    infoheader.width = width;
    infoheader.height = height;
    infoheader.planes = 1;
    infoheader.bpp = 24;
    infoheader.compress_type = 0;
    infoheader.bmp_bytesz = width*height*3;
    infoheader.hres = 0x130B0000;
    infoheader.vres = 0x130B0000;
    infoheader.ncolors = 0;
    infoheader.nimpcolors = 0;

    FILE *f = fopen(filename.c_str(),"wb");
    assert(f != NULL);
    fwrite(&mp,sizeof(BMPMAGIC),1,f);
    fwrite(&bmpheader,sizeof(BMPHEADER),1,f);
    fwrite(&infoheader,sizeof(BITMAPINFOHEADER40),1,f);

    int i=0;
    for(int y = 0; y<infoheader.height;y++){
            unsigned int pad_bytes = 0;
            for(int x = 0; x<infoheader.width;x++){
                pad_bytes++;
                PIXEL24BIT pixel;
                if(channels == 1){
                    pixel.red   = data[0][i];
                    pixel.green = data[0][i];
                    pixel.blue  = data[0][i];
                }else{
                    pixel.red   = data[0][i];
                    pixel.green = data[1][i];
                    pixel.blue  = data[2][i];

                }
                i++;
                fwrite(&pixel,sizeof(PIXEL24BIT),1,f);
            }
            pad_bytes = pad_bytes % 4;
            uint8_t pad = 0;
            for(unsigned int p = 0;p<pad_bytes;p++)
                fwrite(&pad,1,1,f);
        }
        fclose(f);
}


template<>
void Image<float>::saveBMP(std::string filename){
    BMPMAGIC mp;
    BMPHEADER bmpheader;
    BITMAPINFOHEADER40 infoheader;
    mp.magic[0] = 'B';
    mp.magic[1] = 'M';
    bmpheader.size = sizeof(BMPMAGIC) * sizeof(BMPHEADER) * sizeof(BITMAPINFOHEADER40) * width*height*3;
    bmpheader.reserved1 = 0;
    bmpheader.reserved1 = 0;
    bmpheader.offset = 54;


    infoheader.size = 40;
    infoheader.width = width;
    infoheader.height = height;
    infoheader.planes = 1;
    infoheader.bpp = 24;
    infoheader.compress_type = 0;
    infoheader.bmp_bytesz = width*height*3;
    infoheader.hres = 0x130B0000;
    infoheader.vres = 0x130B0000;
    infoheader.ncolors = 0;
    infoheader.nimpcolors = 0;

    FILE *f = fopen(filename.c_str(),"wb");
    assert(f != NULL);
    fwrite(&mp,sizeof(BMPMAGIC),1,f);
    fwrite(&bmpheader,sizeof(BMPHEADER),1,f);
    fwrite(&infoheader,sizeof(BITMAPINFOHEADER40),1,f);

    int i=0;
    for(int y = 0; y<infoheader.height;y++){
            unsigned int pad_bytes = 0;
            for(int x = 0; x<infoheader.width;x++){
                pad_bytes++;
                PIXEL24BIT pixel;
                if(channels == 1){
                    pixel.red   = 255*data[0][i];
                    pixel.green = 255*data[0][i];
                    pixel.blue  = 255*data[0][i];
                }else{
                    pixel.red   = 255*data[0][i];
                    pixel.green = 255*data[1][i];
                    pixel.blue  = 255*data[2][i];
                }
                i++;
                fwrite(&pixel,sizeof(PIXEL24BIT),1,f);
            }
            pad_bytes = pad_bytes % 4;
            uint8_t pad = 0;
            for(unsigned int p = 0;p<pad_bytes;p++)
                fwrite(&pad,1,1,f);
        }
        fclose(f);
}


template<>
Image<uint8_t> Image<uint8_t>::LoadBMP(std::string filename){
    Image<uint8_t> i;
    FILE *file = fopen(filename.c_str(),"rb");
    assert(file && "file could not be loaded");

    BMPMAGIC mg;
    fread(&mg,sizeof(BMPMAGIC),1,file);
    assert(mg.magic[0] == 'B' && mg.magic[1] == 'M' && "Not a bmp file, try again or contact the developers");

    BMPHEADER header;
    fread(&header,sizeof(BMPHEADER),1,file);

    if(header.offset-14 == 40){
        BITMAPINFOHEADER40 info;
        fread(&info,sizeof(BITMAPINFOHEADER40),1,file);

        assert(info.compress_type == BMP_RGB);
        assert(info.planes == 1);
        assert(info.bpp == 24 && "Only 24 bit bmp are support");

        Image<uint8_t> img = Image<uint8_t>(info.width,info.height,3);
        i = img;
        fseek(file,header.offset,SEEK_SET);
        for(int y = 0; y<info.height;y++){
            unsigned int pad_bytes = 0;
            for(int x = 0; x<info.width;x++){
                pad_bytes++;
                PIXEL24BIT pixel;
                fread(&pixel,sizeof(PIXEL24BIT),1,file);
                i.setPixel(x,y,0,pixel.red);
                i.setPixel(x,y,1,pixel.green);
                i.setPixel(x,y,2,pixel.blue);
            }
            pad_bytes = pad_bytes % 4;
            if(pad_bytes)
                fseek(file,pad_bytes,SEEK_CUR);
        }


    }else{
        assert(false && "Header in bmp not yet supported, contect developers for more info");
    }

    fclose(file);
    return i;
}
};
