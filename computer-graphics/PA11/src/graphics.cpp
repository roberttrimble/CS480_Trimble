#include "graphics.h"

Graphics::Graphics()
{

}

Graphics::~Graphics()
{

  //////////// clean up and end program
  // delete the pointers
  //////////// clean up and end program
  // delete the pointers
  dynamicsWorld->removeRigidBody(ballRigidBody);
  delete ballRigidBody->getMotionState();
  delete ballRigidBody;

  dynamicsWorld->removeRigidBody(tableRigidBody);
  delete tableRigidBody->getMotionState();
  delete tableRigidBody;

  delete ballMesh;
  delete ball;
  delete triMesh2;

  delete tableMesh;
  delete table;
  delete triMesh1;

  delete stars;
  delete triMesh0;

  delete dynamicsWorld;
  delete solver;
  delete broadphase;
  delete dispatcher;
  delete collisionConfiguration;
}
bool Graphics::Initialize(int width, int height)
{
  // Used for the linux OS
  #if !defined(__APPLE__) && !defined(MACOSX)

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
  
  // For Bullet
  /////////////////////////////////////////////
  //create brodphase
  broadphase = new btDbvtBroadphase();

  //create collision configuration
  collisionConfiguration = new btDefaultCollisionConfiguration();

  //create a dispatcher
  dispatcher = new btCollisionDispatcher(collisionConfiguration);

  //create a solver
  solver = new btSequentialImpulseConstraintSolver();

  //create the physics world
  dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);

  //set the gravity
  dynamicsWorld->setGravity(btVector3(0, -9.81, 0));


/////////////////////////////////////////////////////////////////////////////
// Create the objects
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
  // background
  triMesh0 = new btTriangleMesh();
  stars = new Object("../models/planet.obj", triMesh0);  
  stars->model = glm::scale(stars->model, glm::vec3(28, 28, 28));

  //Create Table
  triMesh1 = new btTriangleMesh();
  table = new Object("../models/JezzBoard.obj", triMesh1);
  tableMesh = new btBvhTriangleMeshShape(triMesh1, true);
  
  tableMotionState = NULL;
  tableMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 1, 0)));
  
  btRigidBody::btRigidBodyConstructionInfo tableRigidBodyCI(0, tableMotionState, tableMesh, btVector3(0, 0, 0));
  tableRigidBody = new btRigidBody(tableRigidBodyCI);

  tableRigidBody->setActivationState(DISABLE_DEACTIVATION);
    
  dynamicsWorld->addRigidBody(tableRigidBody);
  
  
/////////////////////////////////////////////////////////////////////////////

  //Create Ball
  triMesh2 = new btTriangleMesh();
  ball = new Object("../models/ball2.obj", triMesh2);
  ballMesh = new btSphereShape(.425);
  
  ballMotionState = NULL;
  ballMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-6, 5, 5)));
  
  // the sphere must have a mass
  btScalar mass = 1;

  //we need the inertia of the sphere and we need to calculate it
  btVector3 sphereInertia(0, 0, 0);
  ballMesh->calculateLocalInertia(mass, sphereInertia);

  btRigidBody::btRigidBodyConstructionInfo ballRigidBodyCI(1, ballMotionState, ballMesh, sphereInertia);
  ballRigidBody = new btRigidBody(ballRigidBodyCI);

  ballRigidBody->setActivationState(DISABLE_DEACTIVATION);
    
  dynamicsWorld->addRigidBody(ballRigidBody);
  

/////////////////////////////////////////////////////////////////////////////
  

////////////////////////////////////////////////////////////////////////////

  // Init Camera
  m_camera = new Camera();
  if(!m_camera->Initialize(width, height))
  {
    printf("Camera Failed to Initialize\n");
    return false;
  }

  // Set up the shaders
  m_shader = new Shader();
  if(!m_shader->Initialize())
  {
    printf("Shader Failed to Initialize\n");
    return false;
  }

  // Add the vertex shader
  if(!m_shader->AddShader(GL_VERTEX_SHADER, 0))
  {
    printf("Vertex Shader failed to Initialize\n");
    return false;
  }

  // Add the fragment shader
  if(!m_shader->AddShader(GL_FRAGMENT_SHADER, 0))
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

