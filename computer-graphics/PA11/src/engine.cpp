
#include "engine.h"

Engine::Engine(string name, int width, int height)
{
  m_WINDOW_NAME = name;
  m_WINDOW_WIDTH = width;
  m_WINDOW_HEIGHT = height;
  m_FULLSCREEN = false;
}

Engine::Engine(string name)
{
  m_WINDOW_NAME = name;
  m_WINDOW_HEIGHT = 0;
  m_WINDOW_WIDTH = 0;
  m_FULLSCREEN = true;
}

Engine::~Engine()
{
  delete m_window;
  delete m_graphics;
  m_window = NULL;
  m_graphics = NULL;
}

bool Engine::Initialize()
{
  // Start a window
  m_window = new Window();
  if(!m_window->Initialize(m_WINDOW_NAME, &m_WINDOW_WIDTH, &m_WINDOW_HEIGHT))
  {
    printf("The window failed to initialize.\n");
    return false;
  }

  // Start the graphics
  m_graphics = new Graphics();
  if(!m_graphics->Initialize(m_WINDOW_WIDTH, m_WINDOW_HEIGHT))
  {
    printf("The graphics failed to initialize.\n");
    return false;
  }

  // Set the time
  m_currentTimeMillis = GetCurrentTimeMillis();

  // No errors
  return true;
}

void Engine::Run()
{
  m_running = true;
  state = 0;
  outOfLives = false;
  //outOfLives = false;

  while(m_running)
  {
    // Update the DT
    m_DT = getDT();

    // Check the keyboard input
    while(SDL_PollEvent(&m_event) != 0)
    {
      Keyboard();
    }

    // Update and render the graphics
    outOfLives = m_graphics->Update(m_DT, keyboardInput, newInput);

    m_graphics->Render(keyboardInput, newInput);
    newInput = false;

    // Swap to the Window
    m_window->Swap();
    
  }
}

void Engine::Keyboard()
{
  if(m_event.type == SDL_QUIT)
  {
    m_running = false;
  }
  else if (m_event.type == SDL_KEYDOWN)
  {
    // handle key down events heree
    switch (m_event.key.keysym.sym)
    {
      case SDLK_ESCAPE:
        m_running = false;
        break;
      case SDLK_SPACE:
				keyboardInput = '_';
        newInput = true;
       
       break;
      //left paddle
      case SDLK_LEFT:
        keyboardInput = '<';
        newInput = true;
        
        break;
      //right paddle
      case SDLK_RIGHT:
        keyboardInput = '>';
        newInput = true;
        
        break;

      //release plunger
      case SDLK_UP:
        keyboardInput = '^';
        newInput = true;
        break;

      //pull back plunger
      case SDLK_DOWN:
        keyboardInput = 'v';
        newInput = true;
        break;

      //lowers table lights
      case SDLK_q:
        keyboardInput = 'q';
        newInput = true;
        break;

      //raise table lights
      case SDLK_w:
        keyboardInput = 'w';
        newInput = true;
        break;

      //loweer cylinder lights
      case SDLK_a:
        keyboardInput = 'a';
        newInput = true;
        break;

      //raise cylinder lights
      case SDLK_s:
        keyboardInput = 's';
        newInput = true;
        break;
      //toggle camera
      case SDLK_c:
        keyboardInput = 'c';
        newInput = true;
        break;

     }
    }
    else if (m_event.type == SDL_MOUSEBUTTONDOWN)
  	{
		  if (m_event.button.button == SDL_BUTTON_LEFT)
		  {
		    keyboardInput = 'b';
		    
		    newInput = true;
		  }

		  if (m_event.button.button == SDL_BUTTON_RIGHT)
		  {
		    keyboardInput = 'w';
		    
		    newInput = true;
		  }
  	}
  
}

unsigned int Engine::getDT()
{
  long long TimeNowMillis = GetCurrentTimeMillis();
  assert(TimeNowMillis >= m_currentTimeMillis);
  unsigned int DeltaTimeMillis = (unsigned int)(TimeNowMillis - m_currentTimeMillis);
  m_currentTimeMillis = TimeNowMillis;
  return DeltaTimeMillis;
}

long long Engine::GetCurrentTimeMillis()
{
  timeval t;
  gettimeofday(&t, NULL);
  long long ret = t.tv_sec * 1000 + t.tv_usec / 1000;
  return ret;
}
