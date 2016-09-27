#include "object.h"
#include <stdio.h>

Object::Object(std::string fileInput)
{  
  const char* fileName;
  fileName = fileInput.c_str();
  FILE * file = fopen(fileName, "r");
  while(1)
  {
    char lineHeader[128];
    
    int res = fscanf(file, "%s", lineHeader);
    if(res == EOF)
      break;
    
    if(strcmp(lineHeader, "v") == 0)
    {
      glm::vec3 position;
      glm::vec3 color;
      
      fscanf(file, "%f %f %f\n", &position.x, &position.y, &position.z);
      
      if (Vertices.size()%2 == 0)
      {
        color.x = 1.0f;
        color.y = 0.0f;
        color.z = 0.0f;
      }
      else if (Vertices.size()%2 == 1)
      {
        color.x = 1.0f;
        color.y = 1.0f;
        color.z = 1.0f;
      }
      
      
      Vertex *tempVertex = new Vertex(position, color);
      
      Vertices.push_back(*tempVertex);
    }
    else if (strcmp(lineHeader, "f") == 0)
    {
      string format;
      unsigned int face[3];
      unsigned int junk[6];
      fscanf(file, "%s", &format);
      face[0] = (int)format[0];
      if (format[2] == '/' && format.size() = 3)
      {
        fscanf(file, "%i//%i %i//%i\n", &face[1], &junk[1], &face[2], &junk[2]);
        Indices.push_back(face[0]);
        Indices.push_back(face[1]);
        Indices.push_back(face[2]);
      }
      
      /*
      unsigned int face[3];
      unsigned int junk[3];
      fscanf(file, "%i//%i %i//%i %i//%i\n", &face[0], &junk[0], &face[1], &junk[1], &face[2], &junk[2]);
      Indices.push_back(face[0]);
      Indices.push_back(face[1]);
      Indices.push_back(face[2]);
      
      
      
      unsigned int face[9];
      unsigned int junk[3];
      int matches = fscanf(file, "%*[^0123456789]%i%*[^0123456789]%i%*[^0123456789]%i%*[^0123456789]%i%*[^0123456789]%i%*[^0123456789]%i%*[^0123456789]%i%*[^0123456789]%i%*[^0123456789]%i\n", &face[0], &face[1], &face[2], &face[3], &face[4], &face[5], &face[6], &face[7], &face[8]);
      if (matches == 6)
      {
      Indices.push_back(face[0]);
      Indices.push_back(face[2]);
      Indices.push_back(face[4]);
      }*/
    }
  }

  // The index works at a 0th index
  for(unsigned int i = 0; i < Indices.size(); i++)
  {
    Indices[i] = Indices[i] - 1;
  }

  angle = 0.0f;

  glGenBuffers(1, &VB);
  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);

  glGenBuffers(1, &IB);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * Indices.size(), &Indices[0], GL_STATIC_DRAW);
}

Object::~Object()
{
  Vertices.clear();
  Indices.clear();
}

void Object::Update(unsigned int dt)
{
  angle += dt * M_PI/1000;
 
  model = glm::rotate(glm::mat4(1.0f), (angle), glm::vec3(0.0, 12.0, 0.0));
  model = glm::scale(model, glm::vec3(2.0, 2.0, 2.0));
}

glm::mat4 Object::GetModel()
{
  return model;
}

void Object::Render()
{
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,color));

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);

  glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
}

