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
    btTriangleMesh *triMesh1;
    btTriangleMesh *triMesh2;
    btTriangleMesh *triMesh3;
    btTriangleMesh *triMesh4;
    btTriangleMesh *triMesh5;
    btTriangleMesh *triMesh6;
    btTriangleMesh *triMesh7;
    btTriangleMesh *triMesh8;
    
////////////////////////////////////////////////////

    btCollisionShape *tableMesh;
		btCollisionShape *ballMesh;
		btCollisionShape *cylinder1Mesh;
		btCollisionShape *cylinder2Mesh;
		btCollisionShape *cylinder3Mesh;
		
		btCollisionShape *leftBumperMesh;
		btCollisionShape *rightBumperMesh;
		
		btCollisionShape *launchPlaneMesh;
		btCollisionShape *plungerMesh;
//////////////////////////////////////////////////////		

		Shader *m_shader;
    float tableAmbientx = -0.3, tableAmbienty = -0.3, tableAmbientz = -0.3; 
    float cylSpecularx = .15, cylSpeculary = .15, cylSpecularz = .15;
    float cylDiffusex = .15, cylDiffusey = .15, cylDiffusez = .15;
		
		btTransform trans;
		btQuaternion quat;
    float diffx = 0;
    float diffy = 0;
    float diffz = 0;

float bumperHit = 0;
  private:
    std::string ErrorString(GLenum error);

    Camera *m_camera;

    GLint m_projectionMatrix;
    GLint m_viewMatrix;
    GLint m_modelMatrix;

    Object *table;
    Object *ball;
    Object *cylinder1;
    Object *cylinder2;
    Object *cylinder3;
    
    Object *leftBumper;
    Object *rightBumper;
    
    Object *plunger;
    
    bool ballLaunched = false;
    
    bool rightUp = false;
    unsigned int dt2;
    int rightWaitCount;
    
    bool leftUp = false;
    unsigned int dt3;
    int leftWaitCount;
    
    float plungerForce = 0;
    float plungerPull = -3;
    
    int liveCount = 2;
    
    //Bullet
    
    btDefaultMotionState *tableMotionState;
    btDefaultMotionState *ballMotionState;
    btDefaultMotionState *cylinder1MotionState;
    btDefaultMotionState *cylinder2MotionState;
    btDefaultMotionState *cylinder3MotionState;
    
    btDefaultMotionState *leftBumperMotionState;
    btDefaultMotionState *rightBumperMotionState;
    
    btDefaultMotionState *launchPlaneMotionState;
    btDefaultMotionState *plungerMotionState;
    
    btRigidBody *tableRigidBody;
    btRigidBody *ballRigidBody;
		btRigidBody *cylinder1RigidBody;
		btRigidBody *cylinder2RigidBody;
		btRigidBody *cylinder3RigidBody;
		
		btRigidBody *leftBumperRigidBody;
		btRigidBody *rightBumperRigidBody;
		
		btRigidBody *launchPlaneRigidBody;
		btRigidBody *plungerRigidBody;		
		
		btDiscreteDynamicsWorld *dynamicsWorld;
    btBroadphaseInterface* broadphase;
    btDefaultCollisionConfiguration* collisionConfiguration;
    btCollisionDispatcher* dispatcher;
    btSequentialImpulseConstraintSolver* solver;
};

#endif /* GRAPHICS_H */
