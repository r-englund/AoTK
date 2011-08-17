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
    this->gl_shader = 0;
}
void Shader::setSrc(std::string _src){
    this->src = _src;
}

void ShaderProgram::setTexture(std::string loc,GLuint tex,uint8_t id){
    glActiveTexture(GL_TEXTURE0+id);GLERRORS();
    glUniform1i(_uniforms[loc],id);GLERRORS();
    glBindTexture(GL_TEXTURE_2D,tex);GLERRORS();
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
    GLERRORS();
	int l = src.size();
	GLchar *c = new GLchar[l+1];
	strcpy(c,src.c_str());
	glShaderSource(gl_shader, 1, (const GLchar **)&c, &l);

    glCompileShader(gl_shader);
    GLint err;
    glGetObjectParameterivARB(gl_shader, GL_COMPILE_STATUS, &err);
    if(!err){
        GLERRORS();
        int mL;
        glGetShaderiv(gl_shader, GL_INFO_LOG_LENGTH, &mL);
        char * log = new char[mL];
        glGetShaderInfoLog(gl_shader, mL, &mL, log);
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
    std::memset(buf,'\0',size+1);

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

Shader* ShaderProgram::attachShader(Shader *s){
    auto it = std::find(shaders.begin(),shaders.end(),s);
    if(it != shaders.end())
        return s;
    shaders.push_back(s);

    glAttachShader(pgm,s->gl_shader);
    GLERRORS();
    return s;
}
void ShaderProgram::deteachShader(Shader *s){
    auto it = std::find(shaders.begin(),shaders.end(),s);
    if(it != shaders.end())
        shaders.erase(it);
    glDetachShader(pgm,s->gl_shader);
    GLERRORS();
}


void ShaderProgram::link(bool initInPuts,bool initOutPuts){
    if(initOutPuts){
        std::vector<std::string> outputs;


        for(auto s = shaders.begin();s!=shaders.end();++s){
            auto f = dynamic_cast<AoTK::GPU::FragmentShader *>(*s);
            if(f){
                auto v = f->getOutputs();
                for(unsigned int i = 0;i<v.size();i++){
                    outputs.push_back(v[i]);
                }
            }
        }
        for(unsigned int i = 0;i<outputs.size();i++){
            glBindFragDataLocation(pgm,i,outputs[i].c_str());
            _out[outputs[i]] = i;
        }
    }else if(initInPuts){
        std::vector<std::string> outputs;


        for(auto s = shaders.begin();s!=shaders.end();++s){
            auto f = dynamic_cast<AoTK::GPU::FragmentShader *>(*s);
            if(f){
                auto v = f->getOutputs();
                for(unsigned int i = 0;i<v.size();i++){
                    outputs.push_back(v[i]);
                }
            }
        }
        for(unsigned int i = 0;i<outputs.size();i++){
            _out[outputs[i]] = i;
        }
    }
    glLinkProgram(pgm);
    GLint err;
    glGetProgramiv(pgm, GL_LINK_STATUS, &err);
    this->shaders.size();
    if(!err){
        int mL;
        glGetProgramiv(pgm, GL_INFO_LOG_LENGTH, &mL);
        char * log = new char[mL];
        glGetProgramInfoLog(pgm, mL, &mL, log);
        std::cout << "Could not Link shaders: " << std::endl;
        std::cout << log << std::endl;
        delete [] log;
        GLERRORS();
    }
    #ifdef DEBUG
    else
        std::cout << "ShaderProgram linked ok" << std::endl;
    #endif
    if(initInPuts){
        int num_attribs;
        int num_uniforms;
        glGetProgramiv(pgm,GL_ACTIVE_ATTRIBUTES,&num_attribs);
        glGetProgramiv(pgm,GL_ACTIVE_UNIFORMS,&num_uniforms);

        char *buf = new char[255];
        std::string name;
        for(int i = 0;i<num_attribs;i++){
            int l,s;
            GLenum e;
            glGetActiveAttrib(pgm,i,255,&l,&s,&e,buf);
            name = buf;
            _attributes[name] = glGetAttribLocation(pgm,buf);
//            std::cout << buf << std::endl;
        }

        for(int i = 0;i<num_uniforms;i++){
            int l,s;
            GLenum e;
            glGetActiveUniform(pgm,i,255,&l,&s,&e,buf);
            name = buf;
            _uniforms[name] = glGetUniformLocation(pgm,buf);
            std::cout << buf << " " << _uniforms[name] << std::endl;
        }


        delete buf;
        //glGetActiveAttrib(pgm,);
    }
}


std::vector<std::string> FragmentShader::getOutputs()const{
    std::vector<std::string> list;

    auto it = src.find("out ");

    while(it != std::string::npos){
        if(src.substr(it+4,4).compare("vec4") == 0) it+=9;
        else if(src.substr(it+4,4).compare("vec3") == 0) it+=9;
        else if(src.substr(it+4,4).compare("vec2") == 0) it+=9;
        else if(src.substr(it+4,5).compare("float") == 0) it+=10;
        list.push_back(src.substr(it,src.find(";",it)-it));
        it = src.find("out ",it+1);
    }
    return list;
}


};
};