bool Graphics::Update(unsigned int dt, char keyboardInput, bool newInput)
{

  // variables
  glm::vec3 ballModel = glm::vec3(ball->model[3]);
  btScalar m[16];
  btTransform trans;


 if (newInput == true)
  {
    switch (keyboardInput)
    {
      //Left
      /////////////////////////////
      case '<':
				ballRigidBody->applyCentralImpulse(btVector3(10.0,0.0,0.0));

      break;
      
      //Right
      ///////////////////////
      case '>':
				ballRigidBody->applyCentralImpulse(btVector3(-10.0,0.0,0.0));
  				

      break;
        
      //Up/forward
      ///////////////////////
      case '^':
        ballRigidBody->applyCentralImpulse(btVector3(0.0,0.0,10.0));
        
        
      break;   
      //Down/backwards
      ///////////////////////
      case 'v':
      	ballRigidBody->applyCentralImpulse(btVector3(0.0,0.0,-10.0));
      	
      	
      break;
      //Launch the ball
      ///////////////////////
      case 'b':
      	
      break;
      //toggle camera
      //////////////////
      case 'c':
      	camera = !camera;
      break;
    	}
    }
    
    if (camera)
    {
    	m_camera->UpdateCamera(0.0f ,15.0f , -16.0f, ballModel.x, ballModel.y, ballModel.z, 0.0f, 1.0f, 0.0f);
    }
    else
    {
    	m_camera->UpdateCamera(0.0f ,15.0f , -16.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    }


///////////////////////////////////////////////////////

  dynamicsWorld->stepSimulation(dt, 10);

  diffx = ballModel.x;
  diffy = ballModel.y;
  diffz = ballModel.z;

  
  
  //block off the launch tube
  

  tableRigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  table->model = glm::make_mat4(m);
  
  ballRigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  ball->model = glm::make_mat4(m);


  // clean up!
  ballRigidBody->clearForces();
  
  return true;
}

void Graphics::Render(char keyboardInput, bool newInput)
{
  glm::vec3 ballModel = glm::vec3(ball->model[3]);

  //clear the screen
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Start the correct program
  m_shader->Enable();

  // Send in the projection and view to the shader
  glUniformMatrix4fv(m_projectionMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetProjection())); 
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetView())); 

 if (newInput == true)
  {
    /*switch (keyboardInput)
    {
      case 'q':
        tableAmbientx -= .05;
        tableAmbienty -= .05;
        tableAmbientz -= .05;
      break;

      case 'w':
        tableAmbientx += .05;
        tableAmbienty += .05;
        tableAmbientz += .05;
      break;

      case 'a':
        cylSpecularx -= .05;
        cylSpeculary -= .05;
        cylSpecularz -= .05;
        cylDiffusex -= .05;
        cylDiffusey -= .05;
        cylDiffusez -= .05;
      break;

      case 's':
        cylSpecularx += .05;
        cylSpeculary += .05;
        cylSpecularz += .05;
        cylDiffusex += .05;
        cylDiffusey += .05;
        cylDiffusez += .05;

      break;
    	}*/
  }

  // Render the object 
  glUniform4f(m_shader->GetUniformLocation("LightPosition"), 0,2,0,0);
  glUniform4f(m_shader->GetUniformLocation("AmbientProduct"), 0.5, 0.5, 0.5,1);
  glUniform4f(m_shader->GetUniformLocation("DiffuseProduct"), 1,1,1,1);
  glUniform4f(m_shader->GetUniformLocation("SpecularProduct"), 1,1,1,1);
  glUniform1f(m_shader->GetUniformLocation("Shininess"), 10);
  
  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(stars->GetModel()));
  stars->Render();

  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(table->GetModel()));
  table->Render();


  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(ball->GetModel()));
  ball->Render();
 

  
/////////////////////////////////////////////////////////////////////////////////////////////////////////

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

