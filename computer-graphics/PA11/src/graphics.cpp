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

	dynamicsWorld->removeRigidBody(backPlaneRigidBody);
	delete backPlaneRigidBody->getMotionState();
	delete backPlaneRigidBody;

	dynamicsWorld->removeRigidBody(frontPlaneRigidBody);
	delete frontPlaneRigidBody->getMotionState();
	delete frontPlaneRigidBody;

	dynamicsWorld->removeRigidBody(rightPlaneRigidBody);
	delete rightPlaneRigidBody->getMotionState();
	delete rightPlaneRigidBody;

  dynamicsWorld->removeRigidBody(leftPlaneRigidBody);
	delete leftPlaneRigidBody->getMotionState();
	delete leftPlaneRigidBody;

	for (int i = 0; i < numBalls; i++)
	{
		dynamicsWorld->removeRigidBody(ballRigidBody[i]);
		delete ballRigidBody[i]->getMotionState();
		delete ballRigidBody[i];
	}

  dynamicsWorld->removeRigidBody(tableRigidBody);
  delete tableRigidBody->getMotionState();
  delete tableRigidBody;

  delete backPlaneMesh;
  delete frontPlaneMesh;
  delete rightPlaneMesh;
  delete leftPlaneMesh;

	for (int i = 0; i < numBalls; i++)
	{
		delete ballMesh[i];
  	delete ball[i];
  	delete ballTriMesh[i];
	}

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
  dynamicsWorld->setGravity(btVector3(0, -1.5, 0));


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
  table = new Object("../models/JezzBoard2.obj", triMesh1);
  tableMesh = new btBvhTriangleMeshShape(triMesh1, true);
  
  tableMotionState = NULL;
  tableMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 1, 0)));
  
  btRigidBody::btRigidBodyConstructionInfo tableRigidBodyCI(0, tableMotionState, tableMesh, btVector3(0, 0, 0));
  tableRigidBody = new btRigidBody(tableRigidBodyCI);

  tableRigidBody->setActivationState(DISABLE_DEACTIVATION);
    
  dynamicsWorld->addRigidBody(tableRigidBody);
  
  
