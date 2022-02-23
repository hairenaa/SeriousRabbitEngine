#pragma once
#include "MyTestScript.h"
class ScriptRegister
{
public:
	//初始化你的游戏脚本将会自动注册
	ScriptRegister() 
	{
		MyTestScript* script1 = new MyTestScript();
	}

	
};

