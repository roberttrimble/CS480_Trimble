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
    void Update(unsigned int dt, char keyboardInput, bool newInput, int mouseXlocation, int mouseYlocation);
    void Render(char keyboardInput, bool newInput);

    // Bullet    
    btTriangleMesh *triMesh1;
    btTriangleMesh *triMesh2;
    btTriangleMesh *triMesh3;
    btTriangleMesh *triMesh4;
    btCollisionShape *tableMesh;
		btCollisionShape *ballMesh;
		btCollisionShape *cubeMesh;
		btCollisionShape *cylinder1Mesh;
		btCollisionShape *cylinder2Mesh;
		btCollisionShape *cylinder3Mesh;
		btCollisionShape *topWall;
		
		Shader *m_shader;
    float tableAmbientx = .2, tableAmbienty = .2, tableAmbientz = .2; 
    float cylSpecularx = .05, cylSpeculary = .05, cylSpecularz = .05;
    float cylDiffusex = .05, cylDiffusey = .05, cylDiffusez = .05;
		
  private:
    std::string ErrorString(GLenum error);

    Camera *m_camera;

    GLint m_projectionMatrix;
    GLint m_viewMatrix;
    GLint m_modelMatrix;

    Object *table;
    Object *ball;
    Object *cube;
    Object *cylinder1;
    Object *cylinder2;
    Object *cylinder3;

GLuint Lpos;
    
    //Bullet
    
    btDefaultMotionState *tableMotionState;
    btDefaultMotionState *ballMotionState;
    btDefaultMotionState *cubeMotionState;
    btDefaultMotionState *cylinder1MotionState;
    btDefaultMotionState *cylinder2MotionState;
    btDefaultMotionState *cylinder3MotionState;

    btDefaultMotionState *topWallMotionState;
    
    btRigidBody *tableRigidBody;
    btRigidBody *ballRigidBody;
		btRigidBody *cubeRigidBody;
		btRigidBody *cylinder1RigidBody;
		btRigidBody *cylinder2RigidBody;
		btRigidBody *cylinder3RigidBody;

		btRigidBody *topWallRigidBody;		
		
		btDiscreteDynamicsWorld *dynamicsWorld;
    btBroadphaseInterface* broadphase;
    btDefaultCollisionConfiguration* collisionConfiguration;
    btCollisionDispatcher* dispatcher;
    btSequentialImpulseConstraintSolver* solver;
};

#endif /* GRAPHICS_H */
