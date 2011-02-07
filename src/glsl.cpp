
#include <AoTK/aotk.h>



#include <stdio.h>
#include <assert.h>
#include <iostream>
namespace AoTK{
GLuint loadShaderProgram(std::string vertex,std::string fragment){
    getAllError(__FILE__,__LINE__);
    GLint err;
    FILE *fvert,*ffrag;
    fvert = fopen(vertex.c_str(),"r");
    ffrag = fopen(fragment.c_str(),"r");

    assert(fvert != NULL);
    assert(ffrag != NULL);

    fseek(fvert,0,SEEK_END);
    fseek(ffrag,0,SEEK_END);
    int vert_size = ftell(fvert);
    int frag_size = ftell(ffrag);
    char *buf_vert = new char[vert_size];
    char *buf_frag = new char[frag_size];
    fseek(fvert,0,SEEK_SET);
    fseek(ffrag,0,SEEK_SET);
    fread(buf_vert,sizeof(char),vert_size,fvert);
    fread(buf_frag,sizeof(char),frag_size,ffrag);

    assert(ferror(fvert) == 0);
    assert(ferror(ffrag) == 0);

    fclose(fvert);
    fclose(ffrag);


    buf_vert[vert_size] = 0;
    buf_frag[frag_size] = 0;

    GLuint pgm = glCreateProgram();

    std::cout << buf_vert << std::endl;
    std::cout << buf_frag << std::endl;

    GLuint vShader,fShader;
    vShader = glCreateShader(GL_VERTEX_SHADER);
    fShader = glCreateShader(GL_FRAGMENT_SHADER);
    getAllError(__FILE__,__LINE__);
//    const char *cv=buf_vert;
//    const char *cf=buf_frag;

    glShaderSource(vShader, 1, (const GLchar**)&buf_vert, &vert_size);
    glShaderSource(fShader, 1, (const GLchar**)&buf_frag, &frag_size);
    getAllError(__FILE__,__LINE__);

    glCompileShader(vShader);
    glCompileShader(fShader);
    getAllError(__FILE__,__LINE__);

    glGetObjectParameterivARB(vShader, GL_COMPILE_STATUS, &err);
	if(!err){
        getAllError(__FILE__,__LINE__);
	    int maxL;
		glGetShaderiv(vShader, GL_INFO_LOG_LENGTH, &maxL);
        char * log = new char[maxL];
        glGetShaderInfoLog(vShader, maxL, &maxL, log);
        std::cout << "Could not compile shader: " << vertex << std::endl;
        std::cout << log << std::endl;
        delete [] log;
		return 0;
	}
	getAllError(__FILE__,__LINE__);
	glGetObjectParameterivARB(fShader, GL_COMPILE_STATUS, &err);
	if(!err){
	    getAllError(__FILE__,__LINE__);
	    int maxL;
		glGetShaderiv(fShader, GL_INFO_LOG_LENGTH, &maxL);
        char * log = new char[maxL];
        glGetShaderInfoLog(fShader, maxL, &maxL, log);
        std::cout << "Could not compile shader: " << fragment << std::endl;
        std::cout << log << std::endl;
        delete [] log;
		return 0;
	}
	getAllError(__FILE__,__LINE__);
    glAttachShader(pgm,vShader);
    glAttachShader(pgm,fShader);
    getAllError(__FILE__,__LINE__);

    glBindFragDataLocation(pgm, 0, "out_Color");
    getAllError(__FILE__,__LINE__);
    glLinkProgram(pgm);
    getAllError(__FILE__,__LINE__);

    delete buf_vert;
    delete buf_frag;
//    delete cv;
//    delete cf;

	glGetObjectParameterivARB(pgm, GL_OBJECT_LINK_STATUS_ARB, &err);
	assert(err && "Shaders could not be linked");

    getAllError(__FILE__,__LINE__);

    std::cout << "Shader program created with: " << vertex << " and " << fragment << std::endl;

    return pgm;
}
};
