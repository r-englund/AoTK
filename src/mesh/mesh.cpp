#include <AoTK/mesh.h>

#include <fstream>
#include <sstream>

namespace AoTK{

float Triangle::triangleArea(){
    Vector3<float> e1 = v1->pos-v0->pos;
    Vector3<float> e2 = v2->pos-v0->pos;
    return e1.cross(e2).getLength()*0.5;
}

Mesh::Mesh(){}
Mesh::~Mesh(){}

Face* Mesh::addFace(std::vector<Vector3<float>> positions,std::string mat){
    assert(positions.size() == 3 || positions.size() == 4);

    Vertex *v0,*v1,*v2,*v3;
    v0 = addVertex(positions[0],mat);
    v1 = addVertex(positions[1],mat);
    v2 = addVertex(positions[2],mat);

    Vector3<float> e1 = positions[1] - positions[0];
    Vector3<float> e2 = positions[2] - positions[1];
    Vector3<float> normal = e1.cross(e2);
    normal.normalize();


    if(positions.size() == 4){
        v3 = addVertex(positions[3],mat);
        Quad *q = new Quad();
        q->v0 = v0;
        q->v1 = v1;
        q->v2 = v2;
        q->v3 = v3;
        q->normal = normal;
        faces[mat].push_back(q);
    }else{
        Triangle *t = new Triangle();
        t->v0 = v0;
        t->v1 = v1;
        t->v2 = v2;
        t->normal = normal;
        faces[mat].push_back(t);
    }

}
Vertex* Mesh::addVertex(Vector3<float> position,std::string mat){
    for(auto i = vertices.begin();i<vertices.end();++i){
        if(((*i)->pos-position).getLength()<0.00001){
            return *i;
        }
    }

    Vertex *v = new Vertex();
    v->pos = position;
    v->normal = AoTK::Vector3<float>(0,1,0);
    v->material = mat;

    vertices.push_back(v);
    return v;
}


void Mesh::calculateVertexNormals(){
    for(auto v = vertices.begin();v!=vertices.end();++v){
        (*v)->normal = Vector3<float>(0,0,0);
    }

    for(auto m = faces.begin();m!=faces.end();++m)
    for(auto f = m->second.begin();f!=m->second.end();++f){
        Triangle* t = dynamic_cast<Triangle*>(*f);
        Quad* q = dynamic_cast<Quad*>(*f);
        if(t){
            t->v0->normal += t->normal;
            t->v1->normal += t->normal;
            t->v2->normal += t->normal;
        }else if(q){
            q->v0->normal += q->normal;
            q->v1->normal += q->normal;
            q->v2->normal += q->normal;
            q->v3->normal += q->normal;
            std::cout << "q" << std::endl;
        }else{
            std::cout << ".";
        }
    }

    for(auto v = vertices.begin();v!=vertices.end();++v){
        (*v)->normal.normalize();
    }
}

void Mesh::calculateFaceNormals(){
    for(auto m = faces.begin();m!=faces.end();++m)
    for(auto f = m->second.begin();f!=m->second.end();++f){
        Triangle* t = dynamic_cast<Triangle*>(*f);
        Quad* q = dynamic_cast<Quad*>(*f);
        if(t){
            Vector3<float> e1,e2;
            e1 = t->v1->pos - t->v0->pos;
            e2 = t->v2->pos - t->v1->pos;
            e1.normalize();
            e2.normalize();
            t->normal = e1.cross(e2);
            t->normal.normalize();
        }else if(q){
            Vector3<float> e1,e2;
            e1 = q->v1->pos - q->v0->pos;
            e2 = q->v2->pos - q->v1->pos;
            e1.normalize();
            e2.normalize();
            q->normal = e1.cross(e2);
            q->normal.normalize();
            q->v3->normal += q->normal;
        }
    }
}

void Mesh::loadFromWavefrontMaterials(const char * filename){
    std::ifstream f;
    f.open(filename);
    assert(f.good());

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
}

void Mesh::loadFromWavefront(char * folder,char * filename,Matrix4x4<float> transform){
    if(transform != Matrix4x4<float>()){
        std::cerr << "loadFromWavefront with transform matrix is not yet supported in " << __FILE__ << " at line " << __LINE__ << std::endl;
    }
    std::ifstream f;
    std::stringstream ss;
    ss << folder << "/" << filename;
    f.open(ss.str().c_str());
    assert(f.good());
    std::string s,current_mat = "default";
    std::vector<Vector3<float>> vertices;
    vertices.push_back(Vector3<float>()); //Add dummy vert since indices start at 1 (not zero) in wavefron file format
    f >> s;

    while(!f.eof()){
        if(s.compare("mtllib") == 0){
            std::string mat_filename;
            f >> mat_filename;
            std::stringstream ss;
            ss << folder << "/" << mat_filename;
            loadFromWavefrontMaterials(ss.str().c_str());
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
//                v = transform * v;
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
                this->addFace(positions,current_mat);
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

    if(this->materials.size() == 0){
        this->materials["default"] = Material();
    }

    f.close();
    this->calculateFaceNormals();
    this->calculateVertexNormals();
}


};
