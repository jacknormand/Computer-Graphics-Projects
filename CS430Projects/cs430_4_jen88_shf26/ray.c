#include<stdio.h>
#include<string.h>
#include "v3math.h"

#define NULLOBJ 100
#define CAMERA 200
#define SPHERE 300
#define PLANE 400
#define LIGHT 500

// TODO: change attributes and add new ones
// add shadows


// this doesnt even need to be a struct cus were only using one ray over and over lol
typedef struct ray
{
    // ray origin (A) (vector) (0,0,0 for camera)
    float* origin;

    // ray direction (B) (vector) (along z axis for camera)
    float* direction;

}ray;

// the everything struct
typedef struct object
{
    // 100 = not object
    // 200 = camera
    // 300 = sphere
    // 400 = plane
    int kind;

    union properties
    {
        struct sphere
        {
            float position[3];
            float radius;
            float diffuse_color[3];
            float specular_color[3];
        }sphere;

        struct plane
        {
            float position[3];
            float normal[3];
            float diffuse_color[3];
            // add specular color?
        }plane;

        struct light
        {
            float color[3];
            float theta;
            float radiala0;
            float radiala1;
            float radiala2;
            float angulara0;
            float position[3];
            float direction[3];

        }light;
        
    }properties;

}object;


int main();
void getColor(float* dst, ray inputRay, object sceneObjects[]);
float intersectObj(object* objectShotAt, ray inputRay);
void getLitColor(float *dst, ray inputRay, object* currentObj, object* currentLight, float tVal, object sceneObjects[]);

float intersectObj(object* objectShotAt, ray inputRay)
{
    if (objectShotAt->kind == SPHERE)
    {
        // SPHERE: bt^2 * b + 2tb * (A-C) + (A-C) . (A-C) - r^2 = 0
        // solve for t^2 roots
        float originCenter[] = {0,0,0};

        // solves equation above
        v3_subtract(originCenter, inputRay.origin, objectShotAt->properties.sphere.position);

        // direction dot product with intputray direction
        float directionDot = v3_dot_product(inputRay.direction, inputRay.direction);

        // times 2 by origincenter and direction 
        float twoTimesDot = 2.0 * v3_dot_product(originCenter, inputRay.direction);

        // square radius 
        float radiusSq = objectShotAt->properties.sphere.radius * objectShotAt->properties.sphere.radius;

        // subtract r^2
        float dotOCMinusRSquared = v3_dot_product(originCenter, originCenter) - radiusSq;

        // set result 
        float result = (twoTimesDot * twoTimesDot) - (4 * directionDot * dotOCMinusRSquared);
        
        // if positive result, return 
        if (result >= 0)
        {
            // do some math and return
            float partOne = (-twoTimesDot - sqrt(result));

            return partOne / (2.0*directionDot);
        }
        else
        {
            // otherwise its negative, just return a negative value so we know
            return -1.0;
        }
        return result;
    }
    // gotta be a plane
    else if (objectShotAt->kind == PLANE)
    {
        //t = -(AX0 + BY0 + CZ0 + D) / (AXd + BYd + CZd)
        float distanceFromPlane[] = {0,0,0};

        //Pn times ray direction
        float Vd = v3_dot_product(objectShotAt->properties.plane.normal, inputRay.direction);
        
        // if 0 then paralell to ray, back out
        // NOTE: if one sided planes, stop if vd>0
        if(Vd == 0 )
        {
            // no intersect
            return -1.0;
        }
        // if >0, normal is pointing away. we assume one sided planes for now
        else if (Vd > 0)
        {
            return -1.0;
        }

        v3_subtract(distanceFromPlane, objectShotAt->properties.plane.position, inputRay.origin);

        float vZero = v3_dot_product(distanceFromPlane, objectShotAt->properties.plane.normal);

        float resultONE = vZero/Vd;

        // if less than one, its intersecting behind camera so back out
        if (resultONE < 0)
        {
            return -1.0;
        }

        // otherwise return ray intersection 
        return resultONE;
        
    }

    return 0;

}


