#include "v3math.h"
#include <stdio.h>
#include <assert.h>

int main() {
    float a[] = {0.5, 0.25, 0.6};
    float b[] = {0.75, 0.125, 0.61};
    float c[] = {0, 0, 0};

    v3_add(c, a, b);

    printf("%f %f %f\n", c[0], c[1], c[2]);

    assert(c[0] == 1.25);

    assert(c[1] == .375);

    assert(c[2] == 1.21);
}
