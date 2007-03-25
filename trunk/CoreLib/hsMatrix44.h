#ifndef _HSMATRIX44_H
#define _HSMATRIX44_H

#include "hsStream.h"
#include "../FeatureLib/pfPRC/pfPrcHelper.h"

struct hsMatrix44 {
private:
    float data[4][4];

public:
    hsMatrix44();
    hsMatrix44(hsMatrix44& init);
    ~hsMatrix44();
    
    void Identity();
    bool IsIdentity();
    
    float& operator()(int y, int x);
    hsMatrix44& operator+(const hsMatrix44& other);
    hsMatrix44& operator*(const hsMatrix44& other);
    hsMatrix44& operator*(const float mult);
    //const hsMatrix44& operator+=(const hsMatrix44 &other);
    //const hsMatrix44& operator*=(const hsMatrix44 &other);
    //const hsMatrix44& operator*=(const float mult);
    hsMatrix44& operator=(const hsMatrix44& other);
    bool operator==(const hsMatrix44& other);
    
    hsMatrix44& translate(float x, float y, float z);
    hsMatrix44& scale(float x, float y, float z);
    hsMatrix44& rotate(float x, float y, float z);
    
    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(hsStream* S, pfPrcHelper* prc);

    const char* toString();
};

#endif
