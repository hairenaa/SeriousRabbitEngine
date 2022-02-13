#pragma once
#include <string>
#include <vector>
#include "Mesh.h"
#include "Material.h"
#include "TextureLoadUtil.h"

class Cube : public GameObject
{
public:
	Mesh* mesh;
	Material* material;
	const int GROUP_LEN = 11;
	Cube(std::string _name,Shader* _shader) :GameObject(_name,_shader)
	{
		//this->vertices.push_back()
		this->material = new Material(_name, _shader);
		this->mesh = new Mesh(_name, _shader,this->vertices, GROUP_LEN,this->indices, this->material);
	}

	Cube(std::string _name, Shader* _shader,const std::string _texture_path,TextureType _type) :GameObject(_name, _shader)
	{
		this->material = new Material(_name, _shader);
		std::vector<Texture> textureVec;
		Texture texture;
		unsigned int id= TextureLoadUtil::LoadImageToGpu(_texture_path.c_str());
		texture.id = id;
		texture.path = _texture_path;
		texture.type = _type;
		textureVec.push_back(texture);
		this->mesh = new Mesh(_name, _shader, this->vertices, GROUP_LEN, this->indices,textureVec, this->material);
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
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f,1.0f,1.0f, 0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f,0.0f,1.0f, 1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f,1.0f,0.0f, 1.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f,0.0f,0.0f, 1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f,1.0f,1.0f, 0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f,0.0f,1.0f, 0.0f,  0.0f,
												  
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 1.0f,1.0f,1.0f, 0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 1.0f,0.0f,1.0f, 1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 1.0f,1.0f,0.0f, 1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 1.0f,0.0f,0.0f, 1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f,1.0f,1.0f, 0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 1.0f,0.0f,1.0f, 0.0f,  0.0f,
												  
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 1.0f,1.0f,1.0f, 1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 1.0f,0.0f,1.0f, 1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 1.0f,1.0f,0.0f, 0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 1.0f,0.0f,0.0f, 0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f,1.0f,1.0f, 0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 1.0f,0.0f,1.0f, 1.0f,  0.0f,
												 
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 1.0f,1.0f,1.0f, 1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 1.0f,0.0f,1.0f, 1.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 1.0f,1.0f,0.0f, 0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 1.0f,0.0f,0.0f, 0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f,1.0f,1.0f, 0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 1.0f,0.0f,1.0f, 1.0f,  0.0f,
												  
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 1.0f,1.0f,1.0f, 0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 1.0f,0.0f,1.0f, 1.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.0f,1.0f,0.0f, 1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.0f,0.0f,0.0f, 1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 0.0f,1.0f,1.0f, 0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 1.0f,0.0f,1.0f, 0.0f,  1.0f,
												  
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 1.0f,1.0f,1.0f, 0.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 1.0f,0.0f,1.0f, 1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 1.0f,1.0f,0.0f, 1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 1.0f,0.0f,0.0f, 1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 0.0f,1.0f,1.0f, 0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 1.0f,0.0f,1.0f, 0.0f,  1.0f
		
	};
	std::vector<unsigned int> indices=
	{
		
	};
	
};

