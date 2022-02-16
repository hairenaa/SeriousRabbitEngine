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

#include "GameObject.h"
#include "TextureLoadUtil.h"
#include "TexturePoolSinglton.h"
#include "ConstValues.h"
#include "PhysicsObject.h"
#include "Camera.h"

class Model:public GameObject,public PhysicsObject
{
public:
	std::vector<Mesh> meshes;
	std::string directory;
	Material* material;

	Model(std::string _name,std::string path, Shader* _shader,Camera* _camera)
		:GameObject(_name,_shader),PhysicsObject(_camera)
	{
		this->material = new Material(_name,_shader);
		loadModel(path);
	};
	~Model()
	{
		if (this->material != NULL) 
		{
			delete this->material;
			this->material = NULL;
		}
	}
	
	void Draw()
	{
		GameObject::Draw();
		PhysicsObject::UpdateBefore();
		for (unsigned int i = 0; i < meshes.size(); i++)
		{
			meshes[i].Draw();
		}
		
	};
	std::vector<Texture> AiMaterialToTexture(aiMaterial *mat, aiTextureType type, TextureType textureType)
	{
		std::vector<Texture> textures;
		for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
		{
			aiString str;
			std::string path;
			mat->GetTexture(type, i, &str);
			path = directory + "\\" + str.C_Str();
			textures.push_back(TexturePoolSinglton::Instance()->CheckAndLoadTexture(path, textureType));
		}
		return textures;

	};
	
private:
	void loadModel(std::string path)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			std::cout << "Assimp error!" << std::endl;
			return;
		}
		std::cout << "import model success!" << std::endl;
		directory = path.substr(0, path.find_last_of('\\'));
		std::cout << directory << std::endl;
		processNode(scene->mRootNode, scene);
	};
	void processNode(aiNode* node, const aiScene* scene)
	{
		//std::cout << node->mName.data << std::endl;
		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* curMesh = scene->mMeshes[node->mMeshes[i]];
			meshes.push_back(processMesh(curMesh, scene));
		}

		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			processNode(node->mChildren[i], scene);

		}
	};
	Mesh processMesh(aiMesh * aimesh, const aiScene * scene)
	{
		std::vector<Vertex> tempVertices;
		std::vector<unsigned int> tempIndicies;
		std::vector<Texture> tempTextures;



		Vertex tempVertex;
		for (unsigned int i = 0; i < aimesh->mNumVertices; i++)
		{
			tempVertex.Position.x = aimesh->mVertices[i].x;
			tempVertex.Position.y = aimesh->mVertices[i].y;
			tempVertex.Position.z = aimesh->mVertices[i].z;

			if (aimesh->mColors[0])
			{
				tempVertex.Color.x = aimesh->mColors[0][i].r;
				tempVertex.Color.y = aimesh->mColors[0][i].g;
				tempVertex.Color.z = aimesh->mColors[0][i].b;
			}
			else
			{
				tempVertex.Color = glm::vec3(0.0f, 0.0f, 0.0f);
				//std::cout << "no vertexColor in this mesh: " << aimesh->mName.C_Str() << std::endl;
			}


			if (aimesh->HasNormals())
			{
				tempVertex.Normal.x = aimesh->mNormals[i].x;
				tempVertex.Normal.y = aimesh->mNormals[i].y;
				tempVertex.Normal.z = aimesh->mNormals[i].z;
			}
			else
			{
				tempVertex.Normal = glm::vec3(0.0f, 0.0f, 0.0f);
			}

			if (aimesh->mTextureCoords[0])
			{
				tempVertex.TexCoord.x = aimesh->mTextureCoords[0][i].x;
				tempVertex.TexCoord.y = aimesh->mTextureCoords[0][i].y;

			}
			else
			{
				tempVertex.TexCoord = glm::vec2(0, 0);
				
			}

			tempVertices.push_back(tempVertex);

		}


		for (unsigned int i = 0; i < aimesh->mNumFaces; i++)
		{

			for (unsigned int j = 0; j < aimesh->mFaces[i].mNumIndices; j++)
			{
				tempIndicies.push_back(aimesh->mFaces[i].mIndices[j]);
			}
		}

		bool hasDiffuseFlag = false;
		bool hasSpecularFlag = false;
		if (aimesh->mMaterialIndex >= 0)
		{
			aiMaterial *material = scene->mMaterials[aimesh->mMaterialIndex];
			std::vector<Texture> diffuseMaps = AiMaterialToTexture(material,
				aiTextureType_DIFFUSE, TEXTURE_DIFFUSE);
			if (!diffuseMaps.empty())
			{
				hasDiffuseFlag = true;
			}
			tempTextures.insert(tempTextures.end(), diffuseMaps.begin(), diffuseMaps.end());
			std::vector<Texture> specularMaps = AiMaterialToTexture(material,
				aiTextureType_SPECULAR, TEXTURE_SPECULAR);
			if (!specularMaps.empty())
			{
				hasSpecularFlag = true;
			}

			tempTextures.insert(tempTextures.end(), specularMaps.begin(), specularMaps.end());
		}

		if (!hasDiffuseFlag)
		{
			std::string diff_path = TEXTURE_DEFAULT_DIFFUSE_PATH;
			std::cout << "no Diffuse Texture in this mesh: " << aimesh->mName.C_Str() << std::endl;
			tempTextures.push_back(TexturePoolSinglton::Instance()->CheckAndLoadTexture(diff_path, TEXTURE_DIFFUSE));
		}

		if (!hasSpecularFlag)
		{
			std::string spe_path = TEXTURE_DEFAULT_SPECULAR_PATH;
			std::cout << "no Specular Texture in this mesh: " << aimesh->mName.C_Str() << std::endl;
			tempTextures.push_back(TexturePoolSinglton::Instance()->CheckAndLoadTexture(spe_path, TEXTURE_SPECULAR));
		}
		Mesh mesh(this->name, shader, tempVertices, tempIndicies, tempTextures, this->material);
		return mesh;

	};
};

