#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Game.h"
#define Width 1200
#define Height 1200
#define sense 0.1



void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = Width / 2.0f;
float lastY = Height / 2.0f;
bool firstMouse = true;

float deltaTime = 0.0f; // Time between current frame and last frame 

glm::vec3 lightPos(2.2f, 1.0f, -1.0f);

Game *g;
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

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    glfwMakeContextCurrent(window); // who wouldve guesd makes the main window the current thread

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { // give glad the address of all the open gl function pointeres, glfwGet gets teh address for this os

        ErrorLogger::log("failed to init glad");
        return -1;
    }
    glViewport(0, 0, Width, Height);// tell opengl size of the window 1st 2 set the location of the top left


    ////////
    g = new Game(Width, Height);

    glEnable(GL_DEPTH_TEST);

    float temp = 0;

    float lastFrame = 0.0f; // Time of last frame
    float thisFrame = 0.0f;
 
    g->Init();
    while (!glfwWindowShouldClose(window))
    {
        thisFrame = (float)glfwGetTime();
        deltaTime = thisFrame - lastFrame;
        lastFrame = thisFrame;
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        
        processInput(window);

        // render the triangle



        g->Render();

 
        glfwSwapBuffers(window);
        glfwPollEvents();
        temp += 0.001f;
        //std::cout << 1 / deltaTime << '\n';
    }
    ErrorLogger::shutdown();
    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        g->camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        g->camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        g->camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        g->camera.ProcessKeyboard(RIGHT, deltaTime);
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

    g->camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    g->camera.ProcessMouseScroll(static_cast<float>(yoffset));
}