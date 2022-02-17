#pragma once
class GameScript
{
public:
	virtual void Init() = 0;
	virtual  void Awake() = 0;
	virtual void OnEnable() = 0;
	virtual void Update() = 0;
	virtual void OnDisable() = 0;
	virtual void OnDestroy() = 0;
	
};

