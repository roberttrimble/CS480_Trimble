#include "graphics.h"

Graphics::Graphics()
{

}

Graphics::~Graphics()
{

  //////////// clean up and end program
  // delete the pointers
  dynamicsWorld->removeRigidBody(tableRigidBody);
  delete tableRigidBody->getMotionState();
  delete tableRigidBody;
       
  dynamicsWorld->removeRigidBody(ballRigidBody);
  delete ballRigidBody->getMotionState();
  delete ballRigidBody;
       
  dynamicsWorld->removeRigidBody(cubeRigidBody);
  delete cubeRigidBody->getMotionState();
  delete cubeRigidBody;
        
  dynamicsWorld->removeRigidBody(cylinderRigidBody);
  delete cylinderRigidBody->getMotionState();
  delete cylinderRigidBody;
       
  dynamicsWorld->removeRigidBody(leftWallRigidBody);
  delete leftWallRigidBody->getMotionState();
  delete leftWallRigidBody;

  dynamicsWorld->removeRigidBody(rightWallRigidBody);
  delete rightWallRigidBody->getMotionState();
  delete rightWallRigidBody;
      
  dynamicsWorld->removeRigidBody(backWallRigidBody);
  delete backWallRigidBody->getMotionState();
  delete backWallRigidBody;
        
  dynamicsWorld->removeRigidBody(frontWallRigidBody);
  delete frontWallRigidBody->getMotionState();
  delete frontWallRigidBody;

  delete tableMesh;
  delete leftWall;
  delete rightWall;
  delete backWall;
  delete frontWall;
  delete ballMesh;
  delete cubeMesh;
  delete cylinderMesh;
  delete dynamicsWorld;
  delete solver;
  delete collisionConfiguration;
  delete dispatcher;
  delete broadphase;
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
  
  //Create Table
  triMesh1 = new btTriangleMesh();
  table = new Object("../models/PinballTable3.obj", triMesh1);
  tableMesh = new btStaticPlaneShape(btVector3(0, 1, 0), 0);
  
  tableMotionState = NULL;
  tableMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 1, 0)));
  
  btRigidBody::btRigidBodyConstructionInfo tableRigidBodyCI(0, tableMotionState, tableMesh, btVector3(0, 0, 0));
  tableRigidBody = new btRigidBody(tableRigidBodyCI);

  tableRigidBody->setActivationState(DISABLE_DEACTIVATION);
    
  dynamicsWorld->addRigidBody(tableRigidBody); 


/////////////////////////////////////////////////////////////////////////////


  //Create left wall
  leftWall = new btStaticPlaneShape(btVector3(-1, 0, 0), 1);
  leftWallMotionState = NULL;
  leftWallMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(7.8, 0, 0)));
  
  btRigidBody::btRigidBodyConstructionInfo leftWallRigidBodyCI(0, leftWallMotionState, leftWall, btVector3(0, 0, 0));
  leftWallRigidBody = new btRigidBody(leftWallRigidBodyCI);

  leftWallRigidBody->setActivationState(DISABLE_DEACTIVATION);
    
  dynamicsWorld->addRigidBody(leftWallRigidBody); 

/////////////////////////////////////////////////////////////////////////////


  //Create right wall
  rightWall = new btStaticPlaneShape(btVector3(1, 0, 0), 1);
  rightWallMotionState = NULL;
  rightWallMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-7, 0, 0)));
  
  btRigidBody::btRigidBodyConstructionInfo rightWallRigidBodyCI(0, rightWallMotionState, rightWall, btVector3(0, 0, 0));
  rightWallRigidBody = new btRigidBody(rightWallRigidBodyCI);

  rightWallRigidBody->setActivationState(DISABLE_DEACTIVATION);
    
  dynamicsWorld->addRigidBody(rightWallRigidBody); 

/////////////////////////////////////////////////////////////////////////////


  //Create back wall
  backWall = new btStaticPlaneShape(btVector3(0, 0, -1), 1);
  backWallMotionState = NULL;
  backWallMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 15)));
  
  btRigidBody::btRigidBodyConstructionInfo backWallRigidBodyCI(0, backWallMotionState, backWall, btVector3(0, 0, 0));
  backWallRigidBody = new btRigidBody(backWallRigidBodyCI);

  backWallRigidBody->setActivationState(DISABLE_DEACTIVATION);
    
  dynamicsWorld->addRigidBody(backWallRigidBody); 

