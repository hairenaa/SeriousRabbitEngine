#pragma once
#include <string>
#include <direct.h>


class WinApiUtil
{
public:
	static std::string GetDebugPath() 
	{
		char *buffer;
		if ((buffer = _getcwd(NULL, 0)) == NULL)
		{
			perror("getcwd error");
			return nullptr;
		}
		else
		{
			return std::string(buffer);
		}

		
	}

	/*static bool ISBadPtr1(void* p)
	{
		return IsBadCodePtr(p);
	}
    */

};

