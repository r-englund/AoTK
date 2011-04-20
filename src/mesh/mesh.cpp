#include <AoTK/mesh.h>

#include <fstream>
#include <sstream>

namespace AoTK{

uint32_t Mesh::addFace(std::vector<Vector3<float>> positions,std::string mat){
    assert(positions.size() == 3 || positions.size() == 4);
    assert(positions.size() != 4 && "Quad meshes not yet supported");



    uint32_t v0,v1,v2,v3;
    v0 = addVertex(positions[0],mat);
    v1 = addVertex(positions[1],mat);
    v2 = addVertex(positions[2],mat);

    Triangle t;
    t.v0 = v0;
    t.v1 = v1;
    t.v2 = v2;

    triangles.push_back(t);

    return triangles.size()-1;
}
uint32_t Mesh::addVertex(Vector3<float> position,std::string mat){
    for(uint32_t i = 0;i<vertices.size();i++){
        if((vertices[i].pos-position).getLength()<0.00001){
            return i;
        }
    }

    Vertex v;
    v.pos = position;
    v.normal = AoTK::Vector3<float>(0,1,0);
    v.material = mat;
//    v.color = AoTK::Vector4<float>(0.7,0.7,0.7,1.0);

    vertices.push_back(v);
    return vertices.size()-1;
}


void Mesh::calculateVertexNormals(){
    for(auto v = vertices.begin();v!=vertices.end();++v){
        v->normal = Vector3<float>(0,0,0);
    }

    for(auto t = triangles.begin();t!=triangles.end();++t){
        vertices[t->v0].normal += t->normal;
        vertices[t->v1].normal += t->normal;
        vertices[t->v2].normal += t->normal;
    }

    for(auto v = vertices.begin();v!=vertices.end();++v){
        v->normal.normalize();
    }
}

void Mesh::calculateFaceNormals(){
    for(auto t = triangles.begin();t != triangles.end();++t){
//    for(Triangle t : triangles){
        Vector3<float> e1,e2;
        e1 = vertices[t->v1].pos - vertices[t->v0].pos;
        e2 = vertices[t->v2].pos - vertices[t->v1].pos;
        e1.normalize();
        e2.normalize();
        t->normal = e1.cross(e2);
        t->normal.normalize();
    }
}

float Mesh::triangleArea(uint32_t i){
    Vector3<float> e1 = vertices[triangles[i].v1].pos-vertices[triangles[i].v0].pos;
    Vector3<float> e2 = vertices[triangles[i].v2].pos-vertices[triangles[i].v0].pos;
    return e1.cross(e2).getLength()*0.5;
}

std::map<std::string,Mesh::Material> Mesh::LoadFromWavefrontMaterials(const char * filename){
    std::ifstream f;
    f.open(filename);
    assert(f.good());
    std::map<std::string,Material> materials;
    std::string s,current;

    do{
        f >> s;
        if(s[0] == '#'){
            char c[1000];
            f.getline(c,1000);
        }else if(s.compare("newmtl") == 0){
            f >> current;
        }else if(s.compare("Ns") == 0){
            f >> materials[current].specularity;
        }else if(s.compare("Ka") == 0){
            f >> materials[current].ambient_color.r;
            f >> materials[current].ambient_color.g;
            f >> materials[current].ambient_color.b;
        }else if(s.compare("Kd") == 0){
            f >> materials[current].diffuse_color.r;
            f >> materials[current].diffuse_color.g;
            f >> materials[current].diffuse_color.b;
        }else if(s.compare("Ks") == 0){
            f >> materials[current].specular_color.r;
            f >> materials[current].specular_color.g;
            f >> materials[current].specular_color.b;
        }else if(s.compare("d") == 0 || s.compare("Tr") == 0){
            float t;
            f >> t;
            materials[current].specular_color.a == t;
            materials[current].diffuse_color.a == t;
            materials[current].ambient_color.a == t;
        }else{
            std::cout << "Unhandled material parameter: " << s << std::endl;
        }
    }while(!f.eof());
    return materials;
}
Mesh Mesh::LoadFromWavefront(char * folder,char * filename){
    std::ifstream f;
    std::stringstream ss;
    ss << folder << "/" << filename;
    f.open(ss.str().c_str());
    assert(f.good());

    std::string s,current_mat = "default";
    Mesh m;
    std::vector<Vector3<float>> vertices;
    vertices.push_back(Vector3<float>()); //Add dummy vert since indices start at 1 (not zero) in wavefron file format
    f >> s;
    while(!f.eof()){
        if(s.compare("mtllib") == 0){
            std::string mat_filename;
            f >> mat_filename;
            std::stringstream ss;
            ss << folder << "/" << mat_filename;
            std::map<std::string,Material> materials = LoadFromWavefrontMaterials(ss.str().c_str());
            for(auto i = materials.begin();i!=materials.end();++i)
                m.materials[i->first] = i->second;
        }
        else if(s.compare("usemtl") == 0){
            f >> current_mat;
            if(current_mat.compare("usemtl") == 0){
                current_mat = "default";
            }
        }
        else if(s.length() == 1){
            if(s[0] == '#'){
                char c[1000];
                f.getline(c,1000);
//                std::cout << "Comment: " << c << std::endl;
            }
            else if(s[0] == 'v'){
                Vector3<float> v;
                f >> v.x;
                f >> v.y;
                f >> v.z;
                vertices.push_back(v);
            }
            else if(s[0] == 'f'){
                std::vector<Vector3<float>> positions;
                uint32_t i;
                f >> i;
                positions.push_back(vertices[i]);
                f >> i;
                positions.push_back(vertices[i]);
                f >> i;
                positions.push_back(vertices[i]);
//                if(f >> i){
//                    std::cout << "Found Quad" << std::endl;
//                    positions.push_back(vertices[i]);
//                }
                m.addFace(positions,current_mat);
            }else{
                std::cout << s << std::endl;
            }
        }else{
            std::cout << s << std::endl;
        }
        if(!(f >> s)){
//            std::cerr << "Missed something, damit" << std::endl;
        }
    }

//    std::cout << vertices.size() << std::endl;
//    std::cout << m.vertices.size() << std::endl;
//    std::cout << m.triangles.size() << std::endl;

    if(m.materials.size() == 0){
        m.materials["default"] = Material();
    }

    f.close();
    m.calculateFaceNormals();
    m.calculateVertexNormals();
    return m;
}


};
