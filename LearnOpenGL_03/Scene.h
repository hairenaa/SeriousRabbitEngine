#pragma once

#include <glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include <string>

#include "Shader.h"
#include "Camera.h"
#include "Material.h"
#include "LightDirectional.h"
#include "LightPoint.h"
#include "LightSpot.h"
#include "Mesh.h"
#include "Model.h"
#include "GameObject.h"
#include "Cube.h"
#include "LightManager.h"
#include "Manager.h"
#include "SkyBox.h"
#include "DestroyBase.h"
#include "InputInWindows.h"
#include "WinApiUtil.h"
#include "Object.h"
#include "GameScript.h"


class Scene:public Object,public GameScript
{
public:
	std::vector<GameObject*> gameObjectVec;
	std::vector<Manager*> managerVec;
	std::vector<GameScript*> gameScriptVec;
	InputInWindows* input;
	GLFWwindow* window;
	unsigned int Width;
	unsigned int Height;
	std::string TargetPath;


	Shader* mainShader = nullptr;
	Shader* skyShader = nullptr;
	Camera* mainCamera = nullptr;



	Scene(GLFWwindow* window, std::string _name, unsigned int width, unsigned int height,std::string targetPath) :Object(_name)
	{
		this->window = window;
		this->input == new InputInWindows(window);
		this->Width = width;
		this->Height = height;
		this->TargetPath = targetPath;

	}

	Scene(GLFWwindow* window,std::string _name,unsigned int width,unsigned int height) :Object(_name)
	{
		this->window = window;
		this->input == new InputInWindows(window);
		this->Width = width;
		this->Height = height;
		this->TargetPath = WinApiUtil::GetDebugPath();
	}


	~Scene()
	{

		for (unsigned int i = 0; i < managerVec.size(); i++)
		{
			GameScript* script = gameScriptVec[i];
			script->OnDestroy();
			script->Destroy(script);
		}

		for (unsigned int i = 0; i < gameObjectVec.size(); i++)
		{
			GameObject* obj = gameObjectVec[i];
			obj->Destroy(obj);
		}
		for (unsigned int i = 0; i < managerVec.size(); i++)
		{
			Manager* mana = managerVec[i];
			mana->Destroy(mana);
		}

		
	}

	virtual void Init()
	{
		
		//init mainShader
		mainShader = new Shader(SHADER_DEFAULT_FILE_VERTEX, SHADER_DEFAULT_FILE_FRAGMENT, Shader::MAIN_SHADER);

		skyShader= new Shader("SkyBoxVertex.vert", "SkyboxFragment.frag", Shader::SKYBOX_SHADER);

		mainCamera = new Camera("MainCamera", mainShader, Width, Height, glm::vec3(0, 10, 200.0f), glm::radians(-2.3f), glm::radians(0.3f), glm::vec3(0, 1.0f, 0));
		mainCamera->shaders.push_back(skyShader);

		//init managers to handle the shader source code

		managerVec.push_back(LightManager::Instance());

		gameObjectVec.push_back(mainCamera);
		for (unsigned int i = 0; i < gameScriptVec.size(); i++)
		{
			GameScript* script = gameScriptVec[i];
			script->Init();

		}
		for (unsigned int i = 0; i < managerVec.size(); i++)
		{
			Manager* manager = managerVec[i];
			if (manager->handleType == Manager::HANDLE_FRAGMENT)
			{
				mainShader->Unhandled_fragment_source = manager->HandleShaderSource(mainShader->Unhandled_fragment_source);
			}
			else if (manager->handleType == Manager::HANDLE_VERTEX)
			{
				mainShader->Unhandled_vertext_source = manager->HandleShaderSource(mainShader->Unhandled_vertext_source);
			}

		}

		//init shader
		mainShader->InitShader();
		skyShader->InitShader();

		
	};
	virtual  void Awake()
	{
		
		for (unsigned int i = 0; i < gameScriptVec.size(); i++)
		{
			GameScript* script = gameScriptVec[i];
			script->Awake();
		}
	};
	virtual void OnEnable()
	{
		for (unsigned int i = 0; i < gameScriptVec.size(); i++)
		{
			GameScript* script = gameScriptVec[i];
			script->OnEnable();
		}
	};
	virtual void Update()
	{
		for (unsigned int i = 0; i < gameScriptVec.size(); i++)
		{
			GameScript* script = gameScriptVec[i];
			script->Update();
		}
		for (unsigned int i = 0; i < gameObjectVec.size(); i++)
		{
			GameObject* obj = gameObjectVec[i];
			obj->Draw();
			glDepthFunc(GL_LESS);
		}
	};
	virtual void OnDisable()
	{
		for (unsigned int i = 0; i < gameScriptVec.size(); i++)
		{
			GameScript* script = gameScriptVec[i];
			script->OnDisable();
		}
	};
	virtual void OnDestroy()
	{
		for (unsigned int i = 0; i < gameScriptVec.size(); i++)
		{
			GameScript* script = gameScriptVec[i];
			script->OnDestroy();
		}
	};


	
	void PushScript(GameScript* script) 
	{
		gameScriptVec.push_back(script);
	}
	
	
};

