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

  dynamicsWorld->removeRigidBody(topWallRigidBody);
  delete topWallRigidBody->getMotionState();
  delete topWallRigidBody;

  delete tableMesh;
  delete topWall;
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
  dynamicsWorld->setGravity(btVector3(0, -9.81, -.25));


/////////////////////////////////////////////////////////////////////////////
// Create the objects
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
  
  //Create Table
  triMesh1 = new btTriangleMesh();
  table = new Object("../models/PinballTable5.obj", triMesh1);
  tableMesh = new btBvhTriangleMeshShape(triMesh1, true);
  
  tableMotionState = NULL;
  tableMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 1, 0)));
  
  btRigidBody::btRigidBodyConstructionInfo tableRigidBodyCI(0, tableMotionState, tableMesh, btVector3(0, 0, 0));
  tableRigidBody = new btRigidBody(tableRigidBodyCI);

  tableRigidBody->setActivationState(DISABLE_DEACTIVATION);
    
  dynamicsWorld->addRigidBody(tableRigidBody); 


/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////

  //Create top wall

  topWall = new btStaticPlaneShape(btVector3(0, -1, 0), 0);
  topWallMotionState = NULL;
  topWallMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 5, 0)));
  
  btRigidBody::btRigidBodyConstructionInfo topWallRigidBodyCI(0, topWallMotionState, topWall, btVector3(0, 0, 0));
  topWallRigidBody = new btRigidBody(topWallRigidBodyCI);

  topWallRigidBody->setActivationState(DISABLE_DEACTIVATION);
    
  dynamicsWorld->addRigidBody(topWallRigidBody); 
  
/////////////////////////////////////////////////////////////////////////////

  //Create Ball
  triMesh2 = new btTriangleMesh();
  ball = new Object("../models/sphere_normals.obj", triMesh2);
  ballMesh = new btSphereShape(.85);
  
  ballMotionState = NULL;
  ballMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-5, 10, 5)));
  
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
  cube = new Object("../models/cube_normals.obj", triMesh3);
  cubeMesh = new btBoxShape(btVector3(.5, .5, .5));
  
  cubeMotionState = NULL;
  cubeMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(2, 10, -2)));
  
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
  cylinder = new Object("../models/cylinder_normals.obj", triMesh4);
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

void Graphics::Update(unsigned int dt, char keyboardInput, bool newInput, int mouseXlocation, int mouseYlocation)
{


 float force = 8.0;

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
      //Launch the ball
      ///////////////////////
      case 'b':
        ballRigidBody->applyCentralImpulse(btVector3(0.0,0.0,10.0));
        
      break;
    	}
    }
    
 

  dynamicsWorld->stepSimulation(dt, 10);
  
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

  // clean up!
  ballRigidBody->clearForces();
}

void Graphics::Render(char keyboardInput, bool newInput)
{
  //clear the screen
  glClearColor(0.0, 0.0, 0.2, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Start the correct program
  m_shader->Enable();


  // Send in the projection and view to the shader
  glUniformMatrix4fv(m_projectionMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetProjection())); 
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetView())); 

 if (newInput == true)
  {
    switch (keyboardInput)
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
    	}
  }

  // Render the object 
  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(table->GetModel()));
  glUniform4f(m_shader->GetUniformLocation("LightPosition"), 0,2,0,0);
  glUniform4f(m_shader->GetUniformLocation("AmbientProduct"), tableAmbientx, tableAmbienty, tableAmbientz,1);
  glUniform4f(m_shader->GetUniformLocation("DiffuseProduct"), 1,1,1,1);
  glUniform4f(m_shader->GetUniformLocation("SpecularProduct"), 1,1,1,1);
  glUniform1f(m_shader->GetUniformLocation("Shininess"), 10);
  table->Render();

  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(ball->GetModel()));
  glUniform4f(m_shader->GetUniformLocation("LightPosition"), 0,2,0,0);
  glUniform4f(m_shader->GetUniformLocation("AmbientProduct"), .5,.5,.5,1);
  glUniform4f(m_shader->GetUniformLocation("DiffuseProduct"), 1, 1, 1,1);
  glUniform4f(m_shader->GetUniformLocation("SpecularProduct"), 1, 1, 1,1);
  glUniform1f(m_shader->GetUniformLocation("Shininess"), .0005);

  glUniform1f(m_shader->GetUniformLocation("ball"), 1.0);
  ball->Render();
  glUniform1f(m_shader->GetUniformLocation("ball"), 0.0);

  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(cube->GetModel()));
  glUniform4f(m_shader->GetUniformLocation("LightPosition"), 0,2,0,0);
  glUniform4f(m_shader->GetUniformLocation("AmbientProduct"), .25,.25,.25,1);
  glUniform4f(m_shader->GetUniformLocation("DiffuseProduct"), .25,.25,.25,1);
  glUniform4f(m_shader->GetUniformLocation("SpecularProduct"), 1,1,1,1);
  glUniform1f(m_shader->GetUniformLocation("Shininess"), 10);
  cube->Render();

  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(cylinder->GetModel()));
  glUniform4f(m_shader->GetUniformLocation("LightPosition"), 0,2,0,0);
  glUniform4f(m_shader->GetUniformLocation("AmbientProduct"), .5,.5,.5,1);
  glUniform4f(m_shader->GetUniformLocation("DiffuseProduct"), cylDiffusex, cylDiffusez, cylDiffusez, 1);
  glUniform4f(m_shader->GetUniformLocation("SpecularProduct"), cylSpecularx, cylSpeculary, cylSpecularz,1);
  glUniform1f(m_shader->GetUniformLocation("Shininess"), 10);
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

