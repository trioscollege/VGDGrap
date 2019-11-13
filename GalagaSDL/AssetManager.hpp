#ifndef __ASSETMANAGER_H
#define __ASSETMANAGER_H
#include "Graphics.hpp"
#include <SDL2_mixer/SDL_mixer.h>
#include <map>
#include <sstream>

namespace SDLFramework {

    class AssetManager
    {
    private:
        static AssetManager * sInstance;

        std::map<std::string, SDL_Texture *> mTextures;
        std::map<std::string, TTF_Font *> mFonts;
        std::map<std::string, SDL_Texture *> mText;
        std::map<std::string, Mix_Music *> mMusic;
        std::map<std::string, Mix_Chunk *> mSFX;

        TTF_Font * GetFont(std::string filename, int size);

        AssetManager();
        ~AssetManager();

    public:
        static AssetManager * Instance();
        static void Release();

        SDL_Texture * GetTexture(std::string filename);
        SDL_Texture * GetText(std::string text, std::string filename, int size, SDL_Color color);

        Mix_Music * GetMusic(std::string filename);
        Mix_Chunk * GetSFX(std::string filename);
    };
}
#endif
