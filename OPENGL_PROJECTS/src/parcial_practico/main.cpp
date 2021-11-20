// [Saul Rojas Coila]
// CG_2021_02
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

// stb_image
#include "stb_image.h"

// Library from LearnOpenGL
#include "shader.h"

// Matrices library
#include "matrices.h"
#include "animations.h"

enum class DrawMode { POINTS, TRIANGLES, LINES };
enum class ProgramShape { TRIANGLE, SQUARE, DIAMOND };
DrawMode global_drawing_mode = DrawMode::TRIANGLES;
bool pause_animation = false;
// Console Manual
void manual() 
{
    std::cout << "Las siguientes teclas realizan... \n";
    std::cout << "Presiona P para visualizar puntos.\n";
    std::cout << "Presiona L para visualizar lineas.\n";
    std::cout << "Presiona T para visualizar triangulos.\n";
    std::cout << "Presiona A para pausar la animacion.\n";
    std::cout << "Presiona B para reanudar la animacion.\n";
}

void draw_triangle(DrawMode mode)
{
    switch (mode)
    {
    case DrawMode::POINTS:
        glDrawArrays(GL_POINTS, 0, 3);
        break;
    case DrawMode::TRIANGLES:
        glDrawArrays(GL_TRIANGLES, 0, 3);
        break;
    case DrawMode::LINES:
        glDrawElements(GL_LINES, 6, GL_UNSIGNED_INT, 0);
        break;
    }
}

void draw_square_or_diamond(DrawMode mode)
{
    switch (mode)
    {
    case DrawMode::POINTS:
        glDrawArrays(GL_POINTS, 0, 4);
        break;
    case DrawMode::TRIANGLES:
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        break;
    case DrawMode::LINES:
        glDrawElements(GL_LINES, 8, GL_UNSIGNED_INT, (void*)(6 * sizeof(GLuint)));
        break;
    }
}
void draw_star(DrawMode mode)
{
    switch (mode)
    {
    case DrawMode::POINTS:
        glDrawArrays(GL_POINTS, 0, 11);
        break;
    case DrawMode::TRIANGLES:
        // drawing filled mode
        glDrawElements(GL_TRIANGLES, 15, GL_UNSIGNED_INT, 0); // external triangles (15 first vertices)
        glDrawElements(GL_TRIANGLE_FAN, 7, GL_UNSIGNED_INT, (void*)(15 * sizeof(GLuint))); // internal polygon (7 vertices with offset of 15 uint bits)
        break;
    case DrawMode::LINES:
        glDrawElements(GL_LINES, 20, GL_UNSIGNED_INT, (void*)(22 * sizeof(GLuint))); // internal polygon (11 vertices with offset of 22 uint bits)

        break;
    }
}

