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
	mAudio = AudioManager::Instance();

	mVisible = false;
	mAnimating = false;

	mScore = 0;
	mLives = 2;
	
	mShip = new Texture("PlayerShips.png", 0, 0, 60, 64);
	mShip->Parent(this);
	mShip->Position(Vec2_Zero);

	mMoveSpeed = 100.0f;
	mMoveBounds = Vector2(0.0f, 800.0f);

	mDeathAnimation = new AnimatedTexture("PlayerExplosion.png", 0, 0, 128, 128, 4, 1.0f, AnimatedTexture::Horizontal);
	mDeathAnimation->Parent(this);
	mDeathAnimation->Position(Vec2_Zero);
	mDeathAnimation->SetWrapMode(AnimatedTexture::Once);
}

Player::~Player() {
	mTimer = nullptr;
	mInput = nullptr;
	mAudio = nullptr;

	delete mShip;
	mShip = nullptr;

	delete mDeathAnimation;
	mDeathAnimation = nullptr;
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

void Player::WasHit() {
	mLives -= 1;
	mAnimating = true;
	mDeathAnimation->ResetAnimation();
	mAudio->PlaySFX("SFX\\PlayerExplosion.wav");
}

void Player::Update() {
	if (mAnimating) {
		mDeathAnimation->Update();
		mAnimating = mDeathAnimation->IsAnimating();
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
			mDeathAnimation->Render();
		}
		else {
			mShip->Render();
		}
	}
}
