#pragma once
#include "GameFinder.h"
#include "SceneLoader.h"
#include "Scene.h"


 Shader*  GameFinder::FindShader(std::string _name)
{
	return SceneLoader::Instance()->GetCurrentScene()->GetShaderByName(_name);
}

GameObject * GameFinder::FindGameObject(std::string _name)
{
	return SceneLoader::Instance()->GetCurrentScene()->GetGameObjectByName(_name);
}


 Camera*  GameFinder::GetMainCamera()
{
	return SceneLoader::Instance()->GetCurrentScene()->mainCamera;
}

 Shader*  GameFinder::GetMainShader()
{
	return SceneLoader::Instance()->GetCurrentScene()->mainShader;
}

std::string  GameFinder::GetTargetPath()
{
	return SceneLoader::Instance()->GetCurrentScene()->TargetPath;
}

 Scene*  GameFinder::GetCurrentScene()
{
	return SceneLoader::Instance()->GetCurrentScene();
}

