#pragma once
#include <glad/glad.h>
#include<GLFW/glfw3.h>
#include "DefaultGameObject.h"
#include "Cube.h"
#include <string>
#include <vector>
#include "Shader.h"
#include "Camera.h"
#include "TexturePoolSinglton.h"
class SkyBox :public DefaultGameObject
{
public:
	Cube* cube;


	SkyBox(std::string name, Shader* shader, std::string dir) :DefaultGameObject(name, shader)
	{
		std::vector<Texture> textureVec;
		std::vector<std::string> skyPathes;
		TextureLoadUtil::GetDirFilesPathes(dir, skyPathes);
		Texture tex = TexturePoolSinglton::Instance()->CheckAndLoadSkyTexture(skyPathes, TEXTURE_SKYBOX);
		textureVec.push_back(tex);
		cube = new Cube(name, shader, textureVec);
	}
	//************************************************************************
	SkyBox(std::string name, std::string dir) :DefaultGameObject(name)
	{
		std::vector<Texture> textureVec;
		std::vector<std::string> skyPathes;
		TextureLoadUtil::GetDirFilesPathes(dir, skyPathes);
		Texture tex = TexturePoolSinglton::Instance()->CheckAndLoadSkyTexture(skyPathes, TEXTURE_SKYBOX);
		textureVec.push_back(tex);
		cube = new Cube(name,this->shader,textureVec);
	}

	//************************************************************************************
	SkyBox(std::string name,Shader* shader,Camera* _camera,std::string dir):DefaultGameObject(name,shader)
	{
		std::vector<Texture> textureVec;
		std::vector<std::string> skyPathes  ;
		TextureLoadUtil::GetDirFilesPathes(dir, skyPathes);
		Texture tex= TexturePoolSinglton::Instance()->CheckAndLoadSkyTexture(skyPathes,TEXTURE_SKYBOX);
		textureVec.push_back(tex);
		cube = new Cube(name, shader,_camera,textureVec);
	}

	~SkyBox()
	{
		if (cube != nullptr) 
		{
			cube->Delete<Cube>(cube);
		}
	}

	void Draw() 
	{
		glDepthFunc(GL_LEQUAL);
		GameObject::Draw();
		cube->Draw();
	}

	
};

