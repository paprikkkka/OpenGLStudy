#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include "Wrapper/checkError.h"
#include "Application/Application.h"

GLuint vao, program;
bool swapBuffers = true;

float colorsA[] = {
    // Colors
    0.0f, 0.0f, 0.0f, // Red
    0.0f, 0.0f, 0.0f, // Green
    0.0f, 0.0f, 1.0f, // Blue
    0.5f, 0.5f, 1.0f  // Blue
};

float colorsB[] = {
    // Colors
    1.0f, 0.0f, 0.0f, // Red
    0.0f, 1.0f, 0.0f, // Green
    0.0f, 0.0f, 1.0f, // Blue
    0.5f, 0.5f, 1.0f  // Blue
};


void key_callback(int key, int action, int mods) {
    std::cout << "key: " << key << std::endl;
    std::cout << "action: " << action << std::endl;
    std::cout << "mods: " << mods << std::endl;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        if (swapBuffers) {

            GLuint colorVBO = 0;
            glCheckError(glGenBuffers(1, &colorVBO));
            glCheckError(glBindBuffer(GL_ARRAY_BUFFER, colorVBO));
            glCheckError(glBufferData(GL_ARRAY_BUFFER, sizeof(colorsA), colorsA, GL_STATIC_DRAW));
            glCheckError(glEnableVertexAttribArray(1));
            // 在VAO 1号位置记录颜色属性
            glCheckError(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));
			swapBuffers = !swapBuffers;
        }
        else {

            GLuint colorVBO = 0;
            glCheckError(glGenBuffers(1, &colorVBO));
            glCheckError(glBindBuffer(GL_ARRAY_BUFFER, colorVBO));
            glCheckError(glBufferData(GL_ARRAY_BUFFER, sizeof(colorsB), colorsB, GL_STATIC_DRAW));
            glCheckError(glEnableVertexAttribArray(1));
            // 在VAO 1号位置记录颜色属性
            glCheckError(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));
			swapBuffers = !swapBuffers;
        }
	}
}

void OnReSize(int width, int height) {
    if (width == 0 || height == 0) {
        std::cerr << "Window size is zero, skipping viewport adjustment." << std::endl;
        return;
    }
    
    std::cout << "Resizing viewport to: " << width << "x" << height << std::endl;
    glViewport(0, 0, width, height);
    //glViewport(0, 0, height, width);
}


void prepareShader() {
    const char* vertexShaderSource =
        "#version 460 core\n"
        "layout(location = 0) in vec3 aPos;\n"
        "layout(location = 1) in vec3 aColor;\n"
        "out vec3 color;\n"
        "void main()\n"
        "{\n"
        "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "    color = aColor;"
        "}\0";
    const char* fragmentShaderSource =
        "#version 460 core\n"
        "out vec4 FragColor;\n"
        "in vec3 color;\n"
        "void main()\n"
        "{\n"
        "    FragColor = vec4(color, 1.0f);\n"
        "}\0";

    GLuint vertex, fragment;
    vertex = glCheckError(glCreateShader(GL_VERTEX_SHADER));
    fragment = glCheckError(glCreateShader(GL_FRAGMENT_SHADER));

    glCheckError(glShaderSource(vertex, 1, &vertexShaderSource, NULL));
    glCheckError(glShaderSource(fragment, 1, &fragmentShaderSource, NULL));

    int success = 0;
    glCheckError(glCompileShader(vertex));
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "error\n" << infoLog << std::endl;
    }

    glCheckError(glCompileShader(fragment));
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "error\n" << infoLog << std::endl;
    }

	program = glCreateProgram();
    glCheckError(glAttachShader(program, vertex));
    glCheckError(glAttachShader(program, fragment));
    glCheckError(glLinkProgram(program));
    // 检查链接错误
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cout << "error\n" << infoLog << std::endl;
    }
    // 删除着色器对象
    glCheckError(glDeleteShader(vertex));
    glCheckError(glDeleteShader(fragment));
}

