#pragma once
#include <iostream>
#include <string>
#include "Shader.h"
#include "GameObject.h"
#include "Camera.h"



class SceneLoader;
class Scene;


class GameFinder
{
public:
	static Shader* FindShader(std::string _name);
	static GameObject* FindGameObject(std::string _name);

	static Shader*  GetMainShader();

	static Scene* GetCurrentScene();

	static Camera* GetMainCamera();

	static std::string GetTargetPath();


	
};


