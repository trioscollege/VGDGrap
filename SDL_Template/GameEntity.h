#ifndef __GAMEENTITY_H
#define __GAMEENTITY_H
#include "MathHelper.h"

namespace SDLFramework {

	class GameEntity {
	public:
		enum Space { Local = 0, World = 1 };

	private:
		Vector2 mPosition;
		float mRotation;
		Vector2 mScale;

		bool mActive;
		GameEntity * mParent;

	public:
		GameEntity(float x = 0.0f, float y = 0.0f);
		~GameEntity();

		void Position(float x, float y);
		void Position(const Vector2 & pos);
		Vector2 Position(Space space = World);

		void Rotation(float rot);
		float Rotation(Space space = World);

		void Scale(Vector2 scale);
		Vector2 Scale(Space space = World);

		void Active(bool active);
		bool Active() const;

		void Parent(GameEntity * parent);
		GameEntity * Parent() const;

		virtual void Update() {};
		virtual void Render() {};
	};
}
#endif