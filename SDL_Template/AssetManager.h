#ifndef __ASSETMANAGER_H
#define __ASSETMANAGER_H
#include "Graphics.h"
#include <map>

class AssetManager
{
private:
	static AssetManager * sInstance;

	std::map<std::string, SDL_Texture *> mTextures;

	AssetManager();
	~AssetManager();

public:
	static AssetManager * Instance();
	static void Release();

	SDL_Texture * GetTexture(std::string filename);
};
#endif