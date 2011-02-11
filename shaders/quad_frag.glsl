
#version 150 core
precision highp float;

out vec4 out_Color;

in vec3 out_normal;
in vec2 out_tex_coord;

void main(){
    out_Color  = vec4(out_tex_coord.x,out_tex_coord.y,1.0,1.0);
}

