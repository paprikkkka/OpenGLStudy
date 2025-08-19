#pragma once

#include "camera.h"

class PerpectiveCamera : public Camera {
public:
	PerpectiveCamera(float fov, float aspect, float near, float far);
	~PerpectiveCamera();
	glm::mat4 getProjectionMatrix() override;

private:
	float mFov = 0.0f;
	float mAspect = 0.0f;
	float mNear = 0.0f;
	float mFar = 0.0f;
};