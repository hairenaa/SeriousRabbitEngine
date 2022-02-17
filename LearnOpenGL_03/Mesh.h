#pragma once
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "Shader.h"
#include <iostream>
#include "Material.h"
#include"GameObject.h"
#include "Shader.h"

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec3 Color;
	glm::vec2 TexCoord;
};



enum TextureType
{
	TEXTURE_DIFFUSE,
	TEXTURE_SPECULAR,
	TEXTURE_NORMAL,
	TEXTURE_HEIGHT,
	TEXTURE_SKYBOX
};



struct Texture
{
	unsigned int id;
	TextureType type;
	std::string path;
};


class Mesh:public GameObject
{
public:
	std::string diffusePrefix = FRAGMENT_SHADER_STRUCT_MATERIAL_TEXTURE_DIFFUSE;
	std::string specularPrefix = FRAGMENT_SHADER_STRUCT_MATERIAL_TEXTURE_SPECULAR;
	std::string normalPrefix = FRAGMENT_SHADER_STRUCT_MATERIAL_TEXTURE_NORMAL;
	std::string heightPrefix = FRAGMENT_SHADER_STRUCT_MATERIAL_TEXTURE_HEIGHT;
	std::string SkyBoxName=FRAGMENT_SHADER_VAR_SKYBOX;
	std::string materialName = FRAGMENT_SHADER_VAR_MATERIAL;
	Material* material;
	std::vector<Vertex> vertices;
	std::vector<float> vertices_float;
	std::vector<unsigned int>indices;
	std::vector<Texture> textures;
	int groupLen;

	Mesh(std::string _name, Shader* _shader, std::vector<float> _vertices_array,int _groupLen, std::vector<unsigned int> _indices, std::vector<Texture> _textures, Material* _material)
		:GameObject(_name, _shader) 
	{
		this->groupLen = _groupLen;
		this->textures = _textures;
		this->indices = _indices;
		this->diffusePrefix = materialName + diffusePrefix;
		this->specularPrefix = materialName + specularPrefix;
		this->normalPrefix = materialName + normalPrefix;
		this->heightPrefix = materialName + heightPrefix;
		this->vertices_float = _vertices_array;
		this->material = _material;
		setupMesh();
	}

	
	Mesh(std::string _name, Shader* _shader, std::vector<float> _vertices_array, int _groupLen, std::vector<unsigned int> _indices,std::vector<Texture> _textures)
		:GameObject(_name, _shader)
	{
		this->groupLen = _groupLen;
		this->indices = _indices;
		this->textures = _textures;
		this->diffusePrefix = _name + diffusePrefix;
		this->specularPrefix = _name + specularPrefix;
		this->normalPrefix = _name + normalPrefix;
		this->heightPrefix = _name + heightPrefix;
		this->vertices_float = _vertices_array;
		setupMesh();
	}
	
