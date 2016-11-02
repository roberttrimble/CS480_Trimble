# PA8: Assimp Texture Loading

Robert Trimble  
Andrew Munoz  
Zach Cooper  

The following project builds off of code from PA6. For this project we created a pinball table, cube, ball and cylinder. 
The table and cylinder are static objects. The cube can be controlled using arrow keys to hit the ball. The mouse left click
currently causes the cube to be given an applied force, but clips other object at a high velocity. 

Not complete as of 11/2/2016. 

## Building and Running
The following project was Linux/ubuntu. To build this project, 
simply go into the computer-graphics/PA8 directory, and enter the following command lines.

```bash
mkdir build
cd build
cp ../makefile .
make
./Assignment8
```

##Controls:
Arrow keys move the cube in respective direction.
Mouse click moves the cube to the cursor lovation and collieds with ball - incomplete
