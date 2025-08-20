#include "GLFramWork/core.h"
#include "GLFramWork/Shader.h"
#include "Wrapper/checkError.h"
#include "Application/Application.h"
#include "GLFramWork/Texture.h"

#include "Application/Camera/perspectiveCamera.h"
#include "Application/Camera/orthigraphicCamera.h"

#include "Geometry/Model.h"

Model* model = nullptr;
Shader* shader = nullptr;
Texture* texturea = nullptr;
Texture* textureb = nullptr;
Texture* noiseTexture = nullptr;

glm::mat4 transforma = glm::mat4(1.0f);
glm::mat4 transformb = glm::mat4(1.0f);


#ifdef PERSPECTIVE
PerpectiveCamera* camera = nullptr;
void initCamera() {
    // 创建透视投影相机
    camera = new PerpectiveCamera(
        60.0f,
        (float)app->getWidth() / (float)app->getHeight(),
        0.1f,
        1000.0f
    );
}
#else
OrthographicCamera* camera = nullptr;
void initCamera() {
    // 创建正交投影相机
    float size = 8.0f; // 正交投影的大小
    camera = new OrthographicCamera(
        -size, size, // 左右边界
        size, -size, // 上下边界
        size, -size // 近远裁剪面
    );
}
#endif

#ifdef TRACKBOLL
#include "Application/Camera/trackBallCameraControl.h"
TrackBollCameracontrol* cameraControl = nullptr;
void initCameraControl() {
    cameraControl = new TrackBollCameracontrol();
}
#else
#include "Application/Camera/gameCameraControl.h"
GameCameraControl* cameraControl = nullptr;
void initCameraControl() {
    cameraControl = new GameCameraControl();
}
#endif


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
    if (cameraControl == nullptr) {
        std::cerr << "Camera control is not initialized." << std::endl;
        return;
    }
	cameraControl->onKey(key, action, mods);
}

