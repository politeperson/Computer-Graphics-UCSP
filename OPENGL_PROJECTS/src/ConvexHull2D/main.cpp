// GLAD
#include <glad/glad.h>
#include <glfw/glfw3.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// STL C++
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

// Library from LearnOpenGL
#include "shader.h"

// RegularPolygon library
#include "convex_hull.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Convex Hull (Graham Scan)", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // shader class
    Shader shaderProgram("vertexShader.glsl", "fragmentShader.glsl");

    std::vector<Point> S; // set of 2D points
    int N;
    std::cout << "Ingresa la cantidad de puntos a generar:";
    std::cin >> N;

    // números random entre la caja: {[-0.5, 0.5],[-0.7, 0.7]}
    for (int i = 0; i < N; ++i)
        S.push_back(Point{ random(-0.5, 0.5), random(-0.7, 0.7) });
    
    

    float* vertices = new float[S.size() * 3];
    for (int i = 0; i < S.size(); ++i)
    {
        vertices[i * 3] = S[i].x;
        vertices[i * 3 + 1] = S[i].y;
        vertices[i * 3 + 2] = 0.0f; // porque solo trabajamos en 2D
    }

    // generando los vértices del convex hull
    // tamaño del upper y lower convex hull
    int uconv_size = 0, lconv_size = 0;
    std::vector<Point> convex_hull = GrahamScan(S, uconv_size, lconv_size);
    std::cout << "Tamaño del convex Hull: " << convex_hull.size() - 2 << std::endl;
    // vertices del convex_hull
    float* conv_vertices = new float[convex_hull.size() * 3];
    for (int i = 0; i < convex_hull.size(); ++i)
    {
		conv_vertices[i * 3] = convex_hull[i].x;
		conv_vertices[i * 3 + 1] = convex_hull[i].y;
		conv_vertices[i * 3 + 2] = 0.0f; // porque solo trabajamos en 2D
	}
    


    unsigned int VBO[2], VAO[2];
    glGenVertexArrays(2, VAO);
    glGenBuffers(2, VBO);

    // vertices del conjunto S
    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (S.size() * 3), vertices, GL_STATIC_DRAW);
    // añadiendo los vértices
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    // vértices del convex_hull
    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (convex_hull.size() * 3), conv_vertices, GL_STATIC_DRAW);
    // añadiendo los vértices
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);



    glPointSize(5.0f);

    // podemos liberar la memoria del heap
    delete[] vertices;
    delete[] conv_vertices;

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.03f, 0.05f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        // render container
        shaderProgram.use();
        // vertices del conjunto S
        glBindVertexArray(VAO[0]); 
        shaderProgram.setVec3("colour", 0.0f, 1.0f, 0.0f);
        glDrawArrays(GL_POINTS, 0, S.size());

        // vertices del conjunto del Convex Hull
        glBindVertexArray(VAO[1]);
        shaderProgram.setVec3("colour", 1.0f,1.0f,1.0f);
        glDrawArrays(GL_LINE_STRIP, 0, uconv_size + lconv_size);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(2, VAO);
    glDeleteBuffers(2, VBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

