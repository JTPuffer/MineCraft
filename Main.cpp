#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>



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

    Shader shader = Shader("VertexShader.glsl", "FragmentShader.glsl");



    unsigned int EBO;  //holds the indecies
    glGenBuffers(1, &EBO);

    // load the vertex oin the graphics card
    unsigned int VBO;// vertext buffer object holds the points
    glGenBuffers(1, &VBO);

    //drawing an object

    glBindBuffer(GL_ARRAY_BUFFER,VBO);//Binds the Buffer and the vertext object together so they can share info
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);// copys verticies into the buffer

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)0);//tells open gl the format of the data given
    glEnableVertexAttribArray(0);

    shader.use();//makes it the current rendering state

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


	return 0;
}