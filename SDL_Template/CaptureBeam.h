#ifndef __CAPTUREBEAM_H
#define __CAPTUREBEAM_H
#include "AnimatedGLTexture.h"

using namespace SDLFramework;

class CaptureBeam :
	public AnimatedGLTexture 
{
private:
	float mTotalCaptureTime;
	float mCaptureTimer;

	void RunAnimation() override;

public:
	CaptureBeam();
	~CaptureBeam();

	void ResetAnimation() override;
	void Render() override;
};
#endif