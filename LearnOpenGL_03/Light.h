#pragma once

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "GameObject.h"
#include "Shader.h"

class Light:public GameObject
{
public:
	glm::vec3 position;
	glm::vec3 angles;
	glm::vec3 color;
	glm::vec3 direction = glm::vec3(0, 0, 1.0f);
	std::string pos_name = ".pos";
	std::string color_name = ".color";
	std::string dir_name = ".dir";
	Shader* shader;
	Light(std::string _name,Shader* _shader,glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color = glm::vec3(1.0f, 1.0f, 1.0f)) 
	{
		this->name = _name;
		this->position = _position;
		this->angles = _angles;
		this->color = _color;
		this->pos_name = _name + pos_name;
		this->color_name = _name + color_name;
		this->dir_name = _name + dir_name;
		this->shader = _shader;
	}
	virtual void Draw() 
	{
		this->shader->SetUniform3fByVec3(pos_name.c_str(), position);
		this->shader->SetUniform3fByVec3(color_name.c_str(), color);
		this->shader->SetUniform3fByVec3(dir_name.c_str(), direction);
	};
};

