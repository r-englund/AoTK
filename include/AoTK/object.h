#ifndef OBJECT_H
#define OBJECT_H



namespace AoTK{
class Object{
    friend class AOTK;
    friend class Scene;
protected:
    Matrix toWorld;
    std::string name;

    GLuint pgm;
    GLint proj_matrix_loc;
    GLint view_matrix_loc;
    GLint model_matrix_loc;

    unsigned int prev_frame_logic;
    unsigned int prev_frame_graphics;
    unsigned int prev_frame_prepare;

    virtual void logic() = 0;
    virtual void graphic() = 0;
    virtual void prepare() = 0;
    virtual void render() = 0;

public:
    Object(GLint shader,Matrix toWorld,std::string name = "");
    Object() = delete;
    Object(const Object &o) = delete;
    Object &operator=(const Object &o) = delete;
    virtual ~Object();

    virtual void doLogic  (unsigned int frame);
    virtual void doGraphic(unsigned int frame);
    virtual void doPrepare(unsigned int frame);
    virtual void doRender();

    void setShader(GLint shader);

    Vector4 getCenter();
    Matrix  getToWorldMatrix();
};
};



#endif
