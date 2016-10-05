# PA5: Assimp Model Loading

Robert Trimble  
Andrew Munoz  
Zach Cooper  
The following project builds off of code from PA1. This time though, the object is loaded using Assimp. By using the Assimp importer, a given object file is extracted, and the appropraite verticies and faces are pulled. We also continued to us the previous two vectors, Verticies and Indicies, so that our render function did not need to be changed.  


## Building and Running
The following project was tested on both Mac and NoMachine in the ECC lab. To build this project, simply go into the computer-graphics/PA5 directory, and enter the following command lines.

```bash
mkdir build
cd build
cmake ..
make
./Assignment5 <filepath>
```
  
We provided an object file in our repository. It is located in the models directory. To test that file, one needs to simply enter "./Assignment5 ../models/pinballtable.obj"
