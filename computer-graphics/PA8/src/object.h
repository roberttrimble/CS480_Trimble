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
    void Update(unsigned int dt, int modelNum);
    void Render();

		glm::mat4 model;
    glm::mat4 GetModel();
    
    Magick::Image* m_pImage;
  	Magick::Blob m_blob;

  private:
    
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    GLuint VB;
    GLuint IB;
    
    // texture variables
  	GLuint m_textureObj = 0;

    float angle;
};

#endif /* OBJECT_H */
