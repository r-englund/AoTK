#ifndef AOTK_MESH_H
#define AOTK_MESH_H

#include <AoTK/math.h>

#include <vector>
#include <map>

namespace AoTK{
namespace Mesh{

    struct Material{
        Math::Vector4<float> ambient_color;
        Math::Vector4<float> diffuse_color;
        Math::Vector4<float> specular_color;
        Math::Vector4<float> emessive_color;
        float specularity;

        Material():
        ambient_color(Math::Vector4<float>(0.2f,0.2f,0.2f,1.0f)),
        diffuse_color(Math::Vector4<float>(0.8f,0.8f,0.8f,1.0f)),
        specular_color(Math::Vector4<float>(0.3f,0.3f,0.3f,1.0f)),
        emessive_color(Math::Vector4<float>(0.0f,0.0f,0.0f,0.0f)),
        specularity(0)
        {}
    };

    struct Vertex{
        Vertex():
            pos(Math::Vector3<float>(0,0,0)),
            normal(Math::Vector3<float>(0,0,0)),
            material("")
        {}
        virtual ~Vertex(){}
        Math::Vector3<float> pos;
        Math::Vector3<float> normal;
        std::string material;
    };

    struct Face{
        Math::Vector3<float> normal;
        virtual ~Face(){}
        Face():normal(0){}
    };

    struct Triangle : public Face{
        unsigned int v0,v1,v2;
        virtual ~Triangle(){}
        Triangle():v0(-1),v1(-1),v2(-1){}

        static float triangleArea(const Vertex &v0,const Vertex &v1,const Vertex &v2);


    };

    struct Quad : public Face{
        unsigned int v0,v1,v2,v3;
        virtual ~Quad(){}
        Quad():v0(-1),v1(-1),v2(-1),v3(-1){}
        std::pair<Triangle,Triangle> split(){
            std::pair<Triangle,Triangle> t;
            t.first.v0 = v0;
            t.first.v1 = v1;
            t.first.v2 = v2;
            t.second.v0 = v3;
            t.second.v1 = v1;
            t.second.v2 = v2;
            std::cout << "Check if correct and in right order (CCW) " << __FILE__ << ":"<<__LINE__<<std::endl;
            return t;
        }
    };

    class Mesh{
    public:
        Mesh();
        virtual ~Mesh();

        virtual bool addFace(std::vector<Math::Vector3<float>> positions,std::string mat = "default",bool smooth = true);
        virtual unsigned int addVertex(Math::Vector3<float> position,std::string mat,bool smooth = true);

        virtual void calculateVertexNormals();
        virtual void calculateFaceNormals();

        void loadFromWavefront(char * folder,char * filename,Math::Matrix4x4<float> transform = Math::Matrix4x4<float>());
        void loadCollada(char * filename,Math::Matrix4x4<float> transform = Math::Matrix4x4<float>());
protected:

        Math::Vector3<float> faceCenter(std::string mat,unsigned int id,bool triangle);

        void loadFromWavefrontMaterials(const char * filename);

        std::map<std::string,Material> materials;
        std::vector<Vertex> vertices;
        std::map<std::string,std::vector<Triangle>> triangles;
        std::map<std::string,std::vector<Quad>> quads;
        std::vector<std::pair<std::string,std::pair<unsigned int,bool>>> faces; //TODO did this work?


        Vertex &v(unsigned int id){return vertices[id];}


    };
};
};

#endif
