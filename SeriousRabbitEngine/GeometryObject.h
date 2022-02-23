#pragma once
#include "DefaultGameObject.h"
#include "PhysicsObject.h"
#include "Shader.h"
#include "Camera.h"
#include <string>
class GeometryObject:public DefaultGameObject, public PhysicsObject
{
protected:
	Material* material;
	Mesh* mesh;
	const int GROUP_LEN = 11;
	const std::string DIFF_PATH = TEXTURE_DEFAULT_DIFFUSE_PATH;
	const std::string SPE_PATH = TEXTURE_DEFAULT_SPECULAR_PATH;
public:
	GeometryObject(std::string _name,Shader* _shader) :DefaultGameObject(_name, _shader), PhysicsObject()
	{
	}
	GeometryObject(std::string _name) :DefaultGameObject(_name), PhysicsObject()
	{
	}

	GeometryObject(std::string _name, Shader* _shader,Camera* _camera) : DefaultGameObject(_name, _shader), PhysicsObject(_camera)
	{
	} 

};

