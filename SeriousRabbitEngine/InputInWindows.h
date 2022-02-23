#pragma once

#include "InputBase.h"
#include "Single.h"
#include <glad/glad.h>
#include<GLFW/glfw3.h>
#include "GameScriptAdapter.h"

class InputInWindows:public InputBase
{

	
public:
	InputInWindows(GLFWwindow* window):InputBase(window)
	{
	}

	//virtual void RegisterToUpdate(void(*callback)(GLFWwindow*))
	//{
	//	this->UpdateCallBack = callback;
	//}
	/*virtual void RegisterCursorPosCallBack(void(*callback)(GLFWwindow* window, double xPos, double yPos))
	{
		glfwSetCursorPosCallback(window, callback);
	}
	virtual void RegisterMouseButtonCallBack(void(*callback)(GLFWwindow* window, int button, int action, int mods))
	{
		glfwSetMouseButtonCallback(window, callback);
	}

	virtual void RegisterKeyButtonCallBack(void(*callback)(GLFWwindow* window, int key, int scancode, int action, int mods))
	{

		glfwSetKeyCallback(window, callback);
	}
*/
	/*virtual void RegisterInputModeGroup(void(*set_mode)(GLFWwindow* window))
	{
		set_mode(window);
	}*/

	
};

