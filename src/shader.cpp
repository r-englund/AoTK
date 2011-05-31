#include <AoTK/window_handler.h>
#include <AoTK/shader.h>

#include <fstream>
#include <assert.h>
#include <cstring>
#include <algorithm>

namespace AoTK{
namespace GPU{
Shader::~Shader()
{
    glDeleteShader(gl_shader);
    GLERRORS();
}

Shader::Shader(){
}
void Shader::setSrc(std::string _src){
    this->src = _src;
}

void Shader::init(){
    createShader();
    GLERRORS();
}

void Shader::appendSrc(std::string _src){
    this->src.append(_src);
}
void Shader::prependSrc(std::string _src){
    std::string n = _src;
    n.append(this->src);
    this->src = n;
}

void Shader::setSrcFromFile(std::string filename){
    std::string _src = loadFromFile(filename);
    setSrc(_src);
}
void Shader::appendSrcFromFile(std::string filename){
    std::string _src = loadFromFile(filename);
    appendSrc(_src);
}
void Shader::prependSrcFromFile(std::string filename){
    std::string _src = loadFromFile(filename);
    prependSrc(_src);
}

void Shader::compile()const{

    glShaderSource(gl_shader, 1, (const GLchar**)&src, NULL);

    glCompileShader(gl_shader);
    GLint err;
    glGetObjectParameterivARB(gl_shader, GL_COMPILE_STATUS, &err);
    if(!err){
        GLERRORS();
        int maxL;
        glGetShaderiv(gl_shader, GL_INFO_LOG_LENGTH, &maxL);
        char * log = new char[maxL];
        glGetShaderInfoLog(gl_shader, maxL, &maxL, log);
        std::cout << "Could not compile shader: " <<std::endl << src << std::endl;
        std::cout << log << std::endl;
        delete [] log;
        GLERRORS();
    }
    #ifdef DEBUG
    else
        std::cout << "Shader compiled ok" << std::endl;
    #endif
}

std::string Shader::loadFromFile(std::string filename){
    FILE *f;
    f = fopen(filename.c_str(),"rt");
    assert(f != NULL);
    fseek(f,0,SEEK_END);

    int size = ftell(f);
    char *buf = new char[size+1];
    std::memset(buf,0,size+1);

    fseek(f,0,SEEK_SET);
    fread(buf,sizeof(char),size,f);

    assert(ferror(f) == 0);
    fclose(f);
    std::string s = buf;
    delete buf;
    return s;
}


ShaderProgram::ShaderProgram(){
    pgm = glCreateProgram();
    GLERRORS();
}
ShaderProgram::~ShaderProgram(){
    glDeleteProgram(pgm);
    GLERRORS();
    pgm = 0;
}
void ShaderProgram::attachShader(Shader *s){
    auto it = std::find(shaders.begin(),shaders.end(),s);
    if(it != shaders.end())
        return;
    shaders.push_back(s);

    glAttachShader(pgm,s->gl_shader);
    GLERRORS();
}
void ShaderProgram::deteachShader(Shader *s){
    auto it = std::find(shaders.begin(),shaders.end(),s);
    if(it != shaders.end())
        shaders.erase(it);
    glDetachShader(pgm,s->gl_shader);
    GLERRORS();
}

void ShaderProgram::link(){

//    int i;
//    GLuint* shaders = new GLuint[100];
//    glGetAttachedShaders(pgm,10,&i,shaders);
//    delete shaders;

    glLinkProgram(pgm);
    GLint err;
    glGetProgramiv(pgm, GL_LINK_STATUS, &err);
    this->shaders.size();
    if(!err){
        int maxL;
        glGetProgramiv(pgm, GL_INFO_LOG_LENGTH, &maxL);
        char * log = new char[maxL];
        glGetProgramInfoLog(pgm, maxL, &maxL, log);
        std::cout << "Could not Link shaders: " << std::endl;
        std::cout << log << std::endl;
        delete [] log;
        GLERRORS();
    }
    #ifdef DEBUG
    else
        std::cout << "ShaderProgram linked ok" << std::endl;
    #endif
}
};
};

