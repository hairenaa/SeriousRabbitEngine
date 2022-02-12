#pragma once
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "Light.h"
#include "Shader.h"

class LightSpot :public Light
{
public:
	float cosInnerPhy = 0.65f;
	float cosOutterPhy = 0.6f;
	std::string cosInnerPhy_name = ".cosInnerPhy";
	std::string	cosOutterPhy_name = ".cosOutterPhy";
	LightSpot(std::string _name,Shader* _shader,glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color = glm::vec3(1.0f, 1.0f, 1.0f))
		:Light(_name,_shader,_position, _angles, _color = glm::vec3(1.0f, 1.0f, 1.0f))
	{
		UpdateDirection();
		this->cosInnerPhy_name = this->name + cosInnerPhy_name;
		this->cosOutterPhy_name = this->name + cosOutterPhy_name;
	}
	void  UpdateDirection()
	{
		direction = glm::vec3(0, 0, 1.0f);
		direction = glm::rotateZ(direction, angles.z);
		direction = glm::rotateX(direction, angles.x);
		direction = glm::rotateY(direction, angles.y);
	};
	void Draw()
	{
		UpdateDirection();
		Light::Draw();
		shader->SetUniform1f(cosInnerPhy_name.c_str(), cosInnerPhy);
		shader->SetUniform1f(cosOutterPhy_name.c_str(), cosOutterPhy);
	};
};

