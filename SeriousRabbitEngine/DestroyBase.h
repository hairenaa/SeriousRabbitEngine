#pragma once
class DestroyBase
{
public:
	virtual void Destroy(DestroyBase* obj_ptr)
	{
		delete obj_ptr;
		obj_ptr = nullptr;
	}

};

