#pragma once
template<class T>
class Single
{
public:
	static T* instance;
	static T* Instance()
	{
		if (instance == nullptr)
		{
			instance = new T();
		}
		return instance;
	}
		
};

