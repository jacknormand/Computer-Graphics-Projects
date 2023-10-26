A raytracer created in C from scratch

# Authors
Jack Normand 
jack.normand15@gmail.com

# Usage
Takes input file containing spot lights, point lights, planes, or spheres and outputs a .ppm file to be viewed. Casts rays and calculates phong lighting, supports recursive reflections. Paints one pixel at a time and resolution can be as big (or as small) as you like.<br>
run `make` in file first <br>
then run `./raycast width height demo.scene output.ppm` and replace width and height with numerical values, and input can be demo or other file in same format

ALSO: Bonus 3D glasses effect program is included within the named file. It works the same, but casts two images and seperates the red and blue values. Theoretically should appear 3D if you wear old school 3D glasses but I haven't tried it.

# Known Issues
None! Please note output is a PPM file, and you might need GIMP or another program to view it. (MacOS Preview works well for me)


# SAMPLE PHOTO GALLERY:

Most recent version with lighting and reflection<br>
![v3 w reflection](https://github.com/jacknormand/Computer-Graphics-Projects/assets/21299000/cc45c4fb-487b-4764-8f0e-691788041d0b)

![highres](https://github.com/jacknormand/Computer-Graphics-Projects/assets/21299000/84ae4525-51cd-460c-9d1a-a1837ccc5a00)



3D Glasses version<br>
<img width="501" alt="3d" src="https://github.com/jacknormand/Computer-Graphics-Projects/assets/21299000/8e6d9124-5f92-4418-af2f-c408f559ef44">

50x50 pixel resolution because I thought it looked funny<br>
<img width="517" alt="lowres" src="https://github.com/jacknormand/Computer-Graphics-Projects/assets/21299000/4ccae5f6-a36f-4b20-9218-bbb40cf14381">


Older version with no reflections<br>
![v2 w lighting](https://github.com/jacknormand/Computer-Graphics-Projects/assets/21299000/d3f5d9cc-c29d-44ce-996c-90ba76a5eece)

![v2 sample2](https://github.com/jacknormand/Computer-Graphics-Projects/assets/21299000/552b893d-1b28-4da3-ac65-4d82d4f60570)


And version 1 picture included here just so you can see the progress<br>
![v1](https://github.com/jacknormand/Computer-Graphics-Projects/assets/21299000/e8a52163-35fe-4852-81be-74fb9611bf9d)




