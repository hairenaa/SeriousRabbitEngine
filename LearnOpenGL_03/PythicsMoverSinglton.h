#pragma once
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include "GameObject.h"
#include "Camera.h"
#include "Single.h"
class PythicsMoverSinglton:public Single<PythicsMoverSinglton>
{
public:
	Camera* camera;
	void Rotate() 
	{
		
	};
	void Translate() 
	{
	
	};
	void Scale()
	{
		
	};
};

PythicsMoverSinglton* PythicsMoverSinglton::instance = nullptr;

