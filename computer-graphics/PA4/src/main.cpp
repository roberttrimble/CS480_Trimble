#include <iostream>
#include string

#include "engine.h"


int main(int argc, char **argv)
{
  // Check for correct input
  string fileInput;
  if (argc != 2)
  {
    printf("Incorrect file input.\nTry ./Assignment4 <filename>");
    return 0;
  }
  else
  {
    fileInput = "../" + argv;
  }
  
  // Start an engine and run it then cleanup after
  Engine *engine = new Engine("Tutorial Window Name", 800, 600);
  if(!engine->Initialize(fileName))
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
