#include "v3math.h"
#include <stdio.h>
#include <assert.h>

int main();


int main() {
    // tolerance for equality test
    float tolerance = 1e-3;

    // v3_add tests

    // create vectors to add, and then add them
    float vectorA[] = {0.5, 0.25, 0.6};
    float vectorB[] = {0.75, 0.125, 0.61};
    float dest[] = {0, 0, 0};
    float answer[] = {1.25, .375, 1.21};
    v3_add(dest, vectorA, vectorB);

    // FIRST TEST OF ADD
    assert(v3_equals(answer, dest, tolerance));
    
    // reset values and add
    vectorA[0] = 0.5;  vectorA[1] = 1.56;  vectorA[2] = 0.6;
    vectorB[0] = 0.25;  vectorB[1] = 2.1;  vectorB[2] = 0.81;
    dest[0] = 0;  dest[1] = 0;  dest[2] = 0;
    answer[0] = 0.75;  answer[1] = 3.66;  answer[2] = 1.41;
    v3_add(dest, vectorA, vectorB);

    // SECOND TEST OF ADD
    assert(v3_equals(answer, dest, tolerance));

    // reset values and add
    vectorA[0] = 0.33;  vectorA[1] = 3.6;  vectorA[2] = 9;
    dest[0] = 0;  dest[1] = 0;  dest[2] = 0;
    answer[0] = 0.66;  answer[1] = 7.2;  answer[2] = 18;
    v3_add(dest, vectorA, vectorA);

    // Third TEST OF ADD
    assert(v3_equals(answer, dest, tolerance));

    //v3 from points test

    // reset
    vectorA[0] = 3;  vectorA[1] = 3;  vectorA[2] = 5;
    vectorB[0] = 3;  vectorB[1] = 5;  vectorB[2] = 3;
    answer[0] = 0;  answer[1] = 2;  answer[2] = -2;
    dest[0] = 0;  dest[1] = 0;  dest[2] = 0;
    v3_from_points(dest, vectorA, vectorB);

    // first test of from
    assert(v3_equals(answer, dest, tolerance));

    // reset
    vectorA[0] = 3.5;  vectorA[1] = 3.91;  vectorA[2] = 10;
    vectorB[0] = 3.8;  vectorB[1] = 5.2;  vectorB[2] = 100;
    answer[0] = 0.3;  answer[1] = 1.29;  answer[2] = 90;
    dest[0] = 0;  dest[1] = 0;  dest[2] = 0;
    v3_from_points(dest, vectorA, vectorB);

    // second test of from
    assert(v3_equals(answer, dest, tolerance));

    // reset
    vectorA[0] = 8;  vectorA[1] = 2;  vectorA[2] = 10.5;
    vectorB[0] = -1;  vectorB[1] = 26;  vectorB[2] = 100;
    answer[0] = -9;  answer[1] = 24;  answer[2] = 89.5;
    dest[0] = 0;  dest[1] = 0;  dest[2] = 0;
    v3_from_points(dest, vectorA, vectorB);

    // third test of from
    assert(v3_equals(answer, dest, tolerance));


    // subtract function
    
    // reset 
    vectorA[0] = 0.5;  vectorA[1] = 1.56;  vectorA[2] = 0.6;
    vectorB[0] = 0.25;  vectorB[1] = 2.1;  vectorB[2] = 0.81;
    dest[0] = 0;  dest[1] = 0;  dest[2] = 0;
    answer[0] = .25;  answer[1] = -.54;  answer[2] = -.21;
    v3_subtract(dest, vectorA, vectorB);

    // FIRST TEST OF SUB
    assert(v3_equals(answer, dest, tolerance));

    // reset 
    vectorA[0] = 5;  vectorA[1] = 700;  vectorA[2] = .6554;
    vectorB[0] = 6;  vectorB[1] = 100;  vectorB[2] = 1.334;
    dest[0] = 0;  dest[1] = 0;  dest[2] = 0;
    answer[0] = -1;  answer[1] = 600;  answer[2] = -.6786;
    v3_subtract(dest, vectorA, vectorB);

    // SECOND TEST OF SUB
    assert(v3_equals(answer, dest, tolerance));

    // reset 
    vectorA[0] = 1000;  vectorA[1] = -100;  vectorA[2] = -.6554;
    vectorB[0] = 1000;  vectorB[1] = -100;  vectorB[2] = 1.334;
    dest[0] = 0;  dest[1] = 0;  dest[2] = 0;
    answer[0] = 0;  answer[1] = 0;  answer[2] = -1.9894;
    v3_subtract(dest, vectorA, vectorB);

    // THIRD TEST OF SUB
    assert(v3_equals(answer, dest, tolerance));


    // DOT PRODUCT

    // reset 
    vectorA[0] = 1;  vectorA[1] = 2;  vectorA[2] = 3;
    vectorB[0] = 1;  vectorB[1] = 5;  vectorB[2] = 7;
    dest[0] = 0;  dest[1] = 0;  dest[2] = 0;
    answer[0] = 32;  answer[1] = 0;  answer[2] = 0;
    dest[0] = v3_dot_product(vectorA, vectorB);

    // FIRST TEST OF DOT PRODUCT
    assert(v3_equals(answer, dest, tolerance));

    // reset 
    vectorA[0] = 1.4;  vectorA[1] = 2.5;  vectorA[2] = 3.8;
    vectorB[0] = 1;  vectorB[1] = 5;  vectorB[2] = 7;
    dest[0] = 0;  dest[1] = 0;  dest[2] = 0;
    answer[0] = 40.5;  answer[1] = 0;  answer[2] = 0;
    dest[0] = v3_dot_product(vectorA, vectorB);

    // SECOND TEST OF DOT PRODUCT
    assert(v3_equals(answer, dest, tolerance));

    // reset 
    vectorA[0] = 100.4;  vectorA[1] = 200.5;  vectorA[2] = 300.8;
    vectorB[0] = 1;  vectorB[1] = -5;  vectorB[2] = 7;
    dest[0] = 0;  dest[1] = 0;  dest[2] = 0;
    answer[0] = 1203.5;  answer[1] = 0;  answer[2] = 0;
    dest[0] = v3_dot_product(vectorA, vectorB);

    // SECOND TEST OF DOT PRODUCT
    assert(v3_equals(answer, dest, tolerance));

    // reset 
    vectorA[0] = 100.4;  vectorA[1] = 200.5;  vectorA[2] = 300.6;
    vectorB[0] = 1;  vectorB[1] = -5;  vectorB[2] = 7;
    dest[0] = 0;  dest[1] = 0;  dest[2] = 0;
    answer[0] = 1202.1;  answer[1] = 0;  answer[2] = 0;
    dest[0] = v3_dot_product(vectorA, vectorB);


    printf("ans: %f %f %f\n", answer[0], answer[1], answer[2]);
    printf("result: %f %f %f\n", dest[0], dest[1], dest[2]);

    // THIRD TEST OF DOT PRODUCT
    assert(v3_equals(answer, dest, tolerance));


    // CROSS PRODUCT

    // reset 
    vectorA[0] = 1;  vectorA[1] = 2;  vectorA[2] = 3;
    vectorB[0] = 1;  vectorB[1] = 5;  vectorB[2] = 7;
    dest[0] = 0;  dest[1] = 0;  dest[2] = 0;
    answer[0] = 32;  answer[1] = 0;  answer[2] = 0;
    dest[0] = v3_dot_product(vectorA, vectorB);

    // FIRST TEST OF DOT PRODUCT
    assert(v3_equals(answer, dest, tolerance));

    return 0;
}
