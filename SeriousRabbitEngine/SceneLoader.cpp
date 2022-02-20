#include "SceneLoader.h"

SceneLoader* SceneLoader::instance = nullptr;
SceneLoader*  SceneLoader::Instance()
{
	if (instance != nullptr)
	{
		return instance;
	}
	else
	{
		throw new exception("no instance of SceneLoader!!");
	}
}

SceneLoader::SceneLoader(GLFWwindow* window, unsigned int width, unsigned int height, std::string targetPath)
{
	this->window = window;
	this->Height = height;
	this->Width = width;
	this->TargetPath = targetPath;
	NewSceneInstance(SCENE_DEFAULT_NAME);
	instance = this;
}
SceneLoader::~SceneLoader()
{
	for (unsigned int i = 0; i < scenes.size(); i++)
	{
		Scene* scene = scenes[i];
		scene->Destroy(scene);
	}
}

Scene* SceneLoader::NewSceneInstance(std::string _name)
{
	Scene* scene;
	if (this->TargetPath != "")
	{
		scene = new Scene(this->window, _name, this->Width, this->Height, this->TargetPath);
	}
	else
	{
		scene = new Scene(this->window, _name, this->Width, this->Height);
	}

	scenes.push_back(scene);
	return scene;
}


Scene* SceneLoader::GetCurrentScene()
{
	if (scenes.empty())
	{
		throw new exception("no scene in this window!!");
	}
	if (this->Index >= 0 && this->Index < scenes.size())
	{
		return this->scenes[this->Index];
	}
	return this->scenes[0];


}
void SceneLoader::ChangeSceneNext()
{

	if (this->Index < this->scenes.size() - 1)
	{
		this->Index++;
	}

}

void SceneLoader::ChangeSceneByName(std::string _name)
{
	for (unsigned int i = 0; i < scenes.size(); i++)
	{
		Scene* sce = scenes[i];
		if (sce->name == _name)
		{
			this->Index = i;
			break;
		}
	}
}

Scene* SceneLoader::GetSceneByName(std::string _name)
{
	for (unsigned int i = 0; i < scenes.size(); i++)
	{
		Scene* sce = scenes[i];
		if (sce->name == _name)
		{
			return sce;
		}
	}
}


