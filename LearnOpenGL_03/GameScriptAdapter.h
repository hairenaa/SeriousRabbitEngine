#pragma once
#include "GameScript.h"
#include "SceneLoader.h"
#include "Scene.h"

class GameScriptAdapter:public GameScript
{
public:
	

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
		this->isEnabled = true;
		this->OnEnable();
	};

	virtual void Disable() 
	{
		this->isEnabled = false;
		this->OnDisable();
	}

};

