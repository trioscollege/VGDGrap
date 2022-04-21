#include "CaptureBeam.h"

void CaptureBeam::RunAnimation() {
	mCaptureTimer += mTimer->DeltaTime();
	if (mCaptureTimer >= mTotalCaptureTime) {
		mAnim.done = true;
	}
	else {
		mAnim.frameTimer += mTimer->DeltaTime();
		if (mAnim.frameTimer >= mAnim.speed) {
			mAnim.frameTimer -= mAnim.speed;
		}

		mSourceRect.x = (int)(mAnim.frameTimer / mAnim.timePerFrame) * mWidth;

		if (mCaptureTimer < 2.0f) {
			int temp = (int)(mCaptureTimer * 3.5f);
			mSourceRect.h = (int)(temp / 7.0f * mHeight);
		}
		else if (mCaptureTimer > 4.0f) {
			int temp = (int)((mTotalCaptureTime - mCaptureTimer) * 3.5f);
			mSourceRect.h = (int)(temp / 7.0f * mHeight);
		}
		else {
			mSourceRect.h = mHeight;
		}
	}
}

CaptureBeam::CaptureBeam()
: AnimatedGLTexture("CaptureBeam.png", 0, 0, 184, 320, 3, 0.5f, Animation::Layouts::Horizontal) {
	mTotalCaptureTime = 6.0f;
	ResetAnimation();
}


CaptureBeam::~CaptureBeam() {
}

void CaptureBeam::ResetAnimation() {
	AnimatedGLTexture::ResetAnimation();
	mCaptureTimer = 0.0f;
	mSourceRect.h = 0;
}

void CaptureBeam::Render() {
	Vector2 pos = Position(World);
	Vector2 scale = Scale(World);
	mDestinationRect.x = (int)(pos.x - mWidth * scale.x * 0.5f);
	mDestinationRect.y = (int)(pos.y - mHeight * scale.y * 0.5f);
	mDestinationRect.w = (int)(mWidth * scale.x);
	mDestinationRect.h = mSourceRect.h;

	mGraphics->DrawTexture(mTex, mClipped ? &mSourceRect : nullptr, &mDestinationRect, Rotation(World));
}
