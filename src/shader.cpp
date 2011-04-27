#include <AoTK/window_handler.h>
#include <AoTK/shader.h>

#include <fstream>
#include <assert.h>
#include <cstring>
#include <algorithm>

Shader::~Shader()
{
    glDeleteShader(gl_shader);
}

Shader::Shader(){
}
void Shader::setSrc(std::string _src){
    this->src = _src;
}

void Shader::init(){
    createShader();
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
    glCompileShader(gl_shader);
    std::cout << "Compiled shader but check for error " << __FILE__ << ":" << __LINE__ << std::endl;
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
    return buf;
}


ShaderProgram::ShaderProgram(){
    pgm = glCreateProgram();
}
ShaderProgram::~ShaderProgram(){
    glDeleteProgram(pgm);
    pgm = 0;
}
void ShaderProgram::attachShader(Shader *s){
    auto it = std::find(shaders.begin(),shaders.end(),s);
    if(it != shaders.end())
        return;
    shaders.push_back(s);
    glAttachShader(pgm,s->gl_shader);
}
void ShaderProgram::deteachShader(Shader *s){
    auto it = std::find(shaders.begin(),shaders.end(),s);
    if(it != shaders.end())
        shaders.erase(it);
    glDetachShader(pgm,s->gl_shader);
}

void ShaderProgram::link(){
    glLinkProgram(pgm);
}

