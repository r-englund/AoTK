
//#version 150 compatibility
//precision highp float;

uniform sampler2D front_tex;
uniform sampler2D back_tex;
uniform sampler3D vol_tex;

uniform vec2 window_size;

uniform float threshold;
uniform float stepsize;

vec4 raytrace(vec3 inC,vec3 outC){
    vec3 dir = outC-inC;
    float maxLength = length(dir);
    dir = normalize(dir);

    vec3 pos = inC;
    vec4 color = vec4(0,0,0,0);
    for(int i=0;i<maxLength/stepsize && color.a < 0.9;i++){
        vec4 a = texture3D(vol_tex,pos);
        if(a.w > threshold){
            a.xyz = normalize((a.xyz - 0.5 ) *2);
            float intens = dot(a.xyz,dir) * a.a;
            color = color + vec4(intens,intens,intens,a.a);

        }
        //a.xyz = (a.xyz - 0.5 ) *2;
        //if(length(a.xyz) > threshold){
        //    a.xyz = normalize(a.xyz);
        //    float intens = dot(a.xyz,dir);
        //    return vec4(intens,intens,intens,1);
        //}
        pos = pos + dir*stepsize;
    }

    return color;
}

void main()
	{
		vec2 inout_coords=gl_FragCoord.xy/window_size;
		vec4 color;
		vec4 RayOutCoord = texture2D(back_tex,inout_coords);
		vec4 RayInCoord = texture2D(front_tex,inout_coords);

        vec4 blabla = texture3D(vol_tex,RayInCoord.xyz);

        color = raytrace(RayInCoord.xyz,RayOutCoord.xyz);

		gl_FragColor = color;
   	}
