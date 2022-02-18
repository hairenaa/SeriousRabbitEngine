#include "Scene.h"


Scene::Scene(GLFWwindow* window, std::string _name, unsigned int width, unsigned int height, std::string targetPath) :Object(_name)
{
	this->window = window;
	this->input = new InputInWindows(window);
	this->Width = width;
	this->Height = height;
	this->TargetPath = targetPath;

}

Scene::Scene(GLFWwindow* window, std::string _name, unsigned int width, unsigned int height) :Object(_name)
{
	this->window = window;
	this->input = new InputInWindows(window);
	this->Width = width;
	this->Height = height;
	this->TargetPath = WinApiUtil::GetDebugPath();
}


Scene::~Scene()
{

	for (unsigned int i = 0; i < gameScriptVec.size(); i++)
	{
		GameScript* script = gameScriptVec[i];
		script->OnDestroy();
		script->Destroy(script);
	}

	for (unsigned int i = 0; i < gameObjectVec.size(); i++)
	{
		GameObject* obj = gameObjectVec[i];
		obj->Destroy(obj);
	}



}

void Scene::Init()
{


	mainShader = new Shader(SHADER_DEFAULT_FILE_VERTEX, SHADER_DEFAULT_FILE_FRAGMENT, MAIN_SHADER_DEFAULT_NAME, Shader::MAIN_SHADER);
	PushShader(mainShader);

	mainCamera = new Camera("MainCamera", mainShader, Width, Height, glm::vec3(0, 10.0f, 200.0f), glm::radians(-2.3f), glm::radians(0.3f), glm::vec3(0, 1.0f, 0));
	PushGameObject(mainCamera);

	Shader* skyShader = new Shader("SkyBoxVertex.vert", "SkyboxFragment.frag", SKYBOX_SHADER_DEFAULT_NAME, Shader::SKYBOX_SHADER);
	PushShader(skyShader);


	for (unsigned int i = 0; i < gameScriptVec.size(); i++)
	{
		GameScript* script = gameScriptVec[i];
		script->Init();

	}


};
 void Scene::Awake()
{

	for (unsigned int i = 0; i < gameScriptVec.size(); i++)
	{
		GameScript* script = gameScriptVec[i];
		script->Awake();
	}

	for (unsigned int i = 0; i < gameObjectVec.size(); i++)
	{
		GameObject* obj = gameObjectVec[i];
		ManagerGameObject* mana = dynamic_cast<ManagerGameObject*>(obj);
		if (mana != nullptr)
		{
			Shader* sha = mana->shader;
			if (mana->handleType == ManagerGameObject::HANDLE_FRAGMENT)
			{
				sha->Unhandled_fragment_source = mana->HandleShaderSource(sha->Unhandled_fragment_source);
			}
			else if (mana->handleType == ManagerGameObject::HANDLE_VERTEX)
			{
				sha->Unhandled_vertext_source = mana->HandleShaderSource(sha->Unhandled_vertext_source);
			}
			else if (mana->handleType == ManagerGameObject::HANDLE_VERTEX_FRAGMENT)
			{
				sha->Unhandled_vertext_source = mana->HandleShaderSource(sha->Unhandled_vertext_source);
				sha->Unhandled_fragment_source = mana->HandleShaderSource(sha->Unhandled_fragment_source);
			}
		}

	}

	//init shader
	for (unsigned int i = 0; i < shaderVec.size(); i++)
	{
		shaderVec[i]->InitShader();

	}
};
void Scene::OnEnable()
{
	for (unsigned int i = 0; i < gameScriptVec.size(); i++)
	{
		GameScript* script = gameScriptVec[i];
		script->OnEnable();
	}
};
void Scene::Update()
{
	for (unsigned int i = 0; i < gameScriptVec.size(); i++)
	{
		GameScript* script = gameScriptVec[i];
		script->Update();
	}
	for (unsigned int i = 0; i < gameObjectVec.size(); i++)
	{
		GameObject* obj = gameObjectVec[i];
		obj->Draw();
		glDepthFunc(GL_LESS);
	}
};
void Scene::OnDisable()
{
	for (unsigned int i = 0; i < gameScriptVec.size(); i++)
	{
		GameScript* script = gameScriptVec[i];
		script->OnDisable();
	}
};
void Scene::OnDestroy()
{
	for (unsigned int i = 0; i < gameScriptVec.size(); i++)
	{
		GameScript* script = gameScriptVec[i];
		script->OnDestroy();
	}
};



void Scene::PushScript(GameScript* script)
{
	gameScriptVec.push_back(script);
}
void Scene::PushGameObject(GameObject* obj)
{
	gameObjectVec.push_back(obj);
}


void Scene::PushShader(Shader* shader)
{
	shaderVec.push_back(shader);
	if (shader != mainShader)
	{
		mainCamera->shaders.push_back(shader);
	}

}


Shader* Scene::GetShaderByName(std::string _name)
{
	for (unsigned int i = 0; i < shaderVec.size(); i++)
	{
		Shader* s = shaderVec[i];
		if (s->name == _name)
		{
			return s;
		}
	}
	return nullptr;
}


GameObject* Scene::GetGameObjectByName(std::string _name)
{
	for (unsigned int i = 0; i < shaderVec.size(); i++)
	{
		GameObject* s = gameObjectVec[i];
		if (s->name == _name)
		{
			return s;
		}
	}
	return nullptr;
}
