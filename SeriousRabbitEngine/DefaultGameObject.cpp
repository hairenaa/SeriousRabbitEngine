#include "DefaultGameObject.h"
#include "SceneLoader.h"
#include "Scene.h"


DefaultGameObject::DefaultGameObject(std::string _name, Shader* _shader) :GameObject(_name, _shader)
{
	GameObject* s = (GameObject*)this;
	GameHelper::PushGameObjectToCurrentScene(s);
}

DefaultGameObject::DefaultGameObject(std::string _name) :GameObject(_name)
{
	this->shader = GameHelper::FindShaderFromCurrentScene(MAIN_SHADER_DEFAULT_NAME);
	GameObject* s = (GameObject*)this;
	GameHelper::PushGameObjectToCurrentScene(s);

}