#include "Texture.h"
#include "../Wrapper/checkError.h"


#define STB_IMAGE_IMPLEMENTATION
#include "../Application/stb_image.h"


Texture::Texture(const std::string& path, unsigned int unit) {
	mTextureID = unit;

	stbi_set_flip_vertically_on_load(true); // 翻转纹理图片
	// 加载纹理图片
	unsigned char* data = stbi_load(path.c_str(), &mWidth, &mHeight, &mChannels, STBI_rgb_alpha);

	// 激活纹理单元0
	glCheckError(glGenTextures(1, &mTexture));
	glCheckError(glActiveTexture(GL_TEXTURE0 + mTextureID));

	// 绑定纹理对象
	glCheckError(glBindTexture(GL_TEXTURE_2D, mTexture));

	// 传输纹理数据到GPU
	//glCheckError(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));
	int width = mWidth;
	int height = mHeight;
	for (int level = 0; true; ++level) {
		glCheckError(glTexImage2D(GL_TEXTURE_2D, level, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));

		if (width == 1 && height == 1) {
			break; // 如果纹理已经缩小到1x1，停止生成mipmap
		}
		// 计算下一层的宽度和高度
		width = width > 1 ? width / 2 : 1;
		height = height > 1 ? height / 2 : 1;
	}

	stbi_image_free(data);

	// 设置纹理参数
	glCheckError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	//glCheckError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
	glCheckError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	glCheckError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
}
Texture::~Texture() {
	if (mTexture != 0) {
		glCheckError(glDeleteTextures(1, &mTexture));
	}
}


void Texture::bind() {
	glCheckError(glActiveTexture(GL_TEXTURE0 + mTextureID));
	glCheckError(glBindTexture(GL_TEXTURE_2D, mTexture));
	std::cout << "Texture bound to unit: " << mTextureID << std::endl;
}