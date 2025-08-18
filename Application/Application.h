#pragma once
#include <iostream>

#define app Application::getInstance()

class GLFWwindow;

using ResizeCallback = void(*)(int width, int height);
using KeyCallback = void(*)(int key, int action, int mods);

class Application {
public:
	~Application();

	static Application* getInstance();

	uint32_t getWidth() const { return mWidth; }
	uint32_t getHeight() const { return mHeight; }


	bool init(const int& width = 800, const int& height = 600);
	bool update();
	void destroy();

	void setResizeCallback(ResizeCallback callback) { mResizeCallback = callback; }
	void setKeyCallback(KeyCallback callback) { mKeyCallback = callback; }

private:
	Application();

	static Application* mInstance;
	uint32_t mWidth{ 0 };
	uint32_t mHeight{ 0 };
	GLFWwindow* mWindow{ nullptr };

	ResizeCallback mResizeCallback{ nullptr };
	KeyCallback mKeyCallback{ nullptr };

private:
	static void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};