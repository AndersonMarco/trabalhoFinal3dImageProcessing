#version 130
in vec2 v_texCoord;
out vec4 myfragcolor;
uniform sampler2D texture1;
uniform sampler2D texture2;

uniform vec2 u_resolution;
uniform int pass;
uniform float weights[10];
uniform float PixOffset[10]= float[](0.0,1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0);
uniform float lumThresh;
float luma(vec3 color){
    return (0.2126*color.r)+(0.7152*color.g)+(0.0722*color.b);
}

vec4 pass1(){
    vec4 val=texture2D(texture1,v_texCoord);
    return val*clamp(luma(val.rgb)-lumThresh,0.0,1.0)*(1.0/(1.0-lumThresh));
}
vec4 pass2(){
    float dy=1.0/float(u_resolution.y);
    vec4 sum=vec4(0.0,0.0,0.0,0.0);
    for(int i=0;i<10;i++){
        sum=sum+texture2D(texture2,v_texCoord+vec2(0.0,PixOffset[i])*dy)*weights[i];
        sum=sum+texture2D(texture2,v_texCoord-vec2(0.0,PixOffset[i])*dy)*weights[i];
    }
    return sum;
}
vec4 pass3(){    
    float dx=1.0/float(u_resolution.x);   
    vec4 sum=vec4(0.0,0.0,0.0,0.0);
    for(int i=0;i<10;i++){
        sum=sum+texture2D(texture2,v_texCoord+vec2(PixOffset[i],0.0)*dx)*weights[i];
        sum=sum+texture2D(texture2,v_texCoord-vec2(PixOffset[i],0.0)*dx)*weights[i];
    }
    vec4 val= sum+texture2D(texture1,v_texCoord);
    if(val.x>1.0) val.x=1.0;
    if(val.y>1.0) val.y=1.0;
    if(val.z>1.0) val.z=1.0;
    if(val.w>1.0) val.w=1.0;
    return val;
}
void main(void)
{

    if(pass==1){
        myfragcolor = pass1();
    }

    else if(pass==2){
        myfragcolor = pass2();
    }
    else if(pass==3){
        myfragcolor = pass3();
    }
}
