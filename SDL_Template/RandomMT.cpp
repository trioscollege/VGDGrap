#include "RandomMT.h"

namespace SDLFramework {

	RandomMT * RandomMT::sInstance = nullptr;

	RandomMT * RandomMT::Instance()
	{
		if (sInstance == nullptr) {
			sInstance = new RandomMT();
		}

		return sInstance;
	}
	void RandomMT::Release() {
		delete sInstance;
		sInstance = nullptr;
	}

	int RandomMT::Random()
	{
		std::uniform_int_distribution<int> dist(0, INT32_MAX);
		return dist(gen);
	}

	int SDLFramework::RandomMT::RandomRange(int lo, int hi) {
		std::uniform_int_distribution<int> dist(lo, hi);
		return dist(gen);
	}

	float SDLFramework::RandomMT::RandomRange(float lo, float hi) {
		std::uniform_real_distribution<float> dist(lo, hi);
		return dist(gen);
	}

	RandomMT::RandomMT() {
		unsigned seed = (unsigned)std::chrono::system_clock::now().time_since_epoch().count();
		gen.seed(seed);
	}


	RandomMT::~RandomMT() {
	}
}
