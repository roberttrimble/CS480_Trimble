#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include "graphics_headers.h"

class Object
{
  public:
    Object();
    ~Object();
    void Update(unsigned int dt, char keyboardInput, bool newInput);
    void UpdateMoon(unsigned int dt, glm::mat4 model, keyboardInput, newInput);
    void Render();

    glm::mat4 GetModel();
    
    //Pointer to Moons
    Object *moons;

  private:
    glm::mat4 model;
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    GLuint VB;
    GLuint IB;

    float orbitAngle;
    float rotAngle;
    
    //Bools added for PA2 for keyboard interactions
    bool planetOrbitMoving;
    bool planetOrbitForward;
    bool planetRotMoving;
    bool planetRotForward;
    
    
    
};

#endif /* OBJECT_H */
