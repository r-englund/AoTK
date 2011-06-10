#include <AoTK/mesh.h>

#include <fstream>
#include <sstream>
#include <typeinfo>
#include <assert.h>

namespace AoTK{
namespace Mesh{

float Triangle::triangleArea(const Vertex &v0,const Vertex &v1,const Vertex &v2){
    Math::Vector3<float> e1 = v1.pos-v0.pos;
    Math::Vector3<float> e2 = v2.pos-v0.pos;
    return e1.cross(e2).getLength()*0.5;
}

Mesh::Mesh(){

}
Mesh::~Mesh(){
    //TODO update
}

bool Mesh::addFace(std::vector<Math::Vector3<float>> positions,std::string mat,bool smooth){
    assert(positions.size() == 3 || positions.size() == 4);

    unsigned int v0,v1,v2,v3;
    v0 = addVertex(positions[0],mat,smooth);
    v1 = addVertex(positions[1],mat,smooth);
    v2 = addVertex(positions[2],mat,smooth);

    Math::Vector3<float> e1 = positions[1] - positions[0];
    Math::Vector3<float> e2 = positions[2] - positions[1];
    Math::Vector3<float> normal = e1.cross(e2);
    normal.normalize();
    if(positions.size() == 4){
        v3 = addVertex(positions[3],mat,smooth);
        Quad q;
        q.v0 = v0;
        q.v1 = v1;
        q.v2 = v2;
        q.v3 = v3;
        q.normal = normal;
        unsigned int id = quads[mat].size();
        quads[mat].push_back(q);
        std::pair<unsigned int,bool> p(id,false);
        std::pair<std::string,std::pair<unsigned int,bool>> P(mat,p);
        faces.push_back(P);
        return true;
    }else{
        Triangle t;
        t.v0 = v0;
        t.v1 = v1;
        t.v2 = v2;
        t.normal = normal;
        unsigned int id = triangles[mat].size();
        triangles[mat].push_back(t);
        std::pair<unsigned int,bool> p(id,true);
        std::pair<std::string,std::pair<unsigned int,bool>> P(mat,p);
        faces.push_back(P);
        return true;
    }
    return false;
}

Math::Vector3<float> Mesh::faceCenter(std::string mat,unsigned int id,bool triangle){
    if(triangle){
        return (vertices[triangles[mat][id].v0].pos+vertices[triangles[mat][id].v1].pos+vertices[triangles[mat][id].v2].pos)/3.0;
    }else{
        return (vertices[quads[mat][id].v0].pos+vertices[quads[mat][id].v1].pos+vertices[quads[mat][id].v2].pos+vertices[quads[mat][id].v3].pos)/4.0;
    }
}

unsigned int Mesh::addVertex(Math::Vector3<float> position,std::string mat,bool smooth){
    int a = 0;
    for(auto i = vertices.begin();i<vertices.end()&&smooth;++i){
        if((i->pos-position).getLength()<0.00001){
            assert(a == ((int)&*i - (int)&*vertices.begin())/sizeof(Vertex));
            return a;
        }
        a++;
    }

    Vertex v;
    v.pos = position;
    v.normal = AoTK::Math::Vector3<float>(0,1,0);
    v.material = mat;

    vertices.push_back(v);
    return vertices.size()-1;
}

void Mesh::calculateVertexNormals(){
    for(auto v = vertices.begin();v!=vertices.end();++v){
        v->normal = Math::Vector3<float>(0,0,0);
    }

    for(auto m = triangles.begin();m!=triangles.end();++m)
    for(auto t = m->second.begin();t!=m->second.end();++t){
        v(t->v0).normal += t->normal;
        v(t->v1).normal += t->normal;
        v(t->v2).normal += t->normal;
    }
    for(auto m = quads.begin();m!=quads.end();++m)
    for(auto q = m->second.begin();q!=m->second.end();++q){
        v(q->v0).normal += q->normal;
        v(q->v1).normal += q->normal;
        v(q->v2).normal += q->normal;
        v(q->v3).normal += q->normal;
    }

    for(auto v = vertices.begin();v!=vertices.end();++v){
        v->normal.normalize();
    }
}

void Mesh::calculateFaceNormals(){
    for(auto m = triangles.begin();m!=triangles.end();++m)
    for(auto t = m->second.begin();t!=m->second.end();++t){
        Math::Vector3<float> e1,e2;
        e1 = v(t->v1).pos - v(t->v0).pos;
        e2 = v(t->v2).pos - v(t->v1).pos;
        e1.normalize();
        e2.normalize();
        t->normal = e1.cross(e2);
        t->normal.normalize();
    }
    for(auto m = quads.begin();m!=quads.end();++m)
    for(auto t = m->second.begin();t!=m->second.end();++t){
        Math::Vector3<float> e1,e2;
        e1 = v(t->v1).pos - v(t->v0).pos;
        e2 = v(t->v2).pos - v(t->v1).pos;
        e1.normalize();
        e2.normalize();
        t->normal = e1.cross(e2);
        t->normal.normalize();
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

int char2num(char c){
    if(c == '0') return 0;
    if(c == '1') return 1;
    if(c == '2') return 2;
    if(c == '3') return 3;
    if(c == '4') return 4;
    if(c == '5') return 5;
    if(c == '6') return 6;
    if(c == '7') return 7;
    if(c == '8') return 8;
    if(c == '9') return 9;
}

void Mesh::loadFromWavefront(char * folder,char * filename,Math::Matrix4x4<float> transform){
    std::ifstream f;
    std::stringstream ss;
    ss << folder << "/" << filename;
    f.open(ss.str().c_str());
    assert(f.good());
    std::string s,current_mat = "default";
    std::vector<Math::Vector3<float>> vertices;
    vertices.push_back(Math::Vector3<float>()); //Add dummy vert since indices start at 1 (not zero) in wavefron file format
    f >> s;
    char *line = new char[200];
    bool smooth = true;
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
            if(s[0] == 's'){
                f >> s;
                smooth = s.compare("off")!=0;
            }else if(s[0] == '#'){
                char c[1000];
                f.getline(c,1000);
//                std::cout << "Comment: " << c << std::endl;
            }
            else if(s[0] == 'v'){
                Math::Vector3<float> v;
                f >> v.x;
                f >> v.y;
                f >> v.z;
                Math::Vector4<float> v4;
                v4.x = v.x;
                v4.y = v.y;
                v4.z = v.z;
                v4.w = 1.0;
                v4 = transform * v4;
                v.x = v4.x/v4.w;
                v.y = v4.y/v4.w;
                v.z = v4.z/v4.w;
                vertices.push_back(v);
            }
            else if(s[0] == 'f'){
                std::vector<Math::Vector3<float>> positions;
                memset(line,0,200);
                f.getline(line,200);
                int n = 0;
                unsigned int v0,v1,v2,v3;
                v0 = v1= v2 = v3 = 0;
                int i;
                for(int i = 1;line[i-1]!='\0';i++){
                    if(line[i]==' '||line[i]=='\0'){
                        n++;
                        int mult = 1;
                        for(int j = i-1;line[j]!=' ';j--){
                            if(n==1)
                                v0 += mult*char2num(line[j]);
                            else if(n==2)
                                v1 += mult*char2num(line[j]);
                            else if(n==3)
                                v2 += mult*char2num(line[j]);
                            else if(n==4)
                                v3 += mult*char2num(line[j]);
                            mult *= 10;
                        }
                    }
                }

                positions.push_back(vertices[v0]);
                positions.push_back(vertices[v1]);
                positions.push_back(vertices[v2]);
                if(n == 4)
                    positions.push_back(vertices[v3]);
                char pe;
                this->addFace(positions,current_mat,smooth);
            }else{
                std::cout << s << std::endl;
            }
        }else{
            std::cout << s << std::endl;
        }if(!(f >> s)){
//            std::cerr << "Missed something, damit" << std::endl;
        }
    }
    if(this->materials.size() == 0){
        this->materials["default"] = Material();
    }
    delete line;
    f.close();
    this->calculateFaceNormals();
    this->calculateVertexNormals();
}

enum COLLADA_DATA_SEMANTICS{
    VERTEX,NORMAL
};
void Mesh::loadCollada(char * filename,Math::Matrix4x4<float> transform){
    std::ifstream f;
    f.open(filename);
    assert(f.good());

    bool normalsDone = false;
    std::map<std::string,std::vector<AoTK::Math::Vector3<float>>> float_arrays;

    std::vector<int> face_types;
    std::map<int,std::pair<COLLADA_DATA_SEMANTICS,std::string>> offsets;

    char tag[300],*data;
    f.getline(tag,300,'>');
    data = strchr(tag,'<');
    while(strncmp(data,"</COLLADA",9) != 0){
        if(strncmp(data,"<up_axis",8) == 0){
            f.getline(tag,300,'<');
//            if(strcmp(tag,"Z_UP")==0){
//                transform *= AoTK::Math::Matrix4x4<float>(1,0,0,0,
//                                                          0,0,1,0,
//                                                          0,1,0,0,
//                                                          0,0,0,1);
//            }
             memset(tag,0,300);
            f.getline(tag,300,'>');
            continue;
        }else if(strncmp(data,"<float_array",12) == 0){
            int i,name_start,count_start,count = 0;
            std::string name;
            for(i = 7;i<300;i++){
                if((tag[i-7] == 'c')&&
                (tag[i-6] == 'o')&&
                (tag[i-5] == 'u')&&
                (tag[i-4] == 'n')&&
                (tag[i-3] == 't')&&
                (tag[i-2] == '=')&&
                (tag[i-1] == '"')){
                    count_start = i;
                }
                if((tag[i-4] == 'i')&&
                (tag[i-3] == 'd')&&
                (tag[i-2] == '=')&&
                (tag[i-1] == '"')){
                    name_start = i;
                }
            }
            while(tag[count_start]!='"'){
                count = count*10 + char2num(tag[count_start++]);
            }
            int j = 0;
            while(tag[name_start]!='"'){
                name.push_back(tag[name_start++]);
//                name[j++] = ;
            }
            std::cout << name << " " << count / 3 << std::endl;;
            for(int i = 0;i<count/3;i++){
                AoTK::Math::Vector4<float> v(0,0,0,1);
                f >> v.x;
                f >> v.y;
                f >> v.z;
                v = transform * v;
                float_arrays[name].push_back({v.x,v.y,v.z});
            }
        }else if(strncmp(data,"<polylist",9) == 0){
            int i,count = 0;
            for(i = 7;i<300;i++){
                if((tag[i-7] == 'c')&&
                (tag[i-6] == 'o')&&
                (tag[i-5] == 'u')&&
                (tag[i-4] == 'n')&&
                (tag[i-3] == 't')&&
                (tag[i-2] == '=')&&
                (tag[i-1] == '"')){
                    break;
                }
            }
            while(tag[i]!='"'){
                count = count*10 + char2num(tag[i++]);
            }
            memset(tag,0,300);
            f.getline(tag,300,'>');
            data = strchr(tag,'<');
            while(strncmp(data,"<vcount",7) != 0){
                if(strncmp(data,"<input",6) == 0){
                    char *p;
                    std::string name;
                    if(p = strstr(data,"VERTEX")){
                        int offset;
                        p = strstr(data,"offset=\"");
                        assert(p);
                        offset = char2num(p[8]);
                        p = strstr(data,"source=\"#");
                        for(int j = 9;p[j]!='"';j++){
                            name.push_back(p[j]);
                        }
                        name = name.substr(0,name.find("vertices"));
                        name.push_back('p');
                        name.push_back('o');
                        name.push_back('s');
                        name.push_back('i');
                        name.push_back('t');
                        name.push_back('i');
                        name.push_back('o');
                        name.push_back('n');
                        name.push_back('s');
                        name.push_back('-');
                        name.push_back('a');
                        name.push_back('r');
                        name.push_back('r');
                        name.push_back('a');
                        name.push_back('y');
                        std::cout << name << std::endl;
                        assert(p);
                        offsets[offset] = std::pair<COLLADA_DATA_SEMANTICS,std::string>(VERTEX,name);
                    }
                    else if(p = strstr(data,"NORMAL")){
                        int offset;
                        p = strstr(data,"offset=\"");
                        assert(p);
                        offset = char2num(p[8]);
                        p = strstr(data,"source=\"#");
                        int j;
                        for(j = 9;p[j]!='"';j++){
                            name.push_back(p[j]);
                        }
                        name.push_back('-');
                        name.push_back('a');
                        name.push_back('r');
                        name.push_back('r');
                        name.push_back('a');
                        name.push_back('y');
                        std::cout << name << std::endl;
                        assert(p);
                        offsets[offset] = std::pair<COLLADA_DATA_SEMANTICS,std::string>(NORMAL,name);;
                    }else{
                        assert(false && "Unkown semantic");
                    }

                }
                memset(tag,0,300);
                f.getline(tag,300,'>');
                data = strchr(tag,'<');

            }
            for(int i = 0;i<count;i++){
                int n;
                f >> n;
                face_types.push_back(n);
            }
            memset(tag,0,300);
            f.getline(tag,300,'>');
            data = strchr(tag,'<');
            memset(tag,0,300);
            f.getline(tag,300,'>');
            data = strchr(tag,'<');
            std::vector<AoTK::Math::Vector3<float>> pos;
            int index;
            for(auto face_type = face_types.begin();face_type != face_types.end();++face_type){
                pos.clear();
                for(int i = 0;i<(*face_type);i++){
                    for(auto o = offsets.begin();o != offsets.end();++o){
                        if(o->second.first == NORMAL){
                            f >> index; //normal index
                        }else if(o->second.first == VERTEX){
                            f >> index;
                            pos.push_back(float_arrays[o->second.second][index]);
                        }
                    }
                }
                addFace(pos,"default",true);
            }
        }
        memset(tag,0,300);
        f.getline(tag,300,'>');
        data = strchr(tag,'<');
    }
    if(this->materials.size() == 0){
        this->materials["default"] = Material();
    }
    f.close();
    this->calculateFaceNormals();
    this->calculateVertexNormals();
}

};



};
