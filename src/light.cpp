#include <AoTK/aotk.h>


namespace AoTK{
Light::Light(std::string _name):
    Object(0,Matrix(),_name),
    pos(0.0f,0.0f,0.0f,1.0f),
    amb(0.0f,0.0f,0.0f,1.0f),
    dif(1.0f,1.0f,1.0f,1.0f),
    spec(1.0f,1.0f,1.0f,1.0f),
    spot_exp(20.0f),
    spot_cutoff(30.0f),
    dir(0.0f,0.0f,-1.0f),
    con_att(1.0f),
    lin_att(0.0f),
    quad_att(0.0f)
{
    if(_name.length() == 0){
        static int uid = 0;
        char buf[30];
        sprintf(buf,"unnamed_lightsource_%i",uid++);
        name = buf;
    }else
        name = _name;

    std::cout << "created light: " << name << std::endl;
    aotk->registerLightSource(this);
}

Light::~Light(){
    aotk->unregisterLightSource(this);
}

void Light::graphic(){
    toWorld = Matrix::translate(pos.x,pos.y,pos.z);
}

void Light::setLight(GLuint id){
    glEnable(id);
    glLightfv(id,GL_AMBIENT,amb.arr);
    glLightfv(id,GL_DIFFUSE,dif.arr);
    glLightfv(id,GL_SPECULAR,spec.arr);
    glLightf(id,GL_CONSTANT_ATTENUATION,con_att);
    glLightf(id,GL_LINEAR_ATTENUATION,lin_att);
    glLightf(id,GL_QUADRATIC_ATTENUATION,quad_att);
    if(type == DIRECTION){
        GLfloat d[4] = {0,0,0,1};
        d[0] = dir.x;
        d[1] = dir.y;
        d[2] = dir.z;
        glLightfv(id,GL_POSITION,d);
    }else if(type == POINT){
        GLfloat p[4] = {0,0,0,1};
        p[0] = pos.x;
        p[1] = pos.y;
        p[2] = pos.z;
        glLightfv(id,GL_POSITION,p);
    }else if(type == SPOT){
        GLfloat p[4] = {0,0,0,1};
        p[0] = pos.x;
        p[1] = pos.y;
        p[2] = pos.z;
        glLightfv(id,GL_POSITION,p);
        glLightf(id,GL_SPOT_EXPONENT,spot_exp);
        glLightf(id,GL_SPOT_CUTOFF,spot_cutoff);
        glLightfv(id,GL_SPOT_DIRECTION,dir.arr);

    }
}

void Light::setAmbientColor(Color<> col){
    amb = col;
}
void Light::setDiffuseColor(Color<> col){
    dif = col;
}
void Light::setSpecularColor(Color<> col){
    spec = col;
}

void Light::setSpotExp(float exp){
    spot_exp = exp;
}
void Light::setSpotCutoff(float cutoff){
    spot_cutoff = cutoff;
}

void Light::setConstantAttenuation(float att){
    con_att = att;
}
void Light::setLinearAttenuation(float att){
    lin_att = att;
}
void Light::setQuadraticAttenuation(float att){
    quad_att = att;
}
void Light::setAttenuation(float constant,float linear,float quadratic){
    con_att = constant;
    lin_att = linear;
    quad_att = quadratic;
}

Light* Light::CreatePointLight(std::string name,Position<> pos,Color<> ambient_color,Color<> diffuse_color,Color<> specular_color){
    Light *l = new Light(name);
    l->pos = pos;
    l->amb = ambient_color;
    l->dif = diffuse_color;
    l->spec = specular_color;
    return l;
}
Light* Light::CreateDirectionLight(std::string name,Direction<> dir,Color<> ambient_color,Color<> diffuse_color,Color<> specular_color){
    Light *l = new Light(name);
    l->dir = dir;
    l->amb = ambient_color;
    l->dif = diffuse_color;
    l->spec = specular_color;
    return l;
}

Light* Light::CreateSpotLight(std::string name,Position<> pos,Direction<> dir,Color<> ambient_color,Color<> diffuse_color,Color<> specular_color){
    Light *l = new Light(name);
    l->pos = pos;
    l->amb = ambient_color;
    l->dif = diffuse_color;
    l->spec = specular_color;
    return l;
}


};
