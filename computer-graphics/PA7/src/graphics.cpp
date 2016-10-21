#include "graphics.h"

Graphics::Graphics()
{

}

Graphics::~Graphics()
{

}

bool Graphics::Initialize(int width, int height)
{
  // Used for the linux OS
  #if !defined(__APPLE__) && !defined(MACOSX)
    // cout << glewGetString(GLEW_VERSION) << endl;
    glewExperimental = GL_TRUE;

    auto status = glewInit();

    // This is here to grab the error that comes from glew init.
    // This error is an GL_INVALID_ENUM that has no effects on the performance
    glGetError();

    //Check for error
    if (status != GLEW_OK)
    {
      std::cerr << "GLEW Error: " << glewGetErrorString(status) << "\n";
      return false;
    }
  #endif

  // For OpenGL 3
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // Init Camera
  m_camera = new Camera();
  if(!m_camera->Initialize(width, height))
  {
    printf("Camera Failed to Initialize\n");
    return false;
  }

	// OBJ files
	string planetOBJ = "../models/planet.obj";
	string ringOBJ = "../models/saturnRing.obj";
	string ringJPG = "../models/saturnsring.jpg";
	string moonJPG = "../models/moon.jpg";

  // Create the planet objects
	///////////////////////////
  sun = new Object(planetOBJ, "../models/sun.jpg");

  mercury = new Object(planetOBJ, "../models/mercury.jpg");

  venus = new Object(planetOBJ, "../models/venus.jpg");

	earth = new Object(planetOBJ, "../models/earth.jpg");
	earth->moon = new Object(planetOBJ, moonJPG);

	mars = new Object(planetOBJ, "../models/mars.jpg");
	mars->moon = new Object(planetOBJ, moonJPG);

	jupiter = new Object(planetOBJ, "../models/jupiter.jpg");
	jupiter->moon = new Object(planetOBJ, moonJPG);

	saturn = new Object(planetOBJ, "../models/saturn.png");
	saturnsring = new Object(ringOBJ, ringJPG);
	saturn->moon = new Object(planetOBJ, moonJPG);

	uranus = new Object(planetOBJ, "../models/uranus.jpg");
	uranus->moon = new Object(planetOBJ, moonJPG);

	neptune = new Object(planetOBJ, "../models/neptune.jpg");
	neptune->moon = new Object(planetOBJ, moonJPG);

	pluto = new Object(planetOBJ, "../models/pluto.png");

  stars = new Object(planetOBJ, "../models/stars.png");

  // Set up the shaders
  m_shader = new Shader();
  if(!m_shader->Initialize())
  {
    printf("Shader Failed to Initialize\n");
    return false;
  }

  // Add the vertex shader
  if(!m_shader->AddShader(GL_VERTEX_SHADER))
  {
    printf("Vertex Shader failed to Initialize\n");
    return false;
  }

  // Add the fragment shader
  if(!m_shader->AddShader(GL_FRAGMENT_SHADER))
  {
    printf("Fragment Shader failed to Initialize\n");
    return false;
  }

  // Connect the program
  if(!m_shader->Finalize())
  {
    printf("Program to Finalize\n");
    return false;
  }

  // Locate the projection matrix in the shader
  m_projectionMatrix = m_shader->GetUniformLocation("projectionMatrix");
  if (m_projectionMatrix == INVALID_UNIFORM_LOCATION) 
  {
    printf("m_projectionMatrix not found\n");
    return false;
  }

  // Locate the view matrix in the shader
  m_viewMatrix = m_shader->GetUniformLocation("viewMatrix");
  if (m_viewMatrix == INVALID_UNIFORM_LOCATION) 
  {
    printf("m_viewMatrix not found\n");
    return false;
  }

  // Locate the model matrix in the shader
  m_modelMatrix = m_shader->GetUniformLocation("modelMatrix");
  if (m_modelMatrix == INVALID_UNIFORM_LOCATION) 
  {
    printf("m_modelMatrix not found\n");
    return false;
  }

  //enable depth testing
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  return true;
}

