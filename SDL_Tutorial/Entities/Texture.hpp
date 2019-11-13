#ifndef __TEXTURE_H
#define __TEXTURE_H
#include "Graphics.hpp"
#include "GameEntity.hpp"
#include "AssetManager.hpp"

namespace SDLFramework {

    class Texture : public GameEntity {
    protected:
        SDL_Texture * mTex;
        Graphics * mGraphics;

        int mWidth;
        int mHeight;

        bool mClipped;
        SDL_Rect mSourceRect;
        SDL_Rect mDestinationRect;

    public:
        Texture(std::string filename);
        Texture(std::string filename, int x, int y, int w, int h);
        Texture(std::string text, std::string fontPath, int size, SDL_Color color);
        ~Texture();

        void Render() override;
    };

}
#endif
