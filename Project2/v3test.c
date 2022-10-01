#include "v3math.h"
#include <stdio.h>
#include <assert.h>

int main();


int main() {
    // create vectors to add
    float vectorA[] = {0.5, 0.25, 0.6};
    float vectorB[] = {0.75, 0.125, 0.61};
    // create dest vector
    float dest[] = {0, 0, 0};
    // correct answer vector
    float answer[] = {1.25, .375, 1.21};

    // add vectors
    v3_add(dest, vectorA, vectorB);

    // tolerance
    float tolerance = 1e-9;

    // FIRST TEST OF ADD
    assert(v3_equals(answer, dest, tolerance));
    


}
