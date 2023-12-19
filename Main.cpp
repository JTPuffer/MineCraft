#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

#define Width 1200
#define Height 1200

float vertices[] = {

        -1, -1,  1.0,   1.0f, 0.0f, 0.0f,
         1, -1,  1.0,   0.0f, 1.0f, 0.0f,
        -1,  1,  1.0,   0.0f, 0.0f, 1.0f,
         1,  1,  1.0,   1.0f, 0.5f, 0.0f,

        -1, -1, -1.0,   1.0f, 0.0f, 0.0f,
         1, -1, -1.0,   0.0f, 1.0f, 0.0f,
        -1,  1, -1.0,   0.0f, 0.0f, 1.0f,
         1,  1, -1.0,   1.0f, 0.5f, 0.0f,
};

unsigned int indices[] = { // note that we start from 0!
    //Top
    2, 6, 7,
    2, 3, 7,

    //Bottom
    0, 4, 5,
    0, 1, 5,

    //Left
    0, 2, 6,
    0, 4, 6,

    //Right
    1, 3, 7,
    1, 5, 7,

    //Front
    0, 2, 3,
    0, 1, 3,

    //Back
    4, 6, 7,
    4, 5, 7
};

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

int main(void)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//option then the value 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);// only get accses to a subset of functions


    GLFWwindow* window = glfwCreateWindow(Width, Height, "MineCraft", NULL, NULL);

    if (window == NULL) {
        std::cout << "well that didnt work ";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window); // who wouldve guesd makes the main window the current thread
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { // give glad the address of all the open gl function pointeres, glfwGet gets teh address for this os

        std::cout << "failed to init glad";
        return -1;
    }
    glViewport(0, 0, Width, Height);// tell opengl size of the window 1st 2 set the location of the top left

    Shader shader = Shader("VertexShader.vert", "FragmentShader.glsl");



    unsigned int EBO;  //holds the indecies
    glGenBuffers(1, &EBO);

    // load the vertex oin the graphics card
    unsigned int VBO;// vertext buffer object holds the points
    glGenBuffers(1, &VBO);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    //drawing an object
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);//Binds the Buffer and the vertext object together so they can share info
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);// copys verticies into the buffer

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);//tells open gl the format of the data given
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    shader.use();//makes it the current rendering state

    // define all the matrix
    //glm::mat4 model = glm::mat4(1.0f); // convert to world
    //model = glm::rotate(model, glm::radians(-55.0f),
    //glm::vec3(1.0f, 0.0f, 0.0f));

    glm::mat4 view = glm::mat4(1.0f); // convert to view
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -40.0f));
    glm::mat4 projection; // convert to clip space
    projection = glm::perspective(glm::radians(45.0f), (float)Width / (float)Height, 0.1f, 100.0f);


    glEnable(GL_DEPTH_TEST);

    float temp = 0;

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();



        shader.setmat4("view", view);
        shader.setmat4("projection", projection);


        // render the triangle

        glBindVertexArray(VAO);

        int count = 0;
        for (glm::vec3 pos : cubePositions) {
            
            glm::mat4 model = glm::mat4(1.0f);

            model = glm::translate(model, pos);

            model = glm::rotate(model, glm::radians(count * 20.0f + temp), glm::vec3(1.0f, 0.3f, 0.5f));
            model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
            shader.setmat4("model", model);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
            count++;
        }




        glfwSwapBuffers(window);
        glfwPollEvents();
        temp += 0.01;
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    return 0;
}