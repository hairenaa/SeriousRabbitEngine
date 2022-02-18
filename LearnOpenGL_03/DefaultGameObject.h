#pragma once
#include "GameObject.h"
#include "Shader.h"
#include <string>
#include "GameFinder.h"
#include "ConstValues.h"

class SceneLoader;
class Scene;

class DefaultGameObject:public GameObject
{
public:
	DefaultGameObject(std::string _name, Shader* _shader);
	DefaultGameObject(std::string _name);

};

