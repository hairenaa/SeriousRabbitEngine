#include "Camera.h"


Camera::Camera(glm::vec3 position,glm::vec3 target,glm::vec3 worldup) 
{
	Postion = position;
	WorldUp = worldup;
	Forward = glm::normalize(target - position);
	Right =glm::normalize( glm::cross(Forward, worldup));
	Up =glm::normalize( glm::cross(Right, Forward));


}


Camera::Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldup) 
{
	Postion = position;
	WorldUp = worldup;
	Pitch = pitch;
	Yaw = yaw;
	Forward.x = glm::cos(Pitch)*glm::sin(Yaw);
	Forward.y = glm::sin(Pitch);
	Forward.z = -glm::cos(Pitch)*glm::cos(Yaw);
	Right = glm::normalize(glm::cross(Forward, WorldUp));
	Up = glm::normalize(glm::cross(Right, Forward));
}

glm::mat4 Camera::GetViewMatrix() 
{
	return glm::lookAt(Postion, Postion+Forward, WorldUp);
}

void Camera::updateCameraVectors() 
{
	Forward.x = glm::cos(Pitch)*glm::sin(Yaw);
	Forward.y = glm::sin(Pitch);
	Forward.z = -glm::cos(Pitch)*glm::cos(Yaw);
	Forward = glm::normalize(Forward);
	Right = glm::normalize(glm::cross(Forward, WorldUp));
	Up = glm::normalize(glm::cross(Right, Forward));
}


void Camera::ProcessMouseMovement(float deltaX, float deltaY) 
{

	Pitch -= deltaY*SensY;
	Yaw += deltaX *SensX;
	Pitch = Pitch > 89.0f ? 89.0f : Pitch;
	Pitch = Pitch < -89.0f ? -89.0f : Pitch;
	updateCameraVectors();

}


void Camera::UpdateCameraPos() 
{
	//glm::vec3(speedX*speedMulX, 0, -speedZ*speedMulZ);
	Postion += movVector;
	
}


void Camera::ClearSpeed() 
{
	movVector.x = 0;
	movVector.y = 0;
	movVector.z = 0;
}


void Camera::MovInZAxias(int direction) 
{
	movVector += direction * speedMulZ * Forward;
	
}


void Camera::MovInXAxias(int direction)
{
	movVector +=  direction * speedMulX *Right;
}


void Camera::MovInYAxias(int direction)
{
	movVector +=  direction * speedMulY * Up;
	
}