#pragma once
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "ConstValues.h"
#include "GameObject.h"
#include <vector>



class Camera:public GameObject
{
protected:
	float Asp;
	float Fov = 30.0f;
	float MinDis = 0.1f;
	float MaxDis = 1000.0f;
	float MaxPitch = 1.553343f;
	float MinPitch = -1.553343f;
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
	float SensX = 0.00013f;
	float SensY = 0.00013f;
	glm::vec3 movVector;
	float speedMulZ = 0.01f;
	float speedMulY = 0.01f;
	float speedMulX = 0.01f;
	
	std::vector<Shader*> shaders;


	~Camera();
	

	
	//******************************************************************************
	Camera(std::string _name, Shader* _shader, float _screen_width, float _scree_height, glm::vec3 position, glm::vec3 target, glm::vec3 worldup);
	Camera(std::string _name, Shader* _shader, float _screen_width, float _scree_height, glm::vec3 position, float pitch, float yaw, glm::vec3 worldup);
	
	void SetMaxDis(float maxDis);

	void SetMinDis(float minDis);


	void SetFov(float fov);

	void SetMaxPitch(float top_pitch_angle);

	void SetMinPitch(float bottom_pitch_angle);

	void ProcessMouseMovement(float deltaX, float deltaY);

	
	void MovInZAxias(float speed);
	void MovInXAxias(float speed);
		void MovInYAxias(float speed);
		void Draw();
	
private:
	void updateCameraVectors();

	glm::mat4 GetViewMatrix();


	void UpdateCameraPos();
	void ClearSpeed();
};

