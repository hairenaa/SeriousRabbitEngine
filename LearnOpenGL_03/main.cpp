#include <glad/glad.h>
#include<GLFW/glfw3.h>

#include<iostream>
#include <vector>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
//

#include "Shader.h"
#include "Camera.h"
#include "Material.h"
#include "LightDirectional.h"
#include "LightPoint.h"
#include "LightSpot.h"
#include "Mesh.h"
#include "Model.h"
#include "GameObject.h"
#include "Cube.h"
#include "LightManager.h"
#include "Manager.h"
#include "SkyBox.h"
#include "DestroyBase.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"



using namespace std;


int GameObject::id = 0;
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
	std::vector<GameObject*> gameObjectVec;
	Shader* mainShader = nullptr;
	Camera* mainCamera=nullptr;
	
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
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwSetCursorPosCallback(window, mouse_callback);

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

#pragma region  Init GameObjects

		
		//init mainShader
		mainShader = new Shader(SHADER_DEFAULT_FILE_VERTEX, SHADER_DEFAULT_FILE_FRAGMENT,Shader::MAIN_SHADER);

		Shader* skyShader = new Shader("SkyBoxVertex.vert", "SkyboxFragment.frag",Shader::SKYBOX_SHADER);

		//init managers to handle the shader source code
		std::vector<Manager*> managers;
		managers.push_back(LightManager::Instance());

		//manager build something 
		Light* lightDirectional = LightManager::Instance()->Build(LightManager::LIGHT_DIRECTIONAL, "lightDirectional", mainShader, glm::vec3(9.2f, 3.0f, 40.0f),
			glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0));
		Light* lightPoint0 = LightManager::Instance()->Build(LightManager::LIGHT_POINT, "lightP0", mainShader, glm::vec3(3.0f, 0.0f, 0.0f),
			glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0), glm::vec3(1.0f, 0.0f, 0.0f));
		Light* lightPoint1 = LightManager::Instance()->Build(LightManager::LIGHT_POINT, "lightP1", mainShader, glm::vec3(0.0f, 3.0f, 0.0f),
			glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0), glm::vec3(0.0f, 1.0f, 0.0f));
		Light* lightPoint2 = LightManager::Instance()->Build(LightManager::LIGHT_POINT, "lightP2", mainShader, glm::vec3(3.0f, 0.0f, 0.0f),
			glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0), glm::vec3(0.3f, 0.5f, 0.5f));

		for (unsigned int i = 0; i < managers.size(); i++)
		{
			Manager* manager = managers[i];
			if (manager->handleType == Manager::HANDLE_FRAGMENT)
			{
				mainShader->Unhandled_fragment_source= manager->HandleShaderSource(mainShader->Unhandled_fragment_source);
			}
			else if (manager->handleType == Manager::HANDLE_VERTEX)
			{
				mainShader->Unhandled_vertext_source = manager->HandleShaderSource(mainShader->Unhandled_vertext_source);
			}

		}

		//init shader
		mainShader->InitShader();
		skyShader->InitShader();

		mainCamera = new Camera("MainCamera", mainShader, WIDTH, HEIGHT, glm::vec3(0, 10, 200.0f), glm::radians(-2.3f), glm::radians(0.3f), glm::vec3(0, 1.0f, 0));
		mainCamera->shaders.push_back(skyShader);

		Light* lightSpot = LightManager::Instance()->Build(LightManager::LIGHT_SPOT, "lightSpot", mainShader,glm::vec3(0, 0, 4.0f),
			glm::vec3(glm::radians(0.0f), glm::radians(0.0f), 0), glm::vec3(1.0f, 1.0f, 1.0f));
		Cube* cube = new Cube("cube1", mainShader,mainCamera,"awesomeface.png");
		

		//"\\model\\Crysis\\nanosuit.obj"
	// "\\model\\aigei\\pearl\\pearl.obj"
	//"\\model\\test\\test2.obj"
	//"\\model\\backpack\\backpack.obj"
	//"\\model\\Dog\\Doguinho.obj"
	//"\\model\\erciyuan\\shaonv\\luomo.obj"
		std::string modelPath = debugPath + "\\model\\Crysis\\nanosuit.obj";
		std::string texturePath = debugPath + "\\texture\\skybox\\default";
		std::cout << "modelPath is :" << modelPath << endl;
		std::cout << "texturePath is :" << texturePath << endl;

		Model* model = new Model("model1", modelPath, mainShader,mainCamera);
		SkyBox* skybox = new SkyBox("skybox", skyShader, mainCamera, texturePath);
		//skybox->cube->Scale(glm::vec3(1900.0f, 1900.0f, 1900.0f));
		
		//update model mat
		gameObjectVec.push_back(mainCamera);

		gameObjectVec.push_back(lightDirectional);
		gameObjectVec.push_back(lightPoint0);
		gameObjectVec.push_back(lightPoint1);
		/*gameObjectVec.push_back(lightPoint2);
		gameObjectVec.push_back(lightPoint3);*/
		gameObjectVec.push_back(lightSpot);
		gameObjectVec.push_back(cube);
		//reset model mat
		gameObjectVec.push_back(model);
		gameObjectVec.push_back(skybox);
		

#pragma endregion


	while (!glfwWindowShouldClose(window))
	{
		//processInput
		processInput(window);
		
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
