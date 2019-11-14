#ifndef __RANDOMMT_H
#define __RANDOMMT_H
#include <random>
#include <chrono>

namespace SDLFramework {

	class Random
	{
	private:
		static Random * sInstance;

		std::mt19937 gen;

	public:
		static Random * Instance();
		static void Release();

		unsigned RandomInt();
		float RandomFloat();
		int RandomRange(int lo, int hi);
		float RandomRange(float lo, float hi);

	private:
		Random();
		~Random();
	};
	
}
#endif

