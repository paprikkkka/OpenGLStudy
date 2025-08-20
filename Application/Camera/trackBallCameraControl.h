#pragma once

#include "cameraControl.h"

class TrackBollCameracontrol : public CameraControl {
public:
	TrackBollCameracontrol();
	~TrackBollCameracontrol();
	void onCursor(double xpos, double ypos) override;
	void onScroll(float offset) override;

private:
	void pitch(float angle);
	void yaw(float angle);
private:
	float mMoveSpeed{ 0.01f };
};