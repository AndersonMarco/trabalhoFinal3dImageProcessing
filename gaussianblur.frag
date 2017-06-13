#version 130
in vec2 v_texCoord;
out vec4 myfragcolor;
uniform sampler2D texture1;
uniform vec2 u_resolution;
uniform float weights[5];
uniform float PixOffset[5]= float[](0.0,1.0,2.0,3.0,4.0);
uniform int pass;
vec4 pass1(){
    float dy=1.0/float(u_resolution.y);
    vec4 sum=vec4(0.0,0.0,0.0,0.0);
    for(int i=0;i<5;i++){
        sum=sum+texture2D(texture1,v_texCoord+vec2(0.0,PixOffset[i])*dy)*weights[i];
        sum=sum+texture2D(texture1,v_texCoord-vec2(0.0,PixOffset[i])*dy)*weights[i];
    }
    return sum;
}
vec4 pass2(){
    float dx=1.0/float(u_resolution.x);
    vec4 sum=vec4(0.0,0.0,0.0,0.0);
    for(int i=0;i<5;i++){
        sum=sum+texture2D(texture1,v_texCoord+vec2(PixOffset[i],0.0)*dx)*weights[i];
        sum=sum+texture2D(texture1,v_texCoord-vec2(PixOffset[i],0.0)*dx)*weights[i];
    }
    return sum;
}
vec4 pass1Fake(){
    return vec4(1,0,0,1);
}
vec4 pass2Fake(){
    return texture2D(texture1,v_texCoord)+vec4(0,0,1,0);
}
void main(void)
{
    if(pass==1)
        myfragcolor=pass1();
    if(pass==2)
        myfragcolor=pass2();
}

