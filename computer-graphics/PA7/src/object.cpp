#include "object.h"

Object::Object(std::string fileInput, std::string textureFile)
{ 
  // file name 
  const char * fileName; 
  fileName = fileInput.c_str();

  // variables
  Assimp::Importer importer;
  std::string m_fileName;
 	Magick::Image* m_pImage;
  Magick::Blob m_blob;

	// create and initalalize a scene that contains all of the file data
  const aiScene *myScene = importer.ReadFile(fileName,aiProcess_Triangulate);

	// create a pointer to the first mesh (only one)
	aiMesh *ai_mesh = myScene->mMeshes[0];  

	// initialize magick
  Magick::InitializeMagick(NULL);

	// load texture 
  try {
	  m_pImage = new Magick::Image(textureFile);
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

		  // initialize a temporary Vertex with vertex coordinates and color
		  Vertex *tempVertex = new Vertex(vec, tex);
		  // push back tempVertex onto Vertices
		  Vertices.push_back(*tempVertex);
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
		// bind vertex buffers
		glGenBuffers(1, &VB);
		glBindBuffer(GL_ARRAY_BUFFER, VB);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);

		// bind indice buffer
		glGenBuffers(1, &IB);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * Indices.size(), &Indices[0], GL_STATIC_DRAW);

		// bind texture buffer		
    glGenTextures(1, &m_textureObj);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_textureObj);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_pImage->columns(), m_pImage->rows(), -0.5, GL_RGBA, GL_UNSIGNED_BYTE, m_blob.data());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		angle = 0.0f;
}

Object::~Object()
{
  Vertices.clear();
  Indices.clear();
}

void Object::Update(unsigned int dt, int planetNum)
{
	switch (planetNum){
		// sun
		case 0:
			// update angle
			angle += dt * M_PI/1000;
			// rotate model
			model = glm::rotate(glm::mat4(1.0f), (angle), glm::vec3(0.0, 12.0, 3.0));
			// scale for capsule model
			model = glm::scale(model, glm::vec3(2, 2, 2));
		break;

		// mercury
		case 1:
			// update angle
			angle += dt * M_PI/500;
			// rotate model
			model = (glm::rotate(glm::mat4(1.0f), (angle), glm::vec3(0.0, 12.0, 0.0)) * glm::translate(glm::mat4(1.0f), glm::vec3(4.0, 0.0, 0.0)))
              * glm::rotate(glm::mat4(1.0f), (angle), glm::vec3(0.0, 12.0, 0.0));
			// scale for capsule model
			model = glm::scale(model, glm::vec3(.5, .5, .5));
		break;

		// venus
		case 2:
			// update angle
			angle += dt * M_PI/750;
			// rotate model
			model = (glm::rotate(glm::mat4(1.0f), (angle), glm::vec3(0.0, 12.0, 0.0)) * glm::translate(glm::mat4(1.0f), glm::vec3(6.0, 0.0, 0.0)))
              * glm::rotate(glm::mat4(1.0f), (angle), glm::vec3(0.0, 12.0, 0.0));
			// scale for capsule model
			model = glm::scale(model, glm::vec3(.5, .5, .5));
		break;

		// earth
		case 3:
			// update angle
			angle += dt * M_PI/1000;
			// rotate model
			model = (glm::rotate(glm::mat4(1.0f), (angle), glm::vec3(0.0, 12.0, 0.0)) * glm::translate(glm::mat4(1.0f), glm::vec3(8.0, 0.0, 0.0)))
              * glm::rotate(glm::mat4(1.0f), (angle), glm::vec3(0.0, 12.0, 0.0));
			// scale for capsule model
			model = glm::scale(model, glm::vec3(.5, .5, .5));
		break;
	}
}

glm::mat4 Object::GetModel()
{
  return model;
}

void Object::Render()
{
//glActiveTexture(GL_TEXTURE0);
//glBindTexture(GL_TEXTURE_2D, m_textureObj);
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
  glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,TexCoords));

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
  glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
}

