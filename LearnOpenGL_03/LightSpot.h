#pragma once
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "Light.h"
#include "Shader.h"
#include "ShaderFileUtil.h"

class LightSpot :public Light
{
public:
	float cosInnerPhy = 0.65f;
	float cosOutterPhy = 0.6f;
	std::string cosInnerPhy_name = FRAGMENT_SHADER_STRUCT_LIGHT_POINT_COS_INNER_PHY;
	std::string	cosOutterPhy_name = FRAGMENT_SHADER_STRUCT_LIGHT_POINT_COS_OUTTER_PHY;
	
	LightSpot(std::string _name,  glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color = glm::vec3(1.0f, 1.0f, 1.0f))
		:Light(_name,  _position, _angles, _color)
	{
		AddContent(FRAGMENT_SHADER_DECLARE_LIGHT_SPOT, FRAGMENT_SHADER_CALL_LIGHT_PREFIX_SPOT);
		this->cosInnerPhy_name = this->name + cosInnerPhy_name;
		this->cosOutterPhy_name = this->name + cosOutterPhy_name;
		UpdateDirection();
	}
	//***********************************************************************
	LightSpot(std::string _name,Shader* _shader,glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color = glm::vec3(1.0f, 1.0f, 1.0f))
		:Light(_name,_shader,_position, _angles, _color)
	{
		
		AddContent(FRAGMENT_SHADER_DECLARE_LIGHT_SPOT, FRAGMENT_SHADER_CALL_LIGHT_PREFIX_SPOT);
		this->cosInnerPhy_name = this->name + cosInnerPhy_name;
		this->cosOutterPhy_name = this->name + cosOutterPhy_name;
		UpdateDirection();
	}


	/*LightSpot(std::string _name, glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color = glm::vec3(1.0f, 1.0f, 1.0f))
		:Light(_name, _position, _angles, _color)
	{


		this->cosInnerPhy_name = this->name + cosInnerPhy_name;
		this->cosOutterPhy_name = this->name + cosOutterPhy_name;
		UpdateDirection();
	}*/
	void  UpdateDirection()
	{
		direction = glm::vec3(0, 0, 1.0f);
		direction = glm::rotateZ(direction, angles.z);
		direction = glm::rotateX(direction, angles.x);
		direction = glm::rotateY(direction, angles.y);
	};
	void Draw()
	{
		Light::Draw();
		UpdateDirection();
		shader->SetUniform1f(cosInnerPhy_name.c_str(), cosInnerPhy);
		shader->SetUniform1f(cosOutterPhy_name.c_str(), cosOutterPhy);
	};
};

