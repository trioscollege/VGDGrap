#include "Random.h"

namespace SDLFramework {

	Random * Random::sInstance = nullptr;

	Random * Random::Instance()
	{
		if (sInstance == nullptr) {
			sInstance = new Random();
		}

		return sInstance;
	}
	void Random::Release() {
		delete sInstance;
		sInstance = nullptr;
	}

	unsigned Random::RandomInt()
	{
		return gen();
	}

	float Random::RandomFloat() {
		std::uniform_real_distribution<float> dist(0.0f, 1.0f);
		return dist(gen);
	}

	int SDLFramework::Random::RandomRange(int lo, int hi) {
		std::uniform_int_distribution<int> dist(lo, hi);
		return dist(gen);
	}

	float SDLFramework::Random::RandomRange(float lo, float hi) {
		std::uniform_real_distribution<float> dist(lo, hi);
		return dist(gen);
	}

	Random::Random() {
		unsigned seed = (unsigned)std::chrono::system_clock::now().time_since_epoch().count();
		gen.seed(seed);
	}

	Random::~Random() {
	}
}
