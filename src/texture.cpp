#include <AoTK/aotk.h>




namespace AoTK{


GLuint Create2DTexture(const Image &i,TextureSettings set){
    GLuint tex;
    glGenTextures(1,&tex);
    glBindTexture(GL_TEXTURE_2D,tex);

    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,set.min_filt);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,set.mag_filt);

    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,set.wrap_s);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,set.wrap_t);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_R,set.wrap_r);

    if(!GLEW_ARB_framebuffer_object){
        glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

        glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
    }

    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,i.getWidth(),i.getHeight(),0,GL_RGBA,GL_FLOAT,i.getData());

    if(GLEW_ARB_framebuffer_object){
        glGenerateMipmap(GL_TEXTURE_2D);
    }


    glBindTexture(GL_TEXTURE_2D,0);
    return tex;
}
GLuint Create1DTexture(const Image &i,unsigned int row_or_col,bool row,TextureSettings){
    return 0; //TODO implement
}
};
