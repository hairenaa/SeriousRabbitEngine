#pragma once
#include<vector>
#include<string>
#include<iostream>
#include <io.h>
#include <glad/glad.h>
#include<GLFW/glfw3.h>

#include "stb_image.h"
#define STB_IMAGE_IMPLEMENTATION


class TextureLoadUtil
{
	
public:
	static unsigned int LoadImageToGpu(const char* path)
	{
		std::cout << "LoadImageToGpu path: " << path << std::endl;
		unsigned int TexBuffer;
		glGenTextures(1, &TexBuffer);
		//glActiveTexture(GL_TEXTURE0 + textureSlot);
		glBindTexture(GL_TEXTURE_2D, TexBuffer);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		int width, height, nrChannels;
		unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);

		if (data)
		{
			GLenum format;
			if (nrChannels == 1)
			{
				format = GL_RED;
			}
			else if (nrChannels == 3)
			{
				format = GL_RGB;
			}
			else if (nrChannels == 4)
			{
				format = GL_RGBA;

			}
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "load image failed TexBuffer: "<< path<< std::endl;
		}

		stbi_image_free(data);

		return TexBuffer;
	};

	static unsigned int LoadCubeImageToGpu(const std::vector<std::string> pathes)
	{
		
		unsigned int TexBuffer;
		glGenTextures(1, &TexBuffer);
		//glActiveTexture(GL_TEXTURE0 + textureSlot);
		glBindTexture(GL_TEXTURE_CUBE_MAP, TexBuffer);
		
		

		for (unsigned int i = 0; i < pathes.size(); i++)
		{
			std::string path = pathes[i];
			std::cout << "LoadCubeImageToGpu path: " << path << std::endl;
			int width, height, nrChannels;
			unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

			if (data)
			{
				GLenum format;
				if (nrChannels == 1)
				{
					format = GL_RED;
				}
				else if (nrChannels == 3)
				{
					format = GL_RGB;
				}
				else if (nrChannels == 4)
				{
					format = GL_RGBA;

				}
				unsigned int start = path.find_last_of("\\") + 1;
				unsigned int end = path.find_last_of(".");
				std::string name = path.substr(start, end-start);
				unsigned int cueb_map_index = GL_TEXTURE_CUBE_MAP_POSITIVE_X ;

				if (name == "right") 
				{
					cueb_map_index+=0;
				}
				else if (name == "left")
				{
					cueb_map_index+=1;
				}
				else if (name == "bottom")
				{
					cueb_map_index += 2;
				}
				else if (name == "top")
				{
					cueb_map_index += 3;
				}
				else if (name == "front")
				{
					cueb_map_index += 4;
				}
				else if (name == "back")
				{
					cueb_map_index += 5;
				}
				glTexImage2D(cueb_map_index, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
				//glGenerateMipmap(GL_TEXTURE_2D);
			}
			else
			{
				std::cout << "load image failed TexBuffer: " << path << std::endl;
			}

			stbi_image_free(data);
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		

		return TexBuffer;
	};


	static void GetDirFilesPathes(std::string dir,std::vector<string>& files)
	{
		intptr_t hFile = 0;
		struct _finddata_t fileinfo;
		string p;
		if ((hFile = _findfirst(p.assign(dir).append("\\*").c_str(), &fileinfo)) != -1)
		{
			do
			{

				if ((fileinfo.attrib & _A_SUBDIR))
				{
					if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
						GetDirFilesPathes(p.assign(dir).append("\\").append(fileinfo.name), files);
				}
				else
				{
					files.push_back(p.assign(dir).append("\\").append(fileinfo.name));
				}
			} while (_findnext(hFile, &fileinfo) == 0);
			_findclose(hFile);
		}
		
	}
};

