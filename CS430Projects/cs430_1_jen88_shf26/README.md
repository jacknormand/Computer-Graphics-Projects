# Authors
Jack Normand 
jen88@nau.edu

Henry Fye
shf26@nau.edu
# Usage
Program is used to convert P3 or P6 input .ppm files to P3 or P6 output .ppm files

To convert TO P3 from P3 or P6
ppmrw 3 input.ppm output.ppm

To convert TO P6 from P3 or P6
ppmrw 6 input.ppm output.ppm

# Known Issues
WIP: When reading a P3 file, if the inputted file has a comment more than 1 whitespace away from RGB values, the data might be read incorrectly
otherwise, no other known issues
