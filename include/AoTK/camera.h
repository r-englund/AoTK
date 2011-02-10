#ifndef CAMERA_H
#define CAMERA_H

#include "object.h"
#include "listeners.h"

namespace AoTK{
class Camera : public Object , public ResizeListener{
    Matrix projectionMatrix;
    bool rend;
    float fov;

    float rotX,rotY;

    Position pos;

public:
    Matrix getProjectionMatrix() const;
    Camera(Position pos = Position(0,0,0), Direction dir = Direction(0,0,-1), float fov = 60,std::string name = "");
    virtual ~Camera(){}

    virtual void resize(unsigned int w,unsigned int h);


    void logic();
    void graphic();
    void prepare();
    void render();
};

};
#endif
