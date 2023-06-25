#pragma once
#include "GameHelper.h"
#include "SceneLoader.h"
#include "Scene.h"



 Shader*  GameHelper::FindShaderFromCurrentScene(std::string _name)
{
	return SceneLoader::Instance()->GetCurrentScene()->GetShaderByName(_name);
}

GameObject * GameHelper::FindGameObjectFromCurrentScene(std::string _name)
{
	return SceneLoader::Instance()->GetCurrentScene()->GetGameObjectByName(_name);
}


 Camera*  GameHelper::GetMainCameraFromCurrentScene()
{
	return SceneLoader::Instance()->GetCurrentScene()->mainCamera;
}

 Shader*  GameHelper::GetMainShaderFromCurrentScene()
{
	return SceneLoader::Instance()->GetCurrentScene()->mainShader;
}

//std::string  GameHelper::GetTargetPath()
//{
//	return SceneLoader::Instance()->GetCurrentScene()->TargetPath;
//}

void GameHelper::PushShaderToCurrentScene(Shader* shader)
{
	if (shader != nullptr) 
	{
		SceneLoader::Instance()->GetCurrentScene()->PushShader(shader);
	}
	
}

void GameHelper::PushGameObjectToCurrentScene(GameObject * &obj)
{
	if (obj != nullptr) 
	{
	SceneLoader::Instance()->GetCurrentScene()->PushGameObject(obj);
	}
}

void GameHelper::PushGameScriptToCurrentScene(GameScript * script)
{
	if (script != nullptr) 
	{
		SceneLoader::Instance()->GetCurrentScene()->PushScript(script);
	}
	
}

void GameHelper::SetInputFromCurrentScene(InputBase * input)
{
	SceneLoader::Instance()->GetCurrentScene()->BindInput(input);
}

InputBase* GameHelper::GetInputFromCurrentScene()
{
	return SceneLoader::Instance()->GetCurrentScene()->input;
}

GLFWwindow * GameHelper::GetWindowFromCurrentScene()
{
	return SceneLoader::Instance()->GetCurrentScene()->window;
}

SceneLoader * GameHelper::GetSceneLoader()
{
	return SceneLoader::Instance();
}

GameScript * GameHelper::GetGameScriptFromCurrentScene(std::string _name)
{
	return SceneLoader::Instance()->GetCurrentScene()->GetGameScriptByName(_name);
}

 Scene*  GameHelper::GetCurrentScene()
{
	return SceneLoader::Instance()->GetCurrentScene();
}

 