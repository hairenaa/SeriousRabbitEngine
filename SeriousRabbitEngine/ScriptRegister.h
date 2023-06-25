#pragma once
//#include "../scripts/MyTestScript1"
#include "MyTestScript.h"
class ScriptRegister
{
public:
	//初始化你的游戏脚本将会自动注册
	ScriptRegister() 
	{
		//MyTestScript1* script = new MyTestScript1();
		MyTestScript* script = new MyTestScript();
	}

	
};

