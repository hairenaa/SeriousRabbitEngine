#pragma once
class DestroyBase
{
public:
	bool isDestroyed = false;
	template<class T>
	void Delete(T* &obj_ptr)
	{
		isDestroyed = true;
		delete obj_ptr;
		obj_ptr = nullptr;
	}

	void Destroy() 
	{
		this->isDestroyed = true;
	}
};

