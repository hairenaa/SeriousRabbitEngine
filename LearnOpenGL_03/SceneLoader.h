#pragma once
#include <vector>
#include <glad/glad.h>
#include<GLFW/glfw3.h>
#include "Scene.h"
#include <string>
#include "Object.h"
#include "DestroyBase.h"
class SceneLoader:public DestroyBase
{
private:
	
	GLFWwindow* window;
	unsigned int Width;
	unsigned int Height;
	static SceneLoader* instance;
public:
	std::vector<Scene*> scenes;
	std::string TargetPath="";
	
	unsigned int Index = 0;

	static SceneLoader*  Instance();
	
	SceneLoader(GLFWwindow* window, unsigned int width, unsigned int height, std::string targetPath);
	
	~SceneLoader();
	
	Scene* NewSceneInstance(std::string _name);


	Scene* GetCurrentScene();
	
	void ChangeSceneNext();


	void ChangeSceneByName(std::string _name);
	
	Scene* GetSceneByName(std::string _name);
	


};

