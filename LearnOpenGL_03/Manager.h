#pragma once
#include<iostream>
#include <string>
#include "Shader.h"
#include "DestroyBase.h";

class Manager:public DestroyBase
{
public:
	enum HandleType
	{
		HANDLE_VERTEX,
		HANDLE_FRAGMENT

	};
	HandleType handleType;
	
	/*virtual void Bind(Shader* shader) = 0;*/
	virtual std::string HandleShaderSource(std::string source) = 0;

};

