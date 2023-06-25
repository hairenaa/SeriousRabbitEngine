#include "SceneLoader.h"


SceneLoader* SceneLoader::instance = nullptr;

SceneLoader*  SceneLoader::Instance()
{
	if (instance != nullptr)
	{
		return instance;
	}
	else
	{
		throw new exception("no instance of SceneLoader!!");
	}
}

SceneLoader::SceneLoader(GLFWwindow* window, unsigned int width, unsigned int height)
{
	this->window = window;
	this->Height = height;
	this->Width = width;
	
	NewSceneInstance(SCENE_DEFAULT_NAME);
	instance = this;
}
SceneLoader::~SceneLoader()
{
	for (unsigned int i = 0; i < scenes.size(); i++)
	{
		Scene* scene = scenes[i];
		scene->Delete<Scene>(scene);
	}
}

Scene* SceneLoader::NewSceneInstance(std::string _name)
{
	Scene* scene = new Scene(this->window, _name, this->Width, this->Height);
	scenes.push_back(scene);
	return scene;
}

Scene* SceneLoader::LoadSceneInstance(std::string _name)
{
	//修改
	/*
	引擎初步设计类似于盖瑞模组，意味着需要一个软件来帮助开发者快速开发，因此首先要加入设置子物体的功能，让引擎运行时物体可以设置为摄像机的子物体，跟着摄像机移动，增加UI界面设置旋转缩放材质等UI组件，最后要有相关的保存场景的UI，保存后可以将此场景序列化为JSON文件，引擎的UI设置应该以JSON的方式保存到settings.json中。另外，每次在运行引擎时，sceneloader都要在初始化时加载settings中所指示的场景文件，而不是新创建一个场景。
	注：可以参考learnOpenGL的教程，如加载动画和实战章节。
	关于shader：
	https://www.zhihu.com/question/61140114#:~:text=It%27s%20very%20simple.%20You%20just%20use%20glUseProgram,%28program_id%29%20switch%20between%20shaders%20during%20the%20run-time%20step.
	关于c++序列化：
	https://www.zhihu.com/question/266845585 
	关于粒子效果：
	https://learnopengl-cn.github.io/06%20In%20Practice/2D-Game/06%20Particles/
	关于骨骼动画：
	https://learnopengl-cn.github.io/08%20Guest%20Articles/2020/01%20Skeletal%20Animation/
	learnOpenGL官网：
	https://learnopengl-cn.github.io/
	由于码量巨大此项目封存中。。。。。。
	*/

	std::string fileName = ConfValues::Instance()->GetConfigValue(CONF_SCENE_CURRENT_FILE_NAME_KEY);
	std::string loadPath = WinApiUtil::GetProjectRootPath() + "//" + fileName;
	//Serialization::Deserialize(loadPath) 反序列化为scene对象
	//Scene* scene= ;
	return nullptr;
}


Scene* SceneLoader::GetCurrentScene()
{
	if (scenes.empty())
	{
		throw new exception("no scene in this window!!");
	}
	if (this->Index >= 0 && this->Index < scenes.size())
	{
		return this->scenes[this->Index];
	}
	return this->scenes[0];


}
void SceneLoader::ChangeSceneNext()
{

	if (this->Index < this->scenes.size() - 1)
	{
		this->Index++;
	}

}

void SceneLoader::ChangeSceneByName(std::string _name)
{
	for (unsigned int i = 0; i < scenes.size(); i++)
	{
		Scene* sce = scenes[i];
		if (sce->name == _name)
		{
			this->Index = i;
			break;
		}
	}
}

Scene* SceneLoader::GetSceneByName(std::string _name)
{
	for (unsigned int i = 0; i < scenes.size(); i++)
	{
		Scene* sce = scenes[i];
		if (sce->name == _name)
		{
			return sce;
		}
	}
}


