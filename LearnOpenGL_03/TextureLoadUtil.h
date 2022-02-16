#pragma once
#include<vector>
#include<string>
#include<iostream>


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
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		

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
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
				//glGenerateMipmap(GL_TEXTURE_2D);
			}
			else
			{
				std::cout << "load image failed TexBuffer: " << path << std::endl;
			}

			stbi_image_free(data);
		}
		

		return TexBuffer;
	};
};

