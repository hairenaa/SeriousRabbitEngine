#pragma once
#include "GameScriptAdapter.h"
#include <glad/glad.h>
#include<GLFW/glfw3.h>
#include <iostream>
class MyTestScript:public GameScriptAdapter
{

public:



	Cube* cube;
	Model* model;
	virtual void Init() 
	{
		/*scene->input->RegisterInputModeGroup(SetInputMode);
		scene->input->RegisterCursorPosCallBack(mouse_callback);
		scene->input->RegisterToUpdate(processInput);
	*/
		std::cout << "Init()" << endl;
	};
	virtual  void Awake() 
	{
		std::cout << "Awake()" << endl;
		//manager build something 
		Light* lightDirectional = LightManager::Instance()->Build(LightManager::LIGHT_DIRECTIONAL, "lightDirectional",scene->mainShader, glm::vec3(9.2f, 3.0f, 40.0f),
			glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0));
		Light* lightPoint0 = LightManager::Instance()->Build(LightManager::LIGHT_POINT, "lightP0", scene->mainShader, glm::vec3(3.0f, 0.0f, 0.0f),
			glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0), glm::vec3(1.0f, 0.0f, 0.0f));
		Light* lightPoint1 = LightManager::Instance()->Build(LightManager::LIGHT_POINT, "lightP1", scene->mainShader, glm::vec3(0.0f, 3.0f, 0.0f),
			glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0), glm::vec3(0.0f, 1.0f, 0.0f));
		Light* lightPoint2 = LightManager::Instance()->Build(LightManager::LIGHT_POINT, "lightP2", scene->mainShader, glm::vec3(3.0f, 0.0f, 0.0f),
			glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0), glm::vec3(0.3f, 0.5f, 0.5f));
		Light* lightSpot = LightManager::Instance()->Build(LightManager::LIGHT_SPOT, "lightSpot", scene->mainShader, glm::vec3(0, 0, 4.0f),
			glm::vec3(glm::radians(0.0f), glm::radians(0.0f), 0), glm::vec3(1.0f, 1.0f, 1.0f));
		std::string modelPath = scene->TargetPath + "\\model\\Crysis\\nanosuit.obj";
		std::string texturePath = scene->TargetPath + "\\texture\\skybox\\default";
		std::cout << "modelPath is :" << modelPath << endl;
		std::cout << "texturePath is :" << texturePath << endl;

		cube = new Cube("cube1", scene->mainShader, scene->mainCamera, "awesomeface.png");
		model = new Model("model1", modelPath, scene->mainShader,scene->mainCamera);
		SkyBox* skybox = new SkyBox("skybox",scene->skyShader,scene->mainCamera, texturePath);
		
		scene->gameObjectVec.push_back(lightDirectional);
		scene->gameObjectVec.push_back(lightPoint0);
		scene->gameObjectVec.push_back(lightPoint1);
		scene->gameObjectVec.push_back(lightSpot);
		scene->gameObjectVec.push_back(cube);
		scene->gameObjectVec.push_back(model);
		scene->gameObjectVec.push_back(skybox);

	};
	virtual void OnEnable() 
	{
		std::cout << "OnEnable()" << endl;
	};
	virtual void Update() 
	{
		model->Rotate(0.5f, glm::vec3(0, 1.0f, 0));
		cube->Rotate(0.5f, glm::vec3(1.0f, 1.0f, 0));
		cube->Translate(glm::vec3(0.01f, 0, 0));
		std::cout << "Update()" << endl;
	};
	virtual void OnDisable() 
	{
		std::cout << "OnDisable()" << endl;
	};
	virtual void OnDestroy() 
	{
		std::cout << "OnDestroy()" << endl;
	};



};

