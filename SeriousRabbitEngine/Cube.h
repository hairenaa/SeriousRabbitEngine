#pragma once
#include <string>
#include <vector>
#include "Mesh.h"
#include "Material.h"
#include "TextureLoadUtil.h"
#include "TexturePoolSinglton.h"
#include "ConstValues.h"
#include "Camera.h"
#include "GeometryObject.h"

class Cube : public GeometryObject
{
public:
	

	Cube(std::string _name, Shader* _shader, std::vector<Texture> textureVec) :GeometryObject(_name,_shader)
	{
		this->mesh = new Mesh(_name, _shader, this->vertices, GROUP_LEN, this->indices, textureVec);
	}

	Cube(std::string _name, Shader* _shader) :GeometryObject(_name, _shader)
	{
		this->material = new Material(_name, _shader);
		std::vector<Texture> textureVec;
		textureVec.push_back(TexturePoolSinglton::Instance()->CheckAndLoadTexture(DIFF_PATH, TEXTURE_DIFFUSE));
		textureVec.push_back(TexturePoolSinglton::Instance()->CheckAndLoadTexture(SPE_PATH, TEXTURE_SPECULAR));
		this->mesh = new Mesh(_name, _shader, this->vertices, GROUP_LEN, this->indices, textureVec, this->material);
	}

	Cube(std::string _name, Shader* _shader, const std::string _texture_diffuse_path) :GeometryObject(_name, _shader)
	{
		this->material = new Material(_name, _shader);
		std::vector<Texture> textureVec;
		textureVec.push_back(TexturePoolSinglton::Instance()->CheckAndLoadTexture(_texture_diffuse_path, TEXTURE_DIFFUSE));
		textureVec.push_back(TexturePoolSinglton::Instance()->CheckAndLoadTexture(SPE_PATH, TEXTURE_SPECULAR));
		this->mesh = new Mesh(_name, _shader, this->vertices, GROUP_LEN, this->indices, textureVec, this->material);
	}

	Cube(std::string _name, Shader* _shader, const std::string _texture_diffuse_path, const std::string _texture_specular_path) :GeometryObject(_name, _shader)
	{
		this->material = new Material(_name, _shader);
		std::vector<Texture> textureVec;
		textureVec.push_back(TexturePoolSinglton::Instance()->CheckAndLoadTexture(_texture_diffuse_path, TEXTURE_DIFFUSE));
		textureVec.push_back(TexturePoolSinglton::Instance()->CheckAndLoadTexture(_texture_specular_path, TEXTURE_SPECULAR));
		/*for (unsigned int i = 0; i < this->vertices.size(); i++)
		{
			this->vertices[i] = vertices[i] * 1000;
		}*/
		this->mesh = new Mesh(_name, _shader, this->vertices, GROUP_LEN, this->indices, textureVec, this->material);
	}

	//************************************************************************************
	Cube(std::string _name, std::vector<Texture> textureVec) :GeometryObject(_name)
	{

		this->mesh = new Mesh(_name, this->shader, this->vertices, GROUP_LEN, this->indices, textureVec);
	}

	Cube(std::string _name) :GeometryObject(_name)
	{

		this->material = new Material(_name,this->shader);
		std::vector<Texture> textureVec;
		textureVec.push_back(TexturePoolSinglton::Instance()->CheckAndLoadTexture(DIFF_PATH, TEXTURE_DIFFUSE));
		textureVec.push_back(TexturePoolSinglton::Instance()->CheckAndLoadTexture(SPE_PATH, TEXTURE_SPECULAR));
		this->mesh = new Mesh(_name, this->shader, this->vertices, GROUP_LEN, this->indices, textureVec, this->material);
	}

	Cube(std::string _name,const std::string _texture_diffuse_path) :GeometryObject(_name)
	{
		this->material = new Material(_name, this->shader);
		std::vector<Texture> textureVec;
		textureVec.push_back(TexturePoolSinglton::Instance()->CheckAndLoadTexture(_texture_diffuse_path, TEXTURE_DIFFUSE));
		textureVec.push_back(TexturePoolSinglton::Instance()->CheckAndLoadTexture(SPE_PATH, TEXTURE_SPECULAR));
		this->mesh = new Mesh(_name, this->shader, this->vertices, GROUP_LEN, this->indices, textureVec, this->material);
	}

	Cube(std::string _name,  const std::string _texture_diffuse_path, const std::string _texture_specular_path) :GeometryObject(_name)
	{
		this->material = new Material(_name, this->shader);
		std::vector<Texture> textureVec;
		textureVec.push_back(TexturePoolSinglton::Instance()->CheckAndLoadTexture(_texture_diffuse_path, TEXTURE_DIFFUSE));
		textureVec.push_back(TexturePoolSinglton::Instance()->CheckAndLoadTexture(_texture_specular_path, TEXTURE_SPECULAR));
		/*for (unsigned int i = 0; i < this->vertices.size(); i++)
		{
			this->vertices[i] = vertices[i] * 1000;
		}*/
		this->mesh = new Mesh(_name, this->shader, this->vertices, GROUP_LEN, this->indices, textureVec, this->material);
	}


