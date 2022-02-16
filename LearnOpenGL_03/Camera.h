#pragma once
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include "GameObject.h"
#include "Shader.h"
#include "ConstValues.h"
#include <vector>
class Camera:public GameObject
{
public:
	
	glm::mat4 ViewMat;
	glm::mat4 ProjectionMat;
	glm::vec3 Postion;
	glm::vec3 Forward;
	glm::vec3 Right;
	glm::vec3 Up;
	glm::vec3 WorldUp;
	float Pitch;
	float Yaw;
	float SensX = 0.000013f;
	float SensY = 0.000013f;
	glm::vec3 movVector;
	float speedMulZ = 0.01f;
	float speedMulY = 0.01f;
	float speedMulX = 0.01f;
	float Asp;
	float Fov=90.0f;
	float MinDis=0.1f;
	float MaxDis = 1000.0f;
	std::vector<Shader*> shaders;
	Camera(std::string _name, Shader* _shader,float _screen_width,float _scree_height, glm::vec3 position, glm::vec3 target, glm::vec3 worldup)
		:GameObject(_name,_shader)
	{
		shaders.push_back(_shader);
		Postion = position;
		WorldUp = worldup;
		Forward = glm::normalize(target - position);
		Right = glm::normalize(glm::cross(Forward, worldup));
		Up = glm::normalize(glm::cross(Right, Forward));
		Asp = _screen_width / _scree_height;
		ProjectionMat = glm::perspective(glm::radians(Fov), Asp, MinDis, MaxDis);

	};
	Camera(std::string _name, Shader* _shader, float _screen_width, float _scree_height, glm::vec3 position, float pitch, float yaw, glm::vec3 worldup)
		:GameObject(_name,_shader)
	{
		shaders.push_back(_shader);
		Postion = position;
		WorldUp = worldup;
		Pitch = pitch;
		Yaw = yaw;
		Forward.x = glm::cos(Pitch)*glm::sin(Yaw);
		Forward.y = glm::sin(Pitch);
		Forward.z = -glm::cos(Pitch)*glm::cos(Yaw);
		Right = glm::normalize(glm::cross(Forward, WorldUp));
		Up = glm::normalize(glm::cross(Right, Forward));
		Asp = _screen_width / _scree_height;
		ProjectionMat = glm::perspective(glm::radians(Fov), Asp, MinDis, MaxDis);

	};
	
	void ProcessMouseMovement(float deltaX, float deltaY)
	{

		Pitch -= deltaY * SensY;
		Yaw += deltaX * SensX;
		Pitch = Pitch > 89.0f ? 89.0f : Pitch;
		Pitch = Pitch < -89.0f ? -89.0f : Pitch;
		updateCameraVectors();

	};

	
	void MovInZAxias(float speed)
	{
		movVector += speed * speedMulZ * Forward;

	};
	void MovInXAxias(float speed)
	{
		movVector += speed * speedMulX *Right;
	};
	void MovInYAxias(float speed)
	{
		movVector += speed * speedMulY * Up;

	};
	void Draw()
	{
		for (unsigned int i = 0; i < shaders.size(); i++)
		{
			shaders[i]->use();
			ViewMat = this->GetViewMatrix();
			if (shader->shaderType == Shader::SKYBOX_SHADER) 
			{
				shader->SetUniformMatrix4fv(VERTEX_SHADER_VAR_VIEW_MAT, 1, GL_FALSE,glm::mat4( glm::mat3(ViewMat)));
			}
			else
			{
				shader->SetUniformMatrix4fv(VERTEX_SHADER_VAR_VIEW_MAT, 1, GL_FALSE, ViewMat);
				shader->SetUniform3fByVec3(FRAGMENT_SHADER_VAR_CAMERA_POS, this->Postion);
			}
			//shader->SetUniformMatrix4fv(VERTEX_SHADER_VAR_MODEL_MAT, 1, GL_FALSE, ModelMat);
			shader->SetUniformMatrix4fv(VERTEX_SHADER_VAR_PROJECTION_MAT, 1, GL_FALSE, ProjectionMat);
			
		}
		
		this->UpdateCameraPos();
	}
	
private:
	void updateCameraVectors()
	{
		Forward.x = glm::cos(Pitch)*glm::sin(Yaw);
		Forward.y = glm::sin(Pitch);
		Forward.z = -glm::cos(Pitch)*glm::cos(Yaw);
		Forward = glm::normalize(Forward);
		Right = glm::normalize(glm::cross(Forward, WorldUp));
		Up = glm::normalize(glm::cross(Right, Forward));
	};

	glm::mat4 GetViewMatrix()
	{
		return glm::lookAt(Postion, Postion + Forward, WorldUp);
	};


	void UpdateCameraPos()
	{
		//glm::vec3(speedX*speedMulX, 0, -speedZ*speedMulZ);
		Postion += movVector;
		ClearSpeed();
	};
	void ClearSpeed()
	{
		movVector.x = 0;
		movVector.y = 0;
		movVector.z = 0;
	};
};

