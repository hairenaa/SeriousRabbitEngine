#pragma once
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "Light.h"
#include "Shader.h"
#include "ShaderFileUtil.h"

class LightPoint : public Light
{
public:
	float constant;
	float linear;
	float quadratic;
	std::string constant_name = FRAGMENT_SHADER_STRUCT_LIGHT_POINT_CONSTANT;
	std::string linear_name = FRAGMENT_SHADER_STRUCT_LIGHT_POINT_LINEAR;
	std::string quadratic_name = FRAGMENT_SHADER_STRUCT_LIGHT_POINT_QUADRATIC;
	LightPoint(std::string _name,Shader* _shader,glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color = glm::vec3(1.0f, 1.0f, 1.0f))
		:Light(_name,_shader,_position,_angles,_color)
	{
		constant = 1.0f;
		linear = 0.09f;
		quadratic = 0.032f;

		this->constant_name = this->name + constant_name;
		this->linear_name = this->name + linear_name;
		this->quadratic_name = this->name + quadratic_name;
	};

	LightPoint(std::string _name, glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color = glm::vec3(1.0f, 1.0f, 1.0f))
		:Light(_name,_position, _angles, _color)
	{
		constant = 1.0f;
		linear = 0.09f;
		quadratic = 0.032f;

		this->constant_name = this->name + constant_name;
		this->linear_name = this->name + linear_name;
		this->quadratic_name = this->name + quadratic_name;
	};
	void Draw() 
	{
		Light::Draw();
		shader->SetUniform1f(this->constant_name.c_str(), constant);
		shader->SetUniform1f(this->linear_name.c_str(), linear);
		shader->SetUniform1f(this->quadratic_name.c_str(), quadratic);
	};
};