void getLitColor(float *dst, ray inputRay, object* currentObj, object* currentLight, float tVal, object sceneObjects[])
{
    if (currentObj->kind == SPHERE)
    {
        // ambient
        float ambientCof = 0;
        float ambient[] = {currentObj->properties.sphere.diffuse_color[0],
                            currentObj->properties.sphere.diffuse_color[1],
                            currentObj->properties.sphere.diffuse_color[2]};
        v3_scale(ambient,ambientCof);

        // make all this stuff for diffuse
        float hitpoint[] = {0,0,0};
        float directionTimesLen[] = {inputRay.direction[0],inputRay.direction[1],inputRay.direction[2]};
        float normalOne[] = {0,0,0};
        float lightDir[] = {0,0,0};
        float viewDir[] = {0,0,0};
        float reflectDir[] = {0,0,0};
        float lightDirNormal[] = {0,0,0};

        // get diffuse color
        v3_scale(directionTimesLen, tVal);
        v3_add(hitpoint,inputRay.origin, directionTimesLen);
        v3_subtract(normalOne, hitpoint, currentObj->properties.sphere.position);
        v3_normalize(normalOne, normalOne);
        v3_subtract(lightDir, currentLight->properties.light.position, hitpoint);

        // USE LIGHT DIR FOR SHADOWS




        v3_normalize(lightDirNormal,lightDir);
        // get that diffuse coefficient
        float dotty = v3_dot_product(normalOne, lightDirNormal);


        // clamp value so its not negative
        if( dotty < 0.0)
        {
            dotty = 0;
        }
        else if (dotty > 1)
        {
            dotty = 1;
        }

        // diffuse = light color times dot product
        float diffuse[3] = {currentObj->properties.sphere.diffuse_color[0],currentObj->properties.sphere.diffuse_color[1],currentObj->properties.sphere.diffuse_color[2]};

        //scale by light color
        diffuse[0] *= currentLight->properties.light.color[0];
        diffuse[1] *= currentLight->properties.light.color[1];
        diffuse[2] *= currentLight->properties.light.color[2];

        // diffuse color
        v3_scale(diffuse,dotty);

        // make this stuff for specular
        float resultSpec;
        float specular[] = {0,0,0};
        float viewpos[] = {0,0,0};
        // math for specular
        v3_subtract(viewDir, viewpos, hitpoint);
        v3_normalize(viewDir,viewDir);
        float negLightdir[] = {lightDirNormal[0],lightDirNormal[1],lightDirNormal[2]};
        v3_scale(negLightdir, -1);
        v3_reflect(reflectDir, negLightdir, normalOne);

        //spec result coefficient
        resultSpec = v3_dot_product(viewDir,reflectDir);

        // get spec result from shininess
        if (resultSpec > 0)
        {
            resultSpec = pow(resultSpec, 20);
        }
        else 
        {
            resultSpec = 0;
        }

        specular[0] = currentObj->properties.sphere.specular_color[0];
        specular[1] = currentObj->properties.sphere.specular_color[1];
        specular[2] = currentObj->properties.sphere.specular_color[2];


        specular[0] *= currentLight->properties.light.color[0];
        specular[1] *= currentLight->properties.light.color[1];
        specular[2] *= currentLight->properties.light.color[2];

        v3_scale(specular, resultSpec);

        float specDiffuse[] = {0,0,0};

        // length of ray might be wrong ray lol
        float lengthofray = v3_length(lightDir);
        float attenuation = 1/(currentLight->properties.light.radiala0 + (currentLight->properties.light.radiala1 * lengthofray) + 
        (currentLight->properties.light.radiala2* (lengthofray*lengthofray)));

        // add diffuse and spec
        v3_add(specDiffuse, specular, diffuse);

        // calculate attenuation
        v3_scale(specDiffuse, attenuation);

        // add spec and diffuse to get final pixel color
        v3_add(ambient, ambient, specDiffuse);

        dst[0] = ambient[0];
        dst[1] = ambient[1];
        dst[2] = ambient[2];
    }
    else if(currentObj->kind == PLANE)
    {
        // ambient
        float ambientCof = 0;
        float ambient[] = {currentObj->properties.plane.diffuse_color[0],currentObj->properties.plane.diffuse_color[1],currentObj->properties.plane.diffuse_color[2]};
        v3_scale(ambient,ambientCof);

        // make all this stuff for diffuse
        float hitpoint[] = {0,0,0};
        float directionTimesLen[] = {inputRay.direction[0],inputRay.direction[1],inputRay.direction[2]};
        float normalOne[] = {0,0,0};
        float lightDir[] = {0,0,0};
        float lightDirNormal[] = {0,0,0};

        // get diffuse color ( doesnt really work on plane )
        v3_scale(directionTimesLen, tVal);
        v3_add(hitpoint,inputRay.origin, directionTimesLen);
        v3_subtract(normalOne, hitpoint, currentObj->properties.plane.position);
        v3_normalize(normalOne, normalOne);
        v3_subtract(lightDir, currentLight->properties.light.position, hitpoint);
        v3_normalize(lightDirNormal,lightDir);

        // shadow test initialize
        int objShadowInd;
        float result;

        // create new ray
        ray newRay;
        newRay.origin = hitpoint;
        newRay.direction = lightDir;
        
        // loop through objects, check if theres an intersection with a sphere for a shadow
        for (objShadowInd = 0; objShadowInd < 128; objShadowInd++)
        {
            result = intersectObj(&sceneObjects[objShadowInd], newRay);

            if (result >= 0 && sceneObjects[objShadowInd].kind == SPHERE)
            {
                // if in shadow, return black
                dst[0] = 0;
                dst[1] = 0;
                dst[2] = 0;
                return;
            }
        }


        // get that diffuse coefficient
        float dotty = v3_dot_product(normalOne, lightDirNormal);
        
        //clamp value so its not negative
        if( dotty < 0.0)
        {
            dotty = 0;
        }

        // diffuse = light color times dot product
        float diffuse[3] = {currentObj->properties.plane.diffuse_color[0],currentObj->properties.plane.diffuse_color[1],currentObj->properties.plane.diffuse_color[2]};
        
        // scale by light color
        diffuse[0] *= currentLight->properties.light.color[0];
        diffuse[1] *= currentLight->properties.light.color[1];
        diffuse[2] *= currentLight->properties.light.color[2];

        // diffuse color
        v3_scale(diffuse,dotty);

        // length of ray might be wrong ray lol
        float lengthofray = v3_length(lightDir);
        float attenuation = 1/(currentLight->properties.light.radiala0 + (currentLight->properties.light.radiala1 * lengthofray) + (currentLight->properties.light.radiala2* (lengthofray*lengthofray)));


        // GLITCH HERE. DIFFUSE LIGHTING NOT WORKING PROPERLY ON THE PLANE. 
        // EITHER BECAUSE PLANE INTERSECTION IS WRONG(UNLIKELY) OR DIFFUSE CALCULATION NEEDS TO BE ALTERD FOR THE PLANE
        // DIFFUSE DOT PRODUCT MESSES UP THE COLOR, SO IT MUST BE ADDED TO THE BASE COLOR INSTEAD OF THE AMBIENT

        // TLDR: ONLY THE ATTENUATION LIGHTING IS SHOWING UP ON THE PLANE. NOT DIFFUSE
        float stupidFix[] = {currentObj->properties.plane.diffuse_color[0],currentObj->properties.plane.diffuse_color[1],currentObj->properties.plane.diffuse_color[2]};
        // add diffuse
        v3_add(stupidFix, stupidFix, diffuse);
        v3_add(stupidFix, stupidFix, ambient);

        // calculate attenuation
        v3_scale(stupidFix, attenuation);
        
        dst[0] = stupidFix[0];
        dst[1] = stupidFix[1];
        dst[2] = stupidFix[2];

    }
    
}

