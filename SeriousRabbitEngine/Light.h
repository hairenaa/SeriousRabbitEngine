#pragma once

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "DefaultGameObject.h"
#include "Shader.h"
#include "ShaderFileUtil.h"
#include "ConstValues.h"
#include "ManagerGameObject.h"

class Light:public ManagerGameObject
{

protected:
	

	Light(std::string _name, glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color)
		:ManagerGameObject(_name)
	{
		ManagerGameObject::handleType = HANDLE_FRAGMENT;
		this->position = _position;
		this->angles = _angles;
		this->color = _color;
		this->pos_name = _name + pos_name;
		this->color_name = _name + color_name;
		this->dir_name = _name + dir_name;

	}

	//***********************************************************************************
	Light(std::string _name, Shader* _shader, glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color)
		:ManagerGameObject(_name, _shader)
	{
		ManagerGameObject::handleType = HANDLE_FRAGMENT;
		this->position = _position;
		this->angles = _angles;
		this->color = _color;
		this->pos_name = _name + pos_name;
		this->color_name = _name + color_name;
		this->dir_name = _name + dir_name;

	}
	
	

public:
	glm::vec3 position;
	glm::vec3 angles;
	glm::vec3 color;
	glm::vec3 direction = glm::vec3(0, 0, 1.0f);
	std::string pos_name = FRAGMENT_SHADER_STRUCT_LIGHT_POS;
	std::string color_name = FRAGMENT_SHADER_STRUCT_LIGHT_COLOR;
	std::string dir_name = FRAGMENT_SHADER_STRUCT_LIGHT_DIR;
		
	virtual void Draw() 
	{
		GameObject::Draw();
		this->shader->SetUniform3fByVec3(pos_name.c_str(), position);
		this->shader->SetUniform3fByVec3(color_name.c_str(), color);
		this->shader->SetUniform3fByVec3(dir_name.c_str(), direction);
	};



	std::string HandleShaderSource(std::string source)
	{

		source = ShaderFileUtil::HandleShaderSourceStr(source,
			FRAGMENT_SHADER_LIGHT_TAG_AREA_BEGIN, FRAGMENT_SHADER_LIGHT_TAG_AREA_END, content_dec);
		source = ShaderFileUtil::HandleShaderSourceStr(source,
			FRAGMENT_SHADER_LIGHT_TAG_CALC_BEGIN, FRAGMENT_SHADER_LIGHT_TAG_CALC_END, content_calc);
		return source;
	}

	void AddContent(std::string declare_const, std::string call_const)
	{
		content_dec = content_dec + "\n" + declare_const + this->name + ";";
		content_calc = content_calc + "\n\t" + call_const + this->name + FRAGMENT_SHADER_CALL_LIGHT_AFFIX;

	}
};


