#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include "graphics_headers.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/color4.h>
#include <Magick++.h>
#include <btBulletDynamicsCommon.h>

class Object 
{
  public: 
    Object(std::string fileInput, btTriangleMesh *objMesh);
    ~Object();
    void Render();

		glm::mat4 model;
    glm::mat4 GetModel();
    
    Magick::Image* m_pImage;
  	Magick::Blob m_blob;
  	
  	const float upperBound = 7;
  	const float lowerBound = -7;
  	const float leftBound = 11;
  	const float rightBound = -11;

  private:
    
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    GLuint VB;
    GLuint IB;
    GLuint normal;
    
    // texture variables
  	GLuint m_textureObj = 0;

    float angle;
};

#endif /* OBJECT_H */
