#pragma once

#include "../GLFramWork/core.h"
#include <vector>

class Model {
public:
	Model(const std::string& path);
	Model();
	~Model();
	void draw();
	const glm::mat4& getTransform() const { return mTransform; };

	GLuint getVAO() const { return mVAO; }

	unsigned int getIndices() const { return mIndices; }

public:
	static Model* createBox(float size);
	static Model* createSphere(float radius);

private:
	GLuint mVAO{ 0 };
	GLuint mVBO{ 0 };
	GLuint mUvVBO{ 0 };
	GLuint mEBO{ 0 };
	std::vector<glm::vec3> mVertices;
	unsigned int mIndices;
	glm::mat4 mTransform{ 1.0f };
	std::string mPath;
};