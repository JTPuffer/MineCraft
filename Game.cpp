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
    Shader shader = ResourceManager::loadShader("chunk.vs", "FragmentShader.glsl", "forChunk");
    Shader light = ResourceManager::loadShader("VertexShader.vert", "light.frag", "forlight");

    camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)width / (float)height, 0.1f, 100.0f);
    glEnable(GL_DEPTH_TEST);

    shader.use();

    shader.setint("material.diffuse", 0);
    shader.setint("material.specular", 1);
    shader.setVec2("material.top", glm::vec2(0.0, 0.0));
    shader.setVec2("material.bottom", glm::vec2(0.125, 0.0));
    shader.setVec2("material.side", glm::vec2(0.1875, 0.0));

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

    renderer = new Chunk(shader);
    renderer->setProjectionViewMatrix(projection);

    light.use();
    light.setmat4("projection", projection);
    light.setVec3("lightColour", glm::vec3(1.0,1.0,1.0));
    renderLight = new BlockRenderer(light);

    diff =  ResourceManager::loadTexture("terrain.png", "diffuesmap");
    spec = ResourceManager::loadTexture("terrain.png", "specular");


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
    renderer->DrawChunk(diff,spec,glm::vec3(0.0,0.0,0.0), camera);
}


