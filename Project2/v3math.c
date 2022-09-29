#include <math.h>
#include "v3math.h"

void v3_from_points(float *dst, float *a, float *b)
{
    // distance from a to b is b - a
    dst[0] = b[0] - a[0];
    dst[1] = b[1] - a[1];
    dst[2] = b[2] - a[2];
}

void v3_add(float *dst, float *a, float *b)
{
    dst[0] = a[0] + b[0];
    dst[1] = a[1] + b[1];
    dst[2] = a[2] + b[2];
}

void v3_subtract(float *dst, float *a, float *b)
{
    dst[0] = a[0] - b[0];
    dst[1] = a[1] - b[1];
    dst[2] = a[2] - b[2];
}

float v3_dot_product(float *a, float *b)
{
    float dotProduct = a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
    return dotProduct;
}

void v3_cross_product(float *dst, float *a, float *b)
{
    dst[0] = a[1] * b[2] - a[2] * b[1];
    dst[1] = a[2] * b[0] - a[0] * b[2];
    dst[2] = a[0] * b[1] - a[1] * b[0];
}

void v3_scale(float *dst, float s)
{
    dst[0] = dst[0] * s;
    dst[1] = dst[1] * s;
    dst[2] = dst[2] * s;
}

float v3_angle(float *a, float *b)
{
    float dotProduct = v3_dot_product(a, b);
    float aMag = v3_length(a);
    float bMag = v3_length(b);

    float angle = acos(dotProduct / aMag * bMag);
    return angle;
}

float v3_angle_quick(float *a, float *b)
{
    // initialize final result
    float quickAngle;

    // allocate memory for 2 normalized vectors of a and b
    float normalizedA[3];
    float normalizedB[3];

    // normalize a and b
    v3_normalize(normalizedA, a);
    v3_normalize(normalizedB, b);

    // find dot product with normalized vectors to get angle
    quickAngle = v3_dot_product(normalizedA, normalizedB);

    return quickAngle;
}

void v3_reflect(float *dst, float *v, float *n)
{
    
}

float v3_length(float *a)
{
    return sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
}

void v3_normalize(float *dst, float *a)
{
    float aLength = v3_length(a);
    dst[0] = a[0] / aLength;
    dst[1] = a[1] / aLength;
    dst[2] = a[2] / aLength;
}
