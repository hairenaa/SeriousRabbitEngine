#pragma once
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include "Camera.h"
class PhysicsObject
{
public:
	glm::mat4 ModelMat;
	Camera* camera;

	PhysicsObject(Camera* _camera) 
	{
		this->camera = _camera;
	}
	PhysicsObject()
	{
		this->camera = nullptr;
	}
	virtual void Rotate(float angle,glm::vec3 axis)
	{
		ModelMat = glm::rotate(ModelMat, glm::radians(angle), axis);
		
	};
	virtual void Translate(glm::vec3 vec)
	{
		ModelMat = glm::translate(ModelMat, vec);
		
	};
	virtual void Scale(glm::vec3 scale)
	{
		ModelMat = glm::scale(ModelMat, scale);
		
	};

	virtual void UpdateBefore() 
	{
		if (camera != nullptr) 
		{
			camera->shader->SetUniformMatrix4fv(VERTEX_SHADER_VAR_MODEL_MAT, 1, GL_FALSE, ModelMat);
		}
		
	}

	

	
};

