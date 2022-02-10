#include <glad/glad.h>
#include<GLFW/glfw3.h>

#include<iostream>

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

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


using namespace std;



const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;

#pragma region Model Data



float vertices[] = {
	// positions          // normals           // texture coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};

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

#pragma region Camera Declare
Camera* camera = new Camera(glm::vec3(0, 10, 200.0f), glm::radians(-2.3f), glm::radians(0.3f), glm::vec3(0, 1.0f, 0));
#pragma endregion

#pragma region Light Declare
LightDirectional* lightDirectional = new LightDirectional(glm::vec3(9.2f, 3.0f, 40.0f),
	glm::vec3(glm::radians(45.0f), glm::radians(45.0f),0));
LightPoint* lightPoint0 = new LightPoint(glm::vec3(3.0f, 0.0f, 0.0f),
	glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0),glm::vec3(1.0f,0.0f,0.0f));
LightPoint* lightPoint1 = new LightPoint(glm::vec3(0.0f, 3.0f, 0.0f),
	glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0), glm::vec3(0.0f, 1.0f, 0.0f));
LightPoint* lightPoint2 = new LightPoint(glm::vec3(0.0f, 0.0f, 3.0f),
	glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0), glm::vec3(0.0f, 0.0f, 1.0f));
LightPoint* lightPoint3 = new LightPoint(glm::vec3(5.0f, 5.0f, 5.0f),
	glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0), glm::vec3(0.0f, 1.0f, 1.0f));
LightSpot* lightSpot = new LightSpot(glm::vec3(0, 0, 4.0f),
	glm::vec3(glm::radians(0.0f), glm::radians(0.0f),0), glm::vec3(1.0f, 1.0f, 1.0f));

#pragma endregion


#pragma region Input Declare