/////////////////////////////////////////////////////////////////////////////

  //Create Ball 1
  ///////////////////////////////////
  ballTriMesh[0] = new btTriangleMesh();
  ball[0] = new Object("../models/ball2.obj", ballTriMesh[0]);
  ballMesh[0] = new btSphereShape(ballSize);
  
  ballMotionState[0] = NULL;
  ballMotionState[0] = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 1.15, 0)));

  //we need the inertia of the sphere and we need to calculate it
  btVector3 sphereInertia(0, 0, 0);
  ballMesh[0]->calculateLocalInertia(mass, sphereInertia);

  btRigidBody::btRigidBodyConstructionInfo ballRigidBodyCI0(mass, ballMotionState[0], ballMesh[0], sphereInertia);
  ballRigidBody[0] = new btRigidBody(ballRigidBodyCI0);

  ballRigidBody[0]->setActivationState(DISABLE_DEACTIVATION);
  
  ballRigidBody[0]->setLinearFactor(btVector3(1,0,1));
    
  dynamicsWorld->addRigidBody(ballRigidBody[0]);

  //Create Ball 2
  /////////////////////////////////
  ballTriMesh[1] = new btTriangleMesh();
  ball[1] = new Object("../models/ball2.obj", ballTriMesh[1]);
  ballMesh[1] = new btSphereShape(ballSize);
  
  ballMotionState[1] = NULL;
  ballMotionState[1] = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(3, 1.15, 0)));

  //we need the inertia of the sphere and we need to calculate it
  ballMesh[1]->calculateLocalInertia(mass, sphereInertia);

  btRigidBody::btRigidBodyConstructionInfo ballRigidBodyCI1(mass, ballMotionState[1], ballMesh[1], sphereInertia);
  ballRigidBody[1] = new btRigidBody(ballRigidBodyCI1);

  ballRigidBody[1]->setActivationState(DISABLE_DEACTIVATION);
  
  ballRigidBody[1]->setLinearFactor(btVector3(1,0,1));
    
  dynamicsWorld->addRigidBody(ballRigidBody[1]);
  
  //Create Ball 3
  //////////////////////////////////
  ballTriMesh[2] = new btTriangleMesh();
  ball[2] = new Object("../models/ball2.obj", ballTriMesh[2]);
  ballMesh[2] = new btSphereShape(ballSize);
  
  ballMotionState[2] = NULL;
  ballMotionState[2] = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-3, 1.15, 0)));

  //we need the inertia of the sphere and we need to calculate it
  ballMesh[2]->calculateLocalInertia(mass, sphereInertia);

  btRigidBody::btRigidBodyConstructionInfo ballRigidBodyCI2(mass, ballMotionState[2], ballMesh[2], sphereInertia);
  ballRigidBody[2] = new btRigidBody(ballRigidBodyCI2);
  
  ballRigidBody[2]->setLinearFactor(btVector3(1,0,1));

  ballRigidBody[2]->setActivationState(DISABLE_DEACTIVATION);
  
  
  //Create Ball 4
  ////////////////////////////////////
  ballTriMesh[3] = new btTriangleMesh();
  ball[3] = new Object("../models/ball2.obj", ballTriMesh[3]);
  ballMesh[3] = new btSphereShape(ballSize);
  
  ballMotionState[3] = NULL;
  ballMotionState[3] = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 1.15, 3)));

  //we need the inertia of the sphere and we need to calculate it
  ballMesh[3]->calculateLocalInertia(mass, sphereInertia);

  btRigidBody::btRigidBodyConstructionInfo ballRigidBodyCI3(mass, ballMotionState[3], ballMesh[3], sphereInertia);
  ballRigidBody[3] = new btRigidBody(ballRigidBodyCI3);
  
  ballRigidBody[3]->setLinearFactor(btVector3(1,0,1));

  ballRigidBody[3]->setActivationState(DISABLE_DEACTIVATION);
  
  //Create Ball 5
  //////////////////////////////////
  ballTriMesh[4] = new btTriangleMesh();
  ball[4] = new Object("../models/ball2.obj", ballTriMesh[4]);
  ballMesh[4] = new btSphereShape(ballSize);
  
  ballMotionState[4] = NULL;
  ballMotionState[4] = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 1.15, -3)));

  //we need the inertia of the sphere and we need to calculate it
  ballMesh[4]->calculateLocalInertia(mass, sphereInertia);

  btRigidBody::btRigidBodyConstructionInfo ballRigidBodyCI4(mass, ballMotionState[4], ballMesh[4], sphereInertia);
  ballRigidBody[4] = new btRigidBody(ballRigidBodyCI4);
  
  ballRigidBody[4]->setLinearFactor(btVector3(1,0,1));

  ballRigidBody[4]->setActivationState(DISABLE_DEACTIVATION);
  

/////////////////////////////////////////////////////////////////////////////
  
  leftPlaneMesh = new btStaticPlaneShape(btVector3(-1, 0, 0), 1);
 	leftPlaneMotionState = NULL;
 	leftPlaneMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(25, 0, 0)));
 
 	btRigidBody::btRigidBodyConstructionInfo leftPlaneRigidBodyCI(0, leftPlaneMotionState, leftPlaneMesh, btVector3(0, 0, 0));
 	leftPlaneRigidBody = new btRigidBody(leftPlaneRigidBodyCI);

 	leftPlaneRigidBody->setActivationState(DISABLE_DEACTIVATION);
    
 	dynamicsWorld->addRigidBody(leftPlaneRigidBody);

////////////////////////////////////////////////////////////////////////////

  rightPlaneMesh = new btStaticPlaneShape(btVector3(1, 0, 0), 1);
 	rightPlaneMotionState = NULL;
 	rightPlaneMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-25, 0, 0)));
 
 	btRigidBody::btRigidBodyConstructionInfo rightPlaneRigidBodyCI(0, rightPlaneMotionState, rightPlaneMesh, btVector3(0, 0, 0));
 	rightPlaneRigidBody = new btRigidBody(rightPlaneRigidBodyCI);

 	rightPlaneRigidBody->setActivationState(DISABLE_DEACTIVATION);
    
 	dynamicsWorld->addRigidBody(rightPlaneRigidBody);

