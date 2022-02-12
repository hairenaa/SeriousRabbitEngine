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


#pragma region Init GameObjectVector
	std::vector<GameObject*> gameObjectVec;
	Camera* camera;
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
		camera->MovInZAxias(20.0f);
	}
	
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera->MovInZAxias(-20.0f);
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera->MovInXAxias(-5.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera->MovInXAxias(5.0f);
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
	camera->ProcessMouseMovement(deltaX, deltaY);
}

#pragma endregion



int main(int argc,char* argv[])
{
	cout << argv[0]<<endl;
	std::string exePath = argv[0];

		//"\\model\\Crysis\\nanosuit.obj"
		// "\\model\\aigei\\pearl\\pearl.obj"
		//"\\model\\test\\test2.obj"
		//"\\model\\backpack\\backpack.obj"
		//"\\model\\Dog\\Doguinho.obj"
		//"\\model\\erciyuan\\shaonv\\luomo.obj"

	std::string modelPath = exePath.substr(0, exePath.find_last_of('\\')) + "\\model\\Crysis\\nanosuit.obj";
	std::cout <<modelPath << endl;

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


		Shader* shader = new Shader("vertexSource.vert", "fragmentSource.frag");
		camera = new Camera("MainCamera", shader, glm::vec3(0, 10, 200.0f), glm::radians(-2.3f), glm::radians(0.3f), glm::vec3(0, 1.0f, 0));

		LightDirectional* lightDirectional = new LightDirectional("lightDirectional", shader, glm::vec3(9.2f, 3.0f, 40.0f),
			glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0));
		LightPoint* lightPoint0 = new LightPoint("lightP0", shader, glm::vec3(3.0f, 0.0f, 0.0f),
			glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0), glm::vec3(1.0f, 0.0f, 0.0f));
		LightPoint* lightPoint1 = new LightPoint("lightP1", shader, glm::vec3(0.0f, 3.0f, 0.0f),
			glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0), glm::vec3(0.0f, 1.0f, 0.0f));
		LightPoint* lightPoint2 = new LightPoint("lightP2", shader, glm::vec3(0.0f, 0.0f, 3.0f),
			glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0), glm::vec3(0.0f, 0.0f, 1.0f));
		LightPoint* lightPoint3 = new LightPoint("lightP3", shader, glm::vec3(5.0f, 5.0f, 5.0f),
			glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0), glm::vec3(0.0f, 1.0f, 1.0f));
		LightSpot* lightSpot = new LightSpot("lightSpot", shader, glm::vec3(0, 0, 4.0f),
			glm::vec3(glm::radians(0.0f), glm::radians(0.0f), 0), glm::vec3(1.0f, 1.0f, 1.0f));
		Model* model = new Model("material", modelPath, shader);

		
		gameObjectVec.push_back(lightDirectional);
		gameObjectVec.push_back(lightPoint0);
		gameObjectVec.push_back(lightPoint1);
		gameObjectVec.push_back(lightPoint2);
		gameObjectVec.push_back(lightPoint3);
		gameObjectVec.push_back(lightSpot);
		gameObjectVec.push_back(model);
		gameObjectVec.push_back(camera);

#pragma endregion


	#pragma region Prepare MVP matrices


		glm::mat4 modelMat;
		glm::mat4 viewMat;
		glm::mat4 projectionMat;
		float asp = (float)WIDTH / (float)HEIGHT;
		projectionMat = glm::perspective(glm::radians(90.0f),asp, 0.1f, 1000.0f);
		camera->ProjectionMat = projectionMat;


	#pragma endregion

	while (!glfwWindowShouldClose(window))
	{
		//processInput
		processInput(window);
		
		//...render begin

		//clear screen
		glClearColor(0.5f, 0.5f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		
		

		for (size_t i = 0; i < 1; i++)
		{
			
			
		
			modelMat = glm::rotate(glm::mat4(1.0f), glm::radians(200.0f), glm::vec3(0.0f, 1.0f, 0));
			modelMat = glm::translate(modelMat, cubePositions[i]);
			camera->ModelMat = modelMat;
			
			shader->use();

			for (unsigned int i = 0; i < gameObjectVec.size(); i++)
			{
				GameObject* obj = gameObjectVec[i];
				obj->Draw();
			}


		/*	
			lightDirectional->Draw();
			lightPoint0->Draw();
			lightPoint1->Draw();
			lightPoint2->Draw();
			lightPoint3->Draw();
			lightSpot->Draw();

			model->Draw();

			camera->Draw();*/
		
		
		}



		//...render end
		
		//Clear up,prepare for next render loop
		glfwSwapBuffers(window);
		glfwPollEvents();
		//update camera postion
		
	}

	//Exit Programe 
	glfwTerminate();

	delete shader;
	delete model;
	delete camera;
	delete lightDirectional;
	delete lightPoint0;
	delete lightPoint1;
	delete lightPoint2;
	delete lightPoint3;
	delete lightSpot;
	return 0;

}
