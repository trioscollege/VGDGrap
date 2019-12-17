#ifndef __AUDIOMANAGER_H
#define __AUDIOMANAGER_H
#include "AssetManager.h"

namespace SDLFramework {

	class AudioManager {
	private:
		static AudioManager * sInstance;
		AssetManager * mAssetManager;

	public:
		static AudioManager * Instance();
		static void Release();

		void PlayMusic(std::string filename, int loops = -1, bool managed = true);
		void PauseMusic();
		void ResumeMusic();

		void PlaySFX(std::string filename, int loops = 0, int channel = -1,bool managed = true);

	private:
		AudioManager();
		~AudioManager();
	};
}
#endif