////////////////////////////////////////////////////////////////////////////

  frontPlaneMesh = new btStaticPlaneShape(btVector3(0, 0, 1), 1);
 	frontPlaneMotionState = NULL;
 	frontPlaneMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, -25)));
 
 	btRigidBody::btRigidBodyConstructionInfo frontPlaneRigidBodyCI(0, frontPlaneMotionState, frontPlaneMesh, btVector3(0, 0, 0));
 	frontPlaneRigidBody = new btRigidBody(frontPlaneRigidBodyCI);

 	frontPlaneRigidBody->setActivationState(DISABLE_DEACTIVATION);
    
 	dynamicsWorld->addRigidBody(frontPlaneRigidBody);

////////////////////////////////////////////////////////////////////////////

  backPlaneMesh = new btStaticPlaneShape(btVector3(0, 0, -1), 1);
 	backPlaneMotionState = NULL;
 	backPlaneMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 25)));
 
 	btRigidBody::btRigidBodyConstructionInfo backPlaneRigidBodyCI(0, backPlaneMotionState, backPlaneMesh, btVector3(0, 0, 0));
 	backPlaneRigidBody = new btRigidBody(backPlaneRigidBodyCI);

 	backPlaneRigidBody->setActivationState(DISABLE_DEACTIVATION);
    
 	dynamicsWorld->addRigidBody(backPlaneRigidBody);

