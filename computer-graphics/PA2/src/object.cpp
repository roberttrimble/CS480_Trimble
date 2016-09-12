#include "object.h"

Object::Object()
{  
  /*
    # Blender File for a Cube
    o Cube
    v 1.000000 -1.000000 -1.000000
    v 1.000000 -1.000000 1.000000
    v -1.000000 -1.000000 1.000000
    v -1.000000 -1.000000 -1.000000
    v 1.000000 1.000000 -0.999999
    v 0.999999 1.000000 1.000001
    v -1.000000 1.000000 1.000000
    v -1.000000 1.000000 -1.000000
    s off
    f 2 3 4
    f 8 7 6
    f 1 5 6
    f 2 6 7
    f 7 8 4
    f 1 4 8
    f 1 2 4
    f 5 8 6
    f 2 1 6
    f 3 2 7
    f 3 7 4
    f 5 1 8
  */

  Vertices = {
    {{1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 0.0f}},
    {{1.0f, -1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},
    {{-1.0f, -1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},
    {{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 1.0f}},
    {{1.0f, 1.0f, -1.0f}, {1.0f, 1.0f, 0.0f}},
    {{1.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 1.0f}},
    {{-1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 1.0f}},
    {{-1.0f, 1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}}
  };

  Indices = {
    2, 3, 4,
    8, 7, 6,
    1, 5, 6,
    2, 6, 7,
    7, 8, 4,
    1, 4, 8,
    1, 2, 4,
    5, 8, 6,
    2, 1, 6,
    3, 2, 7,
    3, 7, 4,
    5, 1, 8
  };

  // The index works at a 0th index
  for(unsigned int i = 0; i < Indices.size(); i++)
  {
    Indices[i] = Indices[i] - 1;
  }

  orbitAngle = 0.0f;
  rotAngle = 0.0f;
  
  //Set the orbit and rotation bools for the planet
  planetOrbitMoving = true;
  planetOrbitForward = true;
  planetRotMoving = true;
  planetRotForward = true;

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

void Object::Update(unsigned int dt, char keyboardInput, bool newInput)
{
  //////////////////////////
  //Check for a new keyboard input
  //////////////////////////
  if (newInput == true)
  {
    switch (keyboardInput)
    {
      //Start or Stop planet orbit
      /////////////////////////////
      case 'a':
        if (planetOrbitMoving == true)
          planetOrbitMoving = false;
        else if (planetOrbitMoving == false)
          planetOrbitMoving = true;
        break;
      
      //Reverse planet orbit
      ///////////////////////
      case 's':
        if (planetOrbitForward == true)
          planetOrbitForward = false;
        else if (planetOrbitForward == false)
          planetOrbitForward = true;
        break;
        
      //Start or stop planet rotation
      ///////////////////////
      case 'k':
        if (planetRotMoving == true)
          planetRotMoving = false;
        else if (planetRotMoving == false)
          planetRotMoving = true;
        break;
        
      //Reverse planet rotation
      ///////////////////////
      case 'l':
        if (planetRotForward == true)
          planetRotForward = false;
        else if (planetRotForward == false)
          planetRotForward = true;
        break;
       
      default:
        break;
    }
  }
  
  /////////////////////////////
  //Move the planet accordingly
  /////////////////////////////
  
  ////////////////////////////////////////
  //If the planet is orbiting and rotating
  ////////////////////////////////////////
  if (planetOrbitMoving == true && planetRotMoving == true)
  {
    //If orbit and rotation are normal
    if (planetOrbitForward == true && planetRotForward == true)
    {
      orbitAngle += dt * M_PI/1000;
      rotAngle += dt * M_PI/1000;
      model = (glm::rotate(glm::mat4(1.0f), (orbitAngle), glm::vec3(0.0, 12.0, 0.0)) * glm::translate(glm::mat4(1.0f), glm::vec3(4.0, 0.0, 0.0)))
              * glm::rotate(glm::mat4(1.0f), (rotAngle), glm::vec3(0.0, 12.0, 0.0));
    }
    //If orbit is reversed but rotation is normal
    else if (planetOrbitForward == false && planetRotForward == true)
    {
      orbitAngle -= dt * M_PI/1000;
      rotAngle += dt * M_PI/500; // *2 to offset speed
      model = (glm::rotate(glm::mat4(1.0f), (orbitAngle), glm::vec3(0.0, 12.0, 0.0)) * glm::translate(glm::mat4(1.0f), glm::vec3(4.0, 0.0, 0.0)))
              * glm::rotate(glm::mat4(1.0f), (rotAngle), glm::vec3(0.0, 12.0, 0.0));
    }
    //If orbit is normal but rotation is reversed
    else if (planetOrbitForward == true && planetRotForward == false)
    {
      orbitAngle += dt * M_PI/1000;
      rotAngle -= dt * M_PI/1500; 
      model = (glm::rotate(glm::mat4(1.0f), (orbitAngle), glm::vec3(0.0, 12.0, 0.0)) * glm::translate(glm::mat4(1.0f), glm::vec3(4.0, 0.0, 0.0)))
              * glm::rotate(glm::mat4(1.0f), (rotAngle), glm::vec3(0.0, 12.0, 0.0));
    }
    //If orbit is reversed but rotation is reveresed
    else if (planetOrbitForward == false && planetRotForward == false)
    {
      orbitAngle -= dt * M_PI/1000;
      rotAngle -= dt * M_PI/1000;
      model = (glm::rotate(glm::mat4(1.0f), (orbitAngle), glm::vec3(0.0, 12.0, 0.0)) * glm::translate(glm::mat4(1.0f), glm::vec3(4.0, 0.0, 0.0)))
              * glm::rotate(glm::mat4(1.0f), (rotAngle), glm::vec3(0.0, 12.0, 0.0));
    }
  }
  /////////////////////////////////////////////
  //If the planet is orbiting but not rotating
  /////////////////////////////////////////////
  else if (planetOrbitMoving == true && planetRotMoving == false)
  {
    //If orbit is normal and roate stopped
    if (planetOrbitForward == true)
    {
      orbitAngle += dt * M_PI/1000;
      rotAngle += 0;
      model = (glm::rotate(glm::mat4(1.0f), (orbitAngle), glm::vec3(0.0, 12.0, 0.0)) * glm::translate(glm::mat4(1.0f), glm::vec3(4.0, 0.0, 0.0)))
              * glm::rotate(glm::mat4(1.0f), (rotAngle), glm::vec3(0.0, 12.0, 0.0));
    }
    /*//If orbit is normal and roate was reversed
    else if (planetOrbitForward == true && planetRotForward == false)
    {
      orbitAngle += dt * M_PI/1000;
      rotAngle += 0;
      model = (glm::rotate(glm::mat4(1.0f), (orbitAngle), glm::vec3(0.0, 12.0, 0.0)) * glm::translate(glm::mat4(1.0f), glm::vec3(4.0, 0.0, 0.0)))
              * glm::rotate(glm::mat4(1.0f), (rotAngle), glm::vec3(0.0, 12.0, 0.0));
    }*/
    //If orbit is reversed and roate is stopped
    else if (planetOrbitForward == false)
    {
      orbitAngle -= dt * M_PI/1000;
      rotAngle += 0;
      model = (glm::rotate(glm::mat4(1.0f), (orbitAngle), glm::vec3(0.0, 12.0, 0.0)) * glm::translate(glm::mat4(1.0f), glm::vec3(4.0, 0.0, 0.0)))
              * glm::rotate(glm::mat4(1.0f), (rotAngle), glm::vec3(0.0, 12.0, 0.0));
    }
    /*//If orbit is reveresed and roate was reversed
    else if (planetOrbitForward == false && planetRotForward == false)
    {
      orbitAngle -= dt * M_PI/1000;
      rotAngle += 0;
      model = (glm::rotate(glm::mat4(1.0f), (orbitAngle), glm::vec3(0.0, 12.0, 0.0)) * glm::translate(glm::mat4(1.0f), glm::vec3(4.0, 0.0, 0.0)))
              * glm::rotate(glm::mat4(1.0f), (rotAngle), glm::vec3(0.0, 12.0, 0.0));
    }*/
  }
  ////////////////////////////////////////////
  //If the planet is not orbiting but rotating
  ////////////////////////////////////////////
  else if (planetOrbitMoving == false && planetRotMoving == true)
  {
    //If orbit is stopped and roate is normal
    if (planetRotForward == true)
    {
      orbitAngle += 0;
      rotAngle += dt * M_PI/1000;
      model = (glm::rotate(glm::mat4(1.0f), (orbitAngle), glm::vec3(0.0, 12.0, 0.0)) * glm::translate(glm::mat4(1.0f), glm::vec3(4.0, 0.0, 0.0)))
              * glm::rotate(glm::mat4(1.0f), (rotAngle), glm::vec3(0.0, 12.0, 0.0));
    }
    /*//If orbit was normal and roate is reversed
    else if (planetOrbitForward == true && planetRotForward == false)
    {
      orbitAngle += 0;
      rotAngle -= dt *M_PI/1000;
      model = (glm::rotate(glm::mat4(1.0f), (orbitAngle), glm::vec3(0.0, 12.0, 0.0)) * glm::translate(glm::mat4(1.0f), glm::vec3(4.0, 0.0, 0.0)))
              * glm::rotate(glm::mat4(1.0f), (rotAngle), glm::vec3(0.0, 12.0, 0.0));
    }*/
    /*//If orbit was reversed and roate is normal
    else if (planetOrbitForward == false && planetRotForward == true)
    {
      orbitAngle -= 0;
      rotAngle += dt * M_PI/1000;
      model = (glm::rotate(glm::mat4(1.0f), (orbitAngle), glm::vec3(0.0, 12.0, 0.0)) * glm::translate(glm::mat4(1.0f), glm::vec3(4.0, 0.0, 0.0)))
              * glm::rotate(glm::mat4(1.0f), (rotAngle), glm::vec3(0.0, 12.0, 0.0));
    }*/
    //If orbit is stopped and roate is reversed
    else if (planetRotForward == false)
    {
      orbitAngle += 0;
      rotAngle -= dt * M_PI/1000;
      model = (glm::rotate(glm::mat4(1.0f), (orbitAngle), glm::vec3(0.0, 12.0, 0.0)) * glm::translate(glm::mat4(1.0f), glm::vec3(4.0, 0.0, 0.0)))
              * glm::rotate(glm::mat4(1.0f), (rotAngle), glm::vec3(0.0, 12.0, 0.0));
    }
  }
  ////////////////////////////////////////////
  //If the planet is not orbiting or rotating
  ////////////////////////////////////////////
  else if (planetOrbitMoving == false && planetRotMoving == false)
  {
    orbitAngle += 0;
    rotAngle += 0;
    model = (glm::rotate(glm::mat4(1.0f), (orbitAngle), glm::vec3(0.0, 12.0, 0.0)) * glm::translate(glm::mat4(1.0f), glm::vec3(4.0, 0.0, 0.0)))
              * glm::rotate(glm::mat4(1.0f), (rotAngle), glm::vec3(0.0, 12.0, 0.0));
  }
  
  
  /*if (planetOrbitMoving == false)
  {
    orbitAngle += 0;
    rotAngle += dt * M_PI/1000;
    model = (glm::rotate(glm::mat4(1.0f), (orbitAngle), glm::vec3(0.0, 12.0, 0.0)) * glm::translate(glm::mat4(1.0f), glm::vec3(4.0, 0.0, 0.0)))
            * glm::rotate(glm::mat4(1.0f), (rotAngle), glm::vec3(0.0, 12.0, 0.0));
  } 
  //If the planet is orbiting
  else if (planetOrbitMoving == true)
  {
    //If the planet is orbiting forward
    if (planetOrbitForward == true)
    {
      orbitAngle += dt * M_PI/1000;
      rotAngle += dt * M_PI/1000;
    }
    //If the planet is orbiting is reverse
    else
    {
      orbitAngle -= dt * M_PI/1000;
      rotAngle += dt * M_PI/500;
    }
      model = (glm::rotate(glm::mat4(1.0f), (orbitAngle), glm::vec3(0.0, 12.0, 0.0)) * glm::translate(glm::mat4(1.0f), glm::vec3(4.0, 0.0, 0.0)))
            * glm::rotate(glm::mat4(1.0f), (rotAngle), glm::vec3(0.0, 12.0, 0.0));
  }*/
  
  /*if (keyboardInput == 'a')
  {
    angle += dt * M_PI/1000;
  }
  if (keyboardInput == 's')
  {
    angle += dt * M_PI/ 100;
  }
  
  //Multiply the model's rotation by the translation
  //this causes the "orbit"
  model = (glm::rotate(glm::mat4(1.0f), (angle), glm::vec3(0.0, 12.0, 0.0)) * glm::translate(glm::mat4(1.0f), glm::vec3(4.0, 0.0, 0.0)))
  //Then multiply by another rotation
  //this causes the spin while in "orbit"
          * glm::rotate(glm::mat4(1.0f), (angle), glm::vec3(0.0, 12.0, 0.0));
  */     
  
  
  
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

