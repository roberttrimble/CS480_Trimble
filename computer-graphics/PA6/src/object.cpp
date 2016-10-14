#include "object.h"
//using namespace Magick;


Object::Object(std::string fileInput)
{ 
  // file name 
  const char * fileName; 
  fileName = fileInput.c_str();

  // variables
  Assimp::Importer importer;

  // create and initalalize a scene that contains all of the file data
  const aiScene *myScene = importer.ReadFile(fileName,aiProcess_Triangulate);

  for(unsigned int currentMesh = 0; currentMesh < myScene->mNumMeshes; currentMesh++){

		// create a pointer to the first mesh (only one)
		aiMesh *ai_mesh = myScene->mMeshes[0];  

		// get vertices if number of vertices > 0
		if (ai_mesh->mNumVertices > 0)
		{
		  // loop through vertices
		  for (unsigned int i = 0; i < ai_mesh->mNumVertices; i++)
		  {
		    // creat a 3D vector to hold vertices at ith position
		    aiVector3D ai = ai_mesh->mVertices[i];
		    // create a vec3 to hold the coordiates stored in ai
		    glm::vec3 vec = glm::vec3(ai.x, ai.y, ai.z);

        aiVector3D texture = ai_mesh->mTextureCoords[0][i];
        glm::vec2 tex = glm::vec2(texture.x, texture.y);

		    // initialize a temporary Vertex with vertex coordinates and color
		    Vertex *tempVertex = new Vertex(vec, tex);
		    // push back tempVertex onto Vertices
		    Vertices.push_back(*tempVertex);
		  }
		}

		// get mesh indexes
		// loop through faces
		for (unsigned int j = 0; j < ai_mesh->mNumFaces; j++){
		  // create a face to store the jth face
		  aiFace* face = &ai_mesh->mFaces[j];
		  // if objects are not triangulated
		  if (face->mNumIndices != 3)
		  {   
		    // let user know        
		    std::cout << "Object not trianuglated\n";
		    continue;
		  }
		  // push back face indices onto Indices
		  Indices.push_back(face->mIndices[0]);
		  Indices.push_back(face->mIndices[1]);
		  Indices.push_back(face->mIndices[2]);
		}
	}
;
Magick::InitializeMagick(NULL);
m_Textures.resize(myScene->mNumMaterials);
for (unsigned int i = 0 ; i < myScene->mNumMaterials ; i++) {
  const aiMaterial* pMaterial = myScene->mMaterials[i];

        m_Textures[i] = NULL;
        if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
            aiString Path;

            if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
std::cout << Path.data << std::endl;
                std::string FullPath = Path.data;
                m_Textures[i] = new Texture(GL_TEXTURE_2D, FullPath.c_str());

                if (!m_Textures[i]->Load()) {
                    printf("Error loading texture '%s'\n", FullPath.c_str());
                    delete m_Textures[i];
                    m_Textures[i] = NULL;
                }
            }
        }
      if (!m_Textures[i]) {
          m_Textures[i] = new Texture(GL_TEXTURE_2D, "../models/checker.jpg");
       }
    }

  angle = 0.0f;

  glGenBuffers(1, &VB);
  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);

  glGenBuffers(1, &IB);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * Indices.size(), &Indices[0], GL_STATIC_DRAW);
}

Object::~Object()
{
  Vertices.clear();
  Indices.clear();
}

void Object::Update(unsigned int dt)
{
  angle += dt * M_PI/1000;
  model = glm::rotate(glm::mat4(1.0f), (angle), glm::vec3(0.0, 12.0, 0.0));
}

glm::mat4 Object::GetModel()
{
  return model;
}

void Object::Render()
{
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,TexCoords));

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);

  glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
}
