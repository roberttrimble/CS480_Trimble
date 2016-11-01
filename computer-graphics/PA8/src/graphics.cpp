#include "graphics.h"

Graphics::Graphics()
{

}

Graphics::~Graphics()
{/*
	delete triMesh;
	delete tableMesh;
	delete ballMesh;
	delete tableRigidBody;
	delete ballRigidBody;
	delete cubeRigidBody;
	delete cylinderRigidBody;
	delete solver;
	delete dispatcher;
	delete collisionConfiguration;
	delete broadphase;
	delete dynamicsWorld;*/
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
	//////////////////////////////////////////////////////////////////////////////////////
  // Create the objects
  ///////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////////
  
  //Create Table
  triMesh = new btTriangleMesh();
  table = new Object("../models/PinballTable3.obj", triMesh);
  tableMesh = new btStaticPlaneShape(btVector3(1, 1, 1), 1);
  delete triMesh;
  
  tableMotionState = NULL;
  tableMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));
  
  btRigidBody::btRigidBodyConstructionInfo tableRigidBodyCI(0, tableMotionState, tableMesh, btVector3(0, 0, 0));
  tableRigidBody = new btRigidBody(tableRigidBodyCI);

  tableRigidBody->setCollisionFlags(tableRigidBody->getCollisionFlags() | btCollisionObject::CF_STATIC_OBJECT);
  tableRigidBody->setActivationState(DISABLE_DEACTIVATION);
    
   dynamicsWorld->addRigidBody(tableRigidBody); 
   //dynamicsWorld->addCollisionObject(tableRigidBody);
  
  
  
  
  //Create Ball
  triMesh = new btTriangleMesh();
  ball = new Object("../models/Sphere1.obj", triMesh);
  ballMesh = new btBvhTriangleMeshShape(triMesh, true);
  delete triMesh;
  
  ballMotionState = NULL;
  ballMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 1, 0)));
  
  btRigidBody::btRigidBodyConstructionInfo ballRigidBodyCI(1, ballMotionState, ballMesh, btVector3(0, 0, 0));
  ballRigidBody = new btRigidBody(ballRigidBodyCI);

//  ballRigidBody->setCollisionFlags(ballRigidBody->getCollisionFlags() | btCollisionObject::CF_STATIC_OBJECT);
  ballRigidBody->setActivationState(DISABLE_DEACTIVATION);
    
   dynamicsWorld->addRigidBody(ballRigidBody);
   //dynamicsWorld->addCollisionObject(ballRigidBody);
  
  
  
  //Create Cube
  triMesh = new btTriangleMesh();
  cube = new Object("../models/Cube1.obj", triMesh);
  cubeMesh = new btBvhTriangleMeshShape(triMesh, true);
  delete triMesh;
  
  cubeMotionState = NULL;
  cubeMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(10, 1, 0)));
  
  btRigidBody::btRigidBodyConstructionInfo cubeRigidBodyCI(1, cubeMotionState, cubeMesh, btVector3(0, 0, 0));
  cubeRigidBody = new btRigidBody(cubeRigidBodyCI);

  cubeRigidBody->setCollisionFlags(cubeRigidBody->getCollisionFlags() | btCollisionObject::CF_STATIC_OBJECT);
  cubeRigidBody->setActivationState(DISABLE_DEACTIVATION);
    
  dynamicsWorld->addRigidBody(cubeRigidBody);
  //dynamicsWorld->addCollisionObject(cubeRigidBody);
  
  
  
  //Create Cylinder
  triMesh = new btTriangleMesh();
  cylinder = new Object("../models/Cylinder1.obj", triMesh);
  cylinderMesh = new btBvhTriangleMeshShape(triMesh, true);
	delete triMesh;
	
	cylinderMotionState = NULL;
  cylinderMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(1, 10, 1)));
  
  btRigidBody::btRigidBodyConstructionInfo cylinderRigidBodyCI(0, cylinderMotionState, cylinderMesh, btVector3(0, 0, 0));
  cylinderRigidBody = new btRigidBody(cylinderRigidBodyCI);

  cylinderRigidBody->setCollisionFlags(cylinderRigidBody->getCollisionFlags() | btCollisionObject::CF_STATIC_OBJECT);
  cylinderRigidBody->setActivationState(DISABLE_DEACTIVATION);
    
   dynamicsWorld->addRigidBody(cylinderRigidBody);
   //dynamicsWorld->addCollisionObject(cylinderRigidBody);


////////////////////////////////////////////////////////////////////////////
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

void Graphics::Update(unsigned int dt)
{
std::cout << dt << std::endl;

  dynamicsWorld->stepSimulation(.5, 10);
  
  btTransform trans;
  btScalar m[16];

  tableRigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  table->model = glm::make_mat4(m);
  
  ballRigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  ball->model = glm::make_mat4(m);
  
  cubeRigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  cube->model = glm::make_mat4(m);
  
  cylinderRigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  cylinder->model = glm::make_mat4(m);

  
  
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

