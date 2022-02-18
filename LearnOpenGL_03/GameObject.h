#pragma once
#include <iostream>
#include<string>

#include <glad/glad.h>
#include<GLFW/glfw3.h>
#include "DestroyBase.h"
#include "Shader.h"
#include "Object.h"

class GameObject:public Object,public DestroyBase
{
public:
	
	Shader* shader=nullptr;

	GameObject(std::string _name) :Object(_name)
	{
		this->id ++;
		this->name = _name;
	};
	GameObject(std::string _name,Shader* _shader) :Object(_name)
	{
		this->id++;
		this->name = _name;
		this->shader = _shader;
	};
	

	
	virtual void Draw() 
	{
		std::string s = this->name;
		shader->use();
	};

};

