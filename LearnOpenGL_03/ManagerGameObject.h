#pragma once
#include<iostream>
#include <string>
#include "Shader.h"
#include "DestroyBase.h";
#include "DefaultGameObject.h"

class ManagerGameObject:public DefaultGameObject
{
public:
	enum HandleType
	{
		HANDLE_VERTEX,
		HANDLE_FRAGMENT,
		HANDLE_VERTEX_FRAGMENT

	};
	HandleType handleType;

	std::string content_dec ="" ;
	std::string content_calc="" ;


	ManagerGameObject(std::string _name, Shader* _shader) :DefaultGameObject(_name, _shader)
	{
	}

	ManagerGameObject(std::string _name) :DefaultGameObject(_name)
	{
	}
	/*virtual void Bind(Shader* shader) = 0;*/
	virtual std::string HandleShaderSource(std::string source) = 0;

	virtual void AddContent(std::string declare_const, std::string call_const) = 0;

};

