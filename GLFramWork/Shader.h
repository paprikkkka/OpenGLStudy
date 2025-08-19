#pragma once

#include "core.h"


class Shader {
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();

	void begin();

	void end();

	void setUniFloat(const std::string& name, float value);

	void setUniInt(const std::string& name, int value);

	void setMatrix4x4(const std::string& name, glm::mat4 value);
private:
	void isSuccess(GLuint shader,const std::string& type);

	GLuint mProgram{ 0 };
};