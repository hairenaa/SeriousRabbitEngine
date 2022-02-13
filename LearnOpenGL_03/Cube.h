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
		std::vector<Texture> textureVec;
		Texture texture;
		unsigned int id = TextureLoadUtil::LoadImageToGpu("texture_default_diffuse.png");
		texture.id = id;
		texture.path = "ProjectDir:texture_default_diffuse.png";
		texture.type = TEXTURE_DIFFUSE;
		textureVec.push_back(texture);
		Texture texture1;
		unsigned int id1 = TextureLoadUtil::LoadImageToGpu("texture_default_specular.png");
		texture1.id = id1;
		texture1.path = "ProjectDir:texture_default_specular.png";
		texture1.type = TEXTURE_SPECULAR;
		textureVec.push_back(texture1);
		this->mesh = new Mesh(_name, _shader, this->vertices, GROUP_LEN, this->indices, textureVec, this->material);
	}

	Cube(std::string _name, Shader* _shader,const std::string _texture_diffuse_path) :GameObject(_name, _shader)
	{
		this->material = new Material(_name, _shader);
		std::vector<Texture> textureVec;
		Texture texture;
		unsigned int id= TextureLoadUtil::LoadImageToGpu(_texture_diffuse_path.c_str());
		texture.id = id;
		texture.path = _texture_diffuse_path;
		texture.type = TEXTURE_DIFFUSE;
		textureVec.push_back(texture);
		Texture texture1;
		unsigned int id1 = TextureLoadUtil::LoadImageToGpu("texture_default_specular.png");
		texture1.id = id1;
		texture1.path = "ProjectDir:texture_default_specular.png";
		texture1.type = TEXTURE_SPECULAR;
		textureVec.push_back(texture1);
		this->mesh = new Mesh(_name, _shader, this->vertices, GROUP_LEN, this->indices,textureVec, this->material);
	}

	Cube(std::string _name, Shader* _shader, const std::string _texture_diffuse_path, const std::string _texture_specular_path) :GameObject(_name, _shader)
	{
		this->material = new Material(_name, _shader);
		std::vector<Texture> textureVec;
		Texture texture;
		unsigned int id = TextureLoadUtil::LoadImageToGpu(_texture_diffuse_path.c_str());
		texture.id = id;
		texture.path = _texture_diffuse_path;
		texture.type = TEXTURE_DIFFUSE;
		textureVec.push_back(texture);
		Texture texture1;
		unsigned int id1 = TextureLoadUtil::LoadImageToGpu(_texture_specular_path.c_str());
		texture1.id = id1;
		texture1.path = _texture_specular_path;
		texture1.type = TEXTURE_SPECULAR;
		textureVec.push_back(texture1);
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

