#include <AoTK/aotk.h>

namespace AoTK{

bool glError(std::string file, int line){
    GLenum err =glGetError();
    switch (err){
        case GL_NO_ERROR:
            break;
        case GL_INVALID_ENUM:
            std::cerr << "GL_INVALID_ENUM @ " << file <<":"<<line << ": An unacceptable value is specified for an enumerated argument. The offending command is ignored and has no other side effect than to set the error flag." << std::endl;
            break;
        case GL_INVALID_VALUE:
            std::cerr << "GL_INVALID_VALUE @ " << file <<":"<<line  << ": A numeric argument is out of range. The offending command is ignored and has no other side effect than to set the error flag." << std::endl;
            break;
        case GL_INVALID_OPERATION:
            std::cerr << "GL_INVALID_OPERATION @ " << file <<":"<<line  << ": The specified operation is not allowed in the current state. The offending command is ignored and has no other side effect than to set the error flag." << std::endl;
            break;
        case GL_STACK_OVERFLOW:
            std::cerr << "GL_STACK_OVERFLOW @ " << file <<":"<<line  << ": This command would cause a stack overflow. The offending command is ignored and has no other side effect than to set the error flag." << std::endl;
            break;
        case GL_STACK_UNDERFLOW:
            std::cerr << "GL_STACK_UNDERFLOW @ " << file <<":"<<line  << ": This command would cause a stack underflow. The offending command is ignored and has no other side effect than to set the error flag." << std::endl;
            break;
        case GL_OUT_OF_MEMORY:
            std::cerr << "GL_OUT_OF_MEMORY @ " << file <<":"<<line  << ": There is not enough memory left to execute the command. The state of the GL is undefined, except for the state of the error flags, after this error is recorded." << std::endl;
            break;
        case GL_TABLE_TOO_LARGE:
            std::cerr << "GL_TABLE_TOO_LARGE @ " << file <<":"<<line  << ": The specified table exceeds the implementation's maximum supported table size. The offending command is ignored and has no other side effect than to set the error flag." << std::endl;
            break;
        default:
            std::cerr << "GL_ERROR @ " << file <<":"<<line  << ": Unkown error:" << err << std::endl;
    }
    return err;
}



void getAllError(std::string file, int line){
    while(glError(file,line)){}
}
};

