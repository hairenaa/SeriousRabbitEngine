#pragma once
#include "DestroyBase.h"
class GameScript:public Object, public DestroyBase
{
public:
	bool isEnabled = true;
	
	
	GameScript(std::string _name) 
	{
		this->name = _name;
	}

	GameScript() 
	{
		
	}

	virtual void Enable() {};
	virtual void Disable() {};

	virtual void Init() = 0;
	virtual  void Awake() = 0;
	virtual void OnEnable() = 0;
	virtual void Update() = 0;
	virtual void OnDisable() = 0;
	virtual void OnDestroy() = 0;
	
};

