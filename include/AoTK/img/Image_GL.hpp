namespace AoTK{
    template<>
    GLuint Image<uint8_t>::toGLTexture(){
        GLuint tex;
        glGenTextures(1,&tex);
        glBindTexture(GL_TEXTURE_2D,tex);

        glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

        glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_R,GL_REPEAT);

        //float *glData = (float*)malloc(sizeof(float)*width*height*3);
        GLubyte *glData = (GLubyte*)malloc(sizeof(GLubyte)*width*height*4);
        std::cout << width << " " << height << std::endl;
        for(int i = 0;i<width*height;i++){
            glData[i*4+0] = data[0][i];
            glData[i*4+1] = data[1][i];
            glData[i*4+2] = data[2][i];
            glData[i*4+3] = 255;
        }

        glTexImage2D(GL_TEXTURE_2D,0,4,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,glData);

        free(glData);

        glBindTexture(GL_TEXTURE_2D,0);

        return tex;
    }


    template<>
    GLuint Image<float>::toGLTexture(){
        GLuint tex;
        glGenTextures(1,&tex);
        glBindTexture(GL_TEXTURE_2D,tex);

        glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

        glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_R,GL_REPEAT);

        //float *glData = (float*)malloc(sizeof(float)*width*height*3);
        GLfloat *glData = (GLfloat*)malloc(sizeof(GLfloat)*width*height*4);
        std::cout << width << " " << height << std::endl;
        for(int i = 0;i<width*height;i++){
            if(channels == 3){
                glData[i*4+0] = data[0][i];
                glData[i*4+1] = data[1][i];
                glData[i*4+2] = data[2][i];
                glData[i*4+3] = 1.0;
            }else if(channels == 4){
                glData[i*4+0] = data[0][i]/data[3][i];
                glData[i*4+1] = data[1][i]/data[3][i];
                glData[i*4+2] = data[2][i]/data[3][i];
                glData[i*4+3] = data[3][i]/data[3][i];
            }else if(channels == 1){
                glData[i*4+0] = data[0][i];
                glData[i*4+1] = data[0][i];
                glData[i*4+2] = data[0][i];
                glData[i*4+3] = 1.0;
            }
        }

        glTexImage2D(GL_TEXTURE_2D,0,4,width,height,0,GL_RGBA,GL_FLOAT,glData);

        free(glData);

        glBindTexture(GL_TEXTURE_2D,0);

        return tex;
    }


    template<>
    Image<uint8_t> Image<uint8_t>::FromCurrentGLContext(){
        uint16_t w,h;
        GLint m_viewport[4];
        glGetIntegerv( GL_VIEWPORT, m_viewport );

        w = m_viewport[2];
        h = m_viewport[3];

        Image img(w,h,4);
        GLubyte *data = (GLubyte*)malloc(sizeof(GLubyte)*w*h*4);
        glReadPixels(0,0,w,h,GL_RGBA,GL_UNSIGNED_BYTE,data);
        for(int j = 0;j<w*h;j++)for(int i = 0;i<4;i++){
            img.data[i][j] = data[j*4+i];
        }

        return img;

    }
    template<>
    Image<uint8_t> Image<uint8_t>::FromCurrentGLContextDepth(){
        uint16_t w,h;
        GLint m_viewport[4];
        glGetIntegerv( GL_VIEWPORT, m_viewport );

        w = m_viewport[2];
        h = m_viewport[3];

        Image img(w,h,4);
        GLubyte *data = (GLubyte*)malloc(sizeof(GLubyte)*w*h);
        glReadPixels(0,0,w,h,GL_DEPTH_COMPONENT,GL_UNSIGNED_BYTE,data);
        for(int j = 0;j<w*h;j++){
            img.data[0][j] = data[j];
            img.data[1][j] = data[j];
            img.data[2][j] = data[j];
            img.data[3][j] = 255;
        }

        return img;

    }
    template<>
    Image<float> Image<float>::FromCurrentGLContextDepth(){
        uint16_t w,h;
        GLint m_viewport[4];
        glGetIntegerv( GL_VIEWPORT, m_viewport );

        w = m_viewport[2];
        h = m_viewport[3];

        Image img(w,h,4);
        float *data = (float*)malloc(sizeof(float)*w*h);
        glReadPixels(0,0,w,h,GL_DEPTH_COMPONENT,GL_FLOAT,data);
        for(int j = 0;j<w*h;j++){
            img.data[0][j] = data[j];
            img.data[1][j] = data[j];
            img.data[2][j] = data[j];
            img.data[3][j] = 1;
        }

        return img;

    }


    template<>
    Image<uint8_t> Image<uint8_t>::FromGLTexture(GLuint tex){
        GLint w,h,c,type;
        glBindTexture(GL_TEXTURE_2D,tex);
        glGetTexLevelParameteriv(GL_TEXTURE_2D,0,GL_TEXTURE_WIDTH,&w);
        glGetTexLevelParameteriv(GL_TEXTURE_2D,0,GL_TEXTURE_HEIGHT,&h);
        glGetTexLevelParameteriv(GL_TEXTURE_2D,0,GL_TEXTURE_INTERNAL_FORMAT,&type);

        switch(type){
            case GL_DEPTH_COMPONENT:
            case GL_DEPTH_COMPONENT16:
            case GL_DEPTH_COMPONENT24:
            case GL_DEPTH_COMPONENT32:
                type = GL_DEPTH_COMPONENT;
            case 1:
            case GL_LUMINANCE:
            case GL_ALPHA:
                c = 1;
                break;
            case 3:
            case GL_RGB:
                c = 3;
                break;
            case 4:
            case GL_RGBA:
                c = 4;
                break;
            default:
                std::cerr << "Unsupported internal format: " << type << std::endl;
                assert(false && "unsupported internal format");
        }

        std::cout << tex << " "  << w << " " << h << " " << c << " " << type << std::endl;
        if(w<= 0 || h <= 0 || c <= 0)
            return Image<uint8_t>();

        GLubyte* data = (GLubyte*)malloc(sizeof(GLubyte)*w*h*c);
        glGetTexImage(GL_TEXTURE_2D,0,type,GL_UNSIGNED_BYTE,data);

        GLint err = glGetError();
        if(err != GL_NO_ERROR){
            std::cout << GL_NO_ERROR << std::endl;
        }

        glBindTexture(GL_TEXTURE_2D,0);


        Image<uint8_t> img = Image<uint8_t>(w,h,c);

        for(int j = 0;j<w*h;j++)for(int i = 0;i<c;i++){
            img.data[i][j] = data[j*c+i];
        }

        free(data);
        return img;
    }

    template<>
    Image<float> Image<float>::FromGLTexture(GLuint tex){
        GLint w,h,c,type;
        glBindTexture(GL_TEXTURE_2D,tex);
        glGetTexLevelParameteriv(GL_TEXTURE_2D,0,GL_TEXTURE_WIDTH,&w);
        glGetTexLevelParameteriv(GL_TEXTURE_2D,0,GL_TEXTURE_HEIGHT,&h);
        glGetTexLevelParameteriv(GL_TEXTURE_2D,0,GL_TEXTURE_INTERNAL_FORMAT,&type);

        switch(type){
            case GL_DEPTH_COMPONENT:
            case GL_DEPTH_COMPONENT16:
            case GL_DEPTH_COMPONENT24:
            case GL_DEPTH_COMPONENT32:
                type = GL_DEPTH_COMPONENT;
            case 1:
            case GL_LUMINANCE:
            case GL_ALPHA:
                c = 1;
                break;
            case 3:
            case GL_RGB:
                c = 3;
                break;
            case 4:
            case GL_RGBA:
                c = 4;
                break;
            default:
                std::cerr << "Unsupported internal format: " << type << std::endl;
                assert(false && "unsupported internal format");
        }


        std::cout << tex << " "  << w << " " << h << " " << c << " " << type << std::endl;
        if(w<= 0 || h <= 0 || c <= 0)
            return Image<uint8_t>();



        float* data = (float*)malloc(sizeof(float)*w*h*c);
        glGetTexImage(GL_TEXTURE_2D,0,type,GL_FLOAT,data);

        GLint err = glGetError();
        if(err != GL_NO_ERROR){
            std::cout << GL_NO_ERROR << std::endl;
        }

        glBindTexture(GL_TEXTURE_2D,0);


        Image<float> img = Image<float>(w,h,c);

        for(int j = 0;j<w*h;j++)for(int i = 0;i<c;i++){
            img.data[i][j] = data[j*c+i];
        }

        free(data);
        return img;
    }

};
