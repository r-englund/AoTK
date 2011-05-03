#ifndef AOTK_FBO_H
#define AOTK_FBO_H

#include <AoTK\window_handler.h>
#include <map>


namespace AoTK{
    class FBO{
        std::vector<GLuint> attachment;
        uint16_t _w,_h;
        GLuint _depth;
        GLuint _depthtex;
        bool isInit;
        GLuint _fbo;
        GLuint _numAttachemnts;
    public:
        FBO();
        virtual ~FBO();
        void init();
        void setSize(uint16_t w,uint16_t h);
        uint8_t createAttachment();
        GLuint getTexture(uint8_t attatchemntID = 0);
        GLuint getDepthTexture();

        void bind(uint8_t attatchemntID = 0);
        void bind(uint8_t* attatchemntIDs,uint8_t num_attachemnts);
        void clear(uint8_t attatchemntID = 0);
        void clear(uint8_t* attatchemntIDs,uint8_t num_attachemnts);
        void unbind();

        void fboerror();

        void render(uint8_t attatchemntID = 0); // render on a fullscreen quad
    };
};

#endif
