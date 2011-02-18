#ifndef LIGHT_H
#define LIGHT_H

#include <AoTK/aotk.h>


namespace AoTK{
    class Light: public Object{
        friend class AOTK;
        std::string name;
        Position<> pos;
        Color<> amb;
        Color<> dif;
        Color<> spec;
        float spot_exp;
        float spot_cutoff;
        Direction<> dir;

        float con_att;
        float lin_att;
        float quad_att;

        LIGHT_TYPE type;

        Light(std::string name);
        Light(const Light &l) = delete;
        Light &operator=(const Light &l) = delete;

        void logic(){}
        void graphic();
        void prepare(){}
        void render(){std::cout << "drawing of a lightsource is not yet implemented";}

    public:
        ~Light();

        void setLight(GLuint id);

        void setAmbientColor(Color<> col);
        void setDiffuseColor(Color<> col);
        void setSpecularColor(Color<> col);

        void setSpotExp(float exp);
        void setSpotCutoff(float cutoff);

        void setConstantAttenuation(float att);
        void setLinearAttenuation(float att);
        void setQuadraticAttenuation(float att);
        void setAttenuation(float constant,float linear,float quadratic);

        static Light* CreatePointLight(std::string name = "",Position<> pos = Position<>(),Color<> ambient_color = Color<>(0,0,0,1),Color<> diffuse_color = Color<>(1,1,1,1),Color<> specular_color = Color<>(1,1,1,1));
        static Light* CreateDirectionLight(std::string name = "",Direction<> dir = Direction<>(0,-1,0),Color<> ambient_color = Color<>(0,0,0,1),Color<> diffuse_color = Color<>(1,1,1,1),Color<> specular_color = Color<>(1,1,1,1));
        static Light* CreateSpotLight(std::string name = "",Position<> pos = Position<>(),Direction<> dir = Direction<>(0,-1,0),Color<> ambient_color = Color<>(0,0,0,1),Color<> diffuse_color = Color<>(1,1,1,1),Color<> specular_color = Color<>(1,1,1,1));

    };
};

#endif
