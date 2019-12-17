#include "Texture.h"

namespace SDLFramework {

	Texture::Texture(std::string filename) {
		mGraphics = Graphics::Instance();
		mTex = AssetManager::Instance()->GetTexture(filename);

		SDL_QueryTexture(mTex, nullptr, nullptr, &mWidth, &mHeight);

		mClipped = false;
		mDestinationRect.w = mWidth;
		mDestinationRect.h = mHeight;
	}

	Texture::Texture(std::string filename, int x, int y, int w, int h) {
		mGraphics = Graphics::Instance();
		mTex = AssetManager::Instance()->GetTexture(filename);

		mWidth = w;
		mHeight = h;

		mClipped = true;
		mDestinationRect.w = mWidth;
		mDestinationRect.h = mHeight;

		mSourceRect.x = x;
		mSourceRect.y = y;
		mSourceRect.w = mWidth;
		mSourceRect.h = mHeight;
	}

	Texture::Texture(std::string text, std::string fontPath, int size, SDL_Color color) {
		mGraphics = Graphics::Instance();
		mTex = AssetManager::Instance()->GetText(text, fontPath, size, color);

		mClipped = false;

		SDL_QueryTexture(mTex, nullptr, nullptr, &mWidth, &mHeight);

		mDestinationRect.w = mWidth;
		mDestinationRect.h = mHeight;
	}

	Texture::~Texture() {
		SDL_DestroyTexture(mTex);
		mTex = nullptr;
		mGraphics = nullptr;
	}

	void Texture::Render() {
		Vector2 pos = Position(World);
		Vector2 scale = Scale(World);
		mDestinationRect.x = (int)(pos.x - mWidth * scale.x * 0.5f);
		mDestinationRect.y = (int)(pos.y - mHeight * scale.y * 0.5f);
		mDestinationRect.w = (int)(mWidth * scale.x);
		mDestinationRect.h = (int)(mHeight * scale.y);

		mGraphics->DrawTexture(mTex, mClipped ? &mSourceRect : nullptr, &mDestinationRect, Rotation(World));
	}
}