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
#include "bezier_curve.h"

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
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Bezier", NULL, NULL);
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

    float p0[3] = { -0.7f, -0.2f, 0.0f };
    float p1[3] = { -0.9f, 0.9f, 0.0f };
    float p2[3] = { 0.6f, 0.0f, 0.0f };
    float pFinal[3] = { 0.0f, 0.0f, 0.0f };
    float t = 0.0f, step = 0.01f;

    std::vector<float> bezierVert;
    bezierVert.insert(bezierVert.end(), { p0[0],p0[1],p0[2] });
    bezierVert.insert(bezierVert.end(), { p1[0],p1[1],p1[2] });
    bezierVert.insert(bezierVert.end(), { p2[0],p2[1],p2[2] });
    
    while (t < 1.0f)
    {
        quadraticBezier(p0, p1, p2, t, pFinal);
        bezierVert.insert(bezierVert.end(), { pFinal[0],pFinal[1],pFinal[2] });
        t += step;
    }

    float *vert = &bezierVert[0];
    // cubic bezier
    p0[0] = -0.9f, p0[1]= -0.2f, p0[2] = 0.0f;
    p1[0] = -0.1f, p1[1] = -0.2f, p1[2] = 0.0f;
    p2[0] = -0.9f, p2[1] = 0.7f, p2[2] = 0.0f;
    float p3[3] = { 0.6f, 0.7f, 0.0f };

    t = 0.0f, step = 0.01f;
    std::vector<float> cubicBezierVert;
    cubicBezierVert.insert(cubicBezierVert.end(), { p0[0],p0[1],p0[2] });
    cubicBezierVert.insert(cubicBezierVert.end(), { p1[0],p1[1],p1[2] });
    cubicBezierVert.insert(cubicBezierVert.end(), { p2[0],p2[1],p2[2] });
    cubicBezierVert.insert(cubicBezierVert.end(), { p3[0],p3[1],p3[2] });

    while (t < 1.0f)
    {
        cubicBezier(p0, p1, p2, p3, t, pFinal);
        cubicBezierVert.insert(cubicBezierVert.end(), { pFinal[0],pFinal[1],pFinal[2] });
        t += step;
    }

    float* cubicVert = &cubicBezierVert[0];


    unsigned int VBO[2], VAO[2];
    glGenVertexArrays(2, VAO);
    glGenBuffers(2, VBO);
    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * bezierVert.size(), vert, GL_STATIC_DRAW);
    // añadiendo los vértices
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * cubicBezierVert.size(), cubicVert, GL_STATIC_DRAW);
    // añadiendo los vértices
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);



    glPointSize(5.0f);

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
        glBindVertexArray(VAO[0]); 
        shaderProgram.setVec3("colour", 0.0f, 1.0f, 0.0f);
        glDrawArrays(GL_POINTS, 0, 3);

        shaderProgram.setVec3("colour", 1.0f,1.0f,1.0f);
        glDrawArrays(GL_LINES, 3, (bezierVert.size()-3*3)/3);


        glBindVertexArray(VAO[1]); 
        shaderProgram.setVec3("colour", 0.0f, 1.0f, 0.0f);
        glDrawArrays(GL_POINTS, 0, 4);

        shaderProgram.setVec3("colour", 1.0f, 1.0f, 1.0f);
        glDrawArrays(GL_LINES, 4, (cubicBezierVert.size() - 4 * 3) / 3);



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

