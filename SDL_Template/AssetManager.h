#ifndef __ASSETMANAGER_H
#define __ASSETMANAGER_H
#include "Graphics.h"

#include <SDL_mixer.h>
#include <map>
#include <sstream>
#include "ShaderUtil.h"

namespace SDLFramework {

	class AssetManager
	{
	private:
		static AssetManager * sInstance;

		std::map<std::string, SDL_Texture*> mTextures;
		std::map<std::string, TTF_Font *> mFonts;
		std::map<std::string, SDL_Texture *> mText;
		std::map<std::string, Mix_Music *> mMusic;
		std::map<std::string, Mix_Chunk *> mSFX;
		std::map<std::string, SDL_Surface*> mSurface;
		static std::map<std::string, ShaderUtil> Shaders;


		std::map<SDL_Surface*, unsigned> mSurfaceRefCount;
		std::map<SDL_Texture*, unsigned> mTextureRefCount;
		std::map<Mix_Music *, unsigned> mMusicRefCount;
		std::map<Mix_Chunk *, unsigned*> mSFXRefCount;

		TTF_Font * GetFont(std::string filename, int size);

		static ShaderUtil loadShaderFromFile(const GLchar* vShaderFile, const GLchar* fShaderFile, const GLchar* gShaderFile = nullptr);

		AssetManager();
		~AssetManager();

	public:
		static AssetManager * Instance();
		static void Release();

		SDL_Texture* GetTexture(std::string filename, bool managed = false);
		SDL_Surface* GetSurface(std::string filename, bool managed = false);
		SDL_Texture * GetText(std::string text, std::string filename, int size, SDL_Color color, bool managed = false);

		Mix_Music * GetMusic(std::string filename, bool managed = false);
		Mix_Chunk * GetSFX(std::string filename, bool managed = false);

		static ShaderUtil GetShader(std::string name);

		static ShaderUtil LoadShader(const GLchar* vShaderFile, const GLchar* fShaderFile, const GLchar* gShaderFile, std::string name);

		void DestroyTexture(SDL_Texture* texture);
		void DestroySurface(SDL_Surface* surface);

		void DestroyMusic(Mix_Music * music);
		void DestroySFX(Mix_Chunk * sfx);
	};
}
#endif