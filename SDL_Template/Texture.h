#ifndef __TEXTURE_H
#define __TEXTURE_H
#include "Graphics.h"
#include "GameEntity.h"
#include "AssetManager.h"

namespace SDLFramework {

	class Texture : public GameEntity {
	private:
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
		~Texture();

		void Render() override;
	};
}
#endif