	Mesh(std::string _name,Shader* _shader,std::vector<Vertex> _vertices, std::vector<unsigned int> _indices, std::vector<Texture> _textures, Material* _material)
		:GameObject(_name,_shader)
	{
		this->textures = _textures;
		this->indices = _indices;
		this->diffusePrefix = materialName + diffusePrefix;
		this->specularPrefix = materialName + specularPrefix;
		this->normalPrefix = materialName + normalPrefix;
		this->heightPrefix = materialName + heightPrefix;
		this->vertices = _vertices;
		this->material = _material;
		setupMesh();
	};
	/*
	Mesh(std::string _name,Shader* _shader, std::vector<Vertex> _vertices, std::vector<unsigned int>_indices, Material* _material)
		:GameObject(_name,_shader)
	{
		this->indices = _indices;
		this->diffusePrefix = _name + diffusePrefix;
		this->specularPrefix = _name + specularPrefix;
		this->normalPrefix = _name + normalPrefix;
		this->heightPrefix = _name + heightPrefix;
		this->vertices = _vertices;
		this->material = _material;
		setupMesh();
		
	};
	*/
	/*
	Mesh(std::string _name,Shader* _shader, std::vector<Vertex> _vertices, Material* _material)
		:GameObject(_name,_shader)
	{
		this->diffusePrefix = _name + diffusePrefix;
		this->specularPrefix = _name + specularPrefix;
		this->normalPrefix = _name + normalPrefix;
		this->heightPrefix = _name + heightPrefix;
		this->vertices = _vertices;
		this->material = _material;
		setupMesh();
	};
	*/
	void Draw()
	{
		unsigned int diffuseNr = 1;
		unsigned int specularNr = 1;
		unsigned int normalNr = 1;
		unsigned int heightNr = 1;

		if (material != nullptr) 
		{
			this->material->Draw();
		}
		
		if (!textures.empty())
		{
			for (unsigned int i = 0; i < textures.size(); i++)
			{
				unsigned int slot = i;
				Texture curTexture = textures[i];
				glActiveTexture(GL_TEXTURE0 + slot);
				std::string re_name;
				if (curTexture.type == TEXTURE_DIFFUSE)
				{
					re_name = diffusePrefix + std::to_string(diffuseNr++);
					glBindTexture(GL_TEXTURE_2D, curTexture.id);
					shader->SetUniform1i(re_name.c_str(), slot);
				}
				else if (curTexture.type == TEXTURE_SPECULAR)
				{
					re_name = specularPrefix + std::to_string(specularNr++);
					glBindTexture(GL_TEXTURE_2D, curTexture.id);
					shader->SetUniform1i(re_name.c_str(), slot);
				}
				else if (curTexture.type == TEXTURE_NORMAL)
				{
					re_name = normalPrefix + std::to_string(normalNr++);
					glBindTexture(GL_TEXTURE_2D, curTexture.id);
					shader->SetUniform1i(re_name.c_str(), slot);
				}
				else if (curTexture.type == TEXTURE_HEIGHT)
				{
					re_name = heightPrefix + std::to_string(heightNr++);
					glBindTexture(GL_TEXTURE_2D, curTexture.id);
					shader->SetUniform1i(re_name.c_str(), slot);
				}
				else if(curTexture.type==TEXTURE_SKYBOX)
				{
					re_name = SkyBoxName;
					glBindTexture(GL_TEXTURE_CUBE_MAP, curTexture.id);
					shader->SetUniform1i(re_name.c_str(), slot);
				}
				//std::cout << name << std::endl;
			}
		}


		glBindVertexArray(VAO);

		if (!indices.empty())
		{
			glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		}
		else
		{
			if (!vertices.empty()) 
			{
				glDrawArrays(GL_TRIANGLES, 0, vertices.size());
			}
			else if(!vertices_float.empty())
			{
				glDrawArrays(GL_TRIANGLES, 0, vertices_float.size()/this->groupLen);
			}
			
		}
		glBindVertexArray(0);
		glActiveTexture(GL_TEXTURE0);

	};
	//static unsigned int TextureIndex;
private:
	unsigned int VAO, VBO, EBO;
	void setupMesh()
	{
		if (vertices.empty()&&vertices_float.empty())
		{
			return;
		}

		

		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		if (!vertices.empty()) 
		{
			glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*vertices.size(), vertices.data(), GL_STATIC_DRAW);
		}
		else if(!vertices_float.empty())
		{
			glBufferData(GL_ARRAY_BUFFER, sizeof(float)*vertices_float.size(), vertices_float.data(), GL_STATIC_DRAW);
		}
		

		if (!indices.empty())
		{
			glGenBuffers(1, &EBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*indices.size(), indices.data(), GL_STATIC_DRAW);
		}

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(0 * sizeof(float)));
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6 * sizeof(float)));
		glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(9 * sizeof(float)));

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glEnableVertexAttribArray(3);

		glBindVertexArray(0);

	};

};

