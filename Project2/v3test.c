#include "v3math.h"
#include <stdio.h>
#include <assert.h>

int main();


int main() {
    float a[] = {0.5, 0.25, 0.6};
    float b[] = {0.75, 0.125, 0.61};
    float c[] = {0, 0, 0};

    v3_add(c, a, b);

    printf("%f %f %f\n", c[0], c[1], c[2]);

}
