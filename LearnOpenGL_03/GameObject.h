#pragma once
#include <iostream>
#include<string>

#include <glad/glad.h>
#include<GLFW/glfw3.h>

#include "Shader.h"

class GameObject
{
public:
	static int id;
	std::string name;
	Shader* shader;
	GameObject(std::string _name) 
	{
		this->id ++;
		this->name = _name;
	};
	GameObject(std::string _name,Shader* _shader)
	{
		this->id++;
		this->name = _name;
		this->shader = _shader;
	};
	virtual void Destroy(GameObject* obj_ptr) 
	{
		delete obj_ptr;
		obj_ptr = NULL;
	}

	
	virtual void Draw() =0;

};

