#include "graphics.h"

Graphics::Graphics()
{

}

Graphics::~Graphics()
{

  //////////// clean up and end program
  // delete the pointers
  delete cylinder1RigidBody;
  dynamicsWorld->removeRigidBody(cylinder1RigidBody);
  delete cylinder1RigidBody->getMotionState();
  delete cylinder1Mesh;
  delete cylinder1; 
  delete triMesh4;


  delete cubeRigidBody;
  dynamicsWorld->removeRigidBody(cubeRigidBody);
  delete cubeRigidBody->getMotionState();
  delete cubeMesh;
  delete cube;
  delete triMesh3;

  delete ballRigidBody;
  dynamicsWorld->removeRigidBody(ballRigidBody);
  delete ballRigidBody->getMotionState();
  delete ballMesh;
  delete ball;
  delete triMesh2;

  delete topWallRigidBody;
  dynamicsWorld->removeRigidBody(topWallRigidBody);
  delete topWallRigidBody->getMotionState();
  delete topWall;

  delete tableRigidBody;
  dynamicsWorld->removeRigidBody(tableRigidBody);
  delete tableRigidBody->getMotionState();
  delete tableMesh;
  delete table;
  delete triMesh1;

  delete dynamicsWorld;
  delete solver;
  delete dispatcher;
  delete collisionConfiguration;
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
  table = new Object("../models/PinballTable8.obj", triMesh1);
  tableMesh = new btBvhTriangleMeshShape(triMesh1, true);
  
  tableMotionState = NULL;
  tableMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 1, 0)));
  
  btRigidBody::btRigidBodyConstructionInfo tableRigidBodyCI(0, tableMotionState, tableMesh, btVector3(0, 0, 0));
  tableRigidBody = new btRigidBody(tableRigidBodyCI);

  tableRigidBody->setActivationState(DISABLE_DEACTIVATION);
    
  dynamicsWorld->addRigidBody(tableRigidBody);
  
  //Create paddles
  triMesh5 = new btTriangleMesh();
  leftBumper = new Object("../models/leftBumper.obj", triMesh5);
  leftBumperMesh = new btBvhTriangleMeshShape(triMesh5, true);
  
  leftBumperMotionState = NULL;
  leftBumperMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(5.2, 1, -4.8)));
  
  btRigidBody::btRigidBodyConstructionInfo leftBumperRigidBodyCI(0, leftBumperMotionState, leftBumperMesh, btVector3(0, 0, 0));
  leftBumperRigidBody = new btRigidBody(leftBumperRigidBodyCI);

  leftBumperRigidBody->setActivationState(DISABLE_DEACTIVATION);
    
  dynamicsWorld->addRigidBody(leftBumperRigidBody); 
  ///////////
  triMesh6 = new btTriangleMesh();
  rightBumper = new Object("../models/rightBumper.obj", triMesh6);
  rightBumperMesh = new btBvhTriangleMeshShape(triMesh6, true);
  
  rightBumperMotionState = NULL;
  rightBumperMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-2.5, 1, -4.8)));
  
  btRigidBody::btRigidBodyConstructionInfo rightBumperRigidBodyCI(0, rightBumperMotionState, rightBumperMesh, btVector3(0, 0, 0));
  rightBumperRigidBody = new btRigidBody(rightBumperRigidBodyCI);

  rightBumperRigidBody->setActivationState(DISABLE_DEACTIVATION);
    
  dynamicsWorld->addRigidBody(rightBumperRigidBody);

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
  
  //Create Cylinders
  triMesh4 = new btTriangleMesh();
  cylinder1 = new Object("../models/cylinder_normals.obj", triMesh4);
  cylinder1Mesh = new btCylinderShape(btVector3(1.0,1.0,1.0));
	
	cylinder1MotionState = NULL;
  cylinder1MotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(1, 1, 2)));
  
  btRigidBody::btRigidBodyConstructionInfo cylinder1RigidBodyCI(0, cylinder1MotionState, cylinder1Mesh, btVector3(0, 0, 0));
  cylinder1RigidBody = new btRigidBody(cylinder1RigidBodyCI);

  cylinder1RigidBody->setActivationState(DISABLE_DEACTIVATION);
    
  dynamicsWorld->addRigidBody(cylinder1RigidBody);
  
  
  cylinder2 = new Object("../models/cylinder_normals.obj", triMesh4);
  cylinder2Mesh = new btCylinderShape(btVector3(1.0,1.0,1.0));
	
	cylinder2MotionState = NULL;
  cylinder2MotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(4, 1, 7)));
  
  btRigidBody::btRigidBodyConstructionInfo cylinder2RigidBodyCI(0, cylinder2MotionState, cylinder2Mesh, btVector3(0, 0, 0));
  cylinder2RigidBody = new btRigidBody(cylinder2RigidBodyCI);

  cylinder2RigidBody->setActivationState(DISABLE_DEACTIVATION);
    
  dynamicsWorld->addRigidBody(cylinder2RigidBody);
  
  
  cylinder3 = new Object("../models/cylinder_normals.obj", triMesh4);
  cylinder3Mesh = new btCylinderShape(btVector3(1.0,1.0,1.0));
	
	cylinder3MotionState = NULL;
  cylinder3MotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-2, 1, 7)));
  
  btRigidBody::btRigidBodyConstructionInfo cylinder3RigidBodyCI(0, cylinder3MotionState, cylinder3Mesh, btVector3(0, 0, 0));
  cylinder3RigidBody = new btRigidBody(cylinder3RigidBodyCI);

  cylinder3RigidBody->setActivationState(DISABLE_DEACTIVATION);
    
  dynamicsWorld->addRigidBody(cylinder3RigidBody);

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
 float force = 5.0;


 if (newInput == true)
  {
    switch (keyboardInput)
    {
      //Left
      /////////////////////////////
      case '<':
        cubeRigidBody->applyCentralImpulse(btVector3(force,0.0,0.0));
        
        if(true){
        
        	glm::vec3 cubeModel = glm::vec3(cube->model[3]);
  				glm::vec3 leftBumperModel = glm::vec3(leftBumper->model[3]);

  				float diffx = cubeModel.x - leftBumperModel.x;
  				float diffy = cubeModel.y - leftBumperModel.y;
  				float diffz = cubeModel.z - leftBumperModel.z;

  				if ( abs(diffx) <= 1.8 && abs(diffz) <= 1.8){
    				glm::vec3 normalVec = glm::vec3 (diffx, diffy, diffz);
    				normalize(normalVec);
    				cubeRigidBody->applyCentralImpulse(btVector3(0.0,0.0,10.0));
  					}
        
        
		     	btTransform trans;
		     	btQuaternion quat;
		     	btScalar m[16];
		     	
		     	leftBumperRigidBody->getMotionState()->getWorldTransform(trans);
					quat.setEuler(1.2, 0.0, 0.0);
					trans.setRotation(quat);
					trans.getOpenGLMatrix(m);
					leftBumperRigidBody->getMotionState()->setWorldTransform(trans);
					leftBumperRigidBody->setMotionState(leftBumperRigidBody->getMotionState());
					leftBumper->model = glm::make_mat4(m);
					
					leftWaitCount = 0;
					dt3 = dt;
					leftUp = true;
  			}
      break;
      
      //Right
      ///////////////////////
      case '>':
        cubeRigidBody->applyCentralImpulse(btVector3(-force,0.0,0.0));
        
        if(true){
        
        	glm::vec3 cubeModel = glm::vec3(cube->model[3]);
  				glm::vec3 rightBumperModel = glm::vec3(rightBumper->model[3]);

  				float diffx = cubeModel.x - rightBumperModel.x;
  				float diffy = cubeModel.y - rightBumperModel.y;
  				float diffz = cubeModel.z - rightBumperModel.z;

  				if ( abs(diffx) <= 1.8 && abs(diffz) <= 1.8){
    				glm::vec3 normalVec = glm::vec3 (diffx, diffy, diffz);
    				normalize(normalVec);
    				cubeRigidBody->applyCentralImpulse(btVector3(0.0,0.0,10.0));
  					}
        
        
		     	btTransform trans;
		     	btQuaternion quat;
		     	btScalar m[16];
		     	
		     	rightBumperRigidBody->getMotionState()->getWorldTransform(trans);
					quat.setEuler(-1.2, 0.0, 0.0);
					trans.setRotation(quat);
					trans.getOpenGLMatrix(m);
					rightBumperRigidBody->getMotionState()->setWorldTransform(trans);
					rightBumperRigidBody->setMotionState(rightBumperRigidBody->getMotionState());
					rightBumper->model = glm::make_mat4(m);
					
					rightWaitCount = 0;
					dt2 = dt;
					rightUp = true;
  			}
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
    
    //Put bumpers back down if need be
    if(dt2 != dt)
    {
    	rightWaitCount++;
    	dt2 = dt;
    }

    if(rightUp && (rightWaitCount > 10))
    {
		  	btTransform trans;
		  	btQuaternion quat;
		   	btScalar m[16];
		     	
		   	rightBumperRigidBody->getMotionState()->getWorldTransform(trans);
				quat.setEuler(0.0, 0.0, 0.0);
				trans.setRotation(quat);
				trans.getOpenGLMatrix(m);
				rightBumperRigidBody->getMotionState()->setWorldTransform(trans);
				rightBumperRigidBody->setMotionState(rightBumperRigidBody->getMotionState());
				rightBumper->model = glm::make_mat4(m);
				rightUp = false;
  		}
  		
  		if(dt3 != dt)
    {
    	leftWaitCount++;
    	dt3 = dt;
    }

    if(leftUp && (leftWaitCount > 10))
    {
		  	btTransform trans;
		  	btQuaternion quat;
		   	btScalar m[16];
		     	
		   	leftBumperRigidBody->getMotionState()->getWorldTransform(trans);
				quat.setEuler(0.0, 0.0, 0.0);
				trans.setRotation(quat);
				trans.getOpenGLMatrix(m);
				leftBumperRigidBody->getMotionState()->setWorldTransform(trans);
				leftBumperRigidBody->setMotionState(leftBumperRigidBody->getMotionState());
				leftBumper->model = glm::make_mat4(m);
				leftUp = false;
  		}

  dynamicsWorld->stepSimulation(dt, 10);
  
  glm::vec3 ballModel = glm::vec3(ball->model[3]);
  glm::vec3 cylinderModel1 = glm::vec3(cylinder1->model[3]);

  float diffx = ballModel.x - cylinderModel1.x;
  float diffy = ballModel.y - cylinderModel1.y;
  float diffz = ballModel.z - cylinderModel1.z;

  if ( abs(diffx) <= 1.8 && abs(diffz) <= 1.8){
    glm::vec3 normalVec = glm::vec3 (diffx, diffy, diffz);
    normalize(normalVec);
    ballRigidBody->applyCentralImpulse(btVector3(normalVec.x, normalVec.y, normalVec.z));
  }

  glm::vec3 cylinderModel2 = glm::vec3(cylinder2->model[3]);

  diffx = ballModel.x - cylinderModel2.x;
  diffy = ballModel.y - cylinderModel2.y;
  diffz = ballModel.z - cylinderModel2.z;

  if ( abs(diffx) <= 1.8 && abs(diffz) <= 1.8){
    glm::vec3 normalVec = glm::vec3 (diffx, diffy, diffz);
    normalize(normalVec);
    ballRigidBody->applyCentralImpulse(btVector3(normalVec.x, normalVec.y, normalVec.z));
  }

  glm::vec3 cylinderModel3 = glm::vec3(cylinder3->model[3]);

  diffx = ballModel.x - cylinderModel3.x;
  diffy = ballModel.y - cylinderModel3.y;
  diffz = ballModel.z - cylinderModel3.z;

  if ( abs(diffx) <= 1.8 && abs(diffz) <= 1.8){
    glm::vec3 normalVec = glm::vec3 (diffx, diffy, diffz);
    normalize(normalVec);
    ballRigidBody->applyCentralImpulse(btVector3(normalVec.x, normalVec.y, normalVec.z));
  }

  btTransform trans;
  btScalar m[16];

  tableRigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  table->model = glm::make_mat4(m);
  
  leftBumperRigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  leftBumper->model = glm::make_mat4(m);
  
  rightBumperRigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  rightBumper->model = glm::make_mat4(m); 
  
  ballRigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  ball->model = glm::make_mat4(m);
  
  cubeRigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  cube->model = glm::make_mat4(m);
  
  cylinder1RigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  cylinder1->model = glm::make_mat4(m);
  
  cylinder2RigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  cylinder2->model = glm::make_mat4(m);
  
  cylinder3RigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  cylinder3->model = glm::make_mat4(m);

  // clean up!
  ballRigidBody->clearForces();
  tableRigidBody->clearForces();
  cubeRigidBody->clearForces();
  cylinder1RigidBody->clearForces();
  cylinder2RigidBody->clearForces();
  cylinder3RigidBody->clearForces();
  leftBumperRigidBody->clearForces();
  rightBumperRigidBody->clearForces();
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
  
  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(leftBumper->GetModel()));
  leftBumper->Render();
  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(rightBumper->GetModel()));
  rightBumper->Render();

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

  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(cylinder1->GetModel()));
  glUniform4f(m_shader->GetUniformLocation("LightPosition"), 0,2,0,0);
  glUniform4f(m_shader->GetUniformLocation("AmbientProduct"), .5,.5,.5,1);
  glUniform4f(m_shader->GetUniformLocation("DiffuseProduct"), cylDiffusex, cylDiffusez, cylDiffusez, 1);
  glUniform4f(m_shader->GetUniformLocation("SpecularProduct"), cylSpecularx, cylSpeculary, cylSpecularz,1);
  glUniform1f(m_shader->GetUniformLocation("Shininess"), 10);
  cylinder1->Render();
  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(cylinder2->GetModel()));
  cylinder2->Render();
  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(cylinder3->GetModel()));
  cylinder3->Render();

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

