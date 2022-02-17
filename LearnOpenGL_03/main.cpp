#include <glad/glad.h>
#include<GLFW/glfw3.h>

#include<iostream>
#include <vector>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include "SceneLoader.h"



#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"



using namespace std;



const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;

#pragma region Model Data


glm::vec3 cubePositions[] = {
  glm::vec3(0.0f,  0.0f,  0.0f),
  glm::vec3(1.0f,  2.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3(2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f,  3.0f, -7.5f),
  glm::vec3(1.3f, -2.0f, -2.5f),
  glm::vec3(1.5f,  2.0f, -2.5f),
  glm::vec3(1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f)
};



unsigned int indecies[] = {
	2,1,0,
	0,3,2
};


double lastX;
double lastY;
bool isFirstMouse=true;

#pragma endregion


#pragma region Init VARS
	
	
#pragma endregion





#pragma region Input Declare




void processInput(GLFWwindow* window) 
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) 
	{
		glfwSetWindowShouldClose(window,true);
	}

	//camera->ClearSpeed();
	
	if (glfwGetKey(window,GLFW_KEY_W) == GLFW_PRESS)
	{
		mainCamera->MovInZAxias(20.0f);
	}
	
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		mainCamera->MovInZAxias(-20.0f);
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		mainCamera->MovInXAxias(-15.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		mainCamera->MovInXAxias(15.0f);
	}
	
}

void mouse_callback(GLFWwindow* window,double xPos,double yPos) 
{
	if (isFirstMouse) 
	{
		lastX = xPos;
		lastY = yPos;
		isFirstMouse = false;
	}

	double deltaX, deltaY;
	deltaX = xPos - lastX;
	deltaY = yPos - lastY;

	lastX = xPos;
	lastY = yPos;
	double test = 1.44;
	mainCamera->ProcessMouseMovement(deltaX, deltaY);
}


void SetInputMode(GLFWwindow* window) 
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

#pragma endregion


int main(int argc,char* argv[])
{
	cout << argv[0]<<endl;
	std::string exePath = argv[0];

	
	std::string debugPath = exePath.substr(0, exePath.find_last_of('\\'));


	#pragma region Open a Window

		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		//open glfw window
		GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "MY OpenGL Game", NULL, NULL);

		if (window == NULL)
		{
			cout << "Open Window Failed!";
			glfwTerminate();
			return -1;
		}
		glfwMakeContextCurrent(window);

		
		//init glew
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return -1;
		}

		glViewport(0, 0, WIDTH, HEIGHT);

		glEnable(GL_DEPTH_TEST);
		stbi_set_flip_vertically_on_load(true);

	#pragma endregion

#pragma region  Init SceneLoader

		SceneLoader* sceneLoader = new SceneLoader(window, WIDTH, HEIGHT);

#pragma endregion


	while (!glfwWindowShouldClose(window))
	{
		//processInput
		/*processInput(window);*/
		
		input->UpdateInput();


		//...render begin

		//clear screen
		glClearColor(0.5f, 0.5f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		
		//****
		//update mode mat
		//****
		//cube->Rotate(1.0f, glm::vec3(1.0f, 1.0f, 0));
		model->Rotate(0.5f, glm::vec3(0, 1.0f, 0));
		cube->Rotate(0.5f, glm::vec3(1.0f, 1.0f, 0));
		cube->Translate(glm::vec3(0.01f, 0, 0));
		
		for (unsigned int i = 0; i < gameObjectVec.size(); i++)
		{

			
			GameObject* obj = gameObjectVec[i];
			obj->Draw();
			glDepthFunc(GL_LESS);
		

		}

		//...render end
		//Clear up,prepare for next render loop
		glfwSwapBuffers(window);
		glfwPollEvents();
		//update camera postion
		
	}

	//Exit Programe 
	glfwTerminate();

	for (unsigned int i = 0; i < gameObjectVec.size(); i++)
	{
		DestroyBase* obj = gameObjectVec[i];
		obj->Destroy(obj);
	}

	for (unsigned int i = 0; i < managers.size(); i++) 
	{
		DestroyBase* mana = managers[i];
		mana->Destroy(mana);
	}

	return 0;

}
