#include "trackBallCameraControl.h"

TrackBollCameracontrol::TrackBollCameracontrol() {

}

TrackBollCameracontrol::~TrackBollCameracontrol() {

}

void TrackBollCameracontrol::onCursor(double xpos, double ypos){
	if (mLeftMouseDown) {
		float deltaX = (xpos - mCurrentX) * mSensitivity;
		float deltaY = (ypos - mCurrentY) * mSensitivity;

		pitch(-deltaY);
		yaw(-deltaX);
	}
	if (mMiddleMouseDown) {
		float deltaX = (xpos - mCurrentX) * mMoveSpeed;
		float deltaY = (ypos - mCurrentY) * mMoveSpeed;

		mCamera->mPosition -= mCamera->mRight * deltaX;
		mCamera->mPosition += mCamera->mUp * deltaY;
	}

	mCurrentX = xpos;
	mCurrentY = ypos;
}

void TrackBollCameracontrol::pitch(float angle) {
	auto mat = glm::rotate(glm::mat4(1.0f), glm::radians(angle), mCamera->mRight);

	mCamera->mUp = mat * glm::vec4(mCamera->mUp, 0.0f);
	mCamera->mPosition = mat * glm::vec4(mCamera->mPosition, 1.0f);
}
void TrackBollCameracontrol::yaw(float angle) {
	auto mat = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));


	mCamera->mUp = mat * glm::vec4(mCamera->mUp, 0.0f);
	mCamera->mRight = mat * glm::vec4(mCamera->mRight, 0.0f);
	mCamera->mPosition = mat * glm::vec4(mCamera->mPosition, 1.0f);
}

void TrackBollCameracontrol::onScroll(float offset) {
	mCamera->scale(offset * mScaleSpeed);
}