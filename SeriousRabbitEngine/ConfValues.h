#pragma once
#include "Single.h"
#include <string>

class ConfValues :public Single < ConfValues >
{

public:
	std::string GetConfigValue(std::string key)  //从config/settings.json中读取value，key一般来源于ConstValues.h文件的静态常量
	{
		
		return nullptr;
	}

	void SetConfigValue(std::string key,std::string value)//设置config/settings.json的KV
	{
	
	}

};
ConfValues* ConfValues::instance = nullptr;