	//*******************************************************************************************


	Cube(std::string _name, Shader* _shader, Camera* _camera,std::vector<Texture> textureVec) :GeometryObject(_name,_shader,_camera)
	{
		
		this->mesh = new Mesh(_name, _shader, this->vertices, GROUP_LEN,this->indices,textureVec);
	}

	Cube(std::string _name,Shader* _shader,Camera* _camera) :GeometryObject(_name, _shader, _camera)
	{
		
		this->material = new Material(_name, _shader);
		std::vector<Texture> textureVec;
		textureVec.push_back(TexturePoolSinglton::Instance()->CheckAndLoadTexture(DIFF_PATH,TEXTURE_DIFFUSE));
		textureVec.push_back(TexturePoolSinglton::Instance()->CheckAndLoadTexture(SPE_PATH, TEXTURE_SPECULAR));
		this->mesh = new Mesh(_name, _shader, this->vertices, GROUP_LEN, this->indices, textureVec, this->material);
	}

	Cube(std::string _name, Shader* _shader, Camera* _camera,const std::string _texture_diffuse_path) :GeometryObject(_name, _shader, _camera)
	{
		this->material = new Material(_name, _shader);
		std::vector<Texture> textureVec;
		textureVec.push_back(TexturePoolSinglton::Instance()->CheckAndLoadTexture(_texture_diffuse_path, TEXTURE_DIFFUSE));
		textureVec.push_back(TexturePoolSinglton::Instance()->CheckAndLoadTexture(SPE_PATH, TEXTURE_SPECULAR));
		this->mesh = new Mesh(_name, _shader, this->vertices, GROUP_LEN, this->indices,textureVec, this->material);
	}

	Cube(std::string _name, Shader* _shader, Camera* _camera, const std::string _texture_diffuse_path, const std::string _texture_specular_path) :GeometryObject(_name, _shader, _camera)
	{
		this->material = new Material(_name, _shader);
		std::vector<Texture> textureVec;
		textureVec.push_back(TexturePoolSinglton::Instance()->CheckAndLoadTexture(_texture_diffuse_path, TEXTURE_DIFFUSE));
		textureVec.push_back(TexturePoolSinglton::Instance()->CheckAndLoadTexture(_texture_specular_path, TEXTURE_SPECULAR));
		/*for (unsigned int i = 0; i < this->vertices.size(); i++)
		{
			this->vertices[i] = vertices[i] * 1000;
		}*/
		this->mesh = new Mesh(_name, _shader, this->vertices, GROUP_LEN, this->indices, textureVec, this->material);
	}

	~Cube()
	{
		if (this->mesh!=nullptr) 
		{
			mesh->Delete<Mesh>(mesh);
		}

		if (this->material != nullptr) 
		{
			material->Delete<Material>(material);
		}
	}

	void Draw() 
	{
		GameObject::Draw();
		PhysicsObject::UpdateBefore();
		this->mesh->Draw();
		
	}
private:
	std::vector<float> vertices = 
	{
	 // |       position    |         normal     |      color    |   uv
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f,0.0f,0.0f, 0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f,0.0f,0.0f, 1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f,0.0f,0.0f, 1.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f,0.0f,0.0f, 1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f,0.0f,0.0f, 0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f,0.0f,0.0f, 0.0f,  0.0f,
												  
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f,0.0f,0.0f, 0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f,0.0f,0.0f, 1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f,0.0f,0.0f, 1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f,0.0f,0.0f, 1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f,0.0f,0.0f, 0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f,0.0f,0.0f, 0.0f,  0.0f,
												 
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f,0.0f,0.0f, 1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f,0.0f,0.0f, 1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f,0.0f,0.0f, 0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f,0.0f,0.0f, 0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f,0.0f,0.0f, 0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f,0.0f,0.0f, 1.0f,  0.0f,
												  
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f,0.0f,0.0f, 1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f,0.0f,0.0f, 1.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f,0.0f,0.0f, 0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f,0.0f,0.0f, 0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f,0.0f,0.0f, 0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f,0.0f,0.0f, 1.0f,  0.0f,
												  
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f,0.0f,0.0f, 0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f,0.0f,0.0f, 1.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 0.0f,0.0f,0.0f, 1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 0.0f,0.0f,0.0f, 1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 0.0f,0.0f,0.0f, 0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f,0.0f,0.0f, 0.0f,  1.0f,
												 
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f,0.0f,0.0f, 0.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f,0.0f,0.0f, 1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 0.0f,0.0f,0.0f, 1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 0.0f,0.0f,0.0f, 1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 0.0f,0.0f,0.0f, 0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f,0.0f,0.0f, 0.0f,  1.0f
		
	};
	std::vector<unsigned int> indices=
	{
		
	};
	
};

