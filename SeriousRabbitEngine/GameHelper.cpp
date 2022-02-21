#pragma once
#include "GameHelper.h"
#include "SceneLoader.h"
#include "Scene.h"



 Shader*  GameHelper::FindShader(std::string _name)
{
	return SceneLoader::Instance()->GetCurrentScene()->GetShaderByName(_name);
}

GameObject * GameHelper::FindGameObject(std::string _name)
{
	return SceneLoader::Instance()->GetCurrentScene()->GetGameObjectByName(_name);
}


 Camera*  GameHelper::GetMainCamera()
{
	return SceneLoader::Instance()->GetCurrentScene()->mainCamera;
}

 Shader*  GameHelper::GetMainShader()
{
	return SceneLoader::Instance()->GetCurrentScene()->mainShader;
}

std::string  GameHelper::GetTargetPath()
{
	return SceneLoader::Instance()->GetCurrentScene()->TargetPath;
}

void GameHelper::PushShaderToCurrentScene(Shader* shader)
{
	if (shader != nullptr) 
	{
		SceneLoader::Instance()->GetCurrentScene()->PushShader(shader);
	}
	
}

void GameHelper::PushGameObjectToCurrentScene(GameObject * obj)
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

GameScript * GameHelper::GetGameScript(std::string _name)
{
	return SceneLoader::Instance()->GetCurrentScene()->GetGameScriptByName(_name);
}

 Scene*  GameHelper::GetCurrentScene()
{
	return SceneLoader::Instance()->GetCurrentScene();
}

 