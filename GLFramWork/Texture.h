#pragma	once
#include "core.h"


class Texture {
public:
	Texture(const std::string& path, unsigned int unit);
	~Texture();

	void bind();

	float getWidth()const { return (float)mWidth; }
	float getHeight()const { return (float)mHeight; }
private:
	GLuint mTexture{ 0 };
	int mWidth{ 0 };
	int mHeight{ 0 };
	int mChannels{ 0 };
	unsigned int mTextureID{ 0 };
};