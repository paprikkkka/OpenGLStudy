#include "perspectiveCamera.h"


PerpectiveCamera::PerpectiveCamera(float fov, float aspect, float near, float far) {
	mFov = fov;
	mAspect = aspect;
	mNear = near;
	mFar = far;
}
PerpectiveCamera::~PerpectiveCamera() {

}
glm::mat4 PerpectiveCamera::getProjectionMatrix() {
	return glm::perspective(glm::radians(mFov), mAspect, mNear, mFar);
}

void PerpectiveCamera::scale(float scale) {
	auto front = glm::cross(mUp, mRight);
	mPosition += front * scale;
}