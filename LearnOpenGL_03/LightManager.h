#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Light.h"
#include "LightDirectional.h"
#include "LightPoint.h"
#include "LightSpot.h"
#include "Manager.h"
#include "Single.h"
#include  "Shader.h"


class LightManager :public Single<LightManager>,public Manager
{
public:
	std::string content_dec="";
	std::string content_calc="";
	std::string name;
	std::vector<Light*> Vec;

	enum LightType
	{
		LIGHT_DIRECTIONAL,
		LIGHT_POINT,
		LIGHT_SPOT
	};


	LightManager()
	{
		this->handleType = Manager::HANDLE_FRAGMENT;
	}

	Light* Build(LightType type, std::string _name,Shader* _shader, glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color = glm::vec3(1.0f, 1.0f, 1.0f))
	{
		this->name = _name;
		switch (type)
		{

			case LIGHT_DIRECTIONAL: 
			{
				AddContent(FRAGMENT_SHADER_DECLARE_LIGHT_DIRECTIONAL, FRAGMENT_SHADER_CALL_LIGHT_PREFIX_DIRECTIONAL);
				Light* lightDir = new LightDirectional(_name,_shader, _position, _angles, _color);
				Vec.push_back(lightDir);
				return lightDir;
			}
			case LIGHT_POINT: 
			{
				AddContent(FRAGMENT_SHADER_DECLARE_LIGHT_POINT, FRAGMENT_SHADER_CALL_LIGHT_PREFIX_POINT);
				Light* lightP= new LightPoint(_name, _shader, _position, _angles, _color);
				Vec.push_back(lightP);
				return lightP;
			}
			case LIGHT_SPOT: 
			{
				AddContent(FRAGMENT_SHADER_DECLARE_LIGHT_SPOT, FRAGMENT_SHADER_CALL_LIGHT_PREFIX_SPOT);
				Light* lightS = new LightSpot(_name, _shader, _position, _angles, _color);
				Vec.push_back(lightS);
				return lightS;
			}
		
			}
			return nullptr;
	};

	

	std::string HandleShaderSource(std::string source)
	{
		
		source= ShaderFileUtil::HandleShaderSourceStr(source,
			FRAGMENT_SHADER_LIGHT_TAG_AREA_BEGIN, FRAGMENT_SHADER_LIGHT_TAG_AREA_END, content_dec);
		source= ShaderFileUtil::HandleShaderSourceStr(source,
			FRAGMENT_SHADER_LIGHT_TAG_CALC_BEGIN, FRAGMENT_SHADER_LIGHT_TAG_CALC_END, content_calc);
		return source;
	}

	/*void Bind(Shader* shader) 
	{
		for (unsigned int i = 0; i < Vec.size(); i++)
		{
			Vec[i]->shader=shader;
		}
	}*/


private :
	void AddContent(std::string declare_const,std::string call_const)
	{
		content_dec = content_dec+ "\n"+declare_const + this->name + ";";
		content_calc = content_calc+ "\n\t" +call_const  + this->name + FRAGMENT_SHADER_CALL_LIGHT_AFFIX;

	}
};

LightManager* LightManager::instance = nullptr;