void Graphics::Update(unsigned int dt, char keyboardInput, bool newInput)
{
	if(newInput)
		{
			if(keyboardInput == '1')
				m_camera->UpdateCamera(0.0f ,8.0f ,-16.0f);
			if(keyboardInput == '2')
				m_camera->UpdateCamera(0.0f ,8.0f ,-32.0f);
			if(keyboardInput == '3')
				m_camera->UpdateCamera(0.0f ,8.0f ,-48.0f);
			if(keyboardInput == '4')
				m_camera->UpdateCamera(0.0f ,0.0f ,-32.0f);
			if(keyboardInput == '5')
				m_camera->UpdateCamera(0.0f ,32.0f ,0.0f);
			if(keyboardInput == '6')
				m_camera->UpdateCamera(0.0f ,0.0f ,-48.0f);
		}


	glm::mat4 planetModel;

  // Update the object
  sun->Update(dt, 0);
  mercury->Update(dt, 1);
  venus->Update(dt, 2);
  earth->Update(dt, 3);
		planetModel = earth->GetModel();
		earth->moon->UpdateMoon(planetModel, dt, 3);
	mars->Update(dt, 4);
		planetModel = mars->GetModel();
		mars->moon->UpdateMoon(planetModel, dt, 4);
	jupiter->Update(dt, 5);
		planetModel = jupiter->GetModel();
		jupiter->moon->UpdateMoon(planetModel, dt, 5);
	saturn->Update(dt, 6);
		planetModel = saturn->GetModel();
		saturn->moon->UpdateMoon(planetModel, dt, 6);
		saturnsring->Update(dt,6);
	uranus->Update(dt, 7);
		planetModel = uranus->GetModel();
		uranus->moon->UpdateMoon(planetModel, dt, 7);
	neptune->Update(dt, 8);
		planetModel = neptune->GetModel();
		neptune->moon->UpdateMoon(planetModel, dt, 8);
	pluto->Update(dt, 9);
	stars->Update(dt, 10);
}

void Graphics::Render()
{
  //clear the screen
  glClearColor(0.0, 0.0, 0.2, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Start the correct program
  m_shader->Enable();

  // Send in the projection and view to the shader
  glUniformMatrix4fv(m_projectionMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetProjection())); 
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetView())); 

  // Render the planet and moon objects
	/////////////////////////////////////////
  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(sun->GetModel()));
  sun->Render();

  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(mercury->GetModel()));
  mercury->Render();

  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(venus->GetModel()));
  venus->Render();

  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(earth->GetModel()));
  earth->Render();
 	glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(earth->moon->GetModel()));
  earth->moon->Render();

  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(mars->GetModel()));
  mars->Render();
	glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(mars->moon->GetModel()));
  mars->moon->Render(); 

  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(jupiter->GetModel()));
  jupiter->Render();
	glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(jupiter->moon->GetModel()));
  jupiter->moon->Render();

  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(saturn->GetModel()));
  saturn->Render();
	glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(saturn->moon->GetModel()));
  saturn->moon->Render();
	glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(saturnsring->GetModel()));
  saturnsring->Render();

  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(uranus->GetModel()));
  uranus->Render();
	glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(uranus->moon->GetModel()));
  uranus->moon->Render();

  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(neptune->GetModel()));
  neptune->Render();
	glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(neptune->moon->GetModel()));
  neptune->moon->Render();

  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(pluto->GetModel()));
  pluto->Render();

  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(stars->GetModel()));
  stars->Render();

  // Get any errors from OpenGL
  auto error = glGetError();
  if ( error != GL_NO_ERROR )
  {
    string val = ErrorString( error );
    std::cout<< "Error initializing OpenGL! " << error << ", " << val << std::endl;
  }
}

std::string Graphics::ErrorString(GLenum error)
{
  if(error == GL_INVALID_ENUM)
  {
    return "GL_INVALID_ENUM: An unacceptable value is specified for an enumerated argument.";
  }

  else if(error == GL_INVALID_VALUE)
  {
    return "GL_INVALID_VALUE: A numeric argument is out of range.";
  }

  else if(error == GL_INVALID_OPERATION)
  {
    return "GL_INVALID_OPERATION: The specified operation is not allowed in the current state.";
  }

  else if(error == GL_INVALID_FRAMEBUFFER_OPERATION)
  {
    return "GL_INVALID_FRAMEBUFFER_OPERATION: The framebuffer object is not complete.";
  }

  else if(error == GL_OUT_OF_MEMORY)
  {
    return "GL_OUT_OF_MEMORY: There is not enough memory left to execute the command.";
  }
  else
  {
    return "None";
  }
}

