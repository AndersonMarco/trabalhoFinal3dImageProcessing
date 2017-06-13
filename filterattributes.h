#ifndef FILTERATTRIBUTES_H
#define FILTERATTRIBUTES_H


class FilterAttributes
{
public:
    FilterAttributes();
    static const int filterTypeNone=0;
    static const int filterTypeEdge=1;
    static const int filterTypeBlur=2;
    static const int filterTypeBloom=3;
    static const int filterTypeGamma=4;
    static const int filterTypeUnsharpen=5;
    static const int filterTypeSharpen=6;
    static const int filterTypeWave=7;
    static const int filterTypeNegativo=8;

    static const int maxFilterTypeEdge=500;
    static const int maxFilterTypeBloom=1000;
    static const int maxFilterTypeGamma=4000;
    static const int maxFilterTypeWave=60000;

    static const int minFilterTypeEdge=0;
    static const int minFilterTypeBloom=800;
    static const int minFilterTypeGamma=0;
    static const int minFilterTypeWave=0;

};

#endif // FILTERATTRIBUTES_H
