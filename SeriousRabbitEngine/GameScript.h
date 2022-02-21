#pragma once
#include "DestroyBase.h"
#include "EnableBase.h"
class GameScript:public Object, public DestroyBase,public EnableBase
{
public:
	
	
	
	GameScript(std::string _name) 
	{
		this->name = _name;
	}

	GameScript() 
	{
		
	}

	

	virtual void Init() = 0;
	virtual  void Awake() = 0;
	virtual void OnEnable() = 0;
	virtual void Update() = 0;
	virtual void OnDisable() = 0;
	virtual void OnDestroy() = 0;
	
};

