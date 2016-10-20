#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include "graphics_headers.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/color4.h>
#include <Magick++.h>

class Object 
{
  public: 
		Object(std::string fileInput, std::string textureFile);
    ~Object();
    void Update(unsigned int dt, int planetNum);
		void UpdateMoon(glm::mat4 planetModel, unsigned int dt, int planetNum);
    void Render();

    glm::mat4 GetModel();
		
		// public texture variables
 		Magick::Image* m_pImage;
  	Magick::Blob m_blob;

		// moon point to another object
		Object *moon;

  private:
    glm::mat4 model;
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    GLuint VB;
    GLuint IB;

		// texture variables
  	GLuint m_textureObj = 0;

    float rotationAngle;
		float orbitAngle;
};

#endif /* OBJECT_H */
