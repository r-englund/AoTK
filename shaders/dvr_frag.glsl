
//#version 150 compatibility
//precision highp float;

uniform sampler2D front_tex;
uniform sampler2D back_tex;
uniform sampler3D vol_tex;

uniform vec2 window_size;

uniform float threshold;
uniform float stepsize;
uniform float div_coeff;

uniform int type;

vec4 raytraceGradMag(vec3 inC,vec3 outC){
    vec3 dir = outC-inC;
    float maxLength = length(dir);
    dir = normalize(dir);

    vec3 ppos = inC;    inC += dir*stepsize;
    vec3 pos = inC;     inC += dir*stepsize;
    vec3 npos = inC;
    vec4 color = vec4(0.0,0.0,0.0,0.0);
    for(int i=0;i< int(maxLength/stepsize) && color.a < 0.9;i++){
        vec4 b = texture3D(vol_tex,pos);
        if(b.a > threshold){
            vec4 a = texture3D(vol_tex,ppos);
            vec4 c = texture3D(vol_tex,npos);

            a.xyz = (a.xyz - 0.5 ) * 2.0;
            b.xyz = (b.xyz - 0.5 ) * 2.0;
            c.xyz = (c.xyz - 0.5 ) * 2.0;

            float al = length(a);
            float bl = length(b);
            float cl = length(c);

            if(bl > al && bl > cl){
                float intens = abs(dot(normalize(b.xyz),dir)) * bl * div_coeff;
                color += vec4(intens,intens,intens,b.a*div_coeff);
            }
        }
        ppos = pos;
        pos = npos;
        npos = npos + stepsize*dir;
    }

    return color;
}

vec4 raytraceAvg(vec3 inC,vec3 outC){
    vec3 dir = outC-inC;
    float maxLength = length(dir);
    dir = normalize(dir);

    vec3 pos = inC;
    vec4 color = vec4(0.0,0.0,0.0,0.0);
    int num = 0;
    float avg = 0.0;
    for(int i=0; i < int(maxLength/stepsize) && color.a < 0.9;i++){
        vec4 a = texture3D(vol_tex,pos);
        if(a.a > threshold){
            avg  = avg + a.a;
            num = num + 1;
        }
        pos = pos + dir*stepsize;
    }
    avg = avg / float(num);
    color.r = avg;
    color.g = avg;
    color.b = avg;
    color.a = 1.0;
    return color;
}

vec4 raytraceMip(vec3 inC,vec3 outC){
    vec3 dir = outC-inC;
    float maxLength = length(dir);
    dir = normalize(dir);

    vec3 pos = inC;
    vec4 color = vec4(0.0,0.0,0.0,0.0);
    float max = 0.0;
    for(int i=0;i<int(maxLength/stepsize) && color.a < 0.9;i++){
        vec4 a = texture3D(vol_tex,pos);
        if(a.a>max) max = a.a;

        pos = pos + dir*stepsize;
    }
    if(max<threshold)
        return color;
    color.r = max;
    color.g = max;
    color.b = max;
    color.a = 1.0;
    return color;
}

vec4 raytraceDens(vec3 inC,vec3 outC){
    vec3 dir = outC-inC;
    float maxLength = length(dir);
    dir = normalize(dir);

    vec3 pos = inC;
    vec4 color = vec4(0.0,0.0,0.0,0.0);
    for(int i=0;i < int(maxLength/stepsize) && color.a < 0.9;i++){
        vec4 a = texture3D(vol_tex,pos);
        if(a.a > threshold){
            a.xyz = normalize(a.xyz*2.0-1.0);
            float intens = abs(dot(a.xyz,dir));
            return vec4(intens,intens,intens,1.0);
        }

        pos = pos + dir*stepsize;
    }

    return color;
}

vec4 raytrace(vec3 inC,vec3 outC){
    vec3 dir = outC-inC;
    float maxLength = length(dir);
    dir = normalize(dir);

    vec3 pos = inC;
    vec4 color = vec4(0.0,0.0,0.0,0.0);
    for(int i=0;i < int(maxLength/stepsize) && color.a < 0.9;i++){
        vec4 a = texture3D(vol_tex,pos);


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

    if(type == 0)
        color = RayInCoord;
    if(type == 1)
        color = RayOutCoord;
    if(type == 2)
        color = raytraceAvg(RayInCoord.xyz,RayOutCoord.xyz);
    if(type == 3)
        color = raytraceGradMag(RayInCoord.xyz,RayOutCoord.xyz);
    if(type == 4)
        color = raytraceMip(RayInCoord.xyz,RayOutCoord.xyz);
    if(type == 5)
        color = raytraceDens(RayInCoord.xyz,RayOutCoord.xyz);

    gl_FragColor = color;
}

