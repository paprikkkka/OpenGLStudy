#include "Shader.h"
#include "../Wrapper/checkError.h"


#include <fstream>
#include <sstream>



Shader::Shader(const char* vertexPath, const char* fragmentPath) {
	// Shader受ける変数
	std::string vertexCode;
	std::string fragmentCode;
	// ロード変数
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	// 例外を投げる
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		// ファイルを開く
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		// ファイルの内容を読み込む
		std::stringstream vShaderStream, fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// ファイルを閉じる
		vShaderFile.close();
		fShaderFile.close();
		// ストリームを文字列に変換
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure& e) {
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
		std::cout << "Vertex Shader Path: " << vertexPath << std::endl;
		std::cout << "Fragment Shader Path: " << fragmentPath << std::endl;
		std::cout << e.what() << std::endl;
	}

	GLuint vertex, fragment;
	vertex = glCheckError(glCreateShader(GL_VERTEX_SHADER));
	fragment = glCheckError(glCreateShader(GL_FRAGMENT_SHADER));

	const char* vertexCodeCStr = vertexCode.c_str();
	const char* fragmentCodeCStr = fragmentCode.c_str();

	glCheckError(glShaderSource(vertex, 1, &vertexCodeCStr, NULL));
	glCheckError(glShaderSource(fragment, 1, &fragmentCodeCStr, NULL));

	glCheckError(glCompileShader(vertex));
	isSuccess(vertex, "COMPILE");

	glCheckError(glCompileShader(fragment));
	isSuccess(fragment, "COMPILE");

	mProgram = glCreateProgram();
	glCheckError(glAttachShader(mProgram, vertex));
	glCheckError(glAttachShader(mProgram, fragment));
	glCheckError(glLinkProgram(mProgram));
	isSuccess(mProgram, "LINK");
	// 删除着色器对象
	glCheckError(glDeleteShader(vertex));
	glCheckError(glDeleteShader(fragment));
}

Shader::~Shader() {

}

void Shader::begin() {
	glCheckError(glUseProgram(mProgram));
}

void Shader::end() {
	glCheckError(glUseProgram(0));
}

void Shader::isSuccess(GLuint target,const std::string& type) {
	int success = 0;
	char infoLog[512];
	if (type == "COMPILE") {
		glGetShaderiv(target, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(target, 512, NULL, infoLog);
			std::cout << "error\n" << infoLog << std::endl;
		}
	}
	else if (type == "LINK") {
		glGetProgramiv(target, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(target, 512, NULL, infoLog);
			std::cout << "error\n" << infoLog << std::endl;
		}
	}
	else {
		std::cerr << "Unknown shader type: " << type << std::endl;
	}
}


void Shader::setUniFloat(const std::string& name, float value) {
	GLuint location = glCheckError(glGetUniformLocation(mProgram, name.c_str()));
	if (location == -1) {
		std::cerr << "Uniform '" << name << "' not found in shader program." << std::endl;
		return;
	}
	glCheckError(glUniform1f(location, value));
}

void Shader::setUniInt(const std::string& name, int value) {
	GLuint location = glCheckError(glGetUniformLocation(mProgram, name.c_str()));
	if (location == -1) {
		std::cerr << "Uniform '" << name << "' not found in shader program." << std::endl;
		return;
	}
	glCheckError(glUniform1i(location, value));
}


void Shader::setMatrix4x4(const std::string& name, glm::mat4 value) {
	GLuint location = glCheckError(glGetUniformLocation(mProgram, name.c_str()));
	if (location == -1) {
		std::cerr << "Uniform '" << name << "' not found in shader program." << std::endl;
		return;
	}
	glCheckError(glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value)));
}