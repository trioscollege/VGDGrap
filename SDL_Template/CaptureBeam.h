#ifndef __CAPTUREBEAM_H
#define __CAPTUREBEAM_H
#include "AnimatedTexture.h"

using namespace SDLFramework;

class CaptureBeam :
	public AnimatedTexture 
{
private:
	float mTotalCaptureTime;
	float mCaptureTimer;

private:
	void RunAnimation() override;

public:
	CaptureBeam();
	~CaptureBeam();

	void ResetAnimation() override;
	void Render() override;
};
#endif