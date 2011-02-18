
#include <AoTK/aotk.h>




namespace AoTK{

Object::Object(GLint shader,Matrix _toWorld,std::string _name){
    if(_name.length() == 0){
        static int uid = 0;
        char buf[30];
        sprintf(buf,"unnamed_object_%i",uid++);
        name = buf;
    }else
        name = _name;
    toWorld = _toWorld;
    aotk->registerObject(this);

    prev_frame_logic = 0;
    prev_frame_graphics = 0;
    prev_frame_prepare = 0;

    setShader(shader);
    std::cout << "created object: " << name << std::endl;
}

void Object::setShader(GLint shader){
    pgm = shader;
//    proj_matrix_loc  = glGetUniformLocation(pgm,"projection_matrix");
//    view_matrix_loc  = glGetUniformLocation(pgm,"view_matrix");
//    model_matrix_loc = glGetUniformLocation(pgm,"model_matrix");

}
void Object::doLogic(unsigned int cur_frame){
    if(prev_frame_logic != cur_frame){
        prev_frame_logic = cur_frame;
        logic();
    }
    getAllError(__FILE__,__LINE__);
}
void Object::doGraphic(unsigned int cur_frame){
    if(prev_frame_graphics != cur_frame){
        prev_frame_graphics = cur_frame;
        graphic();
    }
    getAllError(__FILE__,__LINE__);
}
void Object::doPrepare(unsigned int cur_frame){
    if(prev_frame_prepare != cur_frame){
        prev_frame_prepare = cur_frame;
        prepare();
    }

    getAllError(__FILE__,__LINE__);
}
void Object::doRender(){
    //glUseProgram(pgm);
    getAllError(__FILE__,__LINE__);
    glPushMatrix();
    glMultMatrixf(toWorld._1d);
    render();
    glPopMatrix();
    glUseProgram(0);
    getAllError(__FILE__,__LINE__);
}

Vector4<> Object::getCenter(){
//    return toWorld * Vector4<>(0,0,0,1);
    return Vector4<>(); //TODO fix this
}
Matrix Object::getToWorldMatrix(){
    return toWorld;
}


Object::~Object(){
    aotk->unregisterObject(this);
}
};