void processInput(GLFWwindow* window) 
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) 
	{
		glfwSetWindowShouldClose(window,true);
	}

	camera->ClearSpeed();
	
	if (glfwGetKey(window,GLFW_KEY_W) == GLFW_PRESS)
	{
		camera->MovInZAxias(1);
	}
	
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera->MovInZAxias(-1);
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera->MovInXAxias(-1);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera->MovInXAxias(1);
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

	#pragma region Init Shader Program

		Shader* shader = new Shader("vertexSource.vert", "fragmentSource.frag");

	#pragma endregion

	#pragma region Init Material
		Material* material = new Material(shader);
		material->ambient_ins = 0.2f;
		material->diffuse_ins = 1.0f;
		material->specular_ins = 1.0f;
		material->shininess = material->SHININESS_32f;
	#pragma endregion


	#pragma region Init and load Models to VAO,VBO	
		Model* model = new Model(modelPath, shader, material);
	#pragma endregion
	
	#pragma region Prepare MVP matrices


		glm::mat4 modelMat;
		glm::mat4 viewMat;
		glm::mat4 projectionMat;
		float asp = (float)WIDTH / (float)HEIGHT;
		projectionMat = glm::perspective(glm::radians(90.0f),asp, 0.1f, 1000.0f);

	#pragma endregion

	while (!glfwWindowShouldClose(window))
	{
		//processInput
		processInput(window);
		
		//...render begin

		//clear screen
		glClearColor(0.5f, 0.5f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		
		//get view matrix
		viewMat = camera->GetViewMatrix();
		
		

		for (size_t i = 0; i < 1; i++)
		{
			
			// Set Model Matrix			
		
			modelMat = glm::rotate(glm::mat4(1.0f), glm::radians(200.0f), glm::vec3(0.0f, 1.0f, 0));
			modelMat = glm::translate(modelMat, cubePositions[i]);
			
			//Use Shader Program
			shader->use();
			

			////Set Material -> Textures 
			//glActiveTexture(GL_TEXTURE0);
			//glBindTexture(GL_TEXTURE_2D, TexBufferA);
			//glActiveTexture(GL_TEXTURE1);
			//glBindTexture(GL_TEXTURE_2D, TexBufferB);


			//Set Matrial Uniform
			//glUniform1i(glGetUniformLocation(shader->ID, "texture1"), 0);
			//glUniform1i(glGetUniformLocation(shader->ID, "texture2"), 1);

			//Set Matrix Uniform
			shader->SetUniformMatrix4fv("modelMat", 1, GL_FALSE, modelMat);
			shader->SetUniformMatrix4fv("viewMat", 1, GL_FALSE, viewMat);
			shader->SetUniformMatrix4fv("projectionMat", 1, GL_FALSE, projectionMat);

			shader->SetUniform3fByVec3("objColor", glm::vec3(1.0f, 1.0f, 1.0f));
			shader->SetUniform3fByVec3("ambientColor", glm::vec3(0.2f, 0.2f, 0.2f));
			/*shader->SetUniform3fByVec3("lightColor",lightDirectional->color);
			shader->SetUniform3fByVec3("lightPos", lightDirectional->position);
			shader->SetUniform3fByVec3("lightDirUniform", lightDirectional->direction); */
			shader->SetUniform3fByVec3("cameraPos", camera->Postion);
			

			shader->SetUniform3fByVec3("lightP0.pos", lightPoint0->position);
			shader->SetUniform3fByVec3("lightP0.color", lightPoint0->color);
			shader->SetUniform3fByVec3("lightP0.dir", lightPoint0->direction);
			shader->SetUniform1f("lightP0.constant", lightPoint0->constant);
			shader->SetUniform1f("lightP0.linear", lightPoint0->linear);
			shader->SetUniform1f("lightP0.quadratic", lightPoint0->quadratic);


			shader->SetUniform3fByVec3("lightP1.pos", lightPoint1->position);
			shader->SetUniform3fByVec3("lightP1.color", lightPoint1->color);
			shader->SetUniform3fByVec3("lightP1.dir", lightPoint1->direction);
			shader->SetUniform1f("lightP1.constant", lightPoint1->constant);
			shader->SetUniform1f("lightP1.linear", lightPoint1->linear);
			shader->SetUniform1f("lightP1.quadratic", lightPoint1->quadratic);


			shader->SetUniform3fByVec3("lightP2.pos", lightPoint2->position);
			shader->SetUniform3fByVec3("lightP2.color", lightPoint2->color);
			shader->SetUniform3fByVec3("lightP2.dir", lightPoint2->direction);
			shader->SetUniform1f("lightP2.constant", lightPoint2->constant);
			shader->SetUniform1f("lightP2.linear", lightPoint2->linear);
			shader->SetUniform1f("lightP2.quadratic", lightPoint2->quadratic);


			shader->SetUniform3fByVec3("lightP3.pos", lightPoint3->position);
			shader->SetUniform3fByVec3("lightP3.color", lightPoint3->color);
			shader->SetUniform3fByVec3("lightP3.dir", lightPoint3->direction);
			shader->SetUniform1f("lightP3.constant", lightPoint3->constant);
			shader->SetUniform1f("lightP3.linear", lightPoint3->linear);
			shader->SetUniform1f("lightP3.quadratic", lightPoint3->quadratic);


			shader->SetUniform3fByVec3("lightSpotl.pos", lightSpot->position);
			shader->SetUniform3fByVec3("lightSpot.color", lightSpot->color);
			shader->SetUniform3fByVec3("lightSpot.dir", lightSpot->direction);
			shader->SetUniform1f("lightSpot.cosInnerPhy", lightSpot->cosInnerPhy);
			shader->SetUniform1f("lightSpot.cosOutterPhy", lightSpot->cosOutterPhy);

			
			shader->SetUniform3fByVec3("lightDirectional.pos", lightDirectional->position);
			shader->SetUniform3fByVec3("lightDirectional.color", lightDirectional->color);
			shader->SetUniform3fByVec3("lightDirectional.dir", lightDirectional->direction);


			model->Draw();

		}



		//...render end
		
		//Clear up,prepare for next render loop
		glfwSwapBuffers(window);
		glfwPollEvents();
		//update camera postion
		camera->UpdateCameraPos();
	}

	//Exit Programe 
	glfwTerminate();

	delete shader;
	delete model;
	delete material;
	delete camera;
	delete lightDirectional;
	delete lightPoint0;
	delete lightPoint1;
	delete lightPoint2;
	delete lightPoint3;
	delete lightSpot;
	return 0;

}
