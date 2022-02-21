#pragma once
#include <iostream>
#include <string>
#include "GameObject.h"
#include "Camera.h"
#include "GameScript.h"
#include "Shader.h"
#include "InputBase.h"

class SceneLoader;
class Scene;
class Camera;

class GameHelper
{
public:
	static Shader* FindShaderFromCurrentScene(std::string _name);
	static GameObject* FindGameObjectFromCurrentScene(std::string _name);
	static  GameScript* GetGameScriptFromCurrentScene(std::string _name);

	static Shader*  GetMainShaderFromCurrentScene();

	static Scene* GetCurrentScene();

	static Camera* GetMainCameraFromCurrentScene();

	static std::string GetTargetPath();

	static void PushShaderToCurrentScene(Shader* &shader);

	static void PushGameObjectToCurrentScene(GameObject* &obj);

	static void PushGameScriptToCurrentScene(GameScript* &script);
	
	static void SetInputFromCurrentScene(InputBase* &input);

	static InputBase* GetInputFromCurrentScene();

	static GLFWwindow* GetWindowFromCurrentScene();
};


