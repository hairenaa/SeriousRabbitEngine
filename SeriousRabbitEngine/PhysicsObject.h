#pragma once
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include "Camera.h"
#include "DestroyBase.h"
#include "GameHelper.h"

class PhysicsObject
{
protected:
	glm::vec3 position;
	glm::vec3 angles;
	glm::vec3 scale;

public:
	glm::mat4 ModelMat;
	Camera* camera;



	PhysicsObject(Camera* _camera)
	{
		this->camera = _camera;
	}

	PhysicsObject()
	{
		this->camera = GameHelper::GetMainCameraFromCurrentScene();
	}

	~PhysicsObject()
	{
		if (this->camera != nullptr) 
		{
			this->camera = nullptr;
		}
	}

	void SetPosition(glm::vec3 pos)
	{
		glm::vec3 sub = pos - this->position;
		if (sub != glm::vec3(0, 0, 0))
		{
			Translate(sub);
		}

	}

	void SetAngles(glm::vec3 angles)
	{
		glm::vec3 sub = angles - this->angles;
		if (sub != glm::vec3(0, 0, 0))
		{
			Rotate(sub);
		}

	}

	void SetScale(glm::vec3 scale)
	{
		glm::vec3 sub = scale - this->scale;
		if (sub != glm::vec3(0, 0, 0))
		{
			Scale(sub);
		}

	}


	glm::vec3 GetPosition()
	{
		return this->position;
	}

	glm::vec3 GetAngles()
	{
		return this->angles;
	}

	glm::vec3 GetScale() 
	{
		return this->scale;
	}

	virtual void Rotate(glm::vec3 angle)
	{
		this->angles += angle;
		float len= glm::length(angle);
		glm::vec3 axis= glm::normalize(angle);
		
		ModelMat = glm::rotate(ModelMat, len, axis);
		
		
	};
	virtual void Translate(glm::vec3 vec)
	{
		this->position += vec;
		ModelMat = glm::translate(ModelMat, vec);
		
	};
	virtual void Scale(glm::vec3 scale)
	{
		this->scale += scale;
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

