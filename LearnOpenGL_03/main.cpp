#include <glad/glad.h>
#include<GLFW/glfw3.h>

#include<iostream>
#include <vector>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include "SceneLoader.h"
#include "Scene.h"
#include "MyTestScript.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"



using namespace std;

int Object::id = 0;




const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;

SceneLoader* sceneLoader;

#pragma region Input Declare


double lastX;
double lastY;
bool isFirstMouse = true;


void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	//camera->ClearSpeed();

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		sceneLoader->GetCurrentScene()->mainCamera->MovInZAxias(20.0f);
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		sceneLoader->GetCurrentScene()->mainCamera->MovInZAxias(-20.0f);
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		sceneLoader->GetCurrentScene()->mainCamera->MovInXAxias(-15.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		sceneLoader->GetCurrentScene()->mainCamera->MovInXAxias(15.0f);
	}

}

void mouse_callback(GLFWwindow* window, double xPos, double yPos)
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
	sceneLoader->GetCurrentScene()->mainCamera->ProcessMouseMovement(deltaX, deltaY);
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

		 sceneLoader = new SceneLoader(window, WIDTH, HEIGHT,debugPath);
		 sceneLoader->GetCurrentScene()->input->RegisterCursorPosCallBack(mouse_callback);
		 sceneLoader->GetCurrentScene()->input->RegisterInputModeGroup(SetInputMode);
		 sceneLoader->GetCurrentScene()->input->RegisterToUpdate(processInput);
		
#pragma endregion

#pragma region SomeThing Init

		GameScript* myTestScript = new MyTestScript();
		sceneLoader->GetCurrentScene()->PushScript(myTestScript);
		sceneLoader->GetCurrentScene()->Init();
		sceneLoader->GetCurrentScene()->Awake();
		sceneLoader->GetCurrentScene()->OnEnable();


#pragma endregion


	while (!glfwWindowShouldClose(window))
	{
		//processInput
		/*processInput(window);*/
		
		sceneLoader->GetCurrentScene()->input->UpdateInput();

		
		//...render begin

		//clear screen
		glClearColor(0.5f, 0.5f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		
		//****
		//update mode mat
		//****
		//cube->Rotate(1.0f, glm::vec3(1.0f, 1.0f, 0));
		
		sceneLoader->GetCurrentScene()->Update();
		

		//...render end
		//Clear up,prepare for next render loop
		glfwSwapBuffers(window);
		glfwPollEvents();
		//update camera postion
		
	}

	sceneLoader->GetCurrentScene()->OnDisable();

	//Exit Programe 
	glfwTerminate();
	
	sceneLoader->Destroy(sceneLoader);
	return 0;

}