void getColor(float* dst, ray inputRay, object sceneObjects[])
{
    // variable initialization

    // lets hope no t value is greater than this lol
    float nearestTVal = 1e+9;
    float newTVal = -1;
    float pixelColor[] = {0,0,0};
    float finalColor[] = {0,0,0};
    object* currentObj;
    int objectIndex;
    int lightIndex;
    bool oneLight;
    // loop through objects
    for ( objectIndex = 0; objectIndex < 128; objectIndex++)
    {
        // get object
        currentObj = &sceneObjects[objectIndex];

        if (currentObj->kind == SPHERE)
        {
            // get new tVal from current obj
            newTVal = intersectObj(currentObj, inputRay);

            // get nearest
            if (newTVal >= 0 && newTVal < nearestTVal)
            {
                nearestTVal = newTVal;

                for (lightIndex = 0; lightIndex < 128; lightIndex++)
                {

                    // get light
                    if (sceneObjects[lightIndex].kind == LIGHT)
                    {
                        // set oneLight to true
                        oneLight = true;

                        getLitColor(pixelColor,inputRay,currentObj, &sceneObjects[lightIndex], nearestTVal, sceneObjects);
                        // add to final color
                        v3_add(finalColor, finalColor, pixelColor);

                        if (finalColor[0] > 1)
                        {
                            finalColor[0] = 1;
                        }
                        if (finalColor[1] > 1)
                        {
                            finalColor[1] = 1;
                        }
                        if (finalColor[2] > 1)
                        {
                            finalColor[2] = 1;
                        }


                    }

                }

                if (!oneLight) 
                {
                    finalColor[0] = currentObj->properties.sphere.diffuse_color[0];
                    finalColor[1] = currentObj->properties.sphere.diffuse_color[1];
                    finalColor[2] = currentObj->properties.sphere.diffuse_color[2];
                }
            }
        }

        else if (currentObj->kind == PLANE)
        {
            newTVal = intersectObj(currentObj, inputRay);

            // intersects behind origin not of interest
            if (newTVal >= 0 && newTVal < nearestTVal)
            {
                nearestTVal = newTVal;

                for (lightIndex = 0; lightIndex < 128; lightIndex++)
                {

                    // get light
                    if (sceneObjects[lightIndex].kind == LIGHT)
                    {
                        // set oneLight to true
                        oneLight = true;

                        getLitColor(pixelColor,inputRay,currentObj, &sceneObjects[lightIndex], nearestTVal, sceneObjects );
                        // add to final color
                        v3_add(finalColor, finalColor, pixelColor);

                        if (finalColor[0] > 1)
                        {
                            finalColor[0] = 1;
                        }
                        if (finalColor[1] > 1)
                        {
                            finalColor[1] = 1;
                        }
                        if (finalColor[2] > 1)
                        {
                            finalColor[2] = 1;
                        }


                    }

                }
                
                if (!oneLight) 
                {
                    finalColor[0] = currentObj->properties.plane.diffuse_color[0];
                    finalColor[1] = currentObj->properties.plane.diffuse_color[1];
                    finalColor[2] = currentObj->properties.plane.diffuse_color[2];
                }
            }
        }
    // otherwise doesnt fit plane or sphere, skip
    }

    // set pixel
    dst[0] = finalColor[0];
    dst[1] = finalColor[1];
    dst[2] = finalColor[2];

}

