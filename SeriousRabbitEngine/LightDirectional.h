#pragma once

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "Light.h"
#include "Shader.h"
#include "ShaderFileUtil.h"
#include "ConstValues.h"

class LightDirectional:public Light
{

	
public:
	
	LightDirectional(std::string _name ,glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color = glm::vec3(1.0f, 1.0f, 1.0f))
		:Light(_name, _position, _angles, _color)
	{
		AddContent(FRAGMENT_SHADER_DECLARE_LIGHT_DIRECTIONAL, FRAGMENT_SHADER_CALL_LIGHT_PREFIX_DIRECTIONAL); 
		UpdateDirection();
	}
	//***********************************************************************

	LightDirectional(std::string _name, Shader* _shader, glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color = glm::vec3(1.0f, 1.0f, 1.0f))
		:Light(_name, _shader, _position, _angles, _color)
	{
		AddContent(FRAGMENT_SHADER_DECLARE_LIGHT_DIRECTIONAL, FRAGMENT_SHADER_CALL_LIGHT_PREFIX_DIRECTIONAL); 
		UpdateDirection();
	}
	/*LightDirectional(std::string _name, glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color = glm::vec3(1.0f, 1.0f, 1.0f))
		:Light(_name,_position, _angles, _color)
	{

		UpdateDirection();
	}*/
	void UpdateDirection()
	{
		direction = glm::vec3(0, 0, 1.0f);
		direction = glm::rotateZ(direction, angles.z);
		direction = glm::rotateX(direction, angles.x);
		direction = glm::rotateY(direction, angles.y);
		//direction *= -1.0f;
	}
	void Draw() 
	{
		UpdateDirection();
		Light::Draw();
	}

	


};

