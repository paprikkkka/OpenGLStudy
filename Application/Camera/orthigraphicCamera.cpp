#include "orthigraphicCamera.h"


OrthographicCamera::OrthographicCamera(float l, float r, float t, float b, float n, float f) {
	mLeft = l;
	mRight = r;
	mBottom = b;
	mTop = t;
	mNear = n;
	mFar = f;
}
OrthographicCamera::~OrthographicCamera() {

}

glm::mat4 OrthographicCamera::getProjectionMatrix() {
	return glm::ortho(mLeft, mRight, mBottom, mTop, mNear, mFar);
}