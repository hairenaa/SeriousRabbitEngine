#pragma once
#include <string>

#include <glad/glad.h>
#include<GLFW/glfw3.h>


#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "ShaderFileUtil.h"
#include "Object.h"


using namespace std;


class Shader:public Object
{
public:
	
	enum ShaderType
	{
		MAIN_SHADER,
		SKYBOX_SHADER,
		SHADER_CUSTOM
	};
	ShaderType shaderType;
//	vector<Manager*>  managerVec;
	std::string Unhandled_vertext_source;
	std::string Unhandled_fragment_source;
	enum SlotType
	{
		DIFFUSE,
		SPECULAR,
	};
	
	const std::string TYPE_VERTEX_SHDER = "VERTEX_SHDER";
	const std::string TYPE_FRAMENT_SHDER = "FRAGMENT_SHDER";
	const std::string TYPE_PROGRAM = "PROGRAM";
	unsigned int ID;   //shader program ID


	Shader(const char* vertexPath, const char* fragmentPath,std::string _name,ShaderType type):Object(_name)
	{
		
		try
		{
			this->shaderType = type;
			Unhandled_vertext_source  = ShaderFileUtil::ReadAllText(vertexPath).c_str();
			Unhandled_fragment_source= ShaderFileUtil::ReadAllText(fragmentPath);

			
		}
		catch (const std::exception& ex)
		{
			printf(ex.what());
		}



	};


	void InitShader() 
	{
		

		const char* vertexSource = this->Unhandled_vertext_source.c_str();
		const char* fragmentSource = this->Unhandled_fragment_source.c_str();



		cout << "vertex shader source code: \n" << vertexSource << endl;
		cout << "-------------------------------------------------------" << endl;
		cout << "fragment shader source code: \n" << fragmentSource << endl;

		unsigned int vertexShader, fragmentShader;

		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexSource, NULL);
		glCompileShader(vertexShader);
		checkCompileErrors(vertexShader, TYPE_VERTEX_SHDER);

		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
		glCompileShader(fragmentShader);
		checkCompileErrors(fragmentShader, TYPE_FRAMENT_SHDER);

		ID = glCreateProgram();
		glAttachShader(ID, vertexShader);
		glAttachShader(ID, fragmentShader);
		glLinkProgram(ID);
		checkCompileErrors(ID, TYPE_PROGRAM);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		
	}

	
	void use()
	{
		Shader* test = this;
		glUseProgram(ID);
	};
	void SetUniform3fByVec3(const char* paramNameString, glm::vec3 param)
	{
		glUniform3f(glGetUniformLocation(ID, paramNameString), param.x, param.y, param.z);

	};
	void SetUniform1f(const char * paramNameString, float param)
	{
		glUniform1f(glGetUniformLocation(ID, paramNameString), param);
	};
	void SetUniformMatrix4fv(const char * paramNameString, GLint size, GLboolean transpose, glm::mat4 param)
	{
		glUniformMatrix4fv(glGetUniformLocation(ID, paramNameString), 1, GL_FALSE, glm::value_ptr(param));
	};
	void SetUniform1i(const char * paramNameString, unsigned int slot)
	{
		glUniform1i(glGetUniformLocation(ID, paramNameString), slot);
	};
private:
	void checkCompileErrors(unsigned int ID, std::string type)
	{
		const unsigned int LOG_SIZE = 512;
		int success;
		char logInfo[LOG_SIZE];

		if (type == TYPE_VERTEX_SHDER || type == TYPE_FRAMENT_SHDER)
		{
			glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(ID, LOG_SIZE, NULL, logInfo);
				cout << type << " compile error: " << logInfo << endl;
			}
		}
		else if (type == TYPE_PROGRAM)
		{
			glGetProgramiv(ID, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(ID, LOG_SIZE, NULL, logInfo);
				cout << type << " linking error: " << logInfo << endl;

			}
		}

	};

	

};

