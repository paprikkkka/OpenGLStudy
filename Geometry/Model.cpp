#include "Model.h"
#include "../Wrapper/checkError.h"




Model::Model(const std::string& path) {

}

Model::Model() {

}
Model::~Model() {
	if (mVAO != 0)
		glCheckError(glDeleteVertexArrays(1, &mVAO));
	if (mVBO != 0)
		glCheckError(glDeleteBuffers(1, &mVBO));
	if (mUvVBO != 0)
		glCheckError(glDeleteBuffers(1, &mUvVBO));
}

void Model::draw() {

}

Model* Model::createBox(float size) {
    Model* model = new Model();

    float halfSize = size / 2.0f;
    // 8頂点の座標
    float positions[] = {
        // 前面 (z = +0.5)
        -halfSize, -halfSize,  halfSize,   // 左下
         halfSize, -halfSize,  halfSize,   // 右下
         halfSize,  halfSize,  halfSize,   // 右上
        -halfSize,  halfSize,  halfSize,   // 左上

        // 后面 (z = -0.5)
        halfSize, -halfSize, -halfSize,   // 左下
       -halfSize, -halfSize, -halfSize,   // 右下
       -halfSize,  halfSize, -halfSize,   // 右上
        halfSize,  halfSize, -halfSize,   // 左上

        // 左面 (x = -0.5)
       -halfSize, -halfSize, -halfSize,
       -halfSize, -halfSize,  halfSize,
       -halfSize,  halfSize,  halfSize,
       -halfSize,  halfSize, -halfSize,

       // 右面 (x = +0.5)
       halfSize, -halfSize,  halfSize,
       halfSize, -halfSize, -halfSize,
       halfSize,  halfSize, -halfSize,
       halfSize,  halfSize,  halfSize,

       // 上面 (y = +0.5)
      -halfSize,  halfSize,  halfSize,
       halfSize,  halfSize,  halfSize,
       halfSize,  halfSize, -halfSize,
      -halfSize,  halfSize, -halfSize,

      // 下面 (y = -0.5)
     -halfSize, -halfSize, -halfSize,
      halfSize, -halfSize, -halfSize,
      halfSize, -halfSize,  halfSize,
     -halfSize, -halfSize,  halfSize
    };

    float uvs[] = {
        // 前
        0.0f, 0.0f,   1.0f, 0.0f,
        1.0f, 1.0f,   0.0f, 1.0f,

        // 后
        0.0f, 0.0f,   1.0f, 0.0f,
        1.0f, 1.0f,   0.0f, 1.0f,

        // 左
        0.0f, 0.0f,   1.0f, 0.0f,
        1.0f, 1.0f,   0.0f, 1.0f,

        // 右
        0.0f, 0.0f,   1.0f, 0.0f,
        1.0f, 1.0f,   0.0f, 1.0f,

        // 上
        0.0f, 0.0f,   1.0f, 0.0f,
        1.0f, 1.0f,   0.0f, 1.0f,

        // 下
        0.0f, 0.0f,   1.0f, 0.0f,
        1.0f, 1.0f,   0.0f, 1.0f
    };

    // インデックス（各面2三角形×6面）
    unsigned int indices[] = {
        0, 1, 2,   2, 3, 0,       // 前
        4, 5, 6,   6, 7, 4,       // 后
        8, 9,10,  10,11, 8,       // 左
       12,13,14,  14,15,12,       // 右
       16,17,18,  18,19,16,       // 上
       20,21,22,  22,23,20        // 下
    };

    // 頂点データをセット
    model->mIndices = sizeof(indices) / sizeof(indices[0]);

    // VBO, VAO, UVVBO生成
    glCheckError(glGenVertexArrays(1, &model->mVAO));
    glCheckError(glBindVertexArray(model->mVAO));

    glCheckError(glGenBuffers(1, &model->mVBO));
    glCheckError(glBindBuffer(GL_ARRAY_BUFFER, model->mVBO));
    glCheckError(glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW));
    glCheckError(glEnableVertexAttribArray(0));
    glCheckError(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));

    glCheckError(glGenBuffers(1, &model->mUvVBO));
    glCheckError(glBindBuffer(GL_ARRAY_BUFFER, model->mUvVBO));

    glCheckError(glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW));
    glCheckError(glEnableVertexAttribArray(2));
    glCheckError(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0));

    glCheckError(glGenBuffers(1, &model->mEBO));
    glCheckError(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->mEBO));
    glCheckError(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));

    glCheckError(glBindVertexArray(0));

    return model;
    
}

Model* Model::createSphere(float size) {
	Model* model = new Model();

	return model;

}