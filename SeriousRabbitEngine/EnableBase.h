#pragma once
class EnableBase
{
public:
	bool isEnabled = true;
	virtual void Enable() { this->isEnabled = true; };
	virtual void Disable() { this->isEnabled = false; };
};

