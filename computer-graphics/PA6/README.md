#PA6: Assimp Texture Loading

Robert Trimble
Andrew Munoz
Zach Cooper

The following project builds off of code from PA5. We used the ImageMagick (Magick++.h) for this projects texture loading. By using assimp scene to extract the filename from the mtl file in the obj file to be used as the texture, we can pass this file name to the Image constructor in the Magick++ library and it will load this image in a way that can be interpreted by openGL when binding the textures. Along with reading in the vertices and faces using assimp importer, we are reading in the texture (uv) coordinates. Much like the vertices we read the texture coordinates into an aiVector but 2D because their are only two coordinates on a scale of 0 to 1. Instead of passing the Vertices vector (of type Vertex) a color, we replaced color with texture coordinates. Because we do this, our shaders had to be updated to use a vec2 for texture coordinates. We then bind the texture to be used by the fragment shader. In the render function we pass glVertexAttribPointer TexCoords instead of colors to be used in the vertex shader layout 1 (our texture vec2 coordinates) to be passed to the fragment shader.

##Building and Running

The following project was tested on both Mac and NoMachine in the ECC lab. To build this project, simply go into the computer-graphics/PA5 directory, and enter the following command lines.

mkdir build
cd build
cp ../makefile .
make
./Assignment6 <filepath>

##Notes:

Our file name that is used by the image constructor (Magick++ library) is altered in the obj's .mtl files to be "../models/" instead of just . To load the textures successfully, our .mtl files must be used.
