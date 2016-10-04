#include <iostream>
#incluse <string>

#include "engine.h"


int main(int argc, char **argv)
{
  // Check for correct input
  if (argc != 2)
  {
    printf("Incorrect file input.\nTry ./Assignment5 <filenpath>");
    return 0;
  }
  string fileInput = argv[1];
  
  
  // Start an engine and run it then cleanup after
  Engine *engine = new Engine("Assignment 5", 800, 600);
  if(!engine->Initialize(fileInput))
  {
    printf("The engine failed to start.\n");
    delete engine;
    engine = NULL;
    return 1;
  }
  engine->Run();
  delete engine;
  engine = NULL;
  return 0;
}
