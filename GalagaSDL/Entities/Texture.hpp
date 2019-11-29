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
		Texture(std::string filename, bool managed = true);
		Texture(std::string filename, int x, int y, int w, int h, bool managed = true);
		Texture(std::string text, std::string fontPath, int size, SDL_Color color, bool managed = true);
		~Texture();

		void Render() override;
	};
}
#endif