// callbacks
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
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Examen Parcial Practico", NULL, NULL);
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

    // 3 Shaders para aplicar distintas transformaciones en el tiempo
    Shader shaderScaling("vertexShaderScaling.glsl", "fragmentShader.glsl");
    Shader shaderRotation("vertexShaderRotation.glsl", "fragmentShaderRotation.glsl");
    Shader shaderTranslation("vertexShaderTranslation.glsl", "fragmentShader.glsl");
    Shader shaderStar("vertexShaderStar.glsl", "fragmentShader.glsl");

    // Modelado
    // vertices
    GLfloat vert_triangle[] = {
        // triángulo - rojo
        0.0f, 0.1f, 0.0f, 1.0f, 0.0f, 0.0f, // top
        -0.1f, -0.1f, 0.0f, 1.0f, 0.0f, 0.0f, // left
        0.1f, -0.1f, 0.0f, 1.0f, 0.0f, 0.0f// right
    };
    GLfloat vert_square[] = {
        // cuadrado - verde
        0.4f, 0.1f, 0.0f, 0.0f, 0.7f, 0.0f, 1.0f, 1.0f, // top-right
        0.4f, -0.1f, 0.0f, 0.0f, 0.6f, 0.0f, 1.0f, 0.0f, // bottom-right
        0.2f, -0.1f, 0.0f, 0.0f, 0.7f, 0.0f, 0.0f, 0.0f,// bottom-left
        0.2f, 0.1f, 0.0f, 0.0f, 0.8f, 0.0f, 0.0f, 1.0f, // top-left
    };
    GLfloat vert_diamond[] = {
        // rombo - azul
        0.6f, 0.15f, 0.0f, 0.0f, 0.0f, 1.0f, // top
        0.7f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, // right
        0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, // left
        0.6f, -0.15f, 0.0f, 0.0f, 0.0f, 1.0f // bottom
    };

    GLfloat vert_star[] = {
        // external vertices
         0.85f,  0.12f, 0.0f, 0.952f, 0.952f, 0.05f,
         0.95f,  0.04f, 0.0f, 0.952f, 0.952f, 0.05f,
         0.9f, -0.1f, 0.0f, 0.952f, 0.952f, 0.05f,
         0.8f, -0.1f, 0.0f, 0.952f, 0.952f, 0.05f,
         0.75f,  0.04f, 0.0f, 0.952f, 0.952f, 0.05f,
        // interior vertices
         0.83f,  0.04f, 0.0f,  0.952f, 0.952f, 0.05f,
         0.87f,  0.04f, 0.0f,  0.952f, 0.952f, 0.05f,
         0.88f, -0.02f, 0.0f, 0.952f, 0.952f, 0.05f,
         0.85f,  -0.05f, 0.0f, 0.952f, 0.952f, 0.05f,
         0.82f, -0.02f, 0.0f, 0.952f, 0.952f, 0.05f,
        // center
         0.85f,   0.0f, 0.0f, 0.952f, 0.952f, 0.05f
    };
    // indices
    GLuint indices_triangle[] = {
        // modo de dibujo: líneas
        // triángulo
        0,1,1,2,2,0
    };
    GLuint indices_square[] = {
        // modo de dibujo: triángulos
        // cuadrado
        0, 1, 3,
        1, 2, 3,
        // modo de dibujo: líneas
        // cuadrado
        0,1,1,2,2,3,3,0
    };
    GLuint indices_diamond[] = {
		// modo de dibujo: triángulo
        // rombo
		0, 1, 2,
		3, 1, 2,
        // modo de dibujo: líneas
		// rombo
		0, 1, 1, 3, 3, 2, 2, 0
    };
    GLuint indices_star[] = {
        // for filled mode
        // external triangles
        0, 5, 6,
        1, 6, 7,
        2, 7, 8,
        3, 8, 9,
        4, 9, 5,
        // interior polygon (with triangle fan mode)
        10, // first the center of the star
        5, 6, 7, 8, 9, 5, // ending in the same position
        // offset: 22

        // for lined mode
        0, 6, 6, 1,
        1, 7, 7, 2,
        2, 8, 8, 3,
        3, 9, 9, 4,
        4, 5, 5, 0 // offset: 42
    };

    unsigned int VBO[4], VAO[4], EBO[4];
    glGenVertexArrays(4, VAO);
    glGenBuffers(4, VBO);
    glGenBuffers(4, EBO);

    // triangles containers
    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_triangle), indices_triangle, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vert_triangle), vert_triangle, GL_STATIC_DRAW);
    // añadiendo los vértices
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // añadiendo los colores
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // square containers
    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_square), indices_square, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vert_square), vert_square, GL_STATIC_DRAW);
    // añadiendo los vértices
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // añadiendo los colores
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // añadiendo las coordenadas de las texturas
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // rhombus containers
    glBindVertexArray(VAO[2]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[2]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_diamond), indices_diamond, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vert_diamond), vert_diamond, GL_STATIC_DRAW);
    // añadiendo los vértices
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // añadiendo los colores
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // star containers
    glBindVertexArray(VAO[3]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[3]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_star), indices_star, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[3]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vert_star), vert_star, GL_STATIC_DRAW);
    // añadiendo los vértices
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // añadiendo los colores
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // texturas
    GLuint rana;
    // texture 1
    // ---------
    glGenTextures(1, &rana);
    glBindTexture(GL_TEXTURE_2D, rana);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    unsigned char* data = stbi_load("carpincho.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);


    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    shaderRotation.use();
    shaderRotation.setInt("ranaTexture", 0);


    // ejecuto el manual
    manual();

    glLineWidth(5.0f);
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
        glClearColor(0.05f, 0.05f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        // render container
        // primero administramos las animaciones

        // triángulo
        // para el escalamiento
        glBindVertexArray(VAO[0]);
        float mat4x4_scale[4][4] = { 0.0f };
        uniform_scaling(mat4x4_scale, sin(animation_triangle(pause_animation)) * 0.3f + 0.7f);
        shaderScaling.use();
        shaderScaling.setMat4("aScale", mat4x4_scale);
        draw_triangle(global_drawing_mode);
        
        // cuadrado
        glBindVertexArray(VAO[1]);
        // para la rotación
        float mat4x4_rotation_trans[4][4] = { 0 };
        float z[3] = { 0.0f, 0.0f, 1.0f }, vec_tr[3] = {0.0f,0.0f,0.0f}; // alrededor del eje z
        rotation(mat4x4_rotation_trans, animation_triangle(pause_animation), z); // primero obtenemos la matriz de rotación
        animation_rotation(vec_tr, mat4x4_rotation_trans); // rotamos el vector del centro del cuadrado
        translation(mat4x4_rotation_trans, vec_tr); // creamos la matriz de traslación por ese vector rotado
        glBindTexture(GL_TEXTURE_2D, rana);
        shaderRotation.use();
        shaderRotation.setMat4("aRotation", mat4x4_rotation_trans);
        draw_square_or_diamond(global_drawing_mode);

        // rombo o diamante
        glBindVertexArray(VAO[2]);
        // para la traslación
        float trans_vec[3] = { 0.0f, 0.0f, 0.0f };
        float mat4x4_trans[4][4] = { 0 };
        animation_translation(trans_vec, 0.0005f, pause_animation);
        translation(mat4x4_trans, trans_vec);
        shaderTranslation.use();
        shaderTranslation.setMat4("matTrans", mat4x4_trans);
        draw_square_or_diamond(global_drawing_mode);

        // estrella
        glBindVertexArray(VAO[3]);
        // para la traslación
        float mat4x4_star[4][4] = { 0.0f };
        float mat4x4_1[4][4] = { 0.0f };
        float mat4x4_2[4][4] = { 0.0f };
        float mat4x4_3[4][4] = { 0.0f };
        float mat_aux1[4][4] = { 0.0f };
        float mat_aux2[4][4] = { 0.0f };

        float v1[3] = { -0.85f,0.0f,0.0f };
        float v2[3] = { 0.85f,0.0f,0.0f };

        translation(mat4x4_1, v1);
        rotation(mat4x4_2, (float)glfwGetTime(), z);
        translation(mat4x4_3, v2);

        // primero trasladas al origen, luego rotas y por último trasladas a la posición inicial
        MatMul(mat4x4_3, mat4x4_2, mat_aux1);
        MatMul(mat_aux1, mat4x4_1, mat_aux2);

        trans_vec[0] = trans_vec[1] = trans_vec[2] = 0.0f;
        animation_star(trans_vec, 0.0006f, pause_animation);
        translation(mat_aux1, trans_vec);
        MatMul( mat_aux1, mat_aux2, mat4x4_star);

        shaderStar.use();
        shaderStar.setMat4("animStar", mat4x4_star);
        draw_star(global_drawing_mode);


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(4, VAO);
    glDeleteBuffers(4, VBO);
    glDeleteBuffers(4, EBO);


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

    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
        global_drawing_mode = DrawMode::POINTS;
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
        global_drawing_mode = DrawMode::LINES;
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
        global_drawing_mode = DrawMode::TRIANGLES;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        pause_animation = true;
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
        pause_animation = false;


}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

