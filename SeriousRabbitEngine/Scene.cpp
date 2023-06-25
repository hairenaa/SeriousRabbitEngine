#include "Scene.h"


Scene::Scene(GLFWwindow* window, std::string _name, unsigned int width, unsigned int height) :GameScript(_name)
{
	this->window = window;
	this->input = new InputInWindows(window);
	this->Width = width;
	this->Height = height;

}

//Scene::Scene(GLFWwindow* window, std::string _name, unsigned int width, unsigned int height) :GameScript(_name)
//{
//	this->window = window;
//	this->input = new InputInWindows(window);
//	this->Width = width;
//	this->Height = height;
//	
//}


Scene::~Scene()
{

	for (unsigned int i = 0; i < gameScriptVec.size(); i++)
	{
		GameScript* script = gameScriptVec[i];
		script->OnDestroy();
		script->Delete<GameScript>(script);
		
	}

	for (unsigned int i = 0; i < gameObjectVec.size(); i++)
	{
		GameObject* obj = gameObjectVec[i];
		obj->Delete<GameObject>(obj);
		
	}

	for (unsigned int i = 0; i < shaderVec.size(); i++)
	{
		Shader* obj = shaderVec[i];
		obj->Delete<Shader>(obj);

	}


}

void Scene::Init()
{


	mainShader = new Shader(SHADER_DEFAULT_FILE_VERTEX, SHADER_DEFAULT_FILE_FRAGMENT, MAIN_SHADER_DEFAULT_NAME, Shader::MAIN_SHADER);
	PushShader(mainShader);

	mainCamera = new Camera("MainCamera", mainShader, Width, Height, glm::vec3(0, 10.0f, 200.0f), glm::radians(-2.3f), glm::radians(0.3f), glm::vec3(0, 1.0f, 0));
	GameObject* cobj = (GameObject*)mainCamera;
	PushGameObject(cobj);

	/*Shader* skyShader = new Shader(SHADER_SKYBOX_FILE_VERTEX, SHADER_SKYBOX_FILE_FRAGMENT, SKYBOX_SHADER_DEFAULT_NAME, Shader::SKYBOX_SHADER);
	PushShader(skyShader);*/
	
	

	for (unsigned int i = 0; i < gameScriptVec.size(); i++)
	{
		GameScript* script = gameScriptVec[i];
		if (script->isEnabled) 
		{
			script->Init();
		}
		

	}


};
 void Scene::Awake()
{

	for (unsigned int i = 0; i < gameScriptVec.size(); i++)
	{
		GameScript* script = gameScriptVec[i];
		if (script->isEnabled) 
		{
			script->Awake();
		}
		
	}

	for (unsigned int i = 0; i < gameObjectVec.size(); i++)
	{
		GameObject* obj = gameObjectVec[i];
		if (obj != nullptr) 
		{
			LightGameObject* mana = dynamic_cast<LightGameObject*>(obj);
			if (mana != nullptr)
			{
				Shader* sha = mana->shader;
				if (mana->handleType == LightGameObject::HANDLE_FRAGMENT)
				{
					sha->Unhandled_fragment_source = mana->HandleShaderSource(sha->Unhandled_fragment_source);
				}
				else if (mana->handleType == LightGameObject::HANDLE_VERTEX)
				{
					sha->Unhandled_vertext_source = mana->HandleShaderSource(sha->Unhandled_vertext_source);
				}
				else if (mana->handleType == LightGameObject::HANDLE_VERTEX_FRAGMENT)
				{
					sha->Unhandled_vertext_source = mana->HandleShaderSource(sha->Unhandled_vertext_source);
					sha->Unhandled_fragment_source = mana->HandleShaderSource(sha->Unhandled_fragment_source);
				}
				/*std::cout << "////////////////////////////////////////"<<std::endl;
				std:: cout << sha->Unhandled_fragment_source << endl;
				std::cout << "////////////////////////////////////////"<<std::endl;*/
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
		if (script->isEnabled) 
		{
			script->OnEnable();
		}
		
	}
};
void Scene::Update()
{
	for (unsigned int i = 0; i < gameScriptVec.size(); i++)
	{
		GameScript* script = gameScriptVec[i];
		if (script->isEnabled) 
		{
			script->Update();
		}
		
	}
	
	for (std::vector<GameObject*>::iterator it = gameObjectVec.begin(); it != gameObjectVec.end();)
	{
		GameObject* obj = *it;
		
		if (obj != nullptr) 
		{
			if (obj->isDestroyed)
			{
				it = gameObjectVec.erase(it);
				obj->Delete<GameObject>(obj);
			}
			
			else
			{
				if (obj->isEnabled)
				{
					obj->Draw();
				}
				++it;
			}
			
		}
		
		glDepthFunc(GL_LESS);
	}
};
void Scene::OnDisable()
{
	for (unsigned int i = 0; i < gameScriptVec.size(); i++)
	{
		GameScript* script = gameScriptVec[i];
		if (script->isEnabled) 
		{
			script->OnDisable();
		}
		
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


void Scene::PushGameObject(GameObject* &obj)
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

GameScript * Scene::GetGameScriptByName(std::string _name)
{

	for (unsigned int i = 0; i < shaderVec.size(); i++)
	{
		GameScript* s = gameScriptVec[i];
		if (s->name == _name)
		{
			return s;
		}
	}
}

void Scene::BindInput(InputBase * &input)
{
	this->input = input;
}
