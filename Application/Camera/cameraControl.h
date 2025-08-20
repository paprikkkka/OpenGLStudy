#pragma once

#include "camera.h"
#include <map>

class CameraControl {
public:
	CameraControl();
	~CameraControl();
	virtual void update();
	virtual void onKey(int key, int action, int mods);
	virtual void onMouseButton(int button, int action, double xpos, double ypos);
	virtual void onCursor(double xpos, double ypos);
	virtual void onScroll(float offset);

	void setCamera(Camera* camera) { mCamera = camera; }
	void setSensitivity(float sensitivity) { mSensitivity = sensitivity; }
	void setScaleSpeed(float speed) { mScaleSpeed = speed; }
	Camera* getCamera() const { return mCamera; }
protected:
	Camera* mCamera{ nullptr };
	float mSensitivity{ 0.2f };

	float mCurrentX{ 0.0f };
	float mCurrentY{ 0.0f };

	std::map<int, bool> mKeyMap;

	bool mLeftMouseDown{ false };
	bool mRightMouseDown{ false };
	bool mMiddleMouseDown{ false };

	float mScaleSpeed{ 0.2f };
};