////////////////////////////////////////////////////////////////////////////


	glm::vec3 temp = glm::vec3(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < numBalls; i++)
		PrevBallModel[i] = temp;

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
  glm::vec3 ballModel[numBalls];
  for(int i = 0; i < numBalls; i++)
  {
  	ballModel[i] = glm::vec3(ball[i]->model[3]);
  }
  
  btScalar m[16];
  btTransform trans;


 if (newInput == true)
  {
    switch (keyboardInput)
    {
      //Left
      /////////////////////////////
      case '<':
				ballRigidBody[0]->applyCentralImpulse(btVector3(force,0.0,0.0));

      break;
      
      //Right
      ///////////////////////
      case '>':
				ballRigidBody[0]->applyCentralImpulse(btVector3(-force,0.0,0.0));
  				

      break;
        
      //Up/forward
      ///////////////////////
      case '^':
        ballRigidBody[0]->applyCentralImpulse(btVector3(0.0,0.0,force));
        
        
      break;   
      //Down/backwards
      ///////////////////////
      case 'v':
      	ballRigidBody[0]->applyCentralImpulse(btVector3(0.0,0.0,-force));
      	
      	
      break;
      //scatter balls
      ////////////////
      case 'q':
		    if (numBalls == 2)
		    {
		    	ballRigidBody[0]->applyCentralImpulse(btVector3(force*5 ,0.0,-force*5));
		    	ballRigidBody[1]->applyCentralImpulse(btVector3(-force*5,0.0,force*5));
		    }
		    if (numBalls == 3)
		    {
		    	ballRigidBody[0]->applyCentralImpulse(btVector3(force*5 ,0.0,-force*5));
		    	ballRigidBody[1]->applyCentralImpulse(btVector3(-force*5,0.0,force*5));
		    	ballRigidBody[2]->applyCentralImpulse(btVector3(force*5,0.0,-force*5));
		    }
		    if (numBalls == 4)
		    {
		    	ballRigidBody[0]->applyCentralImpulse(btVector3(force*5 ,0.0,-force*5));
		    	ballRigidBody[1]->applyCentralImpulse(btVector3(-force*5,0.0,force*5));
		    	ballRigidBody[2]->applyCentralImpulse(btVector3(force*5,0.0,-force*5));
		    	ballRigidBody[3]->applyCentralImpulse(btVector3(-force*5,0.0,-force*5));
		    }
		    if (numBalls == 5)
		    {
		    	ballRigidBody[0]->applyCentralImpulse(btVector3(force*5 ,0.0,-force*5));
		    	ballRigidBody[1]->applyCentralImpulse(btVector3(-force*5,0.0,force*5));
		    	ballRigidBody[2]->applyCentralImpulse(btVector3(force*5,0.0,-force*5));
		    	ballRigidBody[3]->applyCentralImpulse(btVector3(-force*5,0.0,-force*5));
		    	ballRigidBody[4]->applyCentralImpulse(btVector3(force*5,0.0,force*5));
		    }
      	
      	roundStarted = true;
      	
      break;
      //Launch the ball
      ///////////////////////
      case 'b':
      	if (numBalls < 5)
      	{
      		numBalls++;
      		dynamicsWorld->addRigidBody(ballRigidBody[numBalls - 1]);
      		
      	}
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
    	m_camera->UpdateCamera(0.0f ,25.0f , 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
    }
    else
    {
    	m_camera->UpdateCamera(0.0f ,15.0f , -16.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    }


////////////////////////////////////////////////////////////////////////////////////////////////

  dynamicsWorld->stepSimulation(dt, 10);

	for (int currentBall = 0; currentBall < numBalls; currentBall++)
	{
	
		//Maintain min speed
		////////////////////////////
		btVector3 v = ballRigidBody[currentBall]->getLinearVelocity();
		btScalar currentSpeed = v.length();
		if (currentSpeed < minBallSpeed && roundStarted == true)
		{
			v = v/currentSpeed;
			v = v*minBallSpeed;
			ballRigidBody[currentBall]->setLinearVelocity(v);
		}
		/////////////////////////////////////
	
		diffx[currentBall] = (ballModel[currentBall].x - PrevBallModel[currentBall].x);
		diffy[currentBall] = (ballModel[currentBall].y - PrevBallModel[currentBall].y);
		diffz[currentBall] = (ballModel[currentBall].z - PrevBallModel[currentBall].z);
		

		if ( ballModel[currentBall].x > ball[currentBall]->leftBound){
		
		  //glm::vec3 normalVec = glm::vec3 (ballModel.x , ballModel.y , ballModel.z);
		  //normalize(normalVec);
		  
		  if (diffz[currentBall] >= 0)
		  	ballRigidBody[currentBall]->applyCentralImpulse(btVector3( -force, 0, force ));
		  else
		  	ballRigidBody[currentBall]->applyCentralImpulse(btVector3( -force, 0, -force ));
		}
		if ( ballModel[currentBall].x < ball[currentBall]->rightBound){
		
		  //glm::vec3 normalVec = glm::vec3 (ballModel.x , ballModel.y , ballModel.z);
		  //normalize(normalVec);
		  
		  if (diffz[currentBall] >= 0)
		  	ballRigidBody[currentBall]->applyCentralImpulse(btVector3( force, 0, force ));
		  else
		  	ballRigidBody[currentBall]->applyCentralImpulse(btVector3( force, 0, -force ));
		}
		if ( ballModel[currentBall].z > ball[currentBall]->upperBound){
		
		  //glm::vec3 normalVec = glm::vec3 (ballModel.x , ballModel.y , ballModel.z);
		  //normalize(normalVec);
		  
		  if (diffx[currentBall] >= 0)
		  	ballRigidBody[currentBall]->applyCentralImpulse(btVector3( force, 0, -force ));
		  else
		  	ballRigidBody[currentBall]->applyCentralImpulse(btVector3( -force, 0, -force ));
		}
		if ( ballModel[currentBall].z < ball[currentBall]->lowerBound){

		  //glm::vec3 normalVec = glm::vec3 (ballModel.x , ballModel.y , ballModel.z);
		  //normalize(normalVec);
		  
		  if (diffx[currentBall] >= 0)
		  	ballRigidBody[currentBall]->applyCentralImpulse(btVector3( force, 0, force ));
		  else
		  	ballRigidBody[currentBall]->applyCentralImpulse(btVector3( -force, 0, force ));
		}
		
		
	}
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
  

  tableRigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  table->model = glm::make_mat4(m);
  
  for (int i = 0; i < numBalls; i++)
  {
		ballRigidBody[i]->getMotionState()->getWorldTransform(trans);
		trans.getOpenGLMatrix(m);
		ball[i]->model = glm::make_mat4(m);
	}
	
	
	//printText2D("Hello", 10, 10, 20);
	
	
	
	
  for (int i = 0; i < numBalls; i++)
  {
  	PrevBallModel[i].x = ballModel[i].x;
  	PrevBallModel[i].y = ballModel[i].y;
  	PrevBallModel[i].z = ballModel[i].z;
	}
	
	// clean up!
  //ballRigidBody->clearForces();
	
  return true;
}

void Graphics::Render(char keyboardInput, bool newInput)
{
  //glm::vec3 ballModel = glm::vec3(ball->model[3]);

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

	for (int i = 0; i < numBalls; i++)
  {
		glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(ball[i]->GetModel()));
		ball[i]->Render();
 	}

  
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

