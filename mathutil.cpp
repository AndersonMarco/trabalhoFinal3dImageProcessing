#include "mathutil.h"

MathUtil::MathUtil()
{

}
float* MathUtil::getWeights(int size){
    float *ret= new float[size];
    float sum=0.0f;
    float sigma=2.0;

    for(int i=0; i<size;i++){
        ret[i]=gaussian(i,sigma);
        sum=sum+(2*ret[i]);
    }
    for(int i=0; i<size;i++){
        ret[i]=ret[i]/sum;
    }
    return ret;
}
float MathUtil::gaussian(float x, float sigma){
    double pi=3.14159265359;
    double e=2.71828182846;
    double doubleSigma=sigma*sigma;

    return (float)((1.0/sqrt((double)2*pi*doubleSigma))*(pow(e,(-(x*x))/(2*doubleSigma))));
}
