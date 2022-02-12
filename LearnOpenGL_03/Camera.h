#pragma once
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include "GameObject.h"
#include "Shader.h"

class Camera:public GameObject
{
public:
	Shader* shader;
	glm::mat4 ModelMat;
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
	float speedMulZ = 0.1f;
	float speedMulY = 0.1f;
	float speedMulX = 0.05f;
	

	Camera(std::string name, Shader* _shader, glm::vec3 position, glm::vec3 target, glm::vec3 worldup)
	{
		this->name = name;
		this->shader = _shader;
		Postion = position;
		WorldUp = worldup;
		Forward = glm::normalize(target - position);
		Right = glm::normalize(glm::cross(Forward, worldup));
		Up = glm::normalize(glm::cross(Right, Forward));


	};
	Camera(std::string name, Shader* _shader, glm::vec3 position, float pitch, float yaw, glm::vec3 worldup)
	{
		this->name = name;
		this->shader = _shader;
		Postion = position;
		WorldUp = worldup;
		Pitch = pitch;
		Yaw = yaw;
		Forward.x = glm::cos(Pitch)*glm::sin(Yaw);
		Forward.y = glm::sin(Pitch);
		Forward.z = -glm::cos(Pitch)*glm::cos(Yaw);
		Right = glm::normalize(glm::cross(Forward, WorldUp));
		Up = glm::normalize(glm::cross(Right, Forward));
	};
	glm::mat4 GetViewMatrix()
	{
		return glm::lookAt(Postion, Postion + Forward, WorldUp);
	};

	void ProcessMouseMovement(float deltaX, float deltaY)
	{

		Pitch -= deltaY * SensY;
		Yaw += deltaX * SensX;
		Pitch = Pitch > 89.0f ? 89.0f : Pitch;
		Pitch = Pitch < -89.0f ? -89.0f : Pitch;
		updateCameraVectors();

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
	void MovInZAxias(int direction)
	{
		movVector += direction * speedMulZ * Forward;

	};
	void MovInXAxias(int direction)
	{
		movVector += direction * speedMulX *Right;
	};
	void MovInYAxias(int direction)
	{
		movVector += direction * speedMulY * Up;

	};
	void Draw() 
	{
		ViewMat = this->GetViewMatrix();
		shader->SetUniformMatrix4fv("modelMat", 1, GL_FALSE, ModelMat);
		shader->SetUniformMatrix4fv("viewMat", 1, GL_FALSE, ViewMat);
		shader->SetUniformMatrix4fv("projectionMat", 1, GL_FALSE, ProjectionMat);
		shader->SetUniform3fByVec3("cameraPos",this->Postion);
		this->UpdateCameraPos();
		

	};
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

};

