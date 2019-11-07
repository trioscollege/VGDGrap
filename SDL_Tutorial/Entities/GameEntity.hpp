#ifndef __GAMEENTITY_H
#define __GAMEENTITY_H
#include "MathHelper.hpp"

class GameEntity
{
public:

	enum Space {Local = 0, World = 1};

private:
	Vector2 mPosition;
	float mRotation;

	bool mActive;
	GameEntity * mParent;

public:
	GameEntity(float x = 0.0f, float y = 0.0f);
	~GameEntity();

	void Position(const Vector2 & pos);
	Vector2 Position(Space space = World);

	void Rotation(float rot);
	float Rotation(Space space = World);

	void Active(bool active);
	bool Active();

	void Parent(GameEntity * parent);
	GameEntity * Parent();

	virtual void Update() {};
	virtual void Render() {};

};
#endif

