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
		btCollisionShape *cylinderMesh;
		btCollisionShape *leftWall;
		btCollisionShape *rightWall;
		btCollisionShape *backWall;
		btCollisionShape *frontWall;
		btCollisionShape *topWall;
		
		Shader *m_shader;
    float tableAmbientx = .2, tableAmbienty = .2, tableAmbientz = .2; 
    float cylSpecularx = .05, cylSpeculary = .05, cylSpecularz = .05;
    float cylDiffusex = .05, cylDiffusey = .05, cylDiffusez = .05;
		
  private:
    std::string ErrorString(GLenum error);

    Camera *m_camera;
    //Shader *m_shader;

    GLint m_projectionMatrix;
    GLint m_viewMatrix;
    GLint m_modelMatrix;

    Object *table;
    Object *ball;
    Object *cube;
    Object *cylinder;

GLuint Lpos;
    
    //Bullet
    
    btDefaultMotionState *tableMotionState;
    btDefaultMotionState *ballMotionState;
    btDefaultMotionState *cubeMotionState;
    btDefaultMotionState *cylinderMotionState;

    btDefaultMotionState *leftWallMotionState;
    btDefaultMotionState *rightWallMotionState;
    btDefaultMotionState *backWallMotionState;
    btDefaultMotionState *frontWallMotionState;
    btDefaultMotionState *topWallMotionState;
    
    btRigidBody *tableRigidBody;
    btRigidBody *ballRigidBody;
		btRigidBody *cubeRigidBody;
		btRigidBody *cylinderRigidBody;

		btRigidBody *leftWallRigidBody;
		btRigidBody *rightWallRigidBody;
		btRigidBody *backWallRigidBody;
		btRigidBody *frontWallRigidBody;
		btRigidBody *topWallRigidBody;		
		
		btDiscreteDynamicsWorld *dynamicsWorld;
    btBroadphaseInterface* broadphase;
    btDefaultCollisionConfiguration* collisionConfiguration;
    btCollisionDispatcher* dispatcher;
    btSequentialImpulseConstraintSolver* solver;
};

#endif /* GRAPHICS_H */
