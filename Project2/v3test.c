#include "v3math.h"
#include <stdio.h>
#include <assert.h>

int main();


int main() {
    // tolerance for equality test
    float tolerance = 1e-6;

    // create vectors to add
    float vectorA[] = {0.5, 0.25, 0.6};
    float vectorB[] = {0.75, 0.125, 0.61};

    // create dest vector
    float dest[] = {0, 0, 0};

    // correct answer vector
    float answer[] = {1.25, .375, 1.21};

    // add vectors
    v3_add(dest, vectorA, vectorB);

    // FIRST TEST OF ADD
    assert(v3_equals(answer, dest, tolerance));
    
    // reset values and add
    vectorA[0] = 0.5;  vectorA[1] = 1.56;  vectorA[2] = 0.6;
    vectorB[0] = 0.25;  vectorB[1] = 2.1;  vectorB[2] = 0.81;
    dest[0] = 0;  dest[1] = 0;  dest[2] = 0;
    answer[0] = 0.75;  answer[1] = 3.66;  answer[2] = 1.41;

    v3_add(dest, vectorA, vectorB);

    printf("%f %f %f\n", dest[0], dest[1], dest[2]);
    printf("%f %f %f\n", answer[0], answer[1], answer[2]);

    // SECOND TEST OF ADD
    assert(v3_equals(answer, dest, tolerance));

}
