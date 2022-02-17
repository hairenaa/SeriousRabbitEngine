#pragma once
#include <vector>
#include <glad/glad.h>
#include<GLFW/glfw3.h>
#include "Scene.h"
#include <string>
#include "Object.h"
class SceneLoader
{
private:
	
	GLFWwindow* window;
	unsigned int Width;
	unsigned int Height;
public:
	std::vector<Scene*> scenes;
	std::string TargetPath="";
	
	unsigned int Index = 0;

	SceneLoader(GLFWwindow* window, unsigned int width, unsigned int height,std::string targetPath)
	{
		this->window = window;
		this->Height = height;
		this->Width = width;
		this->TargetPath = targetPath;
		NewSceneInstance("DefaultScene");
	}
	Scene* NewSceneInstance(std::string _name) 
	{
		Scene* scene;
		if (this->TargetPath != "") 
		{
			scene = new Scene(this->window, _name, this->Width, this->Height, this->TargetPath);
		}
		else
		{
			scene = new Scene(this->window, _name, this->Width, this->Height);
		}
		
		scenes.push_back(scene);
		return scene;
	}


	Scene* GetCurrentScene() 
	{
		if (scenes.empty()) 
		{
			throw new exception("no scene in this window!!");
		}
		if (this->Index>=0&&this->Index<scenes.size()) 
		{
			return this->scenes[this->Index];
		}
		return this->scenes[0];
		
		
	}
	void ChangeSceneNext() 
	{
		
		if (this->Index < this->scenes.size()-1) 
		{
			this->Index++;
		}
		
	}

	void ChangeSceneByName(std::string _name) 
	{
		for (unsigned int i = 0; i < scenes.size(); i++)
		{
			Scene* sce = scenes[i];
			if (sce->name == _name) 
			{
				this->Index = i;
				break;
			}
		}
	}

	Scene* GetSceneByName(std::string _name) 
	{
		for (unsigned int i = 0; i < scenes.size(); i++)
		{
			Scene* sce = scenes[i];
			if (sce->name == _name)
			{
				return sce;
			}
		}
	}


};

