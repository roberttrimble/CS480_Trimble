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
    btTriangleMesh *triMesh0; 
    btTriangleMesh *triMesh1;
    btTriangleMesh *ballTriMesh[5];
    
////////////////////////////////////////////////////

    btCollisionShape *tableMesh;
		btCollisionShape *ballMesh[5];
		btStaticPlaneShape *leftPlaneMesh;
		btStaticPlaneShape *rightPlaneMesh;
		btStaticPlaneShape *frontPlaneMesh;
		btStaticPlaneShape *backPlaneMesh;

//////////////////////////////////////////////////////		

		Shader *m_shader;
    float tableAmbientx = .5, tableAmbienty = .5, tableAmbientz = .5; 
		
		btTransform trans;
		btQuaternion quat;
    float diffx[5] = {0, 0, 0, 0, 0};
    float diffy[5] = {0, 0, 0, 0, 0};
    float diffz[5] = {0, 0, 0, 0, 0};
		
		bool camera = false;
		
		int numBalls = 2;
		
  private:
    std::string ErrorString(GLenum error);
    
    btScalar mass = 1; //mass for balls
		float force = 0.33; //for off wall bounce
		float ballSize = 0.425; //radius of ball

    Camera *m_camera;

    GLint m_projectionMatrix;
    GLint m_viewMatrix;
    GLint m_modelMatrix;

    Object *table;
    Object *ball[5];

    Object *stars;
    
    glm::vec3 PrevBallModel[5];
    
    
    //Bullet
    btDefaultMotionState *leftPlaneMotionState;
    btDefaultMotionState *rightPlaneMotionState;
    btDefaultMotionState *frontPlaneMotionState;
    btDefaultMotionState *backPlaneMotionState;

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
