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

		// bind texture buffer		
    glGenTextures(1, &m_textureObj);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_textureObj);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_pImage->columns(), m_pImage->rows(), -0.5, GL_RGBA, GL_UNSIGNED_BYTE, m_blob.data());
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_textureObj);

    rotationAngle = 0.0f;
		orbitAngle = 0.0f;
}

Object::~Object()
{
  Vertices.clear();
  Indices.clear();
}

////////////////////////////////////////////////////////////////
// UPDATE PLANETS FUNCTION
////////////////////////////////////////////////////////////////
void Object::Update(unsigned int dt, int planetNum, bool initialized)
{

	// Stagger the planets for initialization
	///////////////////////////////
	if (!initialized)
	{
		rotationAngle += dt * M_PI/20000;
		orbitAngle += planetNum * 1000;
		model = (glm::rotate(glm::mat4(1.0f), (orbitAngle), glm::vec3(0.0, 12.0, 0.0)) * glm::translate(glm::mat4(1.0f), glm::vec3(6.0, 0.0, 0.0)))
              * glm::rotate(glm::mat4(1.0f), (rotationAngle), glm::vec3(0.0, 12.0, 0.0));
	}

	switch (planetNum){
		// sun
		//////////////
		case 0:
			// update angle
			rotationAngle += dt * M_PI/20000;
			orbitAngle += dt * M_PI/20000;
			// rotate model
			model = glm::rotate(glm::mat4(1.0f), (rotationAngle), glm::vec3(0.0, 12.0, 5.0));
			// scale sun
			model = glm::scale(model, glm::vec3(2, 2, 2));
		break;

		// mercury
		////////////////
		case 1:
			// update angle
			rotationAngle += dt * M_PI/2000;
			orbitAngle += dt * M_PI/1200;
			// rotate model
			model = (glm::rotate(glm::mat4(1.0f), (orbitAngle), glm::vec3(0.0, 12.0, 0.0)) * glm::translate(glm::mat4(1.0f), glm::vec3(6.0, 0.0, 0.0)))
              * glm::rotate(glm::mat4(1.0f), (rotationAngle), glm::vec3(0.0, 12.0, 0.0));
			// scale model
			model = glm::scale(model, glm::vec3(.18, .18, .18));
		break;

		// venus
		////////////////
		case 2:
			// update angle
			rotationAngle -= dt * M_PI/3000;
			orbitAngle += dt * M_PI/1800;
			// rotate model
			model = (glm::rotate(glm::mat4(1.0f), (orbitAngle), glm::vec3(0.0, 12.0, -0.2)) * glm::translate(glm::mat4(1.0f), glm::vec3(8.0, 0.0, 0.0)))
              * glm::rotate(glm::mat4(1.0f), (rotationAngle), glm::vec3(0.0, 12.0, 0.0));
			// scale model
			model = glm::scale(model, glm::vec3(.25, .25, .25));
		break;

		// earth
		////////////////
		case 3:
			// update angle
			rotationAngle += dt * M_PI/600;
			orbitAngle += dt * M_PI/2400;
			// rotate model
			model = (glm::rotate(glm::mat4(1.0f), (orbitAngle), glm::vec3(0.0, 12.0, 0.6)) * glm::translate(glm::mat4(1.0f), glm::vec3(10.0, 0.0, 0.0)))
              * glm::rotate(glm::mat4(1.0f), (rotationAngle), glm::vec3(0.0, 12.0, 0.0));
			// scale model
			model = glm::scale(model, glm::vec3(.25, .25, .25));
		break;

		// mars
		/////////////////
		case 4:
			// update angle
			rotationAngle += dt * M_PI/620;
			orbitAngle += dt * M_PI/3000;
			// rotate model
			model = (glm::rotate(glm::mat4(1.0f), (orbitAngle), glm::vec3(0.0, 12.0, 0.65)) * glm::translate(glm::mat4(1.0f), glm::vec3(12.0, 0.0, 0.0)))
              * glm::rotate(glm::mat4(1.0f), (rotationAngle), glm::vec3(0.0, 12.0, 0.0));
			// scale model
			model = glm::scale(model, glm::vec3(.2, .2, .2));
		break;

		// jupiter
		//////////////////
		case 5:
			// update angle
			rotationAngle += dt * M_PI/400;
			orbitAngle += dt* M_PI/3600;
			// rotate model
			model = (glm::rotate(glm::mat4(1.0f), (orbitAngle), glm::vec3(0.0, 12.0, 0.0)) * glm::translate(glm::mat4(1.0f), glm::vec3(16.0, 0.0, 0.0)))
              * glm::rotate(glm::mat4(1.0f), (rotationAngle), glm::vec3(0.0, 12.0, 0.0));
			// scale model
			model = glm::scale(model, glm::vec3(1, 1, 1));
		break;

		// saturn and its ring
		////////////////////////
		case 6:
			// update angle
			rotationAngle += dt * M_PI/450;
			orbitAngle += dt * M_PI/4200;
			// rotate model
			model = (glm::rotate(glm::mat4(1.0f), (orbitAngle), glm::vec3(0.0, 12.0, 0.7)) * glm::translate(glm::mat4(1.0f), glm::vec3(24.0, 0.0, 0.0)))
              * glm::rotate(glm::mat4(1.0f), (rotationAngle), glm::vec3(0.0, 12.0, 0.0));
			// scale model
			model = glm::scale(model, glm::vec3(.7, .7, .7));
		break;

		// uranus
		////////////////////
		case 7:
			// update angle
			rotationAngle -= dt * M_PI/550;
			orbitAngle += dt * M_PI/4800;
			// rotate model
			model = (glm::rotate(glm::mat4(1.0f), (orbitAngle), glm::vec3(0.0, 12.0, 0.0)) * glm::translate(glm::mat4(1.0f), glm::vec3(33.0, 0.0, 0.0)))
              * glm::rotate(glm::mat4(1.0f), (rotationAngle), glm::vec3(0.0, 12.0, 0.0));
			// scale model
			model = glm::scale(model, glm::vec3(.5, .5, .5));
		break;

		// neptune
		//////////////////
		case 8:
			// update angle
			rotationAngle += dt * M_PI/525;
			orbitAngle += dt * M_PI/5400;
			// rotate model
			model = (glm::rotate(glm::mat4(1.0f), (orbitAngle), glm::vec3(0.0, 12.0, 0.65)) * glm::translate(glm::mat4(1.0f), glm::vec3(39.0, 0.0, 0.0)))
              * glm::rotate(glm::mat4(1.0f), (rotationAngle), glm::vec3(0.0, 12.0, 0.0));
			// scale model
			model = glm::scale(model, glm::vec3(.5, .5, .5));
		break;

		// pluto
		////////////////
		case 9:
			// update angle
			rotationAngle += dt * M_PI/1000;
			orbitAngle += dt * M_PI/6200;
			// rotate model
			model = (glm::rotate(glm::mat4(1.0f), (orbitAngle), glm::vec3(0.0, 12.0, 1.1)) * glm::translate(glm::mat4(1.0f), glm::vec3(45.0, 0.0, 0.0)))
              * glm::rotate(glm::mat4(1.0f), (rotationAngle), glm::vec3(0.0, 12.0, 0.0));
			// scale model
			model = glm::scale(model, glm::vec3(.15, .15, .15));
		break;

		// stars
		////////////////
		case 10:
			// return model
 			 model = glm::mat4(1.0f);
			// scale model
			model = glm::scale(model, glm::vec3(28, 28, 28));
		break;
	}
}


