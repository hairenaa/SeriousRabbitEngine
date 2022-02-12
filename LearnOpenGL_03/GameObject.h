#pragma once
#include<string>
#define SOLE_BUILD_DEMO




class GameObject
{
public:
	static int id;
	std::string name;
	GameObject() 
	{
		this->id ++;
		this->name = "";
	};
	virtual void Draw() =0;

};

