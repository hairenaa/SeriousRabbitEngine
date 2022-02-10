#pragma once
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "Shader.h"
#include <iostream>
#include "Material.h"

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
};



struct Texture
{
	unsigned int id;
	TextureType type;
	std::string path;
};


class Mesh
{
public:
	const char* diffusePrefix = "material.texture_diffuse_";
	const char* specularPrefix = "material.texture_specular_";
	const char* normalPrefix = "material.texture_normal_";
	const char* heightPrefix = "material.texture_height_";

	Mesh(std::vector<Vertex> _vertices,std::vector<unsigned int>_indices,std::vector<Texture> _textures,Material* _material);
	Mesh(std::vector<Vertex> _vertices, std::vector<unsigned int>_indices, Material* _material);
	Mesh(std::vector<Vertex> _vertices, Material* _material);
	Material* material;
	std::vector<Vertex> vertices; 
	std::vector<unsigned int>indices;
	std::vector<Texture> textures;
	void Draw(Shader* shader);
	//static unsigned int TextureIndex;
private:
	unsigned int VAO, VBO, EBO;
	void setupMesh();

};

