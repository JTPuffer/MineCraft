#include "BlockRenderer.h"

BlockRenderer::BlockRenderer(Shader& shader)
{
    this->shader = shader;
    lightPositions = {
        glm::vec3(0.7f, 0.2f, 2.0f),
        glm::vec3(2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f, 2.0f, -12.0f),
        glm::vec3(0.0f, 0.0f, -3.0f)
    };
    initRenderData();
}

BlockRenderer::~BlockRenderer()
{
    glDeleteVertexArrays(1, &quadVAO);
    glDeleteBuffers(1, &VBO);

}
void BlockRenderer::setProjectionViewMatrix(const glm::mat4& matrix)
{
    projectionViewMatrix = matrix;
    shader.use();
    shader.setmat4("projection", projectionViewMatrix);
}
void BlockRenderer::setLightPositions(const std::vector<glm::vec3>& positions) {
    lightPositions = positions;
}
// must change this to render chunk eventually
void BlockRenderer::DrawBlock(Texture diffuse, Texture specular, glm::vec3 position, Camera &cam)
{
    shader.use();



    // point light 1
    shader.setarr3("pointLightPositions", lightPositions);

    // spotLight
    shader.setVec3("spotLight.position", cam.Position);
    shader.setVec3("spotLight.direction", cam.Front);

    glActiveTexture(GL_TEXTURE0);
    diffuse.use();
    glActiveTexture(GL_TEXTURE1);
    specular.use();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);

    shader.setmat4("model", model);
    shader.setmat4("view", cam.GetViewMatrix());

    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);

}

void BlockRenderer::initRenderData()
{
    float vertices[] = {
        // back face                                
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,           0.0f, 0.0f, // bottom-left
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f, -1.0f,        1.0f, 1.0f, // top-right
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, -1.0f,           1.0f, 0.0f, // bottom-right
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f, -1.0f,        1.0f, 1.0f, // top-right
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,          0.0f, 0.0f, // bottom-left
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, -1.0f,           0.0f, 1.0f, // top-left
        // front face
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,         0.0f, 0.0f, // bottom-left
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 1.0f,         1.0f, 0.0f, // bottom-right
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f,          1.0f, 1.0f, // top-right
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f,          1.0f, 1.0f, // top-right
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 1.0f,         0.0f, 1.0f, // top-left
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,            0.0f, 0.0f, // bottom-left
        // left face
        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,         1.0f, 0.0f, // top-right
        -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f,         1.0f, 1.0f, // top-left
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,            0.0f, 1.0f, // bottom-left
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,           0.0f, 1.0f, // bottom-left
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f,            0.0f, 0.0f, // bottom-right
        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,         1.0f, 0.0f, // top-right
        // right face
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,          1.0f, 0.0f, // top-left
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,         0.0f, 1.0f, // bottom-right
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f,         1.0f, 1.0f, // top-right
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,         0.0f, 1.0f, // bottom-right
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,          1.0f, 0.0f, // top-left
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f,             0.0f, 0.0f, // bottom-left
        // bottom face
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,            0.0f, 1.0f, // top-right
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f,             1.0f, 1.0f, // top-left
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,             1.0f, 0.0f, // bottom-left
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,             1.0f, 0.0f, // bottom-left
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f,            0.0f, 0.0f, // bottom-right
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,           0.0f, 1.0f, // top-right
        // top face
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,            0.0f, 1.0f, // top-left
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,               1.0f, 0.0f, // bottom-right
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f,              1.0f, 1.0f, // top-right
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,              1.0f, 0.0f, // bottom-right
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,             0.0f, 1.0f, // top-left
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f,             0.0f, 0.0f // bottom-left
    };

    glGenBuffers(1, &VBO);


    glGenVertexArrays(1, &quadVAO);
    //drawing an object
    glBindVertexArray(quadVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);//Binds the Buffer and the vertext object together so they can share info
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);// copys verticies into the buffer


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);//tells open gl the format of the data given
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

}