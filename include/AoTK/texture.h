#ifndef TEXTURE_H
#define TEXTURE_H



#include "image.h"
namespace AoTK{
struct TextureSettings{
    GLenum type;

    GLfloat min_filt;
    GLfloat mag_filt;
    GLfloat wrap_s;
    GLfloat wrap_t;
    GLfloat wrap_r;

    TextureSettings()
        :
        type(GL_TEXTURE_2D),
        min_filt(GL_LINEAR_MIPMAP_NEAREST),
        mag_filt(GL_LINEAR),
        wrap_s(GL_REPEAT),
        wrap_t(GL_REPEAT),
        wrap_r(GL_REPEAT)
    {


    }
};

GLuint Create2DTexture(const Image &i,TextureSettings = TextureSettings());
GLuint Create1DTexture(const Image &i,unsigned int row_or_col = 0,bool row = true,TextureSettings = TextureSettings());
};
#endif

