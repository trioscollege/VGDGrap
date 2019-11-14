#ifndef __RANDOMMT_H
#define __RANDOMMT_H
#include <random>
#include <chrono>

namespace SDLFramework {

	class RandomMT
	{
	private:
		static RandomMT * sInstance;

		std::mt19937 gen;

	public:
		static RandomMT * Instance();
		static void Release();

		int Random();
		int RandomRange(int lo, int hi);
		float RandomRange(float lo, float hi);

	private:
		RandomMT();
		~RandomMT();
	};
	
}
#endif