/////////////////////////////////////////////////////////////////////////////

  //Create front wall
  frontWall = new btStaticPlaneShape(btVector3(0, 0, 1), 1);
  frontWallMotionState = NULL;
  frontWallMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, -8.8)));
  
  btRigidBody::btRigidBodyConstructionInfo frontWallRigidBodyCI(0, frontWallMotionState, frontWall, btVector3(0, 0, 0));
  frontWallRigidBody = new btRigidBody(frontWallRigidBodyCI);

  frontWallRigidBody->setActivationState(DISABLE_DEACTIVATION);
    
  dynamicsWorld->addRigidBody(frontWallRigidBody);
  
/////////////////////////////////////////////////////////////////////////////
  
  //Create Ball
  triMesh2 = new btTriangleMesh();
  ball = new Object("../models/Sphere1.obj", triMesh2);
  ballMesh = new btSphereShape(1);
  
  ballMotionState = NULL;
  ballMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(2, 10, 0)));
  
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
  
  //Create Cube
  triMesh3 = new btTriangleMesh();
  cube = new Object("../models/Cube1.obj", triMesh3);
  cubeMesh = new btBoxShape(btVector3(1.0, 1.0, 1.0));
  
  cubeMotionState = NULL;
  cubeMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 10, 0)));
  
  // the cube must have a mass
  mass = 1;

  //we need the inertia of the sphere and we need to calculate it
  btVector3 cubeInertia(0, 0, 0);
  cubeMesh->calculateLocalInertia(mass, cubeInertia);

  btRigidBody::btRigidBodyConstructionInfo cubeRigidBodyCI(1, cubeMotionState, cubeMesh, cubeInertia);
  cubeRigidBody = new btRigidBody(cubeRigidBodyCI);

  cubeRigidBody->setActivationState(DISABLE_DEACTIVATION);
    
  dynamicsWorld->addRigidBody(cubeRigidBody);

/////////////////////////////////////////////////////////////////////////////
  
  //Create Cylinder
  triMesh4 = new btTriangleMesh();
  cylinder = new Object("../models/Cylinder1.obj", triMesh4);
  cylinderMesh = new btCylinderShape(btVector3(1.0,1.0,1.0));
	
	cylinderMotionState = NULL;
  cylinderMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 1, 0)));
  
  btRigidBody::btRigidBodyConstructionInfo cylinderRigidBodyCI(0, cylinderMotionState, cylinderMesh, btVector3(0, 0, 0));
  cylinderRigidBody = new btRigidBody(cylinderRigidBodyCI);

  cylinderRigidBody->setActivationState(DISABLE_DEACTIVATION);
    
  dynamicsWorld->addRigidBody(cylinderRigidBody);

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

 float force = 10.0;

 if (newInput == true)
  {
    switch (keyboardInput)
    {
      //Left
      /////////////////////////////
      case '<':
        cubeRigidBody->applyCentralImpulse(btVector3(force,0.0,0.0));
      break;
      
      //Right
      ///////////////////////
      case '>':
        cubeRigidBody->applyCentralImpulse(btVector3(-force,0.0,0.0));
      break;
        
      //Up/forward
      ///////////////////////
      case '^':
        cubeRigidBody->applyCentralImpulse(btVector3(0.0,0.0,force));
      break;
        
      //Down/backwards
      ///////////////////////
      case 'v':
        cubeRigidBody->applyCentralImpulse(btVector3(0.0,0.0,-force));
      break;
    }
  }

  dynamicsWorld->stepSimulation(dt, 10);
  
  btTransform trans;
  btScalar m[16];

  tableRigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  table->model = glm::make_mat4(m);
  table->model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, 7.0))
                              * glm::scale(table->model, glm::vec3(2.0, 2.0, 2.0))
                              * glm::rotate(glm::mat4(1.0f), (float)(M_PI/2), glm::vec3(0.0, 12.0, 0.0));
  
  ballRigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  ball->model = glm::make_mat4(m);
  
  cubeRigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  cube->model = glm::make_mat4(m);
  
  cylinderRigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  cylinder->model = glm::make_mat4(m);

  // clean up!
  ballRigidBody->clearForces();
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

  // Render the object
  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(table->GetModel()));
  table->Render();
  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(ball->GetModel()));
  ball->Render();
  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(cube->GetModel()));
  cube->Render();
  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(cylinder->GetModel()));
  cylinder->Render();

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

