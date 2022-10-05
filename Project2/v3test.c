#include "v3math.h"
#include <stdio.h>
#include <assert.h>

int main();


int main() {
    // error count
    int errors = 0;

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
    if(v3_equals(answer, dest, tolerance))
    {
        // passed
        printf("v3_add test 1 passed\n\n");
    }
    else
    {
        printf("v3_add test 1 failed\n");
        printf("Correct Answer: %f %f %f\n", answer[0], answer[1], answer[2]);
        printf("Actual Result: %f %f %f\n\n", dest[0], dest[1], dest[2]);
        errors++;
    }

    // reset values and add
    vectorA[0] = 0.5;  vectorA[1] = 1.56;  vectorA[2] = 0.6;
    vectorB[0] = 0.25;  vectorB[1] = 2.1;  vectorB[2] = 0.81;
    dest[0] = 0;  dest[1] = 0;  dest[2] = 0;
    answer[0] = 0.75;  answer[1] = 3.66;  answer[2] = 1.41;
    v3_add(dest, vectorA, vectorB);

    // SECOND TEST OF ADD
    if(v3_equals(answer, dest, tolerance))
    {
        // passed
        printf("v3_add test 2 passed\n\n");
    }
    else
    {
        printf("v3_add test 2 failed\n");
        printf("Correct Answer: %f %f %f\n", answer[0], answer[1], answer[2]);
        printf("Actual Result: %f %f %f\n\n", dest[0], dest[1], dest[2]);
        errors++;
    }

    // reset values and add
    vectorA[0] = 0.33;  vectorA[1] = 3.6;  vectorA[2] = 9;
    dest[0] = 0;  dest[1] = 0;  dest[2] = 0;
    answer[0] = 0.66;  answer[1] = 7.2;  answer[2] = 18;
    v3_add(dest, vectorA, vectorA);

    // Third TEST OF ADD
    if(v3_equals(answer, dest, tolerance))
    {
        // passed
        printf("v3_add test 3 passed\n\n");
    }
    else
    {
        printf("v3_add test 3 failed\n");
        printf("Correct Answer: %f %f %f\n", answer[0], answer[1], answer[2]);
        printf("Actual Result: %f %f %f\n\n", dest[0], dest[1], dest[2]);
        errors++;
    }

    //v3 from points test

    // reset
    vectorA[0] = 3;  vectorA[1] = 3;  vectorA[2] = 5;
    vectorB[0] = 3;  vectorB[1] = 5;  vectorB[2] = 3;
    answer[0] = 0;  answer[1] = 2;  answer[2] = -2;
    dest[0] = 0;  dest[1] = 0;  dest[2] = 0;
    v3_from_points(dest, vectorA, vectorB);

    // first test of from
    if(v3_equals(answer, dest, tolerance))
    {
        // passed
        printf("v3_from_points test 1 passed\n\n");
    }
    else
    {
        printf("v3_from_points test 1 failed\n");
        printf("Correct Answer: %f %f %f\n", answer[0], answer[1], answer[2]);
        printf("Actual Result: %f %f %f\n\n", dest[0], dest[1], dest[2]);
        errors++;
    }

    // reset
    vectorA[0] = 3.5;  vectorA[1] = 3.91;  vectorA[2] = 10;
    vectorB[0] = 3.8;  vectorB[1] = 5.2;  vectorB[2] = 100;
    answer[0] = 0.3;  answer[1] = 1.29;  answer[2] = 90;
    dest[0] = 0;  dest[1] = 0;  dest[2] = 0;
    v3_from_points(dest, vectorA, vectorB);

    // second test of from
    if(v3_equals(answer, dest, tolerance))
    {
        // passed
        printf("v3_from_points test 2 passed\n\n");
    }
    else
    {
        printf("v3_from_points test 2 failed\n");
        printf("Correct Answer: %f %f %f\n", answer[0], answer[1], answer[2]);
        printf("Actual Result: %f %f %f\n\n", dest[0], dest[1], dest[2]);
        errors++;
    }

    // reset
    vectorA[0] = 8;  vectorA[1] = 2;  vectorA[2] = 10.5;
    vectorB[0] = -1;  vectorB[1] = 26;  vectorB[2] = 100;
    answer[0] = -9;  answer[1] = 24;  answer[2] = 89.5;
    dest[0] = 0;  dest[1] = 0;  dest[2] = 0;
    v3_from_points(dest, vectorA, vectorB);

    // third test of from
    if(v3_equals(answer, dest, tolerance))
    {
        // passed
        printf("v3_from_points test 3 passed\n\n");
    }
    else
    {
        printf("v3_from_points test 3 failed\n");
        printf("Correct Answer: %f %f %f\n", answer[0], answer[1], answer[2]);
        printf("Actual Result: %f %f %f\n\n", dest[0], dest[1], dest[2]);
        errors++;
    }


    // subtract function
    
    // reset 
    vectorA[0] = 0.5;  vectorA[1] = 1.56;  vectorA[2] = 0.6;
    vectorB[0] = 0.25;  vectorB[1] = 2.1;  vectorB[2] = 0.81;
    dest[0] = 0;  dest[1] = 0;  dest[2] = 0;
    answer[0] = .25;  answer[1] = -.54;  answer[2] = -.21;
    v3_subtract(dest, vectorA, vectorB);

    // FIRST TEST OF SUB
    if(v3_equals(answer, dest, tolerance))
    {
        // passed
        printf("v3_subtract test 1 passed\n\n");
    }
    else
    {
        printf("v3_subtract test 1 failed\n");
        printf("Correct Answer: %f %f %f\n", answer[0], answer[1], answer[2]);
        printf("Actual Result: %f %f %f\n\n", dest[0], dest[1], dest[2]);
        errors++;
    }

    // reset 
    vectorA[0] = 5;  vectorA[1] = 700;  vectorA[2] = .6554;
    vectorB[0] = 6;  vectorB[1] = 100;  vectorB[2] = 1.334;
    dest[0] = 0;  dest[1] = 0;  dest[2] = 0;
    answer[0] = -1;  answer[1] = 600;  answer[2] = -.6786;
    v3_subtract(dest, vectorA, vectorB);

    // SECOND TEST OF SUB
    if(v3_equals(answer, dest, tolerance))
    {
        // passed
        printf("v3_subtract test 2 passed\n\n");
    }
    else
    {
        printf("v3_subtract test 2 failed\n");
        printf("Correct Answer: %f %f %f\n", answer[0], answer[1], answer[2]);
        printf("Actual Result: %f %f %f\n\n", dest[0], dest[1], dest[2]);
        errors++;
    }

    // reset 
    vectorA[0] = 1000;  vectorA[1] = -100;  vectorA[2] = -.6554;
    vectorB[0] = 1000;  vectorB[1] = -100;  vectorB[2] = 1.334;
    dest[0] = 0;  dest[1] = 0;  dest[2] = 0;
    answer[0] = 0;  answer[1] = 0;  answer[2] = -1.9894;
    v3_subtract(dest, vectorA, vectorB);

    // THIRD TEST OF SUB
    if(v3_equals(answer, dest, tolerance))
    {
        // passed
        printf("v3_subtract test 3 passed\n\n");
    }
    else
    {
        printf("v3_subtract test 3 failed\n");
        printf("Correct Answer: %f %f %f\n", answer[0], answer[1], answer[2]);
        printf("Actual Result: %f %f %f\n\n", dest[0], dest[1], dest[2]);
        errors++;
    }


    // DOT PRODUCT
    tolerance = 1e-3;

    // reset 
    vectorA[0] = 1;  vectorA[1] = 2;  vectorA[2] = 3;
    vectorB[0] = 1;  vectorB[1] = 5;  vectorB[2] = 7;
    dest[0] = 0;  dest[1] = 0;  dest[2] = 0;
    answer[0] = 32;  answer[1] = 0;  answer[2] = 0;
    dest[0] = v3_dot_product(vectorA, vectorB);

    // FIRST TEST OF DOT PRODUCT
    if(v3_equals(answer, dest, tolerance))
    {
        // passed
        printf("v3_dot_product test 1 passed\n\n");
    }
    else
    {
        printf("v3_dot_product test 1 failed\n");
        printf("Correct Answer: %f %f %f\n", answer[0], answer[1], answer[2]);
        printf("Actual Result: %f %f %f\n\n", dest[0], dest[1], dest[2]);
        errors++;
    }

    // reset 
    vectorA[0] = 1.4;  vectorA[1] = 2.5;  vectorA[2] = 3.8;
    vectorB[0] = 1;  vectorB[1] = 5;  vectorB[2] = 7;
    dest[0] = 0;  dest[1] = 0;  dest[2] = 0;
    answer[0] = 40.5;  answer[1] = 0;  answer[2] = 0;
    dest[0] = v3_dot_product(vectorA, vectorB);

    // SECOND TEST OF DOT PRODUCT
    if(v3_equals(answer, dest, tolerance))
    {
        // passed
        printf("v3_dot_product test 2 passed\n\n");
    }
    else
    {
        printf("v3_dot_product test 2 failed\n");
        printf("Correct Answer: %f %f %f\n", answer[0], answer[1], answer[2]);
        printf("Actual Result: %f %f %f\n\n", dest[0], dest[1], dest[2]);
        errors++;
    }

    // reset 
    vectorA[0] = 100.4;  vectorA[1] = 200.5;  vectorA[2] = 300.8;
    vectorB[0] = 1;  vectorB[1] = -5;  vectorB[2] = 7;
    dest[0] = 0;  dest[1] = 0;  dest[2] = 0;
    answer[0] = 1203.5;  answer[1] = 0;  answer[2] = 0;
    dest[0] = v3_dot_product(vectorA, vectorB);

    // THIRD TEST OF DOT PRODUCT
    if(v3_equals(answer, dest, tolerance))
    {
        // passed
        printf("v3_dot_product test 3 passed\n\n");
    }
    else
    {
        printf("v3_dot_product test 3 failed\n");
        printf("Correct Answer: %f %f %f\n", answer[0], answer[1], answer[2]);
        printf("Actual Result: %f %f %f\n\n", dest[0], dest[1], dest[2]);
        errors++;
    }


    // CROSS PRODUCT
    tolerance = 1e-3;

    // reset 
    vectorA[0] = 1;  vectorA[1] = 2;  vectorA[2] = 3;
    vectorB[0] = 1;  vectorB[1] = 5;  vectorB[2] = 7;
    dest[0] = 0;  dest[1] = 0;  dest[2] = 0;
    answer[0] = -1;  answer[1] = -4;  answer[2] = 3;
    v3_cross_product(dest, vectorA, vectorB);

    // FIRST TEST OF CROSS PRODUCT
    if(v3_equals(answer, dest, tolerance))
    {
        // passed
        printf("v3_cross_product test 1 passed\n\n");
    }
    else
    {
        printf("v3_cross_product test 1 failed\n");
        printf("Correct Answer: %f %f %f\n", answer[0], answer[1], answer[2]);
        printf("Actual Result: %f %f %f\n\n", dest[0], dest[1], dest[2]);
        errors++;
    }

    // reset 
    vectorA[0] = -50;  vectorA[1] = 100;  vectorA[2] = -2;
    vectorB[0] = -124.2;  vectorB[1] = 5.7;  vectorB[2] = -.5;
    dest[0] = 0;  dest[1] = 0;  dest[2] = 0;
    answer[0] = -38.6;  answer[1] = 223.4;  answer[2] = 12135;
    v3_cross_product(dest, vectorA, vectorB);

    // SECOND TEST OF CROSS PRODUCT
    if(v3_equals(answer, dest, tolerance))
    {
        // passed
        printf("v3_cross_product test 2 passed\n\n");
    }
    else
    {
        printf("v3_cross_product test 2 failed\n");
        printf("Correct Answer: %f %f %f\n", answer[0], answer[1], answer[2]);
        printf("Actual Result: %f %f %f\n\n", dest[0], dest[1], dest[2]);
        errors++;
    }

    // reset 
    vectorA[0] = 0;  vectorA[1] = 0;  vectorA[2] = -2.42124;
    vectorB[0] = 0;  vectorB[1] = -2.34;  vectorB[2] = 0;
    dest[0] = 0;  dest[1] = 0;  dest[2] = 0;
    answer[0] = -5.6657016;  answer[1] = 0;  answer[2] = 0;
    v3_cross_product(dest, vectorA, vectorB);

    // THIRD TEST OF CROSS PRODUCT
    if(v3_equals(answer, dest, tolerance))
    {
        // passed
        printf("v3_cross_product test 3 passed\n\n");
    }
    else
    {
        printf("v3_cross_product test 3 failed\n");
        printf("Correct Answer: %f %f %f\n", answer[0], answer[1], answer[2]);
        printf("Actual Result: %f %f %f\n\n", dest[0], dest[1], dest[2]);
        errors++;
    }

    // SCALE

    // reset 
    float scale = 5;
    vectorA[0] = 5;  vectorA[1] = 10;  vectorA[2] = 25;
    answer[0] = 25;  answer[1] = 50;  answer[2] = 125;
    v3_scale(vectorA, scale);

    // FIRST TEST OF SCALE
    if(v3_equals(answer, vectorA, tolerance))
    {
        // passed
        printf("v3_scale test 1 passed\n\n");
    }
    else
    {
        printf("v3_scale test 1 failed\n");
        printf("Correct Answer: %f %f %f\n", answer[0], answer[1], answer[2]);
        printf("Actual Result: %f %f %f\n\n", dest[0], dest[1], dest[2]);
        errors++;
    }

    // reset 
    scale = 0;
    vectorA[0] = 19;  vectorA[1] = 10;  vectorA[2] = 25;
    answer[0] = 0;  answer[1] = 0;  answer[2] = 0;
    v3_scale(vectorA, scale);

    // SECOND TEST OF SCALE
    if(v3_equals(answer, vectorA, tolerance))
    {
        // passed
        printf("v3_scale test 2 passed\n\n");
    }
    else
    {
        printf("v3_scale test 2 failed\n");
        printf("Correct Answer: %f %f %f\n", answer[0], answer[1], answer[2]);
        printf("Actual Result: %f %f %f\n\n", dest[0], dest[1], dest[2]);
        errors++;
    }

    // reset 
    scale = -5.4;
    vectorA[0] = 5;  vectorA[1] = 10;  vectorA[2] = -25;
    answer[0] = -27;  answer[1] = -54;  answer[2] =  135;
    v3_scale(vectorA, scale);

    // THIRD TEST OF SCALE
    if(v3_equals(answer, vectorA, tolerance))
    {
        // passed
        printf("v3_scale test 3 passed\n\n");
    }
    else
    {
        printf("v3_scale test 3 failed\n");
        printf("Correct Answer: %f %f %f\n", answer[0], answer[1], answer[2]);
        printf("Actual Result: %f %f %f\n\n", dest[0], dest[1], dest[2]);
        errors++;
    }


    // ANGLE
    tolerance = 1e-3;

    // reset 
    vectorA[0] = 2;  vectorA[1] = -4;  vectorA[2] = -1;
    vectorB[0] = 0;  vectorB[1] = 5;  vectorB[2] = 2;
    dest[0] = 0;  dest[1] = 0;  dest[2] = 0;
    answer[0] = 2.6714;  answer[1] = 0;  answer[2] = 0;
    dest[0] = v3_angle(vectorA, vectorB);

    // FIRST TEST OF ANGLE
    if(v3_equals(answer, dest, tolerance))
    {
        // passed
        printf("v3_angle test 1 passed\n\n");
    }
    else
    {
        printf("v3_angle test 1 failed\n");
        printf("Correct Answer: %f %f %f\n", answer[0], answer[1], answer[2]);
        printf("Actual Result: %f %f %f\n\n", dest[0], dest[1], dest[2]);
        errors++;
    }

    // reset 
    vectorA[0] = 2;  vectorA[1] = -4.3;  vectorA[2] = -100;
    vectorB[0] = 0;  vectorB[1] = 5;  vectorB[2] = 0;
    dest[0] = 0;  dest[1] = 0;  dest[2] = 0;
    answer[0] = 1.6137;  answer[1] = 0;  answer[2] = 0;
    dest[0] = v3_angle(vectorA, vectorB);

    // SECOND TEST OF ANGLE
    if(v3_equals(answer, dest, tolerance))
    {
        // passed
        printf("v3_angle test 2 passed\n\n");
    }
    else
    {
        printf("v3_angle test 2 failed\n");
        printf("Correct Answer: %f %f %f\n", answer[0], answer[1], answer[2]);
        printf("Actual Result: %f %f %f\n\n", dest[0], dest[1], dest[2]);
        errors++;
    }

    // reset 
    vectorA[0] = 0;  vectorA[1] = 5;  vectorA[2] = 0;
    vectorB[0] = 0;  vectorB[1] = 5;  vectorB[2] = 0;
    dest[0] = 0;  dest[1] = 0;  dest[2] = 0;
    answer[0] = 0;  answer[1] = 0;  answer[2] = 0;
    dest[0] = v3_angle(vectorA, vectorB);

    // THIRD TEST OF ANGLE
    if(v3_equals(answer, dest, tolerance))
    {
        // passed
        printf("v3_angle test 3 passed\n\n");
    }
    else
    {
        printf("v3_angle test 3 failed\n");
        printf("Correct Answer: %f %f %f\n", answer[0], answer[1], answer[2]);
        printf("Actual Result: %f %f %f\n\n", dest[0], dest[1], dest[2]);
        errors++;
    }

    // QUICK ANGLE

    // reset 
    vectorA[0] = -2;  vectorA[1] = -4.3;  vectorA[2] = -1;
    vectorB[0] = 0;  vectorB[1] = 5;  vectorB[2] = 0;
    dest[0] = 0;  dest[1] = 0;  dest[2] = 0;
    answer[0] = -.88721;  answer[1] = 0;  answer[2] = 0;
    dest[0] = v3_angle_quick(vectorA, vectorB);

    // FIRST TEST OF ANGLEQUICK
    if(v3_equals(answer, dest, tolerance))
    {
        // passed
        printf("v3_angle_quick test 1 passed\n\n");
    }
    else
    {
        printf("v3_angle_quick test 1 failed\n");
        printf("Correct Answer: %f %f %f\n", answer[0], answer[1], answer[2]);
        printf("Actual Result: %f %f %f\n\n", dest[0], dest[1], dest[2]);
        errors++;
    }

    // reset 
    vectorA[0] = 0;  vectorA[1] = 5;  vectorA[2] = 0;
    vectorB[0] = 0;  vectorB[1] = 5;  vectorB[2] = 0;
    dest[0] = 0;  dest[1] = 0;  dest[2] = 0;
    answer[0] = 1;  answer[1] = 0;  answer[2] = 0;
    dest[0] = v3_angle_quick(vectorA, vectorB);

    // SECOND TEST OF ANGLEQUICK
    if(v3_equals(answer, dest, tolerance))
    {
        // passed
        printf("v3_angle_quick test 2 passed\n\n");
    }
    else
    {
        printf("v3_angle_quick test 2 failed\n");
        printf("Correct Answer: %f %f %f\n", answer[0], answer[1], answer[2]);
        printf("Actual Result: %f %f %f\n\n", dest[0], dest[1], dest[2]);
        errors++;
    }

    // reset 
    vectorA[0] = 2;  vectorA[1] = -4;  vectorA[2] = -1;
    vectorB[0] = 0;  vectorB[1] = 5;  vectorB[2] = 2;
    dest[0] = 0;  dest[1] = 0;  dest[2] = 0;
    answer[0] = -.8914;  answer[1] = 0;  answer[2] = 0;
    dest[0] = v3_angle_quick(vectorA, vectorB);

    // THIRD TEST OF ANGLEQUICK
    if(v3_equals(answer, dest, tolerance))
    {
        // passed
        printf("v3_angle_quick test 3 passed\n\n");
    }
    else
    {
        printf("v3_angle_quick test 3 failed\n");
        printf("Correct Answer: %f %f %f\n", answer[0], answer[1], answer[2]);
        printf("Actual Result: %f %f %f\n\n", dest[0], dest[1], dest[2]);
        errors++;
    }


    // REFLECT

    //reset

    // v
    vectorA[0] = 0;  vectorA[1] = 0;  vectorA[2] = 1;
    // n 
    vectorB[0] = 0;  vectorB[1] = 1;  vectorB[2] = 1;
    dest[0] = 0;  dest[1] = 0;  dest[2] = 0;
    answer[0] = 0;  answer[1] = -2;  answer[2] = -1;
    v3_reflect(dest, vectorA, vectorB);

    // First test of reflect
    if(v3_equals(answer, dest, tolerance))
    {
        // passed
        printf("v3_reflect test 1 passed\n\n");
    }
    else
    {
        printf("v3_reflect test 1 failed\n");
        printf("Correct Answer: %f %f %f\n", answer[0], answer[1], answer[2]);
        printf("Actual Result: %f %f %f\n\n", dest[0], dest[1], dest[2]);
        errors++;
    }

    // v
    vectorA[0] = -1.4;  vectorA[1] = 6;  vectorA[2] = 15;
    // n 
    vectorB[0] = 1;  vectorB[1] = 2;  vectorB[2] = 4;
    dest[0] = 0;  dest[1] = 0;  dest[2] = 0;
    answer[0] = -142.6;  answer[1] = -276.4;  answer[2] = -549.8;
    v3_reflect(dest, vectorA, vectorB);

    // second test of reflect
    if(v3_equals(answer, dest, tolerance))
    {
        // passed
        printf("v3_reflect test 2 passed\n\n");
    }
    else
    {
        printf("v3_reflect test 2 failed\n");
        printf("Correct Answer: %f %f %f\n", answer[0], answer[1], answer[2]);
        printf("Actual Result: %f %f %f\n\n", dest[0], dest[1], dest[2]);
        errors++;
    }


    // v
    vectorA[0] = 0;  vectorA[1] = 0;  vectorA[2] = 4;
    // n 
    vectorB[0] = 0;  vectorB[1] = 0;  vectorB[2] = 0;
    dest[0] = 0;  dest[1] = 0;  dest[2] = 0;
    answer[0] = 0;  answer[1] = 0;  answer[2] = 4;
    v3_reflect(dest, vectorA, vectorB);

    // third test of reflect
    if(v3_equals(answer, dest, tolerance))
    {
        // passed
        printf("v3_reflect test 3 passed\n\n");
    }
    else
    {
        printf("v3_reflect test 3 failed\n");
        printf("Correct Answer: %f %f %f\n", answer[0], answer[1], answer[2]);
        printf("Actual Result: %f %f %f\n\n", dest[0], dest[1], dest[2]);
        errors++;
    }


    // LENGTH

    //reset 
    vectorA[0] = 2;  vectorA[1] = -4;  vectorA[2] = -1;
    dest[0] = 0;  dest[1] = 0;  dest[2] = 0;
    answer[0] = 4.58257;  answer[1] = 0;  answer[2] = 0;
    dest[0] = v3_length(vectorA);

    // First test of length
    if(v3_equals(answer, dest, tolerance))
    {
        // passed
        printf("v3_length test 1 passed\n\n");
    }
    else
    {
        printf("v3_length test 1 failed\n");
        printf("Correct Answer: %f %f %f\n", answer[0], answer[1], answer[2]);
        printf("Actual Result: %f %f %f\n\n", dest[0], dest[1], dest[2]);
        errors++;
    }


    //reset 
    vectorA[0] = 2.6;  vectorA[1] = -4000;  vectorA[2] = -12;
    dest[0] = 0;  dest[1] = 0;  dest[2] = 0;
    answer[0] = 4000.01884;  answer[1] = 0;  answer[2] = 0;
    dest[0] = v3_length(vectorA);

    // second test of length
    if(v3_equals(answer, dest, tolerance))
    {
        // passed
        printf("v3_length test 2 passed\n\n");
    }
    else
    {
        printf("v3_length test 2 failed\n");
        printf("Correct Answer: %f %f %f\n", answer[0], answer[1], answer[2]);
        printf("Actual Result: %f %f %f\n\n", dest[0], dest[1], dest[2]);
        errors++;
    }


    //reset 
    vectorA[0] = 0;  vectorA[1] = 0;  vectorA[2] = -1;
    dest[0] = 0;  dest[1] = 0;  dest[2] = 0;
    answer[0] = 1;  answer[1] = 0;  answer[2] = 0;
    dest[0] = v3_length(vectorA);

    // third test of length
    if(v3_equals(answer, dest, tolerance))
    {
        // passed
        printf("v3_length test 3 passed\n\n");
    }
    else
    {
        printf("v3_length test 3 failed\n");
        printf("Correct Answer: %f %f %f\n", answer[0], answer[1], answer[2]);
        printf("Actual Result: %f %f %f\n\n", dest[0], dest[1], dest[2]);
        errors++;
    }

    // NORMALIZE
    vectorA[0] = 2;  vectorA[1] = -4;  vectorA[2] = -1;
    dest[0] = 0;  dest[1] = 0;  dest[2] = 0;
    answer[0] = .436435;  answer[1] = -.872871;  answer[2] = -.218217;
    v3_normalize(dest, vectorA);

    // First test of normalize
    if(v3_equals(answer, dest, tolerance))
    {
        // passed
        printf("v3_normalize test 1 passed\n\n");
    }
    else
    {
        printf("v3_normalize test 1 failed\n");
        printf("Correct Answer: %f %f %f\n", answer[0], answer[1], answer[2]);
        printf("Actual Result: %f %f %f\n\n", dest[0], dest[1], dest[2]);
        errors++;
    }

    // reset
    vectorA[0] = 2;  vectorA[1] = 0;  vectorA[2] = 0;
    dest[0] = 0;  dest[1] = 0;  dest[2] = 0;
    answer[0] = 1;  answer[1] = 0;  answer[2] = 0;
    v3_normalize(dest, vectorA);

    // second test of normalize
    if(v3_equals(answer, dest, tolerance))
    {
        // passed
        printf("v3_normalize test 2 passed\n\n");
    }
    else
    {
        printf("v3_normalize test 2 failed\n");
        printf("Correct Answer: %f %f %f\n", answer[0], answer[1], answer[2]);
        printf("Actual Result: %f %f %f\n\n", dest[0], dest[1], dest[2]);
        errors++;
    }

    //reset
    vectorA[0] = 200;  vectorA[1] = 10000;  vectorA[2] = 20;
    dest[0] = 0;  dest[1] = 0;  dest[2] = 0;
    answer[0] = 0.01999;  answer[1] = 0.99979;  answer[2] = 0.00199;
    v3_normalize(dest, vectorA);

    // third test of normalize
    if(v3_equals(answer, dest, tolerance))
    {
        // passed
        printf("v3_normalize test 3 passed\n\n");
    }
    else
    {
        printf("v3_normalize test 3 failed\n");
        printf("Correct Answer: %f %f %f\n", answer[0], answer[1], answer[2]);
        printf("Actual Result: %f %f %f\n\n", dest[0], dest[1], dest[2]);
        errors++;
    }

    printf("Tests complete\nError Count: %d\n", errors);

    return 0;
}
