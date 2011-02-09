#include <AoTK/aotk.h>


namespace AoTK{
void Sphere::logic(){

}
void Sphere::graphic(){}
void Sphere::prepare(){}
void Sphere::render(){
    static float deg = 0;
    glRotatef(deg,0,1,0);
    deg += 0.005;

    glBegin(GL_TRIANGLES);
    for(auto i = indices.begin(); i != indices.end();++i){
        glNormal3fv(vertices[*i].norm.arr);
        glVertex4fv(vertices[*i].pos.arr);
    }
    glEnd();

//    std::cout << "Num Vert: " << vertices.size() << " | Num Faces: " << indices.size()/3.0 << std::endl;
//
//    glBegin(GL_POINTS);
//    unsigned int a = 0;
//    for(auto i = vertices.begin(); i != vertices.end();++i){
//        glVertex4fv(i->pos.arr);
//        a++;
//    }
//    std::cout << a << std::endl;
//    glEnd();
}

Sphere::Sphere(float _radius,Matrix toWorld,unsigned int _subdivision, std::string name):
Object(0,toWorld,name),
radius(_radius),
subdivisions(_subdivision)
{
    tesselate();
}

void Sphere::tesselate(){
    float t = (1+sqrt(5))/2;
    float tau = t/sqrt(1+t*t);
    float one = 1/sqrt(1+t*t);

    vertices.clear();
    indices.clear();

    Vertex v[12];
    v[0].pos = Position(tau,one,0.0);
    v[1].pos = Position(-tau,one,0.0);
    v[2].pos = Position(-tau,-one,0.0);
    v[3].pos = Position(tau,-one,0.0);

    v[4].pos = Position(one,0.0,tau);
    v[5].pos = Position(one,0.0,-tau);
    v[6].pos = Position(-one,0.0,-tau);
    v[7].pos = Position(-one,0.0,tau);

    v[8].pos = Position(0.0,tau,one);
    v[9].pos = Position(0.0,-tau,one);
    v[10].pos = Position(0.0,-tau,-one);
    v[11].pos = Position(0.0,tau,-one);

    vertices.push_back(v[0]);
    vertices.push_back(v[1]);
    vertices.push_back(v[2]);
    vertices.push_back(v[3]);
    vertices.push_back(v[4]);
    vertices.push_back(v[5]);
    vertices.push_back(v[6]);
    vertices.push_back(v[7]);
    vertices.push_back(v[8]);
    vertices.push_back(v[9]);
    vertices.push_back(v[10]);
    vertices.push_back(v[11]);


     indices = {4, 8, 7,4, 7, 9,5, 6, 11,5, 10, 6,0, 4, 3,0, 3, 5,2, 7, 1,2, 1, 6,8, 0, 11,8, 11, 1,9, 10, 3,9, 2, 10,8, 4, 0,11, 0, 5,4, 9, 3,5, 3, 10,7, 8, 1,6, 1, 11,7, 2, 9,6, 10, 2};

    for(int j = 0;j<subdivisions;j++){
        int curIndiSize = indices.size();
        unsigned int A,B,C,a,b,c;
        std::vector<unsigned short> newIndices;
        for(int i = 0;i<curIndiSize;i+=3){
            A = indices[i+0]; //A
            B = indices[i+1]; //B
            C = indices[i+2]; //C
            a = vertices.size();//a
            b = vertices.size()+1;//b
            c = vertices.size()+2;//c

            Vertex v0,v1,v2;
            v0.pos = (vertices[A].pos) * 0.5 + (vertices[B].pos * 0.5);
            v1.pos = (vertices[B].pos) * 0.5 + (vertices[C].pos * 0.5);
            v2.pos = (vertices[C].pos) * 0.5 + (vertices[A].pos * 0.5);

//            Aca
//            acb
//            abB
//            cCb
            vertices.push_back(v0);
            vertices.push_back(v1);
            vertices.push_back(v2);
            newIndices.push_back(A);newIndices.push_back(c);newIndices.push_back(a);
            newIndices.push_back(a);newIndices.push_back(c);newIndices.push_back(b);
            newIndices.push_back(a);newIndices.push_back(b);newIndices.push_back(B);
            newIndices.push_back(c);newIndices.push_back(C);newIndices.push_back(b);

        }
        indices.clear();
        for(auto in = newIndices.begin();in != newIndices.end();++in){
            indices.push_back(*in);
        }
    }


    for(auto i = vertices.begin(); i != vertices.end();++i){
        i->pos.normalize3();
        i->norm.x = i->pos.x;
        i->norm.y = i->pos.y;
        i->norm.z = i->pos.z;
    }
}
Sphere::~Sphere(){}


};
