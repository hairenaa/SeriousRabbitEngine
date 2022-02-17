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

class Scene:public Object,public DestroyBase,public GameScript
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


	virtual void Init()
	{
		for (unsigned int i = 0; i < gameScriptVec.size(); i++)
		{
			GameScript* script = gameScriptVec[i];
			script->Init();

		}
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
	
	void test() 
	{
		/*input->RegisterInputModeGroup(SetInputMode);
		input->RegisterCursorPosCallBack(mouse_callback);
		input->RegisterToUpdate(processInput);*/
		//init mainShader
		mainShader = new Shader(SHADER_DEFAULT_FILE_VERTEX, SHADER_DEFAULT_FILE_FRAGMENT, Shader::MAIN_SHADER);

		Shader* skyShader = new Shader("SkyBoxVertex.vert", "SkyboxFragment.frag", Shader::SKYBOX_SHADER);

		//init managers to handle the shader source code
		
		managerVec.push_back(LightManager::Instance());

		//manager build something 
		Light* lightDirectional = LightManager::Instance()->Build(LightManager::LIGHT_DIRECTIONAL, "lightDirectional", mainShader, glm::vec3(9.2f, 3.0f, 40.0f),
			glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0));
		Light* lightPoint0 = LightManager::Instance()->Build(LightManager::LIGHT_POINT, "lightP0", mainShader, glm::vec3(3.0f, 0.0f, 0.0f),
			glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0), glm::vec3(1.0f, 0.0f, 0.0f));
		Light* lightPoint1 = LightManager::Instance()->Build(LightManager::LIGHT_POINT, "lightP1", mainShader, glm::vec3(0.0f, 3.0f, 0.0f),
			glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0), glm::vec3(0.0f, 1.0f, 0.0f));
		Light* lightPoint2 = LightManager::Instance()->Build(LightManager::LIGHT_POINT, "lightP2", mainShader, glm::vec3(3.0f, 0.0f, 0.0f),
			glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0), glm::vec3(0.3f, 0.5f, 0.5f));

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

		mainCamera = new Camera("MainCamera", mainShader, Width, Height, glm::vec3(0, 10, 200.0f), glm::radians(-2.3f), glm::radians(0.3f), glm::vec3(0, 1.0f, 0));
		mainCamera->shaders.push_back(skyShader);

		Light* lightSpot = LightManager::Instance()->Build(LightManager::LIGHT_SPOT, "lightSpot", mainShader, glm::vec3(0, 0, 4.0f),
			glm::vec3(glm::radians(0.0f), glm::radians(0.0f), 0), glm::vec3(1.0f, 1.0f, 1.0f));
		Cube* cube = new Cube("cube1", mainShader, mainCamera, "awesomeface.png");


		//"\\model\\Crysis\\nanosuit.obj"
	// "\\model\\aigei\\pearl\\pearl.obj"
	//"\\model\\test\\test2.obj"
	//"\\model\\backpack\\backpack.obj"
	//"\\model\\Dog\\Doguinho.obj"
	//"\\model\\erciyuan\\shaonv\\luomo.obj"
		std::string modelPath = TargetPath + "\\model\\Crysis\\nanosuit.obj";
		std::string texturePath = TargetPath + "\\texture\\skybox\\default";
		std::cout << "modelPath is :" << modelPath << endl;
		std::cout << "texturePath is :" << texturePath << endl;

		Model* model = new Model("model1", modelPath, mainShader, mainCamera);
		SkyBox* skybox = new SkyBox("skybox", skyShader, mainCamera, texturePath);
		//skybox->cube->Scale(glm::vec3(1900.0f, 1900.0f, 1900.0f));

		//update model mat
		gameObjectVec.push_back(mainCamera);

		gameObjectVec.push_back(lightDirectional);
		gameObjectVec.push_back(lightPoint0);
		gameObjectVec.push_back(lightPoint1);
		/*gameObjectVec.push_back(lightPoint2);
		gameObjectVec.push_back(lightPoint3);*/
		gameObjectVec.push_back(lightSpot);
		gameObjectVec.push_back(cube);
		//reset model mat
		gameObjectVec.push_back(model);
		gameObjectVec.push_back(skybox);
	
	}

	


	

};

