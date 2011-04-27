#ifndef AOTK_MESH_H
#define AOTK_MESH_H

#include <AoTK/math.h>

#include <vector>
#include <map>

namespace AoTK{

    struct Material{
        Vector4<float> ambient_color;
        Vector4<float> diffuse_color;
        Vector4<float> specular_color;
        Vector4<float> emission_color;
        float specularity;

        Material():
        ambient_color(Vector4<float>(0.2,0.2,0.2,1.0)),
        diffuse_color(Vector4<float>(0.8,0.8,0.8,1.0)),
        specular_color(Vector4<float>(0.3,0.3,0.3,1)),
        emission_color(Vector4<float>(0,0,0,0)){}
    };

    struct Vertex{
        Vector3<float> pos;
        Vector3<float> normal;
        std::string material;
    };

    struct Face{
        Vector3<float> normal;
        virtual ~Face(){}
    };

    struct Triangle : public Face{
        Vertex *v0,*v1,*v2;
        virtual ~Triangle(){}

        float triangleArea();


    };

    struct Quad : public Face{
        Vertex *v0,*v1,*v2,*v3;
        virtual ~Quad(){}
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

        virtual Face* addFace(std::vector<Vector3<float>> positions,std::string mat = "default");
        virtual Vertex* addVertex(Vector3<float> position,std::string mat);

        virtual void calculateVertexNormals();
        virtual void calculateFaceNormals();

        void loadFromWavefront(char * folder,char * filename,Matrix4x4<float> transform = Matrix4x4<float>());

protected:
        void loadFromWavefrontMaterials(const char * filename);

        std::map<std::string,Material> materials;
        std::vector<Vertex*> vertices;
        std::map<std::string,std::vector<Face*>> faces;


    };
};

#endif
