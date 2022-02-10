#pragma once
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>

class Camera
{
public:
	Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldup);
	Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldup);
	glm::vec3 Postion;
	glm::vec3 Forward;
	glm::vec3 Right;
	glm::vec3 Up;
	glm::vec3 WorldUp;
	glm::mat4 GetViewMatrix();
	float Pitch;
	float Yaw;
	float SensX= 0.000013f;
	float SensY= 0.000013f;
	glm::vec3 movVector;
	float speedMulZ = 0.1f;
	float speedMulY = 0.1f;
	float speedMulX = 0.05f;
	void ProcessMouseMovement(float deltaX, float deltaY);
	void UpdateCameraPos();
	void ClearSpeed();
	void MovInZAxias(int direction);
	void MovInXAxias(int direction);
	void MovInYAxias(int direction);
private:
	void updateCameraVectors();

};

