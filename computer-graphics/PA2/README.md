# PA2: Keyboard/mouse inputs

## General Notes
PA2 builds upon PA1. In this project, specific keyboard and mouse inputs change the behavior of the "planet". This is done primarily through a switch statement to determine what button was pressed. Then if/else if statements to update the object accordingly.

## Building and Running
This project was built and primarily tested on OSX 10.10.5. To run, go into the PA2 directory, and enter the following commands.


```bash
mkdir build
cd build
cmake ..
make
./Tutorial
```

## Instructions
The following inputs will effect the cube: \n
  a - starts/stops the cube's orbit.
  s - reverses the cube's orbit.
  k - starts/stops the the cube's rotation.
  l - reverses the cube's rotation.
  Left Mouse Button - stops the cube's orbit and rotation, and resets the cube back to orbiting and rotating forward.
