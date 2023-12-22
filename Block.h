#pragma once
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Block
{

    float vertices[64] = {

            -0.5f, -0.5f, 0.5f,     0.0f, 0.0f, 1.0f,    0.0f, 0.0f,
             0.5f, -0.5f, 0.5f,     0.0f, 0.0f, 1.0f,    1.0f, 0.0f,
            -0.5f, 0.5f,  0.5f,     0.0f, 0.0f, 1.0f,    0.0f, 1.0f,
             0.5f, 0.5f,  0.5f,     0.0f, 0.0f, 1.0f,    1.0f, 1.0f,

           -0.5f, -0.5f, -0.5f,     0.0f, 0.0f,-1.0f,    0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,     0.0f, 0.0f,-1.0f,    1.0f, 0.0f,
           -0.5f,  0.5f, -0.5f,     0.0f, 0.0f,-1.0f,    0.0f, 1.0f,
            0.5f,  0.5f, -0.5f,     0.0f, 0.0f,-1.0f,    1.0f, 1.0f,
    };

    unsigned int indices[36] = { // note that we start from 0!
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
    unsigned int EBO;  //holds the indecies
    unsigned int VBO;// vertext buffer object holds the points
    unsigned int VAO;
public:
	Block() {

        glGenBuffers(1, &EBO);

        // load the vertex oin the graphics card

        glGenBuffers(1, &VBO);


        glGenVertexArrays(1, &VAO);

        //drawing an object
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);//Binds the Buffer and the vertext object together so they can share info
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);// copys verticies into the buffer

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);//tells open gl the format of the data given
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
	}
    ~Block() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }
    void use() {
        glBindVertexArray(VAO);
    }
};

