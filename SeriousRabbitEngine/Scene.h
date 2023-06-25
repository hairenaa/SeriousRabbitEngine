#pragma once

#include <glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include <string>

#include "Shader.h"
#include "Camera.h"
#include "GameObject.h"
#include "LightGameObject.h"
#include "InputBase.h"
#include  "InputInWindows.h"
#include "WinApiUtil.h"
#include "Object.h"
#include "GameScript.h"


class Scene:public GameScript
{

protected:
	std::vector<GameObject*> gameObjectVec;
	
	std::vector<GameScript*> gameScriptVec;
	std::vector<Shader*> shaderVec;
	
	
	unsigned int Width;
	unsigned int Height;
	

	

public:
	GLFWwindow* window;
	InputBase* input = nullptr;
	Shader* mainShader = nullptr;
	Camera* mainCamera = nullptr;
	
	
	

	/*Scene(GLFWwindow* window, std::string _name, unsigned int width, unsigned int height, std::string loadPath);*/
	Scene(GLFWwindow* window, std::string _name, unsigned int width, unsigned int height) ;

	~Scene();

	virtual void Init();
	
	virtual  void Awake();
	
	virtual void OnEnable();
	
	virtual void Update();
	
	virtual void OnDisable();

	virtual void OnDestroy();

	
	void PushScript(GameScript* script);

	void PushGameObject(GameObject* &obj);

	void PushShader(Shader* shader);

	
	Shader* GetShaderByName(std::string _name);

	
	GameObject* GetGameObjectByName(std::string _name);

	GameScript* GetGameScriptByName(std::string _name);
	

	void BindInput(InputBase* &input);



};

