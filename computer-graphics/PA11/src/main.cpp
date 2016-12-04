#include <iostream>
#include <string>

#include "engine.h"


int main(int argc, char **argv)
{
  // Check for correct input
  if (argc != 1)
	{
		printf("\nThere is no need to enter any file name\nSimply enter: ./Assignment11\n");
		return 1;
	}
  
  
  // Start an engine and run it then cleanup after
  Engine *engine = new Engine("Assignment 11 - JezzBall");
  if(!engine->Initialize())
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
