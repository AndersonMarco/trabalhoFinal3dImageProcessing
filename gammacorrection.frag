#version 130
in vec2 v_texCoord;
out vec4 myfragcolor;
uniform sampler2D texture1;
uniform vec2 u_resolution;
uniform float gamma;
//uniform vec2 u_textureSize;
void main(void)
{
    myfragcolor=vec4(pow(texture2D(texture1,v_texCoord).rgb,vec3(1.0/gamma)),1.0);

}

