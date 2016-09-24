# PA3: Moons

## General Notes
PA3 builds upon PA2. In this project, a moon was added to orbit the planet while also rotating. Certain keyboard inputs can also alter the moon's orbit and rotation. Extra credit was attempted but not completed. Thus, that part of the code is commented out.

## Building and Running
This project was built and primarily tested on OSX 10.10.5. To run, go into the PA3 directory, and enter the following commands.


```bash
mkdir build
cd build
cmake ..
make
./Tutorial
```

## Input Instructions
The following inputs will effect the planet and/or moon:  
  a - starts/stops the planets's orbit.  
  s - reverses the planets's orbit.  
  k - starts/stops the the planet's rotation.  
  l - reverses the planet's rotation.  
  up arrow - starts/stops the moon's orbit.   
  down arrown - reverses the moon's orbit.   
  left arrow - starts/stops the moon's rotation.   
  right arrow - reverses the moon's rotation.   
  Left Mouse Button - stops the cube's orbit and rotation, and resets the cube back to orbiting and rotating forward.  
