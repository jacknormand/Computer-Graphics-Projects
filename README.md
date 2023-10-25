# Authors
Jack Normand 
jack.normand15@gmail.com

# Usage
Takes input file containing spot lights, point lights, planes, or spheres and outputs a .ppm file to be viewed. Casts rays and calculates phong lighting, supports recursive reflections. Paints one pixel at a time and resolution can be as big (or as small) as you like.<br>
run `make` in file first <br>
then run `./raycast width height demo.scene output.ppm` and replace width and height with numerical values, and input can be demo or other file in same format

ALSO: Bonus 3D glasses effect program is included within the named file. It works the same, but casts two images and seperates the red and blue values. Theoretically should appear 3D if you wear old school 3D glasses but I haven't tried it.

# Known Issues
None! Please not output is a PPM file, and you might need GIMP or another program to view it. (MacOS Preview works well for me)


# SAMPLE PHOTO GALLERY:

Most recent version with lighting and reflection<br>
![v3 w reflection](https://github.com/jacknormand/Computer-Graphics-Projects/assets/21299000/6fd75240-cfd5-4889-9473-539e2ab8a3d3)

![Screenshot 2023-10-25 at 1 26 21 PM](https://github.com/jacknormand/Computer-Graphics-Projects/assets/21299000/49656e8d-bc15-4dea-9d17-8552ea646848)

3D Glasses version<br>
<img width="501" alt="Screenshot 2023-10-25 at 3 53 38 PM" src="https://github.com/jacknormand/Computer-Graphics-Projects/assets/21299000/68486e83-41e5-43c1-aebb-843c1201bb04">

50x50 pixel resolution because I thought it looked funny<br>
<img width="517" alt="Screenshot 2023-10-25 at 3 50 00 PM" src="https://github.com/jacknormand/Computer-Graphics-Projects/assets/21299000/6b16302f-957a-4675-a6f2-bf589c0584cf">


Older version with no reflections<br>
![v2 sample2](https://github.com/jacknormand/Computer-Graphics-Projects/assets/21299000/5765030f-cda9-48e9-b377-22bb110d3f4f)


![v2 w lighting](https://github.com/jacknormand/Computer-Graphics-Projects/assets/21299000/465ba46a-972c-46a9-b64d-d279436b4da7)

And version 1 picture included here just so you can see the progress<br>
![v1](https://github.com/jacknormand/Computer-Graphics-Projects/assets/21299000/4df609d3-3f0e-4bff-8b83-47ee0cbac516)





