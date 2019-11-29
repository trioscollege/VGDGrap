#ifndef __SCOREBOARD_H
#define __SCOREBOARD_H
#include "Texture.hpp"
#include <vector>

using namespace SDLFramework;

class Scoreboard : public GameEntity {
private:
	std::vector<Texture *> mScore;

public:
	Scoreboard();
	~Scoreboard();

	void Score(int score);

	void Render();

private:
	void ClearBoard();
};
#endif
