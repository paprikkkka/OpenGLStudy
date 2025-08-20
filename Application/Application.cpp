#include "Application.h"

//#include "Wrapper/checkError.h"

Application* Application::mInstance = nullptr;

Application::Application() {
	// Initialize the application
}
Application::~Application() {
	// Clean up the application
	glfwTerminate();
}

Application* Application::getInstance() {
	if (mInstance == nullptr) {
		mInstance = new Application();
	}
	return mInstance;
}

bool Application::init(const int& width, const int& height) {
	mWidth = width;
	mHeight = height;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	mWindow = glfwCreateWindow(mWidth, mHeight, "OpenGL Window", nullptr, nullptr);

	if (mWindow == nullptr) {
		std::cerr << "Failed to create GLFW window" << std::endl;
		return false;
	}
	glfwMakeContextCurrent(mWindow);
	glfwSetWindowUserPointer(mWindow, this);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to initialize GLAD" << std::endl;
		return false;
	}

	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glfwSetFramebufferSizeCallback(mWindow, frameBufferSizeCallback);
	glfwSetKeyCallback(mWindow, keyCallback);
	glfwSetMouseButtonCallback(mWindow, mouseCallback);
	glfwSetCursorPosCallback(mWindow, cursorCallback);
	glfwSetScrollCallback(mWindow, scrollCallback);

	return true;
}

bool Application::update() {
	if (glfwWindowShouldClose(mWindow)) {
		return false;
	}

	glfwPollEvents();
	glfwSwapBuffers(mWindow);
	return true;
}

void Application::destroy() {

}

void Application::frameBufferSizeCallback(GLFWwindow* window, int width, int height) {
	std::cout << "Framebuffer size changed: " << width << "x" << height << std::endl;
	Application* self = (Application*)(glfwGetWindowUserPointer(window));
	if (self->mResizeCallback != nullptr) {
		self->mResizeCallback(width, height);
	}
	//if (app->mResizeCallback != nullptr) {
	//	app->mResizeCallback(width, height);
	//}
}

void Application::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	std::cout << "Key pressed: " << key << ", Action: " << action << ", Mods: " << mods << std::endl;
	Application* self = (Application*)(glfwGetWindowUserPointer(window));
	if (self->mKeyCallback != nullptr) {
		self->mKeyCallback(key, action, mods);
	}
}


void Application::mouseCallback(GLFWwindow* window, int button, int action, int mods) {
	std::cout << "Mouse button: " << button << ", Action: " << action << ", Mods: " << mods << std::endl;
	Application* self = (Application*)(glfwGetWindowUserPointer(window));
	if (self->mMouseCallback != nullptr) {
		self->mMouseCallback(button, action, mods);
	}
}

void Application::cursorCallback(GLFWwindow* window, double xpos, double ypos) {
	std::cout << "Cursor position: (" << xpos << ", " << ypos << ")" << std::endl;
	Application* self = (Application*)(glfwGetWindowUserPointer(window));
	if (self->mCursorCallback != nullptr) {
		self->mCursorCallback(xpos, ypos);
	}
}

void Application::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
	std::cout << "Scroll offset: (" << xoffset << ", " << yoffset << ")" << std::endl;
	Application* self = (Application*)(glfwGetWindowUserPointer(window));
	if (self->mScrollCallback != nullptr) {
		self->mScrollCallback(yoffset);
	}
}


void Application::getCursorPosition(double* xpos, double* ypos) {
	glfwGetCursorPos(mWindow, xpos, ypos);
}