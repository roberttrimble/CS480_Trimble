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

	for (int i = 0; i < numBalls; i++)
	{
		dynamicsWorld->removeRigidBody(ballRigidBody[i]);
		delete ballRigidBody[i]->getMotionState();
		delete ballRigidBody[i];
	}

  dynamicsWorld->removeRigidBody(tableRigidBody);
  delete tableRigidBody->getMotionState();
  delete tableRigidBody;

	for (int i = 0; i < numBalls; i++)
	{
		delete ballMesh[i];
  	delete ball[i];
	}

  delete tableMesh;
  delete table;
  delete triMesh;

  delete stars;

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
  stars = new Object("../models/planet.obj");  
  stars->model = glm::scale(stars->model, glm::vec3(28, 28, 28));
  
  cursor = new Object("../models/jezzBallArrow_v2.obj");
  cursor->model = (glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 1.5, 0.0)));

  //wall = new Object("../models/wall_v3.obj");
  //wall->model = (glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 1.0, 0.0)));

  //Create Table
  triMesh = new btTriangleMesh();
  table = new Object("../models/JezzBoard2.obj", triMesh);
  tableMesh = new btBvhTriangleMeshShape(triMesh, true);
  
  tableMotionState = NULL;
  tableMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 1, 0)));
  
  btRigidBody::btRigidBodyConstructionInfo tableRigidBodyCI(0, tableMotionState, tableMesh, btVector3(0, 0, 0));
  tableRigidBody = new btRigidBody(tableRigidBodyCI);

  tableRigidBody->setActivationState(DISABLE_DEACTIVATION);
    
  dynamicsWorld->addRigidBody(tableRigidBody);
  
  
