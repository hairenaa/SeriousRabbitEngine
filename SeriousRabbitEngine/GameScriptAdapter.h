#pragma once
#include "GameScript.h"
#include "Scene.h"
#include "SceneLoader.h"



class GameScriptAdapter:public GameScript
{
public:
	
	GameScriptAdapter(bool bindToCurrentScene) 
	{
		if (bindToCurrentScene) 
		{
			GameHelper::PushGameScriptToCurrentScene(this);
		}
		
	}

	
	virtual void Init() 
	{
		
	};
	virtual  void Awake() 
	{
	
	};
	virtual void OnEnable() 
	{
	
	};
	virtual void Update() 
	{
	
	};
	virtual void OnDisable() 
	{
	
	};
	virtual void OnDestroy() 
	{
	
	};

	virtual void Enable() 
	{
		EnableBase::Enable();
		this->OnEnable();
	};

	virtual void Disable() 
	{
		EnableBase::Disable();
		this->OnDisable();
	}

};

