#include "DefaultGameObject.h"
#include "SceneLoader.h"
#include "Scene.h"


DefaultGameObject::DefaultGameObject(std::string _name, Shader* _shader) :GameObject(_name, _shader)
{
	SceneLoader::Instance()->GetCurrentScene()->PushGameObject(this);
}

DefaultGameObject::DefaultGameObject(std::string _name) :GameObject(_name)
{
	this->shader = GameFinder::FindShader(MAIN_SHADER_DEFAULT_NAME);
	SceneLoader::Instance()->GetCurrentScene()->PushGameObject(this);

}