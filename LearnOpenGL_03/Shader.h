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
#include "DestroyBase.h"

using namespace std;




class Shader:public Object,public DestroyBase
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


	Shader(const char* vertexPath, const char* fragmentPath, std::string _name, ShaderType type);


	void InitShader();

	
	void use();
	void SetUniform3fByVec3(const char* paramNameString, glm::vec3 param);
	void SetUniform1f(const char * paramNameString, float param);
	void SetUniformMatrix4fv(const char * paramNameString, GLint size, GLboolean transpose, glm::mat4 param);
	void SetUniform1i(const char * paramNameString, unsigned int slot);
private:
	void checkCompileErrors(unsigned int ID, std::string type);

	

};

