#pragma once
#include <string>
#include <vector>
#include "Mesh.h"
#include "Material.h"
#include "TextureLoadUtil.h"
#include "TexturePoolSinglton.h"
#include "ConstValues.h"

class Cube : public GameObject
{
public:
	Mesh* mesh;
	Material* material;
	const int GROUP_LEN = 11;
	const std::string DIFF_PATH = TEXTURE_DEFAULT_DIFFUSE_PATH;
	const std::string SPE_PATH = TEXTURE_DEFAULT_SPECULAR_PATH;
	Cube(std::string _name,Shader* _shader) :GameObject(_name,_shader)
	{
		//this->vertices.push_back()
		this->material = new Material(_name, _shader);
		std::vector<Texture> textureVec;
		textureVec.push_back(TexturePoolSinglton::Instance()->CheckAndLoadTexture(DIFF_PATH,TEXTURE_DIFFUSE));
		textureVec.push_back(TexturePoolSinglton::Instance()->CheckAndLoadTexture(SPE_PATH, TEXTURE_SPECULAR));
		this->mesh = new Mesh(_name, _shader, this->vertices, GROUP_LEN, this->indices, textureVec, this->material);
	}

	Cube(std::string _name, Shader* _shader,const std::string _texture_diffuse_path) :GameObject(_name, _shader)
	{
		this->material = new Material(_name, _shader);
		std::vector<Texture> textureVec;
		textureVec.push_back(TexturePoolSinglton::Instance()->CheckAndLoadTexture(_texture_diffuse_path, TEXTURE_DIFFUSE));
		textureVec.push_back(TexturePoolSinglton::Instance()->CheckAndLoadTexture(SPE_PATH, TEXTURE_SPECULAR));
		this->mesh = new Mesh(_name, _shader, this->vertices, GROUP_LEN, this->indices,textureVec, this->material);
	}

	Cube(std::string _name, Shader* _shader, const std::string _texture_diffuse_path, const std::string _texture_specular_path) :GameObject(_name, _shader)
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
		if (this->mesh!=NULL) 
		{
			delete this->mesh;
			this->mesh = NULL;
		}

		if (this->material != NULL) 
		{
			delete this->material;
			this->material = NULL;
		}
	}

	void Draw() 
	{
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

