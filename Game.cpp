#include "Game.h"

Game::Game(unsigned int width, unsigned int height)
{
    this->width = width;
    this->height = height;
}

Game::~Game()
{
    delete renderer;
}

void Game::Init()
{
    Shader shader = ResourceManager::loadShader("VertexShader.vert", "FragmentShader.glsl", "forblocks");
    Shader light = ResourceManager::loadShader("VertexShader.vert", "light.frag", "forlight");

    camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)width / (float)height, 0.1f, 100.0f);
    glEnable(GL_DEPTH_TEST);

    shader.use();

    shader.setint("material.diffuse", 0);
    shader.setint("material.specular", 1);
    shader.setFloat("material.shininess", 128.0f);
    // sun
    shader.setVec3("dirLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
    shader.setVec3("dirLight.ambient", glm::vec3(0.05f, 0.05f, 0.05f));
    shader.setVec3("dirLight.diffuse", glm::vec3(0.4f, 0.4f, 0.4f));
    shader.setVec3("dirLight.specular", glm::vec3(0.5f, 0.5f, 0.5f));


    shader.setVec3("pointLight.ambient", glm::vec3(0.05f, 0.05f, 0.05f));
    shader.setVec3("pointLight.diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
    shader.setVec3("pointLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));
    shader.setFloat("pointLight.constant", 1.0f);
    shader.setFloat("pointLight.linear", 0.09f);
    shader.setFloat("pointLight.quadratic", 0.032f);


    shader.setVec3("spotLight.ambient", glm::vec3(0.0f, 0.0f, 0.0f));
    shader.setVec3("spotLight.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
    shader.setVec3("spotLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));
    shader.setFloat("spotLight.constant", 1.0f);
    shader.setFloat("spotLight.linear", 0.09f);
    shader.setFloat("spotLight.quadratic", 0.032f);
    shader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
    shader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

    renderer = new BlockRenderer(shader);
    renderer->setProjectionViewMatrix(projection);

    light.use();
    light.setmat4("projection", projection);
    light.setVec3("lightColour", glm::vec3(1.0,1.0,1.0));
    renderLight = new BlockRenderer(light);

    diff =  ResourceManager::loadTexture("container2.png", "diffuesmap");
    spec = ResourceManager::loadTexture("container2_specular.png", "specular");


}

void Game::ProcessInput(float dt)
{
}

void Game::Update(float dt)
{
}

glm::vec3 cubePositions[] = { glm::vec3(0.0f, 0.0f, 0.0f),
                               glm::vec3(2.0f, 5.0f, -15.0f),
                                glm::vec3(-1.5f, -2.2f, -2.5f),
                                glm::vec3(-3.8f, -2.0f, -12.3f),
                                glm::vec3(2.4f, -0.4f, -3.5f),
                                glm::vec3(-1.7f, 3.0f, -7.5f),
                                glm::vec3(1.3f, -2.0f, -2.5f),
                                glm::vec3(1.5f, 2.0f, -2.5f),
                                glm::vec3(1.5f, 0.2f, -1.5f),
                                glm::vec3(-1.3f, 1.0f, -1.5f)
};

void Game::Render()
{
    glm::vec3 lightPositions[4] = {
        glm::vec3(0.7f, 0.2f, 2.0f),
        glm::vec3(2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f, 2.0f, -12.0f),
        glm::vec3(0.0f, 0.0f, -3.0f)
    };
    for (glm::vec3 pos : cubePositions) {
        renderer->DrawBlock(diff, spec, pos, camera);
    }

    
    for (glm::vec3 pos : lightPositions) {
        renderLight->DrawBlock(diff, spec, pos, camera);
    }

}
