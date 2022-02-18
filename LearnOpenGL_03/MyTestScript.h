#pragma once
#include "GameScriptAdapter.h"
#include <glad/glad.h>
#include<GLFW/glfw3.h>
#include <iostream>
#include "Cube.h"
#include "Model.h"
#include "LightDirectional.h"
#include "LightPoint.h"
#include "LightSpot.h"
#include "SkyBox.h"

class MyTestScript:public GameScriptAdapter
{

public:



	Cube* cube;
	Model* model;

	//初始化游戏对象
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
		
		Light* lightDirectional = new LightDirectional("lightDirectional", glm::vec3(9.2f, 3.0f, 40.0f),
			glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0));
		Light* lightPoint0 = new LightPoint("lightP0", glm::vec3(3.0f, 0.0f, 0.0f),
			glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0), glm::vec3(1.0f, 0.0f, 0.0f));
		Light* lightPoint1 = new LightPoint("lightP1", glm::vec3(0.0f, 3.0f, 0.0f),
			glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0), glm::vec3(0.0f, 1.0f, 0.0f));
		
		Light* lightSpot = new LightSpot("lightSpot", glm::vec3(0, 0, 4.0f),
			glm::vec3(glm::radians(0.0f), glm::radians(0.0f), 0), glm::vec3(1.0f, 1.0f, 1.0f));


		std::string modelPath = GameFinder::GetTargetPath() + "\\model\\Crysis\\nanosuit.obj";
		std::string texturePath = GameFinder::GetTargetPath() + "\\texture\\skybox\\default";
		std::cout << "modelPath is :" << modelPath << endl;
		std::cout << "texturePath is :" << texturePath << endl;

		cube = new Cube("cube1", "awesomeface.png");
		model = new Model("model1", modelPath);
		SkyBox* skybox = new SkyBox("skybox", GameFinder::FindShader("skyShader"), texturePath);

	
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

