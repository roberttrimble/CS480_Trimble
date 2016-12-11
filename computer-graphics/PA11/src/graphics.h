#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <iostream>
using namespace std;

#include "graphics_headers.h"
#include "camera.h"
#include "shader.h"
#include "object.h"
//#include "text2D.h"
#include <btBulletDynamicsCommon.h>

class Graphics
{
  public:
    Graphics();
    ~Graphics();
    bool Initialize(int width, int height);
    bool Update(unsigned int dt, char keyboardInput, bool newInput);
    void Render(char keyboardInput, bool newInput);

    // Bullet   
    btTriangleMesh *triMesh;

    
////////////////////////////////////////////////////

    btCollisionShape *tableMesh;
		btCollisionShape *ballMesh[5];

//////////////////////////////////////////////////////		

		Shader *m_shader;
    float tableAmbientx = .5, tableAmbienty = .5, tableAmbientz = .5; 
		
		btTransform trans;
		btQuaternion quat;
    float diffx[5] = {0, 0, 0, 0, 0};
    float diffy[5] = {0, 0, 0, 0, 0};
    float diffz[5] = {0, 0, 0, 0, 0};
		
		bool camera = false;
		
		bool roundStarted = false;
		
		int numBalls = 2;
		float ballSpeed = 1.25;
		
		int numWalls = 0;
		int wallLength[50] = {0};
		bool wallMaking = false;
		
		
		
  private:
    std::string ErrorString(GLenum error);
    
    btScalar mass = 1; //mass for balls
		float force = 1; //for off wall bounce
		float ballSize = 0.425; //radius of ball
		
		float cursor_x = 0.0;
		float cursor_y = 0.0;
		bool cursorVertical = true;

    Camera *m_camera;

    GLint m_projectionMatrix;
    GLint m_viewMatrix;
    GLint m_modelMatrix;

    Object *table;
    Object *ball[5];
    Object *cursor;
    
    Object *wall[50][40];
    std::vector<float> wallLocationX;
    std::vector<float> wallLocationY;
    unsigned int waitTime;
    unsigned int waitCount = 0;
    unsigned int wallCount = 1;
    unsigned int wallOffset = 1;

    Object *stars;
    
    glm::vec3 PrevBallModel[5];
    
    
    //Bullet
    btDefaultMotionState *tableMotionState;
    btDefaultMotionState *ballMotionState[5];
    
    btRigidBody *tableRigidBody;

    btRigidBody *ballRigidBody[5];

		btRigidBody *leftPlaneRigidBody;	
		btRigidBody *rightPlaneRigidBody;
		btRigidBody *frontPlaneRigidBody;
		btRigidBody *backPlaneRigidBody;	

		btDiscreteDynamicsWorld *dynamicsWorld;
    btBroadphaseInterface* broadphase;
    btDefaultCollisionConfiguration* collisionConfiguration;
    btCollisionDispatcher* dispatcher;
    btSequentialImpulseConstraintSolver* solver;
};

#endif /* GRAPHICS_H */
