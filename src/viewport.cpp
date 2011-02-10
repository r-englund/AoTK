
#include <AoTK/aotk.h>





namespace AoTK{

Viewport::Viewport(Scene *s,Camera *_cam,std::string _name):ResizeListener(_name),size(1,1),pos(0.5,0.5),cam(_cam),scene(s){
    if(_name.length() == 0){
        static int uid = 0;
        char buf[30];
        sprintf(buf,"unnamed_viewport_%i",uid++);
        name = buf;
    }else
        name = _name;
    aotk->registerViewport(this);
    std::cout << "Created Viewport: " << name << std::endl;
}

Viewport::~Viewport(){
    aotk->unregisterViewport(this);
}

void Viewport::setViewport(){
    getAllError(__FILE__,__LINE__);
    glViewport(vp_params[0],vp_params[1],vp_params[2],vp_params[3]);
    getAllError(__FILE__,__LINE__);

}
void Viewport::resize(unsigned int w,unsigned int h){
    if(abs(size.w - 1) < 0.001 && abs(size.h - 1) < 0.001 ){
        vp_params[0] = 0;
        vp_params[1] = 0;
        vp_params[2] = w;
        vp_params[3] = h;
    }
    else if(size.w<=1 && size.h>0){
        vp_params[0] = w*pos.x - (size.w*w*0.5);
        vp_params[2] = w*pos.x + (size.w*w*0.5);
        vp_params[1] = h*pos.y - (size.h*h*0.5);
        vp_params[3] = h*pos.y + (size.h*h*0.5);

    }else{
        vp_params[0] = w*pos.x - size.w*0.5;
        vp_params[1] = w*pos.x - size.h*0.5;
        vp_params[2] = h*pos.y + size.w*0.5;
        vp_params[3] = h*pos.y + size.h*0.5;
    }
}


};
