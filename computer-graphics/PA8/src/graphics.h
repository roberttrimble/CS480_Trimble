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
    void Update(unsigned int dt);
    void Render();
    
    btTriangleMesh *triMesh;
    btCollisionShape *tableMesh;
		btCollisionShape *ballMesh;
		btCollisionShape *cubeMesh;
		btCollisionShape *cylinderMesh;
		
  private:
    std::string ErrorString(GLenum error);

    Camera *m_camera;
    Shader *m_shader;

    GLint m_projectionMatrix;
    GLint m_viewMatrix;
    GLint m_modelMatrix;

		

    Object *table;
    Object *ball;
    Object *cube;
    Object *cylinder;
    
    //Bullet
    
    btDefaultMotionState *tableMotionState;
    btDefaultMotionState *ballMotionState;
    btDefaultMotionState *cubeMotionState;
    btDefaultMotionState *cylinderMotionState;
    
    btRigidBody *tableRigidBody;
    btRigidBody *ballRigidBody;
		btRigidBody *cubeRigidBody;
		btRigidBody *cylinderRigidBody;
		
		
		btDiscreteDynamicsWorld *dynamicsWorld;
    btBroadphaseInterface* broadphase;
    btDefaultCollisionConfiguration* collisionConfiguration;
    btCollisionDispatcher* dispatcher;
    btSequentialImpulseConstraintSolver* solver;
};

#endif /* GRAPHICS_H */
