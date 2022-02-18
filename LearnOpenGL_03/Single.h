#pragma once
template<class T>
class Single
{
public:
	
	static T* Instance()
	{
		if (instance == nullptr)
		{
			instance = new T();
			
		}
		return instance;
	}

	

protected:
	static T* instance;
};

