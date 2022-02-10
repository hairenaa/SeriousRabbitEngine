#pragma once
#include "Shader.h"

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include <vector>




class Material
{
public:
	const  float SHININESS_32f = 32.0f;
	const float SHININESS_64f = 64.0f;
	const float SHININESS_128f = 128.0f;
	const float SHININESS_256f = 256.0f;
	Shader* shader;
	float ambient_ins = 0.2f;
	float diffuse_ins=1.0f;
	float specular_ins=1.0f;
	float shininess=SHININESS_32f;
	Material(Shader* _shader, float _ambient_ins, float _diffuse_ins, float _specular_ins, float _shininess);
	Material(Shader* _shader);
	void Draw();
};