void prepareSingleBuffer() {
    float vertices[] = {
        // Positions
        -0.5f, -0.5f, 0.0f, // Bottom Left
         0.5f, -0.5f, 0.0f, // Bottom Right
         0.0f,  0.5f, 0.0f  // Top
    };
    float colors[] = {
        // Colors
        1.0f, 0.0f, 0.0f, // Red
        0.0f, 1.0f, 0.0f, // Green
        0.0f, 0.0f, 1.0f  // Blue
    };

    GLuint vetVBO = 0, colVBO = 0;
    glCheckError(glGenBuffers(1, &vetVBO));
    glCheckError(glGenBuffers(1, &colVBO));

    glCheckError(glBindBuffer(GL_ARRAY_BUFFER, vetVBO));
    glCheckError(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));

    glCheckError(glBindBuffer(GL_ARRAY_BUFFER, colVBO));
    glCheckError(glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW));

    // 创建VAO
    GLuint aVAO = 0;
    glCheckError(glGenVertexArrays(1, &aVAO));
    glCheckError(glBindVertexArray(aVAO));
    // 绑定想要记录到VAO的VBO
    glCheckError(glBindBuffer(GL_ARRAY_BUFFER, vetVBO));
    // 激活VAO的属性
    glCheckError(glEnableVertexAttribArray(0));
    // 在VAO 0号位置记录顶点属性
    // glVertexAttribPointer运行时bind的是那个VBO就用那个VBO的值
    glCheckError(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));

    // 绑定颜色VBO
    glCheckError(glBindBuffer(GL_ARRAY_BUFFER, colVBO));
    // 激活颜色属性
    glCheckError(glEnableVertexAttribArray(1));
    // 在VAO 1号位置记录顶点属性
    glCheckError(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));

    // 解绑VAO
    glCheckError(glBindVertexArray(0));
}

void prepareInterleavedBuffer() {
    float vertices[] = {
        // Positions          // Colors
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // Bottom Left (Red)
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // Bottom Right (Green)
         0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,  // Top (Blue)
         0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f  // Top (Blue)
    };
    GLuint interleavedVBO = 0;
    glCheckError(glGenBuffers(1, &interleavedVBO));
    glCheckError(glBindBuffer(GL_ARRAY_BUFFER, interleavedVBO));
    glCheckError(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
    // 创建VAO
    glCheckError(glGenVertexArrays(1, &vao));
    glCheckError(glBindVertexArray(vao));
    // 绑定想要记录到VAO的VBO
    // interleavedVBO没有解绑无需绑定
    

    glCheckError(glBindBuffer(GL_ARRAY_BUFFER, interleavedVBO));
    // 激活VAO的属性
    glCheckError(glEnableVertexAttribArray(0));
    // 在VAO 0号位置记录顶点属性
    glCheckError(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0));
    // 激活颜色属性
    glCheckError(glEnableVertexAttribArray(1));
    // 在VAO 1号位置记录颜色属性
    glCheckError(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))));
    // 解绑VAO
    glCheckError(glBindVertexArray(0));
}

void prepareVAOForGLTriangles() {
    float vertices[] = {
        // Positions
        -0.5f, -0.5f, 0.0f, // Bottom Left
         0.5f, -0.5f, 0.0f, // Bottom Right
         0.0f,  0.5f, 0.0f,  // Top
		 0.5f,  0.5f, 0.0f,  // Top Right
		 0.8f,  0.8f, 0.0f,   // Top Right
		 0.8f,  0.0f, 0.0f   // Top Left

    };
    GLuint interleavedVBO = 0;
    glCheckError(glGenBuffers(1, &interleavedVBO));
    glCheckError(glBindBuffer(GL_ARRAY_BUFFER, interleavedVBO));
    glCheckError(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
    // 创建VAO
    glCheckError(glGenVertexArrays(1, &vao));
    glCheckError(glBindVertexArray(vao));
    // 绑定想要记录到VAO的VBO
    // interleavedVBO没有解绑无需绑定


    glCheckError(glBindBuffer(GL_ARRAY_BUFFER, interleavedVBO));
    // 激活VAO的属性
    glCheckError(glEnableVertexAttribArray(0));
    // 在VAO 0号位置记录顶点属性
    glCheckError(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));
    // 解绑VAO
    glCheckError(glBindVertexArray(0));
}

