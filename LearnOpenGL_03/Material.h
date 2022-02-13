#pragma once
#include "Shader.h"

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include <vector>
#include "GameObject.h"

class Material:public GameObject
{
public:
	const  float SHININESS_32f = 32.0f;
	const float SHININESS_64f = 64.0f;
	const float SHININESS_128f = 128.0f;
	const float SHININESS_256f = 256.0f;
	std::string ambient_ins_name = ".ambient_ins";
	std::string shininess_name = ".shininess";
	std::string diffuse_ins_name = ".diffuse_ins";
	std::string specular_ins_name = ".specular_ins";
	std::string ambientColor_name = ".ambientColor";
	float ambient_ins = 1.0f;
	float diffuse_ins=1.0f;
	float specular_ins=1.0f;
	float shininess=SHININESS_32f;
	glm::vec3 ambientColor = glm::vec3(0.2f, 0.2f, 0.2f);

	Material(std::string _name,Shader* _shader,glm::vec3 _ambientColor ,float _ambient_ins, float _diffuse_ins, float _specular_ins, float _shininess) 
	    :GameObject(_name,_shader),
		ambientColor(_ambientColor),
		ambient_ins(_ambient_ins),
		diffuse_ins(_diffuse_ins),
		specular_ins(_specular_ins),
		shininess(_shininess)
	{
		this->ambientColor_name = _name + ambientColor_name;
		this->ambient_ins_name = _name + ambient_ins_name;
		this->shininess_name = _name + shininess_name;
		this->diffuse_ins_name = _name + diffuse_ins_name;
		this->specular_ins_name = _name + specular_ins_name;
	};
	Material(std::string _name, Shader* _shader)
		: GameObject(_name,_shader)
	{
		this->ambientColor_name = _name + ambientColor_name;
		this->ambient_ins_name = _name + ambient_ins_name;
		this->shininess_name = _name + shininess_name;
		this->diffuse_ins_name = _name + diffuse_ins_name;
		this->specular_ins_name = _name + specular_ins_name;
	};
	void Draw()
	{
		shader->SetUniform1f(this->ambient_ins_name.c_str(), ambient_ins);
		shader->SetUniform3fByVec3(this->ambientColor_name.c_str(), ambientColor);
		shader->SetUniform1f(this->shininess_name.c_str() , shininess);
		shader->SetUniform1f(this->diffuse_ins_name.c_str(), diffuse_ins);
		shader->SetUniform1f(this->specular_ins_name.c_str(), specular_ins);
	};
};

