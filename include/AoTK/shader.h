#ifndef SHADER_H
#define SHADER_H

#include <AoTK/externals/glew.h>
#include <string>
#include <iostream>
#include <vector>

namespace AoTK{
class Shader
{
    friend class ShaderProgram;
    public:
        Shader();
        virtual ~Shader();

        void init();

        void setSrc(std::string src);
        void appendSrc(std::string src);
        void prependSrc(std::string src);
        void setSrcFromFile(std::string filename);
        void appendSrcFromFile(std::string filename);
        void prependSrcFromFile(std::string filename);
        void compile()const;
        std::string getSrc()const{return src;}
    protected:
        virtual void createShader() = 0;
        std::string loadFromFile(std::string filename);
        std::string src;
        GLuint gl_shader;
};

class VertexShader : public Shader{
    public:
        VertexShader():Shader(){};
        virtual ~VertexShader(){}
    protected:
        virtual void createShader(){
            gl_shader = glCreateShader(GL_VERTEX_SHADER);
        }
};

class FragmentShader : public Shader{
    public:
        FragmentShader():Shader(){};
        virtual ~FragmentShader(){}
    protected:
        virtual void createShader(){
            gl_shader = glCreateShader(GL_FRAGMENT_SHADER);
        }
};

class ShaderProgram{
    public:

        ShaderProgram();
        virtual ~ShaderProgram();
        void attachShader(Shader *s);
        void deteachShader(Shader *s);

        void link();
        void use(){glUseProgram(pgm);}

        GLuint getProgram(){return pgm;}

    protected:
        std::vector<Shader*> shaders;
        GLuint pgm;
};
};

#endif // SHADER_H
