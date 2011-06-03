#include <AoTK/window_handler.h>
#include <AoTK/math.h>

namespace AoTK{
namespace Math{
#ifdef GL_MODELVIEW_MATRIX

    template< > Matrix4x4<float> Matrix4x4<float>::fromCurrentModelViewGLMatrix(){
        Matrix4x4<float> m;
        glGetFloatv(GL_MODELVIEW_MATRIX,m._1d);
        return {m.toOpenGLMatrix()};
    }
    template< > Matrix4x4<double> Matrix4x4<double>::fromCurrentModelViewGLMatrix(){
        Matrix4x4<double> m;
        glGetDoublev(GL_MODELVIEW_MATRIX,m._1d);
        return {m.toOpenGLMatrix()};
    }



    template< > Matrix4x4<float> Matrix4x4<float>::fromCurrentProjectionGLMatrix(){
        Matrix4x4<float> m;
        glGetFloatv(GL_PROJECTION_MATRIX,m._1d);
        return {m.toOpenGLMatrix()};
    }
    template< > Matrix4x4<double> Matrix4x4<double>::fromCurrentProjectionGLMatrix(){
        Matrix4x4<double> m;
        glGetDoublev(GL_PROJECTION_MATRIX,m._1d);
        return {m.toOpenGLMatrix()};
    }

    template< > Matrix4x4<float> Matrix4x4<float>::fromCurrentTextureGLMatrix(){
        Matrix4x4<float> m;
        glGetFloatv(GL_TEXTURE_MATRIX,m._1d);
        return {m.toOpenGLMatrix()};
    }
    template< > Matrix4x4<double> Matrix4x4<double>::fromCurrentTextureGLMatrix(){
        Matrix4x4<double> m;
        glGetDoublev(GL_TEXTURE_MATRIX,m._1d);
        return {m.toOpenGLMatrix()};
    }
    #endif
};
};

