
//#version 150 compatibility
//precision highp float;

void main()
{
    gl_FrontColor = gl_Color;
    gl_Position = ftransform();
}


