#include <AoTK/aotk.h>


namespace AoTK{
void Sphere::logic(){

}
void Sphere::graphic(){}
void Sphere::prepare(){}
void Sphere::render(){
//    glBindTexture(GL_TEXTURE_2D,texture);
//    glBegin(GL_TRIANGLES);
//    for(auto i = indices.begin(); i != indices.end();++i){
//        glTexCoord2fv(vertices[*i].tex_coord.arr);
//        glNormal3fv(vertices[*i].norm.arr);
//        glVertex4fv(vertices[*i].pos.arr);
//    }
//    glEnd();


    glBindTexture(GL_TEXTURE_2D,texture);
    glBegin(GL_TRIANGLES);
    glColor3f(1,1,1);
    for(auto i = vertices.begin(); i != vertices.end();++i){
        glTexCoord2fv(i->tex_coord.arr);
//        glColor3f(i->tex_coord.x,i->tex_coord.y,0);
        glNormal3fv(i->norm.arr);
        glVertex4fv(i->pos.arr);
    }
    glEnd();
    glBindTexture(GL_TEXTURE_2D,0);
}

Sphere::Sphere(float _radius,Matrix toWorld,unsigned int _subdivision, std::string name):
Object(0,toWorld,name),
radius(_radius),
subdivisions(_subdivision)
{
    tesselate();
    rotx = 0;
    roty = 0;
}

void Sphere::mousemotion(int dx,int dy){
    rotx += dx * 0.03;
    roty += dy * 0.03;
    toWorld = Matrix::rotateX(roty)*Matrix::rotateY(-rotx);
}
//void Sphere::tesselate(){
//    float t = (1+sqrt(5))/2;
//    float tau = t/sqrt(1+t*t);
//    float one = 1/sqrt(1+t*t);
//
//    vertices.clear();
//    indices.clear();
//
//    Vertex v[12];
//    v[0].pos = Position(tau,one,0.0);
//    v[1].pos = Position(-tau,one,0.0);
//    v[2].pos = Position(-tau,-one,0.0);
//    v[3].pos = Position(tau,-one,0.0);
//
//    v[4].pos = Position(one,0.0,tau);
//    v[5].pos = Position(one,0.0,-tau);
//    v[6].pos = Position(-one,0.0,-tau);
//    v[7].pos = Position(-one,0.0,tau);
//
//    v[8].pos = Position(0.0,tau,one);
//    v[9].pos = Position(0.0,-tau,one);
//    v[10].pos = Position(0.0,-tau,-one);
//    v[11].pos = Position(0.0,tau,-one);
//
//    vertices.push_back(v[0]);
//    vertices.push_back(v[1]);
//    vertices.push_back(v[2]);
//    vertices.push_back(v[3]);
//    vertices.push_back(v[4]);
//    vertices.push_back(v[5]);
//    vertices.push_back(v[6]);
//    vertices.push_back(v[7]);
//    vertices.push_back(v[8]);
//    vertices.push_back(v[9]);
//    vertices.push_back(v[10]);
//    vertices.push_back(v[11]);
//
//
//    indices = {4, 8, 7,4, 7, 9,5, 6, 11,5, 10, 6,0, 4, 3,0, 3, 5,2, 7, 1,2, 1, 6,8, 0, 11,8, 11, 1,9, 10, 3,9, 2, 10,8, 4, 0,11, 0, 5,4, 9, 3,5, 3, 10,7, 8, 1,6, 1, 11,7, 2, 9,6, 10, 2};
//    reverse(indices.begin(),indices.end());
//
//    for(int j = 0;j<subdivisions;j++){
//        int curIndiSize = indices.size();
//        unsigned int A,B,C,a,b,c;
//        std::vector<unsigned short> newIndices;
//        for(int i = 0;i<curIndiSize;i+=3){
//            A = indices[i+0]; //A
//            B = indices[i+1]; //B
//            C = indices[i+2]; //C
//            a = vertices.size();//a
//            b = vertices.size()+1;//b
//            c = vertices.size()+2;//c
//
//            Vertex v0,v1,v2;
//            v0.pos = (vertices[A].pos) * 0.5 + (vertices[B].pos * 0.5);
//            v1.pos = (vertices[B].pos) * 0.5 + (vertices[C].pos * 0.5);
//            v2.pos = (vertices[C].pos) * 0.5 + (vertices[A].pos * 0.5);
//
//            vertices.push_back(v0);
//            vertices.push_back(v1);
//            vertices.push_back(v2);
//            newIndices.push_back(A);newIndices.push_back(a);newIndices.push_back(c);
//            newIndices.push_back(a);newIndices.push_back(b);newIndices.push_back(c);
//            newIndices.push_back(a);newIndices.push_back(B);newIndices.push_back(b);
//            newIndices.push_back(c);newIndices.push_back(b);newIndices.push_back(C);
//
//        }
//        indices.clear();
//        for(auto in = newIndices.begin();in != newIndices.end();++in){
//            indices.push_back(*in);
//        }
//    }
//
//    float maxU = -10;
//    float minU = 10;
//    float maxV = -10;
//    float minV = 10;
//    for(auto i = vertices.begin(); i != vertices.end();++i){
//        i->pos.normalize3();
//        i->norm.x = i->pos.x;
//        i->norm.y = i->pos.y;
//        i->norm.z = i->pos.z;
//
//        i->tex_coord.u = atan2(i->pos.z,i->pos.x)+M_PI;
//        i->tex_coord.u /= M_PI * 2;
//
//        i->tex_coord.v = 1 - acos(i->pos.y) / M_PI;
//
//        i->pos *= radius;
//    }
//
//}
 //TODO Check wheter the coorinates for a triangle overlaps the u == 0 lize, in that case set the coordinate to above 1 ore below zero to get correct wrapping, that might probobly do it (use the outcomment version)
void Sphere::tesselate(){
    float t = (1+sqrt(5))/2;
    float tau = t/sqrt(1+t*t);
    float one = 1/sqrt(1+t*t);

    vertices.clear();
    indices.clear();

    Vertex v[12];
    v[0].pos = Position<>(tau,one,0.0);
    v[1].pos = Position<>(-tau,one,0.0);
    v[2].pos = Position<>(-tau,-one,0.0);
    v[3].pos = Position<>(tau,-one,0.0);

    v[4].pos = Position<>(one,0.0,tau);
    v[5].pos = Position<>(one,0.0,-tau);
    v[6].pos = Position<>(-one,0.0,-tau);
    v[7].pos = Position<>(-one,0.0,tau);

    v[8].pos = Position<>(0.0,tau,one);
    v[9].pos = Position<>(0.0,-tau,one);
    v[10].pos = Position<>(0.0,-tau,-one);
    v[11].pos = Position<>(0.0,tau,-one);

    indices = {4, 8, 7,4, 7, 9,5, 6, 11,5, 10, 6,0, 4, 3,0, 3, 5,2, 7, 1,2, 1, 6,8, 0, 11,8, 11, 1,9, 10, 3,9, 2, 10,8, 4, 0,11, 0, 5,4, 9, 3,5, 3, 10,7, 8, 1,6, 1, 11,7, 2, 9,6, 10, 2};
    reverse(indices.begin(),indices.end());
    for(auto in = indices.begin();in != indices.end();++in){
        vertices.push_back(v[*in]);
    }

    for(int j = 0;j<subdivisions;j++){
        int curVertexSize = vertices.size();
        Vertex A,B,C,a,b,c;
        std::vector<Vertex> newVertex;
        for(int i = 0;i<curVertexSize;i+=3){
            Vertex A,B,C,a,b,c;
            A = vertices[i+0];
            B = vertices[i+1];
            C = vertices[i+2];
            a.pos = (A.pos+B.pos)*0.5;
            b.pos = (C.pos+B.pos)*0.5;
            c.pos = (A.pos+C.pos)*0.5;
            newVertex.push_back(A);newVertex.push_back(a);newVertex.push_back(c);
            newVertex.push_back(a);newVertex.push_back(b);newVertex.push_back(c);
            newVertex.push_back(a);newVertex.push_back(B);newVertex.push_back(b);
            newVertex.push_back(c);newVertex.push_back(b);newVertex.push_back(C);
        }
        vertices.clear();
        for(auto in = newVertex.begin();in != newVertex.end();++in){
            vertices.push_back(*in);
        }

    }

    float maxU = -10;
    float minU = 10;
    float maxV = -10;
    float minV = 10;
    for(auto i = vertices.begin(); i != vertices.end();++i){
        i->pos.normalize3();
        i->norm.x = i->pos.x;
        i->norm.y = i->pos.y;
        i->norm.z = i->pos.z;

        i->tex_coord.u = atan2(i->pos.z,i->pos.x)+M_PI;
        i->tex_coord.u /= M_PI * 2;

        i->tex_coord.v = 1 - acos(i->pos.y) / M_PI;

        if(i->tex_coord.u > maxU) maxU = i->tex_coord.u;
        if(i->tex_coord.u < minU) minU = i->tex_coord.u;
        if(i->tex_coord.v > maxV) maxV = i->tex_coord.v;
        if(i->tex_coord.v < minV) minV = i->tex_coord.v;
    }
    for(int i = 0;i<vertices.size();i+=3){
        vertices[i].pos.x *= radius;
        vertices[i].pos.y *= radius;
        vertices[i].pos.z *= radius;
        vertices[i+1].pos.x *= radius;
        vertices[i+1].pos.y *= radius;
        vertices[i+1].pos.z *= radius;
        vertices[i+2].pos.x *= radius;
        vertices[i+2].pos.y *= radius;
        vertices[i+2].pos.z *= radius;

        Vector2<> *t0,*t1,*t2;
        t0 = &vertices[i].tex_coord;
        t1 = &vertices[i+1].tex_coord;
        t2 = &vertices[i+2].tex_coord;
        float dx1,dx2,dy1,dy2,l1,l2;
            dx1 = t0->x - t1->x;
            dx2 = t0->x - t2->x;
            dy1 = t0->y - t1->y;
            dy2 = t0->y - t2->y;
            l1 = sqrt(dx1*dx1+dy1*dy1);
            l2 = sqrt(dx2*dx2+dy2*dy2);
        if(l1 > 0.5 || l2 > 0.5){
            float dx1,dx2,dy1,dy2,l1,l2;
            dx1 = t0->x - t1->x;
            dx2 = t0->x - t2->x;
            dy1 = t0->y - t1->y;
            dy2 = t0->y - t2->y;
            l1 = sqrt(dx1*dx1+dy1*dy1);
            l2 = sqrt(dx2*dx2+dy2*dy2);

//            if(fabs(l1-l2) > 0.1){
                if(t0->x < 0.5 && t1->x < 0.5 && t2->x > 0.5){
                    t2->x -= 1;
                }else if(t0->x < 0.5 && t1->x > 0.5 && t2->x < 0.5){
                    t1->x -= 1;
                }else if(t0->x < 0.5 && t1->x > 0.5 && t2->x > 0.5){
                    t0->x += 1;//Seams to never happen
                }else if(t0->x > 0.5 && t1->x < 0.5 && t2->x < 0.5){
                    t0->x -= 1;//Seams to never happen
                }else if(t0->x > 0.5 && t1->x < 0.5 && t2->x > 0.5){
                    t1->x += 1;
//                    std::cout << t0->x << " " <<  t1->x  << " " <<  t2->x << std::endl;
                }else if(t0->x > 0.5 && t1->x > 0.5 && t2->x < 0.5){
                    t2->x += 1;
                }

//            }
        }
//        if(l1 > 0.5 || l2 > 0.5){
//            t0->x = 0;t0->y=0;
//            t1->x = 0;t1->y=0;
//            t2->x = 0;t2->y=0;
//        }

    }
}
Sphere::~Sphere(){}


};
