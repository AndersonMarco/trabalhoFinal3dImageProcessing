#version 130
in vec2 v_texCoord;
out vec4 myfragcolor;
uniform sampler2D texture1;
uniform vec2 u_resolution;
void main(void)
{

    myfragcolor=vec4(1.0-texture2D(texture1,v_texCoord).rgb,1);

}


