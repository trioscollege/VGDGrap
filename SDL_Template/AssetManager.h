#ifndef __ASSETMANAGER_H
#define __ASSETMANAGER_H
#include "Graphics.h"
#include <map>

namespace SDLFramework {

	class AssetManager {
	private:
		static AssetManager * sInstance;

		std::map<std::string, SDL_Texture *> mTextures;

		std::map<SDL_Texture *, unsigned> mTextureRefCount;

	private:
		void UnloadTexture(SDL_Texture * texture);

		AssetManager();
		~AssetManager();

	public:
		static AssetManager * Instance();
		static void Release();

		SDL_Texture * GetTexture(std::string filename, bool managed = false);

		void DestroyTexture(SDL_Texture * texture);
	};
}
#endif