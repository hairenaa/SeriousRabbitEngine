#pragma once
#include "Camera.h"



Camera::~Camera()
{
	for (unsigned int i = 0; i < shaders.size(); i++)
	{
		if (shaders[i] != nullptr)
		{
			shaders[i] = nullptr;
		}

	}
}

//******************************************************************************
Camera::Camera(std::string _name, Shader* _shader, float _screen_width, float _scree_height, glm::vec3 position, glm::vec3 target, glm::vec3 worldup)
	:GameObject(_name, _shader)
{
	shaders.push_back(_shader);
	Postion = position;
	WorldUp = worldup;
	Forward = glm::normalize(target - position);
	Right = glm::normalize(glm::cross(Forward, worldup));
	Up = glm::normalize(glm::cross(Right, Forward));
	Asp = _screen_width / _scree_height;
	ProjectionMat = glm::perspective(Fov, Asp, MinDis, MaxDis);

};
Camera::Camera(std::string _name, Shader* _shader, float _screen_width, float _scree_height, glm::vec3 position, float pitch, float yaw, glm::vec3 worldup)
	:GameObject(_name, _shader)
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
	ProjectionMat = glm::perspective(Fov, Asp, MinDis, MaxDis);

};

void Camera::SetMaxDis(float maxDis)
{
	this->MaxDis = maxDis;
	ProjectionMat = glm::perspective(Fov, Asp, MinDis, MaxDis);
}

void Camera::SetMinDis(float minDis)
{
	this->MinDis = minDis;
	ProjectionMat = glm::perspective(Fov, Asp, MinDis, MaxDis);
}


void Camera::SetFov(float fov)
{
	this->Fov = fov;
	ProjectionMat = glm::perspective(Fov, Asp, MinDis, MaxDis);
}

void Camera::SetMaxPitch(float top_pitch_angle)
{
	this->MaxPitch = glm::radians(top_pitch_angle);
}

void Camera::SetMinPitch(float bottom_pitch_angle)
{
	this->MinPitch = glm::radians(bottom_pitch_angle);
}

void Camera::ProcessMouseMovement(float deltaX, float deltaY)
{

	Pitch -= deltaY * SensY;
	//std::cout << Pitch << endl;
	Yaw += deltaX * SensX;
	Pitch = Pitch > MaxPitch ? MaxPitch : Pitch;
	Pitch = Pitch < MinPitch ? MinPitch : Pitch;
	updateCameraVectors();

};


void Camera::MovInZAxias(float speed)
{
	movVector += speed * speedMulZ * Forward;

};
void Camera::MovInXAxias(float speed)
{
	movVector += speed * speedMulX *Right;
};
void Camera::MovInYAxias(float speed)
{
	movVector += speed * speedMulY * Up;

};
void Camera::Draw()
{
	for (unsigned int i = 0; i < shaders.size(); i++)
	{
		Shader* shader = shaders[i];
		shader->use();
		ViewMat = this->GetViewMatrix();
		if (shader->shaderType == Shader::SKYBOX_SHADER)
		{
			shader->SetUniformMatrix4fv(VERTEX_SHADER_VAR_VIEW_MAT, 1, GL_FALSE, glm::mat4(glm::mat3(ViewMat)));
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



void Camera::updateCameraVectors()
{
	Forward.x = glm::cos(Pitch)*glm::sin(Yaw);
	Forward.y = glm::sin(Pitch);
	Forward.z = -glm::cos(Pitch)*glm::cos(Yaw);
	Forward = glm::normalize(Forward);
	Right = glm::normalize(glm::cross(Forward, WorldUp));
	Up = glm::normalize(glm::cross(Right, Forward));
};

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(Postion, Postion + Forward, WorldUp);
};


void Camera::UpdateCameraPos()
{
	//glm::vec3(speedX*speedMulX, 0, -speedZ*speedMulZ);
	Postion += movVector;
	ClearSpeed();
};
void Camera::ClearSpeed()
{
	movVector.x = 0;
	movVector.y = 0;
	movVector.z = 0;
};