#pragma once
#include <glad/glad.h>
#include<GLFW/glfw3.h>
#include "GameObject.h"
#include "Cube.h"
#include <string>
#include <vector>
#include "Shader.h"
#include "Camera.h"
#include "TexturePoolSinglton.h"
class SkyBox :public GameObject
{
public:
	Cube* cube;
	SkyBox(std::string name,Shader* shader,Camera* _camera,std::string dir):GameObject(name,shader)
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
			delete cube;
			cube = nullptr;
		}
	}

	void Draw() 
	{
		glDepthFunc(GL_LEQUAL);
		GameObject::Draw();
		cube->Draw();
	}

	
};

