#include <AoTK/aotk.h>

namespace AoTK{


Camera::Camera(float _fov,Matrix _toWorld,std::string _name)
:Object(0,_toWorld,_name),
    ResizeListener(_name),
    projectionMatrix(Matrix()),
    rend(0),
    fov(_fov)
{
}

Matrix Camera::getProjectionMatrix() const{
    return projectionMatrix;
}

void Camera::resize(unsigned int w,unsigned int h){
    if(fov<=0){
        projectionMatrix = Matrix::orthogonalProjection(-w/2,w/2,-h/2,h/2,0.001,100);
    }else{
        projectionMatrix = Matrix::perspectiveProjection(fov,w/(float(h)),0.001,100);
    }
}

void Camera::logic(){
    if(aotk->keyState(ARROW_UP) ||aotk->keyState(W)){
        std::cout << "move forward" << std::endl;
    }else if(aotk->keyState(ARROW_DOWN) ||aotk->keyState(S)){
        std::cout << "move Back" << std::endl;
    }else if(aotk->keyState(ARROW_RIGHT) ||aotk->keyState(D)){
        std::cout << "move RIGHT" << std::endl;
    }else if(aotk->keyState(ARROW_LEFT) ||aotk->keyState(A)){
        std::cout << "move LEFT" << std::endl;
    }

}
void Camera::graphic(){}
void Camera::prepare(){}
void Camera::render(){
    if(!rend)
        return;
}
};
