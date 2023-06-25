#include <glad/glad.h>
#include<GLFW/glfw3.h>

#include<iostream>
#include <vector>
//#include <unistd.h>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include "SceneLoader.h"
#include "Scene.h"
#include "ScriptRegister.h" 

//#pragma region Include Custom GameScript
//
//#pragma endregion
//



#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"






using namespace std;

int Object::id = 0;

const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;

SceneLoader* sceneLoader;


//c++ 11
int test() {
	//func();
	int x = __cplusplus;
	cout << x << endl;
	return 0;
}


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

		
		//init glad
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

		 sceneLoader = new SceneLoader(window, WIDTH, HEIGHT);
		
		
#pragma endregion

#pragma region Init Custom GameScript Register

		 ScriptRegister* scriptRegister = new ScriptRegister();

#pragma endregion




#pragma region Scene Init Awake OnEnable

		sceneLoader->GetCurrentScene()->Init();
		sceneLoader->GetCurrentScene()->Awake();
		sceneLoader->GetCurrentScene()->OnEnable();


#pragma endregion


	while (!glfwWindowShouldClose(window))
	{
		//processInput
		/*processInput(window);*/
		
		

		
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
	
	sceneLoader->GetCurrentScene()->OnDestroy();
	sceneLoader->Delete<SceneLoader>(sceneLoader);

	return 0;

}
