#ifndef DVR_H
#define DVR_H

#include "../object.h"
#include "../listeners.h"
#include "../fbo.h"
#include "../aotk.h"

namespace AoTK{

class DVR : public Object, KeyboardListener, ResizeListener, MouseMotionListener, ScrollListener{
    enum RayMethod{
        RayInCoord = 0,
        RayOutCoord,
        avg,
        GradMag,
        mip,
        density
    } type;
public:
    struct VolumeInfo{
        std::string filename;
        unsigned int width;
        unsigned int height;
        unsigned int depth;
        VolumeInfo():filename(""),width(0),height(0),depth(0){}
        VolumeInfo(std::string f,unsigned int w,unsigned int h,unsigned int d):filename(f),width(w),height(h),depth(d){}
        VolumeInfo(const VolumeInfo &v):filename(v.filename),width(v.width),height(v.height),depth(v.depth){}
    };


    virtual void mousemotion(int dx,int dy);
    virtual void passiveMousemotion(int dx,int dy){}

    DVR(GLint shader,VolumeInfo vi,Matrix toWorld = Matrix(),std::string = "");
    ~DVR();
    DVR() = delete;
    DVR(const DVR &o) = delete;
    DVR &operator=(const DVR &o) = delete;


    virtual void resize(unsigned int w,unsigned int h);

    virtual void scroll(int p);

    virtual void keyUp(KEY key);
    virtual void keyDown(KEY key);
    virtual void keyImpulse(unsigned char key);

private:
    Matrix trans;
    GLubyte *data;
    float roty;
    float rotx;
    float threshold;
    float stepsize;
    float div_coeff;
    VolumeInfo volumeInfo;
    GLuint tex;
    FBO frontFace;
    FBO backFace;

    GLint vol_tex_loc;
    GLint front_tex_loc;
    GLint back_tex_loc;
    GLint window_size_loc;
    GLint threshold_loc;
    GLint stepsize_loc;
    GLint div_coeff_loc;
    GLint type_loc;

    unsigned int win_w,win_h;

    void calcGradients();
    void drawFaces();
protected:
    virtual void logic();
    virtual void graphic();
    virtual void prepare();
    virtual void render();

};
};

#endif
