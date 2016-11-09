# PA9: Lighting

Robert Trimble  
Andrew Munoz  
Zach Cooper  

The following project builds off of code from PA8. For this project we used our pinball table, cube, ball and cylinder models. 
The table and cylinder are static objects. The cube can be controlled using arrow keys to hit the ball. We added different forms of lighting
such as Diffuse, Ambient, and Specular to the table and the objects per vertex shading and per fragment shading (see controls below). There is also a spotlight that highlights the sphere as it moves around the table. 

## Building and Running
The following project was built on Linux/ubuntu. To build this project, 
simply go into the computer-graphics/PA9 directory, and enter the following command lines.

```bash
mkdir build
cd build
cp ../makefile .
make
./Assignment9
```

##Controls:
Arrow keys move the cube in respective direction.  
q - lowers ambient lighting on the table  
w - raises ambient lighting on the table  
a - lowers specular lighting on the cylinder  
s - raises specular lighting on the cylinder  
space bar - toggle per vertex and per fragment shading  

