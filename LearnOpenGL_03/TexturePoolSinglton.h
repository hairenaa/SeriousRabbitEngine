#pragma once
#include <map>
#include <string>
#include "Mesh.h"
#include "TextureLoadUtil.h"
#include "Single.h"

class TexturePoolSinglton : public Single<TexturePoolSinglton>
{
public:
	std::map<std::string,Texture> texturePool;
	

	bool ExistTexture(std::string path) 
	{
		
		if (texturePool.count(path)>0) 
		{
			return true;
		}
		return false;

	}

	Texture CheckAndLoadTexture(std::string path,TextureType type) 
	{
		
		if (!ExistTexture(path)) 
		{
			Texture tex1;
			tex1.id = TextureLoadUtil::LoadImageToGpu(path.c_str());
			tex1.path = path;
			tex1.type = type;
			texturePool.insert(std::pair<std::string,Texture>(path, tex1));
			return tex1;
		}
		else
		{
			return texturePool[path];
		}

	}

};
TexturePoolSinglton* TexturePoolSinglton::instance = nullptr;