/////////////////////////////////////////////////////////////////////////////
// UPDATE MOON(s)
/////////////////////////////////////////////////////////////////////////////
void Object::UpdateMoon(glm::mat4 planetModel, unsigned int dt, int planetNum)
{
	//**NOTE**  
	// -sun mercury venus and pluto do not have moons
	// -All others but earch have multiple
	//	but is not yet modified for that
	// -Scaling the moon is relative to the planets size

	switch (planetNum){
		// earth moon
		////////////////
		case 3:
			// update angle
			rotationAngle += dt * M_PI/4800;
			orbitAngle += dt * M_PI/1200;
			// rotate model
			model = planetModel * ((glm::rotate(glm::mat4(1.0f), (orbitAngle), glm::vec3(0.0, 12.0, 0.0)) * glm::translate(glm::mat4(1.0f), glm::vec3(3, 2.0, 0.0))))
              * glm::rotate(glm::mat4(1.0f), (rotationAngle), glm::vec3(0.0, 12.0, 0.0));
			// scale model
			model = glm::scale(model, glm::vec3(.5, .5, .5));
		break;

		// mars moon
		/////////////////
		case 4:
			// update angle
			rotationAngle += dt * M_PI/6400;
			orbitAngle += dt * M_PI/1600;
			// rotate model
			model = planetModel * ((glm::rotate(glm::mat4(1.0f), (orbitAngle), glm::vec3(0.0, 12.0, 0.0)) * glm::translate(glm::mat4(1.0f), glm::vec3(3, 2.0, 0.0))))
              * glm::rotate(glm::mat4(1.0f), (rotationAngle), glm::vec3(0.0, 12.0, 0.0));
			// scale model
			model = glm::scale(model, glm::vec3(.5, .5, .5));
		break;

		// jupiter moon
		//////////////////
		case 5:
			// update angle
			rotationAngle += dt * M_PI/8000;
			orbitAngle += dt * M_PI/2000;
			// rotate model
			model = planetModel * ((glm::rotate(glm::mat4(1.0f), (orbitAngle), glm::vec3(0.0, 12.0, 0.0)) * glm::translate(glm::mat4(1.0f), glm::vec3(3, -2.0, 0.0))))
              * glm::rotate(glm::mat4(1.0f), (rotationAngle), glm::vec3(0.0, 12.0, 0.0));
			// scale model
			model = glm::scale(model, glm::vec3(.5, .5, .5));
		break;

		// saturn moon
		////////////////////////
		case 6:
			// update angle
			rotationAngle += dt * M_PI/9600;
			orbitAngle += dt * M_PI/2400;
			// rotate model
			model = planetModel * ((glm::rotate(glm::mat4(1.0f), (orbitAngle), glm::vec3(0.0, 12.0, 0.0)) * glm::translate(glm::mat4(1.0f), glm::vec3(3.0, 2.0, 0.0)))
          * glm::rotate(glm::mat4(1.0f), (rotationAngle), glm::vec3(0.0, 12.0, 0.0)));
			// scale model
			model = glm::scale(model, glm::vec3(.5, .5, .5));
		break;

		// uranus moon
		////////////////////
		case 7:
			// update angle
			rotationAngle += dt * M_PI/11200;
			orbitAngle += dt * M_PI/2800;
			// rotate model
			model = planetModel * ((glm::rotate(glm::mat4(1.0f), (orbitAngle), glm::vec3(0.0, 12.0, 0.0)) * glm::translate(glm::mat4(1.0f), glm::vec3(4, 1.0, 0.0))))
              * glm::rotate(glm::mat4(1.0f), (rotationAngle), glm::vec3(0.0, 12.0, 0.0));
			// scale model
			model = glm::scale(model, glm::vec3(.5, .5, .5));
		break;

		// neptune moon
		//////////////////
		case 8:
			// update angle
			rotationAngle += dt * M_PI/12800;
			orbitAngle += dt * M_PI/3200;
			// rotate model
			model = planetModel * ((glm::rotate(glm::mat4(1.0f), (orbitAngle), glm::vec3(0.0, 12.0, 0.0)) * glm::translate(glm::mat4(1.0f), glm::vec3(3, -1.0, 0.0))))
              * glm::rotate(glm::mat4(1.0f), (rotationAngle), glm::vec3(0.0, 12.0, 0.0));
			// scale model
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

	// bind vertex buffers
	glGenBuffers(1, &VB);
	glBindBuffer(GL_ARRAY_BUFFER, VB);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);

	// bind indice buffer
	glGenBuffers(1, &IB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * Indices.size(), &Indices[0], GL_STATIC_DRAW);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, m_textureObj);

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

