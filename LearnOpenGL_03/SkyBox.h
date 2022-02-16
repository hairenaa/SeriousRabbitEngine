#pragma once
#include "GameObject.h"
#include "Cube.h"
#include <string>
#include <vector>
#include "Shader.h"
#include "TexturePoolSinglton.h"
class SkyBox :public GameObject
{
public:
	Cube* cube;
	SkyBox(std::string name,Shader* shader,std::vector<std::string> skyPathes):GameObject(name,shader)
	{
		std::vector<Texture> textureVec;
		Texture tex= TexturePoolSinglton::Instance()->CheckAndLoadSkyTexture(skyPathes,TEXTURE_SKYBOX);
		textureVec.push_back(tex);
		cube = new Cube(name, shader,textureVec);
	}

	void Draw() 
	{
		GameObject::Draw();
		cube->Draw();
	}
};

