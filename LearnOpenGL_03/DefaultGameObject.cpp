#include "DefaultGameObject.h"
#include "SceneLoader.h"
#include "Scene.h"


DefaultGameObject::DefaultGameObject(std::string _name, Shader* _shader) :GameObject(_name, _shader)
{
	GameHelper::PushGameObjectToCurrentScene(this);
}

DefaultGameObject::DefaultGameObject(std::string _name) :GameObject(_name)
{
	this->shader = GameHelper::FindShader(MAIN_SHADER_DEFAULT_NAME);
	GameHelper::PushGameObjectToCurrentScene(this);

}