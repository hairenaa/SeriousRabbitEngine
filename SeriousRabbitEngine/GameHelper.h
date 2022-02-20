#pragma once
#include <iostream>
#include <string>
#include "GameObject.h"
#include "Camera.h"
#include "GameScript.h"
#include "Shader.h"

class SceneLoader;
class Scene;


class GameHelper
{
public:
	static Shader* FindShader(std::string _name);
	static GameObject* FindGameObject(std::string _name);
	static  GameScript* GetGameScript(std::string _name);

	static Shader*  GetMainShader();

	static Scene* GetCurrentScene();

	static Camera* GetMainCamera();

	static std::string GetTargetPath();

	static void PushShaderToCurrentScene(Shader* shader);

	static void PushGameObjectToCurrentScene(GameObject* obj);

	static void PushGameScriptToCurrentScene(GameScript* script);
	
	
};


