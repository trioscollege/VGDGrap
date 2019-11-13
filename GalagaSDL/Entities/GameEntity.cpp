#include "GameEntity.hpp"

namespace SDLFramework {

    GameEntity::GameEntity(float x, float y)
        : mPosition(x, y), mRotation(0.0f), mScale(Vec2_One), mActive(true), mParent(nullptr) {}


    GameEntity::~GameEntity() {
        mParent = nullptr;
    }

    void GameEntity::Position(const Vector2 & pos) {
        mPosition = pos;
    }

    Vector2 GameEntity::Position(Space space) {
        if (space == Local || mParent == nullptr) {
            return mPosition;
        }

        return mParent->Position(World) + RotateVector(mPosition, mParent->Rotation(Local));
    }

    void GameEntity::Rotation(float rot) {
        mRotation = rot;

        while (mRotation > 360.0f) {
            mRotation -= 360.0f;
        }

        while (mRotation < 0.0f) {
            mRotation += 360.0f;
        }
    }

    float GameEntity::Rotation(Space space) {
        if (space == Local || mParent == nullptr) {
            return mRotation;
        }

        return mParent->Rotation(World) + mRotation;
    }

    void GameEntity::Scale(Vector2 scale) {
        mScale = scale;
    }

    Vector2 GameEntity::Scale(Space space) {
        if (space == Local || mParent == nullptr) {
            return mScale;
        }
        
        Vector2 scale = mParent->Scale(World);
        scale.x *= mScale.x;
        scale.y *= mScale.y;
        
        return scale;
    }

    void GameEntity::Active(bool active) {
        mActive = active;
    }

    bool GameEntity::Active() const {
        return mActive;
    }

    void GameEntity::Parent(GameEntity * parent) {
        mPosition = Position(World) - parent->Position(World);

        mParent = parent;
    }

    GameEntity * GameEntity::Parent() const
    {
        return mParent;
    }

    void GameEntity::Translate(Vector2 vec) {
        mPosition += vec;
    }

    void GameEntity::Rotate(float amount) {
        mRotation += amount;
    }
}
