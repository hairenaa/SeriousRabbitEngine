#pragma once



#include<vector>
#include<string>
#include "Mesh.h"
#include<iostream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Shader.h"
#include "Material.h"

class Model
{
public:
	Model(std::string path, Shader* _shader);
	Model(std::string path, Shader* _shader,Material* _material);
	std::vector<Mesh> meshes;
	Shader* shader;
	std::string directory;
	std::vector<Texture> loadedTextures;
	Material* material;
	void Draw();
	std::vector<Texture> AiMaterialToTexture(aiMaterial *mat, aiTextureType type, TextureType textureType);
	unsigned int LoadImageToGpu(const char* path);
private:
	void loadModel(std::string path);
	void processNode(aiNode* node,const aiScene* scene);
	Mesh processMesh(aiMesh* aimesh, const aiScene* scene);
};

