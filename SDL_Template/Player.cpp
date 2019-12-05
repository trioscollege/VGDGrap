#include "Player.h"

void Player::HandleMovement() {
	if (mInput->KeyDown(SDL_SCANCODE_RIGHT)) {
		Translate(Vec2_Right * mMoveSpeed * mTimer->DeltaTime());
	}
	else if (mInput->KeyDown(SDL_SCANCODE_LEFT)) {
		Translate(-Vec2_Right * mMoveSpeed * mTimer->DeltaTime());
	}

	Vector2 pos = Position(Local);
	if (pos.x < mMoveBounds.x) {
		pos.x = mMoveBounds.x;
	}
	else if (pos.x > mMoveBounds.y) {
		pos.x = mMoveBounds.y;
	}

	Position(pos);
}

Player::Player() {
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();

	mVisible = false;
	mAnimating = false;

	mScore = 0;
	mLives = 2;
	
	mShip = new Texture("PlayerShips.png", 0, 0, 60, 64);
	mShip->Parent(this);
	mShip->Position(Vec2_Zero);

	mMoveSpeed = 100.0f;
	mMoveBounds = Vector2(0.0f, 800.0f);
}

Player::~Player() {
	mTimer = nullptr;
	mInput = nullptr;

	delete mShip;
	mShip = nullptr;
}

void Player::Visible(bool visible) {
	mVisible = visible;
}

bool Player::IsAnimating() {
	return mAnimating;
}

int Player::Score() {
	return mScore;
}

int Player::Lives() {
	return mLives;
}

void Player::AddScore(int change) {
	mScore += change;
}

void Player::Update() {
	if (mAnimating) {

	}
	else {
		if (Active()) {
			HandleMovement();
		}
	}
}

void Player::Render() {
	if (mVisible) {
		if (mAnimating) {

		}
		else {
			mShip->Render();
		}
	}
}
