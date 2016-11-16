# PA10: Lighting

Robert Trimble  
Andrew Munoz  
Zach Cooper  

The following project builds off of code from PA9. There are three cylinders instead of one. 
The table is now a triMesh, thus the dividing wall has collision detection. Can now launch the ball. 
And the cylinders "bumpers" apply force when colliding with the ball.

## Building and Running
The following project was built on Linux/ubuntu. To build this project, 
simply go into the computer-graphics/PA10 directory, and enter the following command lines.

```bash
mkdir build
cd build
cp ../makefile .
make
./Assignment10
```

##Controls:
Arrow keys move the cube in respective direction.
q - lowers ambient lighting on the table
w - raises ambient lighting on the table
a - lowers specular lighting on the cylinder
s - raises specular lighting on the cylinder
space bar - toggle per vertex and per fragment shading
left mouse click - launch the ball

