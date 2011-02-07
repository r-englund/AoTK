#ifndef CAMERA_H
#define CAMERA_H

#include "object.h"
#include "listeners.h"

namespace AoTK{
class Camera : public Object , public ResizeListener{
    Matrix projectionMatrix;
    float fov;
public:
    Matrix getProjectionMatrix() const;
    Camera(float fov,Matrix toWorld = Matrix(),std::string name = "");
    virtual ~Camera(){}

    virtual void resize(unsigned int w,unsigned int h);

    void logic();
    void graphic();
    void prepare();
    void render();
};

};
#endif
