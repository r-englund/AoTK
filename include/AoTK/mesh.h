#ifndef AOTK_MESH_H
#define AOTK_MESH_H

#include <AoTK/math.h>

#include <vector>
#include <map>

namespace AoTK{
    class Mesh{
    public:


        struct Material{
            Vector4<float> ambient_color;
            Vector4<float> diffuse_color;
            Vector4<float> specular_color;
            Vector4<float> emmesive_color;
            float specularity;

            Material():
            ambient_color(Vector4<float>(0.7,0.7,0.7,1.0)),
            diffuse_color(Vector4<float>(0.7,0.7,0.7,1.0)),
            specular_color(Vector4<float>(1,1,1,1)),
            emmesive_color(Vector4<float>(0,0,0,0))
            {}
        };

        struct Vertex{
            Vector3<float> pos;
            Vector3<float> normal;
            std::string material;
        };

//        struct Face{};
        struct Triangle{// : public Face{
            uint32_t v0,v1,v2;
            Vector3<float> normal;
        };

//        struct Quad : public Face{
//            uint32_t v0,v1,v2,v3;
//            Vector3<float> normal;
//        };

        Mesh(){}
        ~Mesh(){}

        virtual float triangleArea(uint32_t i);

        virtual uint32_t addFace(std::vector<Vector3<float>> positions,std::string mat = "default");
        virtual uint32_t addVertex(Vector3<float> position,std::string mat);

        virtual void calculateVertexNormals();
        virtual void calculateFaceNormals();

        static Mesh LoadFromWavefront(char * folder,char * filename);
private:
        static std::map<std::string,Material> LoadFromWavefrontMaterials(const char * filename);

        std::map<std::string,Material> materials;
        std::vector<Vertex> vertices;
        std::vector<Triangle> triangles;


    };
};

#endif
