#pragma once
#include "Shader.h"


Shader::Shader(const char* vertexPath, const char* fragmentPath, std::string _name, ShaderType type) 
	:Object(_name)
{

	try
	{
		this->shaderType = type;
		Unhandled_vertext_source = ShaderFileUtil::ReadAllText(vertexPath).c_str();
		Unhandled_fragment_source = ShaderFileUtil::ReadAllText(fragmentPath);


	}
	catch (const std::exception& ex)
	{
		printf(ex.what());
	}

}



void Shader::InitShader()
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


void Shader::use()
{
	Shader* test = this;
	glUseProgram(ID);
};



void Shader::SetUniform3fByVec3(const char* paramNameString, glm::vec3 param)
{
	glUniform3f(glGetUniformLocation(ID, paramNameString), param.x, param.y, param.z);

};
void Shader::SetUniform1f(const char * paramNameString, float param)
{
	glUniform1f(glGetUniformLocation(ID, paramNameString), param);
};
void Shader::SetUniformMatrix4fv(const char * paramNameString, GLint size, GLboolean transpose, glm::mat4 param)
{
	glUniformMatrix4fv(glGetUniformLocation(ID, paramNameString), 1, GL_FALSE, glm::value_ptr(param));
};
void Shader::SetUniform1i(const char * paramNameString, unsigned int slot)
{
	glUniform1i(glGetUniformLocation(ID, paramNameString), slot);
};


void Shader::checkCompileErrors(unsigned int ID, std::string type)
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