/////////////////////////////////////////////////////////////////////////////

  //Create Ball 1
  ///////////////////////////////////
  ball[0] = new Object("../models/ball2.obj");
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
  ball[1] = new Object("../models/ball2.obj");
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
  ball[2] = new Object("../models/ball2.obj");
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
  ball[3] = new Object("../models/ball2.obj");
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
  ball[4] = new Object("../models/ball2.obj");
  ballMesh[4] = new btSphereShape(ballSize);
  
  ballMotionState[4] = NULL;
  ballMotionState[4] = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 1.15, -3)));

  //we need the inertia of the sphere and we need to calculate it
  ballMesh[4]->calculateLocalInertia(mass, sphereInertia);

  btRigidBody::btRigidBodyConstructionInfo ballRigidBodyCI4(mass, ballMotionState[4], ballMesh[4], sphereInertia);
  ballRigidBody[4] = new btRigidBody(ballRigidBodyCI4);
  
  ballRigidBody[4]->setLinearFactor(btVector3(1,0,1));

  ballRigidBody[4]->setActivationState(DISABLE_DEACTIVATION);

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
  //launch the balls to start
	if(!roundStarted)
	{
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
	}

	float angle = M_PI/2;
	 if (newInput == true)
		{
		  switch (keyboardInput)
		  {
		    //Left
		    /////////////////////////////
		    case '<':
					if(wallMaking == false)
		    	{
				  	if(!cursorVertical && cursor_x < 13){
		          cursor_x += 1;
				  		cursor->model = (glm::translate(glm::mat4(1.0f), glm::vec3(cursor_x, 1.5, cursor_y)));
				  		cursor->model =	 glm::rotate(cursor->model, angle, glm::vec3(0.0, 12.0, 0.0));
				  	}
				  	else if(cursor_x < 13){
		          cursor_x += 1;
							cursor->model = (glm::translate(glm::mat4(1.0f), glm::vec3(cursor_x, 1.5, cursor_y)));
		        }
          }
		    break;
		    
		    //Right
		    ///////////////////////
		    case '>':
					if(wallMaking == false)
		    	{
						if(!cursorVertical && cursor_x > -13){
		          cursor_x -= 1;
				  		cursor->model = (glm::translate(glm::mat4(1.0f), glm::vec3(cursor_x, 1.5, cursor_y)));
				  		cursor->model =	 glm::rotate(cursor->model, angle, glm::vec3(0.0, 12.0, 0.0));
				  	}
				  	else if(cursor_x > -13){
		          cursor_x -= 1;
							cursor->model = (glm::translate(glm::mat4(1.0f), glm::vec3(cursor_x, 1.5, cursor_y)));
						}
					}
		    break;
		      
		    //Up
		    ///////////////////////
		    case '^':    
		      if(wallMaking == false)
		    	{
				    if(!cursorVertical && cursor_y < 7){
		          cursor_y += 1;
				  		cursor->model = (glm::translate(glm::mat4(1.0f), glm::vec3(cursor_x, 1.5, cursor_y)));
				  		cursor->model =	 glm::rotate(cursor->model, angle, glm::vec3(0.0, 12.0, 0.0));
				  	}
		        else if(cursor_y < 7){
		          cursor_y += 1;
							cursor->model = (glm::translate(glm::mat4(1.0f), glm::vec3(cursor_x, 1.5, cursor_y)));
		        }
		      }
		      
		      
		    break;   
		    //Down
		    ///////////////////////
		    case 'v':
		    	if(wallMaking == false)
		    	{
				  	if(!cursorVertical && cursor_y > -7){
		          cursor_y -= 1;
				  		cursor->model = (glm::translate(glm::mat4(1.0f), glm::vec3(cursor_x, 1.5, cursor_y)));
				  		cursor->model =	 glm::rotate(cursor->model, angle, glm::vec3(0.0, 12.0, 0.0));
				  	}
		        else if(cursor_y > -7){
		          cursor_y -= 1;
							cursor->model = (glm::translate(glm::mat4(1.0f), glm::vec3(cursor_x, 1.5, cursor_y)));
		        }
          }
		    break;

		    //turn cursor
		    ////////////////
		    case '_':
		    	if(wallMaking == false)
		    	{
				  	cursor->model = glm::rotate(cursor->model, angle, glm::vec3(0.0, 12.0, 0.0));
		    		cursorVertical = !cursorVertical;
		    	}
		    break;
		    //Launch the ball
		    ///////////////////////
		    case 'n':
		    	if(wallMaking == false)
		    	{
				  	if (numWalls < 300)
				  	{
							wall[numWalls][0] = new Object("../models/wall_v3.obj");
							wall[numWalls][0]->model = (glm::translate(glm::mat4(1.0f), glm::vec3(cursor_x, 1.0, cursor_y)));
								if(cursorVertical)
							wall[numWalls][0]->model = glm::rotate(wall[numWalls][0]->model, angle, glm::vec3(0.0, 12.0, 0.0));
						
						numWalls++;
						wallMaking = true;
				  	}
		    	}
		    break;
		    
		    case 'b':
		    	if (numBalls < 5)
		    	{
		    	
		    		//Object *wall[50][40];
		    		for (int i = 0; i < 50; i++)
		    		{
		    			for (int j = 0; j < 40; j++)
		    			{
		    				wall[i][j] = NULL;
		    			}
		    		}
		    		
		    		for (int i = 0; i < numBalls; i++)
		    		{
		    			ball[i]->upperBound = 7;
		    			ball[i]->lowerBound = -7;
		    			ball[i]->leftBound = 13;
		    			ball[i]->rightBound = -13;
		    		}
		    	
		    	
		    	
		    		numBalls++;
		    		dynamicsWorld->addRigidBody(ballRigidBody[numBalls - 1]);
		    		
		    			
				  	ballRigidBody[0]->getMotionState()->getWorldTransform(trans);
						trans.setOrigin(btVector3(0.0f, 1.15f, 0.0f));
						ballRigidBody[0]->getMotionState()->setWorldTransform(trans);
						ballRigidBody[0]->setMotionState(ballRigidBody[0]->getMotionState());
						ball[0]->model = glm::make_mat4(m);
						
						ballRigidBody[1]->getMotionState()->getWorldTransform(trans);
						trans.setOrigin(btVector3(3.0f, 1.15f, 0.0f));
						ballRigidBody[1]->getMotionState()->setWorldTransform(trans);
						ballRigidBody[1]->setMotionState(ballRigidBody[1]->getMotionState());
						ball[1]->model = glm::make_mat4(m);
						
						ballRigidBody[2]->getMotionState()->getWorldTransform(trans);
						trans.setOrigin(btVector3(-3.0f, 1.15f, 0.0f));
						ballRigidBody[2]->getMotionState()->setWorldTransform(trans);
						ballRigidBody[2]->setMotionState(ballRigidBody[2]->getMotionState());
						ball[2]->model = glm::make_mat4(m);
						
						ballRigidBody[3]->getMotionState()->getWorldTransform(trans);
						trans.setOrigin(btVector3(0.0f, 1.15f, 3.0f));
						ballRigidBody[3]->getMotionState()->setWorldTransform(trans);
						ballRigidBody[3]->setMotionState(ballRigidBody[3]->getMotionState());
						ball[3]->model = glm::make_mat4(m);
						
						ballRigidBody[4]->getMotionState()->getWorldTransform(trans);
						trans.setOrigin(btVector3(0.0f, 1.15f, -3.0f));
						ballRigidBody[4]->getMotionState()->setWorldTransform(trans);
						ballRigidBody[4]->setMotionState(ballRigidBody[4]->getMotionState());
						ball[4]->model = glm::make_mat4(m);
		    		
		    		
		    		roundStarted = false;
		    	}
		    break;
		    //toggle camera
		    //////////////////
		    case 'c':
		    	camera = !camera;
		    break;
		  	}
		  }
		  
		  if (!camera)
    	{
    		m_camera->UpdateCamera(0.0f ,25.0f , 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
    	}
    	else
    	{
    		m_camera->UpdateCamera(0.0f ,15.0f , -16.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    	}
    	
    	
///////////////////////////////////////////////////////////////////////////////////////
	//Get delay time
	if(waitTime != dt)
    {
    	waitCount++;
    	waitTime = dt;
    }


	//Build vertical walls
	///////////////////////////
			if(cursorVertical && wallMaking == true)
			{
				  	if(waitCount > 8)
				  	{
				  		float stopTop = 8;
				  		float stopBottom = -8;
				  		
				  		for(unsigned int i = 0; i < wallLocationY.size(); i++)
				  		{
				  			if(cursor_y < wallLocationY[i])
				  				stopTop = wallLocationY[i];
				  				
				  			if(cursor_y > wallLocationY[i])
				  				stopBottom = wallLocationY[i];
				  		}
				  	
				  	
				  	
				  		if(cursor_y - wallOffset >= stopBottom && cursor_y + wallOffset <= stopTop)
				  		{
				  			wall[numWalls-1][wallCount] = new Object("../models/wall_v4.obj");
				  			wall[numWalls-1][wallCount]->model = (glm::translate(glm::mat4(1.0f), glm::vec3(cursor_x, 1.0, cursor_y - wallOffset)));
				  			wall[numWalls-1][wallCount]->model = glm::rotate(wall[numWalls-1][wallCount]->model, angle, glm::vec3(0.0, 12.0, 0.0));
				  			
				  			wallLength[numWalls-1]++;
				  			wallCount++;
				  			
				  			wall[numWalls-1][wallCount] = new Object("../models/wall_v4.obj");
				  			wall[numWalls-1][wallCount]->model = (glm::translate(glm::mat4(1.0f), glm::vec3(cursor_x, 1.0, cursor_y + wallOffset)));
				  			wall[numWalls-1][wallCount]->model = glm::rotate(wall[numWalls-1][wallCount]->model, angle, glm::vec3(0.0, 12.0, 0.0));
				  			
				  			wallLength[numWalls-1]++;
				  			wallCount++;
				  			wallOffset++;
				  		}
				  		else if(cursor_y - wallOffset >= stopBottom)
				  		{
				  			wall[numWalls-1][wallCount] = new Object("../models/wall_v3.obj");
				  			wall[numWalls-1][wallCount]->model = (glm::translate(glm::mat4(1.0f), glm::vec3(cursor_x, 1.0, cursor_y - wallOffset)));
				  			wall[numWalls-1][wallCount]->model = glm::rotate(wall[numWalls-1][wallCount]->model, angle, glm::vec3(0.0, 12.0, 0.0));
				  			
				  			wallLength[numWalls-1]++;
				  			wallCount++;
				  			wallOffset++;
				  		}
				  		else if(cursor_y + wallOffset <= stopTop)
				  		{
				  			wall[numWalls-1][wallCount] = new Object("../models/wall_v3.obj");
				  			wall[numWalls-1][wallCount]->model = (glm::translate(glm::mat4(1.0f), glm::vec3(cursor_x, 1.0, cursor_y + wallOffset)));
				  			wall[numWalls-1][wallCount]->model = glm::rotate(wall[numWalls-1][wallCount]->model, angle, glm::vec3(0.0, 12.0, 0.0));
				  			
				  			wallLength[numWalls-1]++;
				  			wallCount++;
				  			wallOffset++;
				  		}
				  		else
				  		{
				  			wallMaking = false;
				  			wallCount = 1;
				  			wallOffset = 1;
				  			
				  			wallLocationX.push_back(cursor_x);
				  			//wallLocationX.push_back(stopTop);
				  			//wallLocationX.push_back();
				  			
				  			for(int currentBall = 0; currentBall < numBalls; currentBall++)
				  			{
				  				if(ballModel[currentBall].x > cursor_x && ball[currentBall]->rightBound < cursor_x 
				  						&& ballModel[currentBall].z < stopTop && ballModel[currentBall].z > stopBottom)
				  				{
				  					ball[currentBall]->rightBound = cursor_x+1.25;
				  				}
				  				else if(ballModel[currentBall].x < cursor_x && ball[currentBall]->leftBound > cursor_x
				  						&& ballModel[currentBall].z < stopTop && ballModel[currentBall].z > stopBottom)
				  				{
				  					ball[currentBall]->leftBound = cursor_x-1.25;
				  				}
				  			}
				  			
				  		}
				  	waitCount = 0;
				  	}
				  }
	
	//Build horizontal walls
	///////////////////////////
			if(!cursorVertical && wallMaking == true)
				  {
				  	
				  	if(waitCount > 8)
				  	{
				  	
				  		float stopLeft = 14;
				  		float stopRight = -14;
				  		
				  		for(unsigned int i = 0; i < wallLocationX.size(); i++)
				  		{
				  			if(cursor_x < wallLocationX[i])
				  				stopLeft = wallLocationX[i];
				  				
				  			if(cursor_x > wallLocationX[i])
				  				stopRight = wallLocationX[i];
				  		}
				  	
				  	
				  		if(cursor_x - wallOffset >= stopRight && cursor_x + wallOffset <= stopLeft)
				  		{
				  			wall[numWalls-1][wallCount] = new Object("../models/wall_v4.obj");
				  			wall[numWalls-1][wallCount]->model = (glm::translate(glm::mat4(1.0f), glm::vec3(cursor_x - wallOffset, 1.0, cursor_y)));
				  			
				  			wallLength[numWalls-1]++;
				  			wallCount++;
				  			
				  			wall[numWalls-1][wallCount] = new Object("../models/wall_v4.obj");
				  			wall[numWalls-1][wallCount]->model = (glm::translate(glm::mat4(1.0f), glm::vec3(cursor_x + wallOffset, 1.0, cursor_y)));
				  			
				  			wallLength[numWalls-1]++;
				  			wallCount++;
				  			wallOffset++;
				  		}
				  		else if(cursor_x - wallOffset >= stopRight)
				  		{
				  			wall[numWalls-1][wallCount] = new Object("../models/wall_v3.obj");
				  			wall[numWalls-1][wallCount]->model = (glm::translate(glm::mat4(1.0f), glm::vec3(cursor_x - wallOffset, 1.0, cursor_y)));
				  			
				  			wallLength[numWalls-1]++;
				  			wallCount++;
				  			wallOffset++;
				  		}
				  		else if(cursor_x + wallOffset <= stopLeft)
				  		{
				  			wall[numWalls-1][wallCount] = new Object("../models/wall_v3.obj");
				  			wall[numWalls-1][wallCount]->model = (glm::translate(glm::mat4(1.0f), glm::vec3(cursor_x + wallOffset, 1.0, cursor_y)));
				  			
				  			wallLength[numWalls-1]++;
				  			wallCount++;
				  			wallOffset++;
				  		}
				  		else
				  		{
				  			wallMaking = false;
								wallCount = 1;
								wallOffset = 1;
								
								wallLocationY.push_back(cursor_y);
								
								for(int currentBall = 0; currentBall < numBalls; currentBall++)
				  			{
				  				if(ballModel[currentBall].z > cursor_y && ball[currentBall]->lowerBound < cursor_y
				  						&& ballModel[currentBall].x < stopLeft && ballModel[currentBall].x > stopRight)
				  				{
				  					ball[currentBall]->lowerBound = cursor_y+1.25;
				  				}
				  				else if(ballModel[currentBall].z < cursor_y && ball[currentBall]->upperBound > cursor_y
				  						&& ballModel[currentBall].x < stopLeft && ballModel[currentBall].x > stopRight)
				  				{
				  					ball[currentBall]->upperBound = cursor_y-1.25;
				  				}
				  			}
								
				  		}
				  	waitCount = 0;
				  	}
				  }

////////////////////////////////////////////////////////////////////////////////////////////////

  dynamicsWorld->stepSimulation(dt, 10);

	for (int currentBall = 0; currentBall < numBalls; currentBall++)
	{
	
		//Maintain min speed
		////////////////////////////
		btVector3 v = ballRigidBody[currentBall]->getLinearVelocity();
		btScalar currentSpeed = v.length();
		if (/*currentSpeed < minBallSpeed &&*/ roundStarted == true)
		{
			v = v/currentSpeed;
			v = v*ballSpeed;
			ballRigidBody[currentBall]->setLinearVelocity(v);
		}
		/////////////////////////////////////
	
		diffx[currentBall] = (ballModel[currentBall].x - PrevBallModel[currentBall].x);
		diffy[currentBall] = (ballModel[currentBall].y - PrevBallModel[currentBall].y);
		diffz[currentBall] = (ballModel[currentBall].z - PrevBallModel[currentBall].z);
		

		if ( ballModel[currentBall].x > ball[currentBall]->leftBound){
	
		  if (diffz[currentBall] >= 0)
		  	ballRigidBody[currentBall]->applyCentralImpulse(btVector3( -force, 0, force ));
		  else
		  	ballRigidBody[currentBall]->applyCentralImpulse(btVector3( -force, 0, -force ));
		  	
		}
		if ( ballModel[currentBall].x < ball[currentBall]->rightBound){
		
		  if (diffz[currentBall] >= 0)
		  	ballRigidBody[currentBall]->applyCentralImpulse(btVector3( force, 0, force ));
		  else
		  	ballRigidBody[currentBall]->applyCentralImpulse(btVector3( force, 0, -force ));
		  	
		}
		if ( ballModel[currentBall].z > ball[currentBall]->upperBound){
		 
		  if (diffx[currentBall] >= 0)
		  	ballRigidBody[currentBall]->applyCentralImpulse(btVector3( force, 0, -force ));
		  else
		  	ballRigidBody[currentBall]->applyCentralImpulse(btVector3( -force, 0, -force ));
		  	
		}
		if ( ballModel[currentBall].z < ball[currentBall]->lowerBound){

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
  
  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(cursor->GetModel()));
  cursor->Render();

	for(int i = 0; i < numWalls; i++)
	{
		for(int j = 0; j < wallLength[i]; j++)
		{
			glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(wall[i][j]->GetModel()));
			wall[i][j]->Render();
		}
	}

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