void prepareEBOForGLTriangles() {
    float vertices[] = {
        // Positions
        -0.5f, -0.5f, 0.0f, // Bottom Left
         0.5f, -0.5f, 0.0f, // Bottom Right
         0.0f,  0.5f, 0.0f,  // Top
         0.5f,  0.5f, 0.0f  // Top Right
    };

    unsigned int indices[] = {
        0, 1, 2, // First Triangle
        2, 1, 3  // Second Triangle
	};

    float colors[] = {
        // Colors
        1.0f, 0.0f, 0.0f, // Red
        0.0f, 1.0f, 0.0f, // Green
        0.0f, 0.0f, 1.0f, // Blue
        0.5f, 0.5f, 1.0f  // Blue
    };

    GLuint interleavedVBO = 0;
    glCheckError(glGenBuffers(1, &interleavedVBO));
    glCheckError(glBindBuffer(GL_ARRAY_BUFFER, interleavedVBO));
    glCheckError(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));

	GLuint colorVBO = 0;
    glCheckError(glGenBuffers(1, &colorVBO));
    glCheckError(glBindBuffer(GL_ARRAY_BUFFER, colorVBO));
    glCheckError(glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW));
    // 创建EBO
	// EBO是索引缓冲对象，记录顶点的索引

	GLuint ebo;
	glCheckError(glGenBuffers(1, &ebo));
	glCheckError(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo));
	glCheckError(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));

    // 创建VAO
    glCheckError(glGenVertexArrays(1, &vao));
	// 绑定VAO
	// 绑定VAO后，所有gl操作会默认记录到这个VAO中。
    glCheckError(glBindVertexArray(vao));
    // 绑定想要记录到VAO的VBO
    // interleavedVBO没有解绑无需绑定
    glCheckError(glBindBuffer(GL_ARRAY_BUFFER, interleavedVBO));
    // 激活VAO的属性
    glCheckError(glEnableVertexAttribArray(0));
    // 在VAO 0号位置记录顶点属性
    glCheckError(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));
	// 绑定颜色VBO
    glCheckError(glBindBuffer(GL_ARRAY_BUFFER, colorVBO));
    // 激活颜色属性
    glCheckError(glEnableVertexAttribArray(1));
    // 在VAO 1号位置记录颜色属性
	glCheckError(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));
    
	// 绑定EBO
	// 绑定VAO后，所有gl操作会默认记录到这个VAO中。所以ebo只绑定就够了
	glCheckError(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo));
    // 解绑VAO
    glCheckError(glBindVertexArray(0));
}

void render() {
    glCheckError(glClear(GL_COLOR_BUFFER_BIT));

    // 使用着色器程序
    glCheckError(glUseProgram(program));

	// 绑定VAO
    glCheckError(glBindVertexArray(vao));

    // 绘制三角形
    //glCheckError(glDrawArrays(GL_TRIANGLE_STRIP, 0, 6));

	glCheckError(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));

}

int main(){

    if (!app->init(800, 600)) {
        return -1;
    }
    app->setResizeCallback(OnReSize);
    app->setKeyCallback(key_callback);



    glCheckError(glViewport(0, 0, 800, 600));
    glCheckError(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));

    prepareShader();
    prepareEBOForGLTriangles();


    while (app->update()) {

		 render();

    }

    app->destroy();
    std::cout << "Window closed successfully." << std::endl;
    return 0;
}