void onScroll(double yoffset) {
    std::cout << "Scroll offset: " << yoffset << std::endl;
    if (cameraControl == nullptr) {
        std::cerr << "Camera control is not initialized." << std::endl;
        return;
    }
    cameraControl->onScroll(static_cast<float>(yoffset));
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

void onMouse(int button, int action, int mods) {
    std::cout << "Mouse button: " << button << std::endl;
    std::cout << "Mouse action: " << action << std::endl;
    std::cout << "Mouse mods: " << mods << std::endl;
    if (cameraControl == nullptr) {
        std::cerr << "Camera control is not initialized." << std::endl;
        return;
    }
	double xpos, ypos;
	app->getCursorPosition(&xpos, &ypos);
	cameraControl->onMouseButton(button, action, xpos, ypos);
}

void onCursor(double xpos, double ypos) {
    std::cout << "Cursor position: (" << xpos << ", " << ypos << ")" << std::endl;
    if (cameraControl == nullptr) {
        std::cerr << "Camera control is not initialized." << std::endl;
        return;
	}
	cameraControl->onCursor(xpos, ypos);
}

void prepareShader() {
	shader = new Shader("Assets/Shaders/vertex.glsl", "Assets/Shaders/fragment.glsl");
}
/*
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
        // 正方形的坐标
        -0.5f, -0.5f, 0.0f, // Bottom Left
         0.5f, -0.5f, 0.0f, // Bottom Right
        -0.5f,  0.5f, 0.0f,  // Top Left
         0.5f,  0.5f, 0.0f // Top Right
    };

    float uvs[] = {
        // UV Coordinates
        0.0f, 0.0f, // Bottom Left
        1.0f, 0.0f, // Bottom Right
        0.0f, 1.0f,  // Top Left
        1.0f, 1.0f // Top Right
	};

    unsigned int indices[] = {
        0, 1, 2, // First Triangle
        2, 1, 3  // Second Triangle
    };
    //unsigned int indices[] = {
    //    0, 1, 2
    //};

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

    GLuint uvVBO = 0;
    glCheckError(glGenBuffers(1, &uvVBO));
    glCheckError(glBindBuffer(GL_ARRAY_BUFFER, uvVBO));
    glCheckError(glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW));

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

    // 顶点坐标
    // 绑定想要记录到VAO的VBO
    glCheckError(glBindBuffer(GL_ARRAY_BUFFER, interleavedVBO));
	// 激活VAO的0号位置属性
    glCheckError(glEnableVertexAttribArray(0));
    // 在VAO 0号位置记录顶点属性
    glCheckError(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));

	// 绑定颜色VBO
    // 绑定想要记录到VAO的VBO
    glCheckError(glBindBuffer(GL_ARRAY_BUFFER, colorVBO));
	// 激活vao的1号位置属性
    glCheckError(glEnableVertexAttribArray(1));
    // 在VAO 1号位置记录颜色属性
	glCheckError(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));

    // 绑定uvVBO
    // 绑定想要记录到VAO的VBO
    glCheckError(glBindBuffer(GL_ARRAY_BUFFER, uvVBO));
	// 激活vao的2号位置属性
    glCheckError(glEnableVertexAttribArray(2));
    // 在VAO 2号位置记录uv属性
    glCheckError(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0));
    
	// 绑定EBO
	// ebo不需要绑定在属性，ebo跟VAO绑定
	// 绑定VAO后，所有gl操作会默认记录到这个VAO中。所以ebo只绑定就够了
	glCheckError(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo));

    // 解绑VAO
    glCheckError(glBindVertexArray(0));


    // 动态获取Shader中属性参照的是VAO那个位置
    // 通常：
    // 1. 创建VAO和shader时，指定顶点存在那个位置，比如0号位
    // 2. shader中需要用location来指定从VAO的哪里获取数据
    // 
    // 动态获取的方式是：
    // 1. 创建VAO时，通过下记代码获取当前shader中的变量使用的是VAO那个位置
    // 2. 在VAO中记录顶点属性时，使用这个位置
    // 
    // GLuint posLocation = glGetAttribLocation(shader->getProgram(), "aPos");
    // 
    // 这个posLocation就是顶点属性在VAO中的位置
    // 将顶点属性记录到VAO的posLocation的位置
    // 
    // glEnableVertexAttribArray(posLocation)
    // glVertexAttribPointer(posLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0)
    //
    // 在不在shader中指定location时，默认分配的GLuint是根据定义从上到下从0开始的。

}
*/

void prepareTexture() {
    texturea = new Texture("Assets/Textures/testa.jpg", 0);
    textureb = new Texture("Assets/Textures/test.jpg", 0);
	//noiseTexture = new Texture("Assets/Textures/noise.jpg", 2);
}


void render() {
    glCheckError(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    // 使用着色器程序
	shader->begin();
    // 绑定VAO
    glCheckError(glBindVertexArray(model->getVAO()));

	//vs,fs中定义重名uni变量时，使用glGetUniformLocation会同时更改双方的值
	//shader->setUniFloat("time", glfwGetTime());
    shader->setUniInt("samplera", 0);
	shader->setMatrix4x4("transform", transforma);
    shader->setMatrix4x4("viewMatrix", camera->getViewMatrix());
    shader->setMatrix4x4("projectionMatrix", camera->getProjectionMatrix());

    textureb->bind();
    glCheckError(glDrawElements(GL_TRIANGLES, model->getIndices(), GL_UNSIGNED_INT, 0));
	glCheckError(glBindVertexArray(0));
    shader->end();
}


void prepareCamera() {
    initCamera();
    initCameraControl();
    cameraControl->setCamera(camera);
}

int main(){
    if (!app->init(800, 600)) {
        return -1;
    }
    app->setResizeCallback(OnReSize);
    app->setKeyCallback(key_callback);
	app->setMouseCallback(onMouse);
	app->setCursorCallback(onCursor);
	app->setScrollCallback(onScroll);
    model = Model::createBox(2.0f);


    glCheckError(glViewport(0, 0, 800, 600));
    glCheckError(glClearColor(0.2f, 0.2f, 0.2f, 1.0f));
	glCheckError(glClearDepth(1.0f));

    prepareShader();
    //prepareEBOForGLTriangles();
    prepareTexture();
    prepareCamera();

    while (app->update()) {
		cameraControl->update();
		render();

    }
    delete texturea;
    delete textureb;
    app->destroy();
    std::cout << "Window closed successfully." << std::endl;
    return 0;
}