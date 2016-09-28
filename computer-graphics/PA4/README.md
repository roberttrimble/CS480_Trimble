# PA4: Model Loader

The current program is designed to take in an obj file and then output it to the screen. Previous code as taken from PA1. While it can take in my blender obj that I made, and a stanford dragon that I found online, it CAN NOT take in all obj files. ONLY those that are in the format #//# #//# #//#. It will NOT accept any faces in any other format.



## Building and Running
To build this project, simply go into the computer-graphics/PA4 directory, and enter the following command lines.

```bash
mkdir build
cd build
cmake ..
make
./Assignment4 <filelocation>
```
In my PA4 directory is "PA4ColorBox.obj". So I would run "./Assignment4 ../PA4Colorbox.obj" or "./Assignment4 ../dragon_smooth.obj" (I did not include that file due to its size).  
Again, I can only accept files in the #//# type format.
