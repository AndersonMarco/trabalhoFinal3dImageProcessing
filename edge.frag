#version 130
in vec2 v_texCoord;
out vec4 myfragcolor;
uniform sampler2D texture1;
uniform float edgeThreshould;
uniform vec2 u_resolution;
float luma(vec3 color){
    return (0.2126*color.r)+(0.7152*color.g)+(0.0722*color.b);
}

void main(void)
{

    vec2 onePixel=vec2(1.0,1.0)/u_resolution;
    float s00=luma(texture2D(texture1,v_texCoord+vec2(-onePixel.x,onePixel.y)).rgb);
    float s10=luma(texture2D(texture1,v_texCoord+vec2(-onePixel.x,0.0)).rgb);
    float s20=luma(texture2D(texture1,v_texCoord+vec2(-onePixel.x,-onePixel.y)).rgb);
    float s01=luma(texture2D(texture1,v_texCoord+vec2(0.0,onePixel.y)).rgb);
    float s21=luma(texture2D(texture1,v_texCoord+vec2(0.0,-onePixel.y)).rgb);
    float s02=luma(texture2D(texture1,v_texCoord+vec2(onePixel.x,onePixel.y)).rgb);
    float s12=luma(texture2D(texture1,v_texCoord+vec2(onePixel.x,0.0)).rgb);
    float s22=luma(texture2D(texture1,v_texCoord+vec2(onePixel.x,-onePixel.y)).rgb);
    float sx=s00+2*s10+s20-(s02+2*s12+s22);
    float sy=s00+2*s01+s02-(s20+2*s21+s22);
    float dist=sx*sx+sy*sy;
    if(dist>edgeThreshould){
        myfragcolor = vec4(0.0,0.0,0.0,1.0);
    }

    else{
        myfragcolor = vec4(1.0,1.0,1.0,1.0);
    }
}

