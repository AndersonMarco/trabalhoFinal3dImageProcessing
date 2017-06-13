#ifndef MATHUTIL_H
#define MATHUTIL_H
#include<math.h>

class MathUtil
{
public:
    MathUtil();
    static float* getWeights(int size);
    static float gaussian(float x,float sigma);
};

#endif // MATHUTIL_H
