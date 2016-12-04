#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <iostream>
using namespace std;

#include "graphics_headers.h"
#include "camera.h"
#include "shader.h"
#include "object.h"
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
    btTriangleMesh *triMesh2;
    
////////////////////////////////////////////////////

    btCollisionShape *tableMesh;
		btCollisionShape *ballMesh;
		btStaticPlaneShape *leftPlaneMesh;
		btStaticPlaneShape *rightPlaneMesh;
		btStaticPlaneShape *frontPlaneMesh;
		btStaticPlaneShape *backPlaneMesh;

//////////////////////////////////////////////////////		

		Shader *m_shader;
    float tableAmbientx = .5, tableAmbienty = .5, tableAmbientz = .5; 
		
		btTransform trans;
		btQuaternion quat;
    float diffx = 0;
    float diffy = 0;
    float diffz = 0;
		
		bool camera = false;
  private:
    std::string ErrorString(GLenum error);

    Camera *m_camera;

    GLint m_projectionMatrix;
    GLint m_viewMatrix;
    GLint m_modelMatrix;

    Object *table;
    Object *ball;
    Object *stars;
    
    glm::vec3 PrevBallModel = glm::vec3(0.0f,0.0f,0.0f);
    
    //Bullet
    btDefaultMotionState *leftPlaneMotionState;
    btDefaultMotionState *rightPlaneMotionState;
    btDefaultMotionState *frontPlaneMotionState;
    btDefaultMotionState *backPlaneMotionState;

    btDefaultMotionState *tableMotionState;
    btDefaultMotionState *ballMotionState;
    
    btRigidBody *tableRigidBody;
    btRigidBody *ballRigidBody;
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
