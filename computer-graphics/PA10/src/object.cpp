#include "object.h"

Object::Object(std::string fileInput, btTriangleMesh *objMesh)
{ 
  // file name 
  const char * fileName; 
  fileName = fileInput.c_str();

  // variables
  Assimp::Importer importer;
  std::string m_fileName;
	aiString Path;

	// create and initalalize a scene that contains all of the file data
  const aiScene *myScene = importer.ReadFile(fileName,aiProcess_Triangulate);

	// create a pointer to the first mesh (only one)
	aiMesh *ai_mesh = myScene->mMeshes[0];  

	// initialize magick
  Magick::InitializeMagick(NULL);

	// create a pointer to the first material
	const aiMaterial* pMaterial = myScene->mMaterials[1];
	
	// get texture (initialize Path)
	pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &Path, NULL, NULL, NULL, NULL, NULL);

	// load texture 
  try {
	  m_pImage = new Magick::Image(Path.C_Str());
    m_pImage->write(&m_blob, "RGBA");
	}
  catch (Magick::Error& Error) {
    std::cout << "Error loading texture '" << fileName << "': " << Error.what() << std::endl;
  }

	// get vertices if number of vertices > 0
	if (ai_mesh->mNumVertices > 0)
	{
		// loop through vertices
	  for (unsigned int i = 0; i < ai_mesh->mNumVertices; i++)
	  {
	  	// create a 3D vector to hold vertices at ith position
		  aiVector3D ai = ai_mesh->mVertices[i];
		  // create a vec3 to hold the coordiates stored in ai
		  glm::vec3 vec = glm::vec3(ai.x, ai.y, ai.z);
			// create a 3D vector to hold texture coords
		  aiVector3D texture = ai_mesh->mTextureCoords[0][i];
			//create a vec2 to hold the texture coordiates stored in texture
		  glm::vec2 tex = glm::vec2(texture.x, texture.y);

      // normals
      glm::vec3 norm;
      // if vertex has normals set them to vec3 norm 
      if (ai_mesh->HasNormals()){
        aiVector3D normal = ai_mesh->mNormals[i];
        norm = glm::vec3(normal.x, normal.y, normal.z);
      }
      // else set normals to 0
      else {
        norm = glm::vec3(0.0, 0.0, 0.0);
      } 
        
		  // initialize a temporary Vertex with vertex, texture and normal coordinates.
		  Vertex *tempVertex = new Vertex(vec, tex, norm);
		  // push back tempVertex onto Vertices
		  Vertices.push_back(*tempVertex);
		}

		// get mesh indexes
		// loop through faces
		for (unsigned int j = 0; j < ai_mesh->mNumFaces; j++)
		{
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
		
		
		// Get faces for bullet
		btVector3 triArray[3];
		for (unsigned int k = 0; k < ai_mesh->mNumFaces; k++)
		{
			aiFace* face = &ai_mesh->mFaces[k];
			
			for (unsigned int l = 0; l < 3; l++)
			{
				aiVector3D position = ai_mesh->mVertices[face->mIndices[l]];
				triArray[l] = btVector3(position.x, position.y, position.z);
			}
			
			objMesh->addTriangle(triArray[0], triArray[1], triArray[2]);
		}
		
	}

		// bind texture buffer		
    glGenTextures(1, &m_textureObj);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_textureObj);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_pImage->columns(), m_pImage->rows(), -0.5, GL_RGBA, GL_UNSIGNED_BYTE, m_blob.data());
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_textureObj);

		angle = 0.0f;
		
		m_pImage = NULL;
		delete m_pImage;
}

Object::~Object()
{
  Vertices.clear();
  Indices.clear();
}

glm::mat4 Object::GetModel()
{
  return model;
}

void Object::Render()
{
	// bind vertex buffers
	glGenBuffers(1, &VB);
	glBindBuffer(GL_ARRAY_BUFFER, VB);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);

	// bind indice buffer
	glGenBuffers(1, &IB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * Indices.size(), &Indices[0], GL_STATIC_DRAW);

	// bind indice buffer
	glGenBuffers(1, &normal);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, normal);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, m_textureObj);

//glEnable(GL_LIGHTING);

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);

  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
  glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,TexCoords));
  glVertexAttribPointer( 2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);

  glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(2);
}

