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


	//注意使用指针形式创建对象
	//
public:

	//可以使用空参构造函数来给脚本命名，他的优先级最高，发生在场景加载器和当前场景构造完成后
	MyTestScript() 
	{
		this->name = "MyTestScript";
	}

	Cube* cube;
	Model* model;

	//在此函数中初始化shader并使用GameHelper加入到当前场景中
	//注意创建GameObject对象是手动无需加入将自动注册
	virtual void Init() 
	{
		/*scene->input->RegisterInputModeGroup(SetInputMode);
		scene->input->RegisterCursorPosCallBack(mouse_callback);
		scene->input->RegisterToUpdate(processInput);
	*/
		Shader* skyShader = new Shader(SHADER_SKYBOX_FILE_VERTEX, SHADER_SKYBOX_FILE_FRAGMENT, SKYBOX_SHADER_DEFAULT_NAME, Shader::SKYBOX_SHADER);
		GameHelper::PushShaderToCurrentScene(skyShader);
		std::cout << "Init()" << endl;
	};

	//建议在此函数中初始化GameObject

	virtual  void Awake() 
	{

		std::cout << "Awake()" << endl;
		//manager build something 
		
		Light* lightDirectional = new LightDirectional("lightDirectional", glm::vec3(9.2f, 3.0f, 40.0f),
			glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0),glm::vec3(1.0f,1.0f,1.0f));
		Light* lightPoint0 = new LightPoint("lightP0", glm::vec3(3.0f, 0.0f, 0.0f),
			glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0), glm::vec3(1.0f, 0.0f, 0.0f));
		Light* lightPoint1 = new LightPoint("lightP1", glm::vec3(0.0f, 3.0f, 0.0f),
			glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0), glm::vec3(0.0f, 1.0f, 0.0f));
		
		Light* lightSpot = new LightSpot("lightSpot", glm::vec3(0, 0, 4.0f),
			glm::vec3(glm::radians(0.0f), glm::radians(0.0f), 0), glm::vec3(0.0f, 1.0f, 1.0f));


		std::string modelPath = GameHelper::GetTargetPath() + "\\model\\Crysis\\nanosuit.obj";
		std::string texturePath = GameHelper::GetTargetPath() + "\\texture\\skybox\\default";
		std::cout << "modelPath is :" << modelPath << endl;
		std::cout << "texturePath is :" << texturePath << endl;

		cube = new Cube("cube1", "awesomeface.png");
		model = new Model("model1", modelPath);
		SkyBox* skybox = new SkyBox("skybox", GameHelper::FindShader(SKYBOX_SHADER_DEFAULT_NAME), texturePath);
	
		GameScript* s = GameHelper::GetGameScript("MyTestScript");
		MyTestScript* o = (MyTestScript*)s;
		//o->cube->SetScale(glm::vec3(2.0f, 2.0f, 2.0f));
		o->cube->Scale(glm::vec3(2.0f, 2.0f, 2.0f));
	};

	//脚本启用时发生
	virtual void OnEnable() 
	{
		std::cout << "OnEnable()" << endl;
	};

	//更新函数
	virtual void Update() 
	{
		//glm::vec3 a = model->GetAngles() + glm::vec3(0.0f, 0.0f, 0.5f);
		//model->SetAngles(a);
		model->Rotate(glm::vec3(0, 0.5f, 0));
		cube->Rotate( glm::vec3(0.5f, 0.5f, 0));
		//cube->SetPosition(glm::vec3(0.01f, 0.01f, 0)+ cube->GetPosition());
		cube->Translate(glm::vec3(0.01f, 0.01f, 0));
	};

	//当脚本被禁用事发生
	virtual void OnDisable() 
	{
		std::cout << "OnDisable()" << endl;
	};

	//当脚本被销毁时发生，这通常发生在程序关闭前，之后将由引擎管理销毁所有对象
	virtual void OnDestroy() 
	{
		std::cout << "OnDestroy()" << endl;
	};



};

