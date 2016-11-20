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
    void Update(unsigned int dt, char keyboardInput, bool newInput);
    void Render(char keyboardInput, bool newInput);

    // Bullet    
    btTriangleMesh *triMesh1;
    btTriangleMesh *triMesh2;
    btTriangleMesh *triMesh5;
    btTriangleMesh *triMesh6;
    
    btCollisionShape *tableMesh;
		btCollisionShape *ballMesh;
		btCollisionShape *cylinder1Mesh;
		btCollisionShape *cylinder2Mesh;
		btCollisionShape *cylinder3Mesh;
		
		btCollisionShape *leftBumperMesh;
		btCollisionShape *rightBumperMesh;
		
		btCollisionShape *launchPlaneMesh;
		
		Shader *m_shader;
    float tableAmbientx = .2, tableAmbienty = .2, tableAmbientz = .2; 
    float cylSpecularx = .05, cylSpeculary = .05, cylSpecularz = .05;
    float cylDiffusex = .05, cylDiffusey = .05, cylDiffusez = .05;
		
		btTransform trans;
		btQuaternion quat;
    float diffx = 0;
    float diffy = 0;
    float diffz = 0;
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
    
    bool ballLaunched = false;
    
    bool rightUp = false;
    unsigned int dt2;
    int rightWaitCount;
    
    bool leftUp = false;
    unsigned int dt3;
    int leftWaitCount;

GLuint Lpos;
    
    //Bullet
    
    btDefaultMotionState *tableMotionState;
    btDefaultMotionState *ballMotionState;
    btDefaultMotionState *cylinder1MotionState;
    btDefaultMotionState *cylinder2MotionState;
    btDefaultMotionState *cylinder3MotionState;
    
    btDefaultMotionState *leftBumperMotionState;
    btDefaultMotionState *rightBumperMotionState;
    
    btDefaultMotionState *launchPlaneMotionState;
    
    btRigidBody *tableRigidBody;
    btRigidBody *ballRigidBody;
		btRigidBody *cylinder1RigidBody;
		btRigidBody *cylinder2RigidBody;
		btRigidBody *cylinder3RigidBody;
		
		btRigidBody *leftBumperRigidBody;
		btRigidBody *rightBumperRigidBody;
		
		btRigidBody *launchPlaneRigidBody;		
		
		btDiscreteDynamicsWorld *dynamicsWorld;
    btBroadphaseInterface* broadphase;
    btDefaultCollisionConfiguration* collisionConfiguration;
    btCollisionDispatcher* dispatcher;
    btSequentialImpulseConstraintSolver* solver;
};

#endif /* GRAPHICS_H */