
#version 150 core
precision highp float;

uniform mat4 projection_matrix;
uniform mat4 view_matrix;
uniform mat4 model_matrix;

in vec4 in_pos;
in vec3 in_normal;
in vec2 in_tex_coord;

out vec3 out_normal;
out vec2 out_tex_coord;

void main(void){
    out_normal = in_normal;
    out_tex_coord = in_tex_coord;
    gl_Position = projection_matrix * view_matrix * model_matrix * in_pos;
}
