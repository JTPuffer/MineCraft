#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "camera.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "ErrorLogger.h"
#define Width 1200
#define Height 1200
#define sense 0.1


glm::vec3 cubePositions[] = {   glm::vec3(0.0f, 0.0f, 0.0f),
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
glm::vec3 pointLightPositions[] = {
    glm::vec3(0.7f, 0.2f, 2.0f),
    glm::vec3(2.3f, -3.3f, -4.0f),
    glm::vec3(-4.0f, 2.0f, -12.0f),
    glm::vec3(0.0f, 0.0f, -3.0f)
};

float vertices[] = { // positions
    // normals // texture coords
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f, 0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f, -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
};

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = Width / 2.0f;
float lastY = Height / 2.0f;
bool firstMouse = true;

float deltaTime = 0.0f; // Time between current frame and last frame 

glm::vec3 lightPos(2.2f, 1.0f, -1.0f);

int main(void)
{
    ErrorLogger::init("log.txt");
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//option then the value 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);// only get accses to a subset of functions


    GLFWwindow* window = glfwCreateWindow(Width, Height, "MineCraft", NULL, NULL);

    if (window == NULL) {
        ErrorLogger::log("well that didnt work ");
        glfwTerminate();
        return -1;
    }

    Camera cam = Camera();

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    glfwMakeContextCurrent(window); // who wouldve guesd makes the main window the current thread

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { // give glad the address of all the open gl function pointeres, glfwGet gets teh address for this os

        ErrorLogger::log("failed to init glad");
        return -1;
    }
    glViewport(0, 0, Width, Height);// tell opengl size of the window 1st 2 set the location of the top left


    Shader shader = ResourceManager::loadShader("VertexShader.vert", "FragmentShader.glsl","forblocks");

    Shader light = ResourceManager::loadShader("VertexShader.vert", "light.frag","forlight");


    /////////
    unsigned int VBO;// vertext buffer object holds the points
    unsigned int VAO;



        // load the vertex oin the graphics card

        glGenBuffers(1, &VBO);


        glGenVertexArrays(1, &VAO);

        //drawing an object
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);//Binds the Buffer and the vertext object together so they can share info
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);// copys verticies into the buffer


        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);//tells open gl the format of the data given
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

    ////////
    shader.use();//makes it the current rendering state

    Texture diffuseMap = ResourceManager::loadTexture("container2.png","diffuesmap");
    Texture specular = ResourceManager::loadTexture("container2_specular.png","specular");
    glEnable(GL_DEPTH_TEST);

    float temp = 0;

    float lastFrame = 0.0f; // Time of last frame
    float thisFrame = 0.0f;
 
    glm::vec3 lightColour(1.0f, 1.0f, 1.0f);
    while (!glfwWindowShouldClose(window))
    {
        thisFrame = (float)glfwGetTime();
        deltaTime = thisFrame - lastFrame;
        lastFrame = thisFrame;
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();
        shader.setmat4("view", view);

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)Width / (float)Height, 0.1f, 100.0f);
        shader.setmat4("projection", projection);


        processInput(window);

        // render the triangle


        light.use();
        light.setmat4("view", view);
        light.setmat4("projection", projection);
        light.setVec3("lightColour", lightColour);

        for (glm::vec3 pos : pointLightPositions) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::mat4(1.0f);
            model = glm::translate(model, pos);
            model = glm::scale(model, glm::vec3(0.2f));
            light.setmat4("model", model);
            //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        shader.use();
        glBindVertexArray(VAO);
        shader.setVec3("objectColour", glm::vec3(1.0f, 0.5f, 0.31f));


        shader.setint("material.diffuse", 0);
        shader.setint("material.specular", 1);
        shader.setFloat("material.shininess", 128.0f);

        shader.setVec3("dirLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
        shader.setVec3("dirLight.ambient", glm::vec3(0.05f, 0.05f, 0.05f));
        shader.setVec3("dirLight.diffuse", glm::vec3(0.4f, 0.4f, 0.4f));
        shader.setVec3("dirLight.specular", glm::vec3(0.5f, 0.5f, 0.5f));
        // point light 1
        shader.setVec3("pointLights[0].position", pointLightPositions[0]);
        shader.setVec3("pointLights[0].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
        shader.setVec3("pointLights[0].diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
        shader.setVec3("pointLights[0].specular", glm::vec3(1.0f, 1.0f, 1.0f));
        shader.setFloat("pointLights[0].constant", 1.0f);
        shader.setFloat("pointLights[0].linear", 0.09f);
        shader.setFloat("pointLights[0].quadratic", 0.032f);
        // point light 2
        shader.setVec3("pointLights[1].position", pointLightPositions[1]);
        shader.setVec3("pointLights[1].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
        shader.setVec3("pointLights[1].diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
        shader.setVec3("pointLights[1].specular", glm::vec3(1.0f, 1.0f, 1.0f));
        shader.setFloat("pointLights[1].constant", 1.0f);
        shader.setFloat("pointLights[1].linear", 0.09f);
        shader.setFloat("pointLights[1].quadratic", 0.032f);
        // point light 3
        shader.setVec3("pointLights[2].position", pointLightPositions[2]);
        shader.setVec3("pointLights[2].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
        shader.setVec3("pointLights[2].diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
        shader.setVec3("pointLights[2].specular", glm::vec3(1.0f, 1.0f, 1.0f));
        shader.setFloat("pointLights[2].constant", 1.0f);
        shader.setFloat("pointLights[2].linear", 0.09f);
        shader.setFloat("pointLights[2].quadratic", 0.032f);
        // point light 4
        shader.setVec3("pointLights[3].position", pointLightPositions[3]);
        shader.setVec3("pointLights[3].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
        shader.setVec3("pointLights[3].diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
        shader.setVec3("pointLights[3].specular", glm::vec3(1.0f, 1.0f, 1.0f));
        shader.setFloat("pointLights[3].constant", 1.0f);
        shader.setFloat("pointLights[3].linear", 0.09f);
        shader.setFloat("pointLights[3].quadratic", 0.032f);
        // spotLight
        shader.setVec3("spotLight.position", camera.Position);
        shader.setVec3("spotLight.direction", camera.Front);
        shader.setVec3("spotLight.ambient", glm::vec3(0.0f, 0.0f, 0.0f));
        shader.setVec3("spotLight.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
        shader.setVec3("spotLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        shader.setFloat("spotLight.constant", 1.0f);
        shader.setFloat("spotLight.linear", 0.09f);
        shader.setFloat("spotLight.quadratic", 0.032f);
        shader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
        shader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

        int count = 0;
        glActiveTexture(GL_TEXTURE0);
        diffuseMap.use();
        glActiveTexture(GL_TEXTURE1);
        specular.use();
        for (glm::vec3 pos : cubePositions) {

            glm::mat4 model = glm::mat4(1.0f);

            model = glm::translate(model, pos);

            model = glm::rotate(model, glm::radians(count * 20.0f + temp * 100), glm::vec3(1.0f, 0.3f, 0.5f));
            //model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
            shader.setmat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            count++;
        }


 
        glfwSwapBuffers(window);
        glfwPollEvents();
        temp += 0.001f;
        //std::cout << 1 / deltaTime << '\n';
        lightColour.x = 1;
        lightColour.y = 1;
        lightColour.z = 1;
    }
    ErrorLogger::shutdown();
    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}