int main(int argc, char *argv[])
{
    if (argc != 5)
    {
        //ERROR UNSUPPORTED FILE to stderr
        fprintf( stderr, "Error: Unsupported number of arguments\n");

        // input error
        return 1;
    }

    // parse in data
    FILE* filehandle = fopen(argv[3], "r");

    if (!filehandle)
    {
        // print
        fprintf(stderr, "Error: Wrong input file\n");

        // input error
        return 1;
    }

    // get first line
    char currentLine[2048];
    float recoveredNum = 0.0;
    int objIndex = 0;
    float cameraWidth = 0;
    float cameraHeight = 0;
    object sceneObjects[128];

    // loop through lines
    while(fgets(currentLine, 2048, filehandle) && objIndex < 128)
    {
        char* word = strtok(currentLine, ",");

        // if camera
        if (strcmp(word, "camera") == 0)
        {
            object newObj;
            newObj.kind = CAMERA;

            // loop wild word isnt null
            while(word)
            {
                // get next word
                word = strtok(NULL, ": ");

                // if word isnt null
                if(word)
                {
                    if (strcmp(word, "width") == 0)
                    {
                        // get width
                        recoveredNum = atof(strtok(NULL, ","));
                        cameraWidth = recoveredNum;

                    }
                    else if (strcmp(word, "height") == 0)
                    {
                        // get height
                        recoveredNum = atof(strtok(NULL, ","));
                        cameraHeight = recoveredNum;
                    }
                }

            }

            // set to new object
            sceneObjects[objIndex] = newObj;
            objIndex++;
        }

        else if (strcmp(word, "sphere") == 0)
        {
            object newObj;
            newObj.kind = SPHERE;

            // defaults
            newObj.properties.sphere.diffuse_color[0] = 0;
            newObj.properties.sphere.diffuse_color[1] = 0;
            newObj.properties.sphere.diffuse_color[2] = 0;

            newObj.properties.sphere.position[0] = 0;
            newObj.properties.sphere.position[1] = 0;
            newObj.properties.sphere.position[2] = 0;

            newObj.properties.sphere.specular_color[0] = 0;
            newObj.properties.sphere.specular_color[1] = 0;
            newObj.properties.sphere.specular_color[2] = 0;

            newObj.properties.sphere.radius = 0;


            while(word)
            {
                // get next word
                word = strtok(NULL, ": ");

                // if word isnt null
                if(word)
                {
                    if (strcmp(word, "diffuse_color") == 0)
                    {
                        // get left brace
                        word = strtok(NULL, "[");
                        // get Red
                        recoveredNum = atof(strtok(NULL, ","));
                        newObj.properties.sphere.diffuse_color[0] = recoveredNum;

                        // get Blue
                        recoveredNum = atof(strtok(NULL, ","));
                        newObj.properties.sphere.diffuse_color[1] = recoveredNum;

                        // get Green
                        recoveredNum = atof(strtok(NULL, "]"));
                        newObj.properties.sphere.diffuse_color[2] = recoveredNum;
                    }

                    // get specular color
                    else if (strcmp(word, "specular_color") == 0)
                    {
                        // get left brace
                        word = strtok(NULL, "[");
                        // get Red
                        recoveredNum = atof(strtok(NULL, ","));
                        newObj.properties.sphere.specular_color[0] = recoveredNum;

                        // get Blue
                        recoveredNum = atof(strtok(NULL, ","));
                        newObj.properties.sphere.specular_color[1] = recoveredNum;

                        // get Green
                        recoveredNum = atof(strtok(NULL, "]"));
                        newObj.properties.sphere.specular_color[2] = recoveredNum;
                    }

                    else if (strcmp(word, "position") == 0)
                    {
                        // get left brace
                        word = strtok(NULL, "[");

                        // get X
                        recoveredNum = atof(strtok(NULL, ","));
                        newObj.properties.sphere.position[0] = recoveredNum;

                        // get Y
                        recoveredNum = atof(strtok(NULL, ","));
                        newObj.properties.sphere.position[1] = recoveredNum;

                        // get Z
                        recoveredNum = atof(strtok(NULL, "]"));
                        if (recoveredNum > 0)
                        {
                            printf("Warning: A sphere z coordinate is positive. Changing to negative...\n");
                            recoveredNum *= -1;
                        }
                        newObj.properties.sphere.position[2] = recoveredNum;
                    }
                    else if (strcmp(word, "radius") == 0)
                    {
                        // get radius
                        recoveredNum = atof(strtok(NULL, ","));
                        newObj.properties.sphere.radius = recoveredNum;
                    }
                }

            }

            // set to new object
            sceneObjects[objIndex] = newObj;
            objIndex++;
        }

        else if (strcmp(word, "plane") == 0)
        {
            object newObj;
            newObj.kind = PLANE;

            newObj.properties.plane.diffuse_color[0] = 0;
            newObj.properties.plane.diffuse_color[1] = 0;
            newObj.properties.plane.diffuse_color[2] = 0;

            newObj.properties.plane.position[0] = 0;
            newObj.properties.plane.position[1] = 0;
            newObj.properties.plane.position[2] = 0;

            newObj.properties.plane.normal[0] = 0;
            newObj.properties.plane.normal[1] = 0;
            newObj.properties.plane.normal[2] = 0;

            while(word)
            {
                // get next word
                word = strtok(NULL, ": ");

                // if word isnt null
                if(word)
                {
                    if (strcmp(word, "diffuse_color") == 0)
                    {
                        // get left brace
                        word = strtok(NULL, "[");
                        // get Red
                        recoveredNum = atof(strtok(NULL, ","));
                        newObj.properties.plane.diffuse_color[0] = recoveredNum;

                        // get Blue
                        recoveredNum = atof(strtok(NULL, ","));
                        newObj.properties.plane.diffuse_color[1] = recoveredNum;

                        // get Green
                        recoveredNum = atof(strtok(NULL, "]"));
                        newObj.properties.plane.diffuse_color[2] = recoveredNum;
                    }
                    else if (strcmp(word, "position") == 0)
                    {
                        // get left brace
                        word = strtok(NULL, "[");

                        // get X
                        recoveredNum = atof(strtok(NULL, ","));
                        newObj.properties.plane.position[0] = recoveredNum;

                        // get Y
                        recoveredNum = atof(strtok(NULL, ","));
                        newObj.properties.plane.position[1] = recoveredNum;

                        // get Z
                        recoveredNum = atof(strtok(NULL, "]"));
                        newObj.properties.plane.position[2] = recoveredNum;
                    }
                    else if (strcmp(word, "normal") == 0)
                    {
                        // get left brace
                        word = strtok(NULL, "[");

                        // get X
                        recoveredNum = atof(strtok(NULL, ","));
                        newObj.properties.plane.normal[0] = recoveredNum;

                        // get Y
                        recoveredNum = atof(strtok(NULL, ","));
                        newObj.properties.plane.normal[1] = recoveredNum;

                        // get Z
                        recoveredNum = atof(strtok(NULL, "]"));
                        newObj.properties.plane.normal[2] = recoveredNum;
                    }
                }

            }

            // set to new object
            sceneObjects[objIndex] = newObj;
            objIndex++;
        }




        else if (strcmp(word, "light") == 0)
        {
            object newObj;
            newObj.kind = LIGHT;

            // defaults
            newObj.properties.light.color[0] = 0;
            newObj.properties.light.color[1] = 0;
            newObj.properties.light.color[2] = 0;

            newObj.properties.light.theta = 0;
            newObj.properties.light.radiala0 = 0;
            newObj.properties.light.radiala1 = 0;
            newObj.properties.light.radiala2 = 0;
            newObj.properties.light.angulara0 = 0;

            newObj.properties.light.position[0] = 0;
            newObj.properties.light.position[1] = 0;
            newObj.properties.light.position[2] = 0;

            newObj.properties.light.direction[0] = 0;
            newObj.properties.light.direction[1] = 0;
            newObj.properties.light.direction[2] = 0;


            while(word)
            {
                // get next word
                word = strtok(NULL, ": ");

                // if word isnt null
                if(word)
                {
                    // get light color
                    if (strcmp(word, "color") == 0)
                    {
                        // get left brace
                        word = strtok(NULL, "[");
                        // get Red
                        recoveredNum = atof(strtok(NULL, ","));
                        newObj.properties.light.color[0] = recoveredNum;

                        // get Blue
                        recoveredNum = atof(strtok(NULL, ","));
                        newObj.properties.light.color[1] = recoveredNum;

                        // get Green
                        recoveredNum = atof(strtok(NULL, "]"));
                        newObj.properties.light.color[2] = recoveredNum;
                    }

                    // get specular color
                    else if (strcmp(word, "position") == 0)
                    {
                        // get left brace
                        word = strtok(NULL, "[");
                        // get Red
                        recoveredNum = atof(strtok(NULL, ","));
                        newObj.properties.light.position[0] = recoveredNum;

                        // get Blue
                        recoveredNum = atof(strtok(NULL, ","));
                        newObj.properties.light.position[1] = recoveredNum;

                        // get Green
                        recoveredNum = atof(strtok(NULL, "]"));
                        newObj.properties.light.position[2] = recoveredNum;
                    }

                    else if (strcmp(word, "direction") == 0)
                    {
                        // get left brace
                        word = strtok(NULL, "[");

                        // get X
                        recoveredNum = atof(strtok(NULL, ","));
                        newObj.properties.light.direction[0] = recoveredNum;

                        // get Y
                        recoveredNum = atof(strtok(NULL, ","));
                        newObj.properties.light.direction[1] = recoveredNum;

                        // get Z
                        recoveredNum = atof(strtok(NULL, "]"));

                        newObj.properties.light.direction[2] = recoveredNum;
                    }
                    else if (strcmp(word, "theta") == 0)
                    {
                        // get theta
                        recoveredNum = atof(strtok(NULL, ","));
                        newObj.properties.light.theta = recoveredNum;
                    }
                    else if (strcmp(word, "radial-a0") == 0)
                    {
                        // get radiala0
                        recoveredNum = atof(strtok(NULL, ","));
                        newObj.properties.light.radiala0 = recoveredNum;
                    }
                    else if (strcmp(word, "radial-a1") == 0)
                    {
                        // get radiala1
                        recoveredNum = atof(strtok(NULL, ","));
                        newObj.properties.light.radiala1 = recoveredNum;
                    }
                    else if (strcmp(word, "radial-a2") == 0)
                    {
                        // get radiala2
                        recoveredNum = atof(strtok(NULL, ","));
                        newObj.properties.light.radiala2 = recoveredNum;
                    }
                    else if (strcmp(word, "angular-a0") == 0)
                    {
                        // get angulara0
                        recoveredNum = atof(strtok(NULL, ","));
                        newObj.properties.light.angulara0 = recoveredNum;
                    }

                }

            }

            // set to new object
            sceneObjects[objIndex] = newObj;
            objIndex++;
        }

        else
        {
            printf("Error: Invalid input object\n");
            return 20;
        }
    }

    fclose(filehandle);
    //done parsing

    // read in width height
    int sceneWidth = atoi(argv[1]);
    int sceneHeight = atoi(argv[2]);

    // if aspect ratio of scene and camera dont line up, give warning
    if (sceneWidth/sceneHeight != (int)(cameraWidth/cameraHeight))
    {
        printf("Warning: Aspect ratio of scene and camera do not match. Picture may look screwed up\n");
    }

    // focal length always 1, same with origin always 0,0,0
    float focalLength = 1;
    float origin[] = {0,0,0};
    // horizontal and vertical floats to traverse view
    float horizontal[] = {cameraWidth, 0, 0};
    float vertical[] = {0, cameraHeight, 0};

    //CALCULATIONS
    // origin- vector-horizontal/2 - vertical/2 - (0,0,focallength) = lowerleft corner
    float horizontalHalved[] = {horizontal[0], horizontal[1], horizontal[2]};
    float verticalHalved[] = {vertical[0], vertical[1], vertical[2]};
    float FocalLengthZ[] = {0,0,focalLength};
    float lowerLeft[] = {0,0,0};
    // half
    v3_scale(horizontalHalved, .5);
    v3_scale(verticalHalved, .5);
    // math subtract
    v3_subtract(lowerLeft, origin, horizontalHalved);
    v3_subtract(lowerLeft, lowerLeft, verticalHalved);
    v3_subtract(lowerLeft, lowerLeft, FocalLengthZ);

    char* outputFileName = argv[4];
    FILE* outputFile;

    // open up
    outputFile = fopen(outputFileName, "w");

    // ppm header
    fprintf(outputFile, "P3\n");
    fprintf(outputFile, "%d %d\n", sceneWidth, sceneHeight);
    fprintf(outputFile, "%d\n", 255);

    // index vars
    float widthIndex;
    float heightIndex;
    float xVal;
    float yVal;
    float directionVar[] = {lowerLeft[0],lowerLeft[1],lowerLeft[2]};
    float horizontalTimesX[] = {horizontal[0],horizontal[1],horizontal[2]};
    float verticalTimesY[] = {vertical[0],vertical[1],vertical[2]};
    // pixel that gets written out
    float pixelColor[] = {0,0,0};

    // ray
    ray currentRay;
    currentRay.origin = origin;

    // iterate over pixels in image, one a time,  shooting a ray 
    // through the center of the pixel out into the scene, 
    // looking for intersections between each ray and the scene geometry.
    // For loop vertical
    for ( heightIndex = sceneHeight-1; heightIndex >= 0; heightIndex--)
    {
        // For loop horizontal
        for (widthIndex = 0; widthIndex < sceneWidth; widthIndex++)
        {
            xVal = (widthIndex/(sceneWidth-1));
            yVal = (heightIndex/(sceneHeight-1));

            // do some quick maf
            v3_scale(horizontalTimesX, xVal);
            v3_scale(verticalTimesY, yVal);
            v3_add(directionVar, directionVar, horizontalTimesX);
            v3_add(directionVar, directionVar, verticalTimesY);
            v3_subtract(directionVar, directionVar, origin);

            // normalize direction 
            v3_normalize(directionVar, directionVar);

            // set ray direciton
            currentRay.direction = directionVar;

            // get ray color 
            getColor(pixelColor, currentRay, sceneObjects); 
            
            fprintf(outputFile, "%f %f %f ", pixelColor[0]*255.9, pixelColor[1]*255.9, pixelColor[2]*255.9);

            // reset (this is ugly ik)
            directionVar[0] = lowerLeft[0];
            directionVar[1] = lowerLeft[1];
            directionVar[2] = lowerLeft[2];
            horizontalTimesX[0] = horizontal[0];
            horizontalTimesX[1] = horizontal[1];
            horizontalTimesX[2] = horizontal[2];
            verticalTimesY[0] = vertical[0];
            verticalTimesY[1] = vertical[1];
            verticalTimesY[2] = vertical[2];
        }
        fprintf(outputFile, "\n");
    }

    fclose(outputFile);
    return 0;
}