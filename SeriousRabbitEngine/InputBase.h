#pragma once
#include <glad/glad.h>
#include<GLFW/glfw3.h>
#include <vector>
class InputBase
{


	/*void(*UpdateCallBack)(GLFWwindow*);*/
public:

	/*virtual void KeyPressInputHandler() {};
	virtual void KeyDownInputHandler() {};
	virtual void KeyUpInputHandler() {};
	virtual void MouseMoveHandler() {};
	virtual void MouseLeftClickHandler() {};
	virtual void MouseRightClickHandler() {};
	virtual void MouseMiddleClickHandler() {};*/

	GLFWwindow* window;
	
	InputBase(GLFWwindow* window)
	{
		this->window = window;
	}

	/*virtual void RegisterToUpdate(void(*callback)(GLFWwindow*))
		= 0;*/
	/*virtual void RegisterCursorPosCallBack(void(*callback)(GLFWwindow* window, double xPos, double yPos)) 
		= 0;
	virtual void RegisterMouseButtonCallBack(void(*callback)(GLFWwindow* window, int button, int action, int mods))
		= 0;
	virtual void RegisterKeyButtonCallBack(void(*callback)(GLFWwindow* window, int key, int scancode, int action, int mods)) 
		= 0;*/
	/*virtual void RegisterInputModeGroup(void(*set_mode)(GLFWwindow* window))
		= 0;*/
/*
	virtual void UpdateInput()
	{
		UpdateCallBack(window);
	}
	*/
	

};

