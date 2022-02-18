#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <regex>


class ShaderFileUtil
{
public:


	static std::string ReadAllText(std::string path)
	{
		std::string str;    
		std::ifstream fin(path.c_str(),std::ios::in);   
		if (!fin)              
		{
			std::cerr << "fail ReadAllText path: "<<path << std::endl;
			return "";
		}
		std::stringstream buffer;
		buffer << fin.rdbuf();
		std::string contents(buffer.str());
		fin.close();
		return contents;
	}
	static void WriteAllText(std::string text,std::string path) 
	{
		std::ofstream fout(path, std::ios::out);
		if (!fout)
		{
			std::cerr << "fail  WriteAllText path: " << path << std::endl;
			return;
		}
		fout << text;
		fout.close();
		
	}

	static void InsertShaderFile(std::string path,std::string headerName,std::string tailerName,std::string content) 
	{
		
		std::string  str_buffer= ReadAllText(path);
		int index_header= str_buffer.find(headerName);
		if (index_header < 0) 
		{
			std::cerr << "fail  Handle index_header is negetive, path: " << path << std::endl;
			return;
		}
		index_header += headerName.length();

		int index_tailer = str_buffer.find(tailerName);
		if (index_tailer < 0)
		{
			std::cerr << "fail  Handle index_tailer is negetive, path: " << path << std::endl;
			return;
		}
		

		str_buffer = str_buffer.substr(0, index_header) + content + str_buffer.substr(index_tailer);

		WriteAllText(str_buffer, path);
		
	};
	static std::string HandleShaderSourceStr(std::string source, std::string headerName, std::string tailerName, std::string content)
	{

		std::string str_buffer = source;
		int index_header = str_buffer.find(headerName);
		if (index_header < 0)
		{
			std::cout << "warn Handle index_header is negetive,in source text,return source"  << std::endl;
			return source;
		}
		index_header += headerName.length();

		
		/*int index_tailer = str_buffer.find(tailerName);
		if (index_tailer < 0)
		{
			std::cout << "warn Handle index_tailer is negetive,in source text,return source" << std::endl;
			return source;
		}


		str_buffer = str_buffer.substr(0, index_header) + content + str_buffer.substr(index_tailer);
*/

		str_buffer= str_buffer.insert(index_header, content);
		return str_buffer;

	}

};




