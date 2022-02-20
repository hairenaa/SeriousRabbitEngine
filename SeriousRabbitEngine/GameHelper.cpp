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
	/*Shader* skyShader = new Shader(SHADER_SKYBOX_FILE_VERTEX, SHADER_SKYBOX_FILE_FRAGMENT, SKYBOX_SHADER_DEFAULT_NAME, Shader::SKYBOX_SHADER);
	PushShader(skyShader);*/
	SceneLoader::Instance()->GetCurrentScene()->PushShader(shader);
}

void GameHelper::PushGameObjectToCurrentScene(GameObject * obj)
{
	SceneLoader::Instance()->GetCurrentScene()->PushGameObject(obj);
}

void GameHelper::PushGameScriptToCurrentScene(GameScript * script)
{
	SceneLoader::Instance()->GetCurrentScene()->PushScript(script);
}

GameScript * GameHelper::GetGameScript(std::string _name)
{
	return SceneLoader::Instance()->GetCurrentScene()->GetGameScriptByName(_name);
}

 Scene*  GameHelper::GetCurrentScene()
{
	return SceneLoader::Instance()->GetCurrentScene();
}

 