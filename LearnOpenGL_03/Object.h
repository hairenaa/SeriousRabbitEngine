#pragma once
#include<string>
class Object
{
public:
	static int id;
	std::string name;
	Object(std::string _name)
	{
		this->id++;
		this->name = _name;
	};
};

