// [CG_2021-II] Saul A. Rojas Coila
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

// Library from LearnOpenGL
#include "shader.h"

// Local Headers
#include "vertices_indices_flor_1.h"
#include "vertices_indices_flor_2.h"



void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);


// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// PARA ELEGIR EL MODO DE LAS PRIMITIVAS
enum class PRIMITIVES { POINTS, LINE, LINE_STRIP, TRIANGLES, QUADS, POLYGON };
PRIMITIVES drawMode = PRIMITIVES::TRIANGLES;


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
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Flor con primitivas", NULL, NULL);
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
    
    // generando vértices e índices de las hojas para la flor 1, con triángulos
    std::vector<float> vertices_hojas_flor_1;
    std::vector<unsigned int> indices_hojas_flor_1;
    // generando las hojas de la primera flor para triángulos
    generar_hojas_flor_1_triangulos(vertices_hojas_flor_1, indices_hojas_flor_1);
    float* vertices_hojas_flor_1_puntero = &vertices_hojas_flor_1[0];
    unsigned int* indices_hojas_flor_1_puntero = &indices_hojas_flor_1[0];
    
    // generando vértices e índices de las hojas para la flor 1, con líneas. strip y normal
    std::vector<float> vertices_hojas_flor_1_lineas;
    std::vector<unsigned int> indices_hojas_flor_1_lineas;
    generar_hojas_flor_1_lineas(vertices_hojas_flor_1_lineas, indices_hojas_flor_1_lineas);

    float* vertices_hojas_flor_1_lineas_puntero = &vertices_hojas_flor_1_lineas[0];
    unsigned int* indices_hojas_flor_1_lineas_puntero = &indices_hojas_flor_1_lineas[0];




    // generando vértices e índices para la flor 2
    // cuadrantes y tallo
    float* vertices_flor_2_puntero = &vertices_flor_2[0];
    unsigned int* indices_flor_2_puntero = &indices_flor_2[0];
    // pétalos
    std::vector<float> flor_2_petalos_vert;
    std::vector<unsigned int> flor_2_petalos_inds;
    flor_2_generar_petalos(flor_2_petalos_vert, flor_2_petalos_inds);
    float* vertices_petalos_flor_2_puntero = &flor_2_petalos_vert[0];
    unsigned int* indices_petalos_flor_2_puntero = &flor_2_petalos_inds[0];
    // hojas
    std::vector<float> flor_2_hojas_vert;
    std::vector<unsigned int> flor_2_hojas_inds;
    flor_2_generar_hojas(flor_2_hojas_vert, flor_2_hojas_inds);
    float* vertices_hojas_flor_2_puntero = &flor_2_hojas_vert[0];
    unsigned int* indices_hojas_flor_2_puntero = &flor_2_hojas_inds[0];

    const int N_CONT_F1 = 3; // N contenedores para la flor 1
    const int N_CONT_F2 = 3; // N contenedores para la flor 2

    unsigned int VBO_flor1[N_CONT_F1], VAO_flor1[N_CONT_F1], EBO_flor1[N_CONT_F1];
    unsigned int VBO_flor2[N_CONT_F2], VAO_flor2[N_CONT_F2], EBO_flor2[N_CONT_F2];

    glGenVertexArrays(N_CONT_F1, VAO_flor1);
    glGenBuffers(N_CONT_F1, VBO_flor1);
    glGenBuffers(N_CONT_F1, EBO_flor1);

    glGenVertexArrays(N_CONT_F2, VAO_flor2);
    glGenBuffers(N_CONT_F2, VBO_flor2);
    glGenBuffers(N_CONT_F2, EBO_flor2);

    // flor 1
    // primer VAO flor_1_pétalos y cuadros
    {
        glBindVertexArray(VAO_flor1[0]);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_flor1[0]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_flor_1), indices_flor_1, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, VBO_flor1[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_flor_1), vertices_flor_1, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }

    // segundo VAO flor_1_hojas : triángulos
    {
        glBindVertexArray(VAO_flor1[1]);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_flor1[1]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_hojas_flor_1.size() * sizeof(unsigned int),
            indices_hojas_flor_1_puntero, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, VBO_flor1[1]);
        glBufferData(GL_ARRAY_BUFFER, vertices_hojas_flor_1.size() * sizeof(float),
            vertices_hojas_flor_1_puntero, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }
    
    // tercer VAO flor_1_hojas : líneas
    {
        glBindVertexArray(VAO_flor1[2]);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_flor1[2]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_hojas_flor_1_lineas.size() * sizeof(unsigned int),
            indices_hojas_flor_1_lineas_puntero, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, VBO_flor1[2]);
        glBufferData(GL_ARRAY_BUFFER, vertices_hojas_flor_1_lineas.size() * sizeof(float),
            vertices_hojas_flor_1_lineas_puntero, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }


    // flor 2
    // primer VAO flor_2 cuadros y tallo
    {
        glBindVertexArray(VAO_flor2[0]);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_flor2[0]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_flor_2.size() * sizeof(unsigned int),
            indices_flor_2_puntero, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, VBO_flor2[0]);
        glBufferData(GL_ARRAY_BUFFER, vertices_flor_2.size() * sizeof(float), vertices_flor_2_puntero, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }
    // segundo VAO flor 2 pétalos
    {
        glBindVertexArray(VAO_flor2[1]);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_flor2[1]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, flor_2_petalos_inds.size() * sizeof(unsigned int),
            indices_petalos_flor_2_puntero, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, VBO_flor2[1]);
        glBufferData(GL_ARRAY_BUFFER, flor_2_petalos_vert.size() * sizeof(float), 
            vertices_petalos_flor_2_puntero, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }
    // cuarto VAO flor 2: hojas
    {
        glBindVertexArray(VAO_flor2[2]);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_flor2[2]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, flor_2_hojas_inds.size() * sizeof(unsigned int),
            indices_hojas_flor_2_puntero, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, VBO_flor2[2]);
        glBufferData(GL_ARRAY_BUFFER, flor_2_hojas_vert.size() * sizeof(float),
            vertices_hojas_flor_2_puntero, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }


    // instrucciones
    std::cout << "Comandos para primitivas\n";
    std::cout << "presiona P para dibujar con puntos\n";
    std::cout << "presiona L para dibujar con lineas\n";
    std::cout << "presiona S para dibujar con lineas (line_strip)\n";
    std::cout << "presiona T para dibujar con triangulos\n";
    std::cout << "presiona Q para dibujar con quads\n";
    std::cout << "presiona O para dibujar con poligonos\n";


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
        switch (drawMode)
        {
        case PRIMITIVES::POINTS:
        {
            glPointSize(3.0f);
            // flor 1
            // drawing hojas
            glBindVertexArray(VAO_flor1[1]);
            // hoja derecha e izquierda
            shaderProgram.setVec3("colour", 0.27, 0.75, 0.24);
            glDrawArrays(GL_POINTS, 0, vertices_hojas_flor_1.size());
            glBindVertexArray(VAO_flor1[0]);
            // pétalos de la flor
            shaderProgram.setVec3("colour", 0.96, 0.04, 0.05);
            glDrawArrays(GL_POINTS, 54, 33 + 27 + 48 + 24 + 51);
            // tallo
            glLineWidth(5.0f);
            shaderProgram.setVec3("colour", 0.09, 0.04, 0.05);
            glDrawArrays(GL_POINTS, 237, 9);
            // cuadrados menores
            shaderProgram.setVec3("colour", 0.72, 0.89, 0.24);
            glDrawArrays(GL_POINTS, 0, 24);
            // rectángulos menores
            shaderProgram.setVec3("colour", 0.93, 0.96, 0.86);
            glDrawArrays(GL_POINTS, 24, 24);
            // rectángulo central
            shaderProgram.setVec3("colour", 0.45, 0.71, 0.95);
            glDrawArrays(GL_POINTS, 48, 6);

            // flor 2
            // cuadros y tallo
            glBindVertexArray(VAO_flor2[0]);
            shaderProgram.setVec3("colour", 0.91, 0.92, 0.84);
            glDrawArrays(GL_POINTS, 0, vertices_flor_2.size());
            // pétalos
            glBindVertexArray(VAO_flor2[1]);
            glDrawArrays(GL_POINTS, 0, flor_2_petalos_vert.size());
            // hojas
            glBindVertexArray(VAO_flor2[2]);
            glDrawArrays(GL_POINTS, 0, flor_2_hojas_vert.size());

            break;
        }
        case PRIMITIVES::LINE:
        {

            // flor 1
            // pétalos y cuadros
            glBindVertexArray(VAO_flor1[0]);
            shaderProgram.setVec3("colour", 0.91, 0.92, 0.84);
            //cuadrados
            glDrawElements(GL_LINES, 8, GL_UNSIGNED_INT, (void*)(246 * sizeof(unsigned int)));
            glDrawElements(GL_LINES, 8, GL_UNSIGNED_INT, (void*)(254 * sizeof(unsigned int)));
            glDrawElements(GL_LINES, 8, GL_UNSIGNED_INT, (void*)(262 * sizeof(unsigned int)));
            glDrawElements(GL_LINES, 8, GL_UNSIGNED_INT, (void*)(270 * sizeof(unsigned int)));
            // rectángulos
            glDrawElements(GL_LINES, 4, GL_UNSIGNED_INT, (void*)(278 * sizeof(unsigned int)));
            glDrawElements(GL_LINES, 4, GL_UNSIGNED_INT, (void*)(282 * sizeof(unsigned int)));
            glDrawElements(GL_LINES, 4, GL_UNSIGNED_INT, (void*)(286 * sizeof(unsigned int)));
            glDrawElements(GL_LINES, 4, GL_UNSIGNED_INT, (void*)(290 * sizeof(unsigned int)));

            // pétalos
            shaderProgram.setVec3("colour", 0.96, 0.04, 0.05);
            glDrawElements(GL_LINES, 20, GL_UNSIGNED_INT, (void*)(294 * sizeof(unsigned int)));
            glDrawElements(GL_LINES, 20, GL_UNSIGNED_INT, (void*)(314 * sizeof(unsigned int)));
            glDrawElements(GL_LINES, 20, GL_UNSIGNED_INT, (void*)(334 * sizeof(unsigned int)));
            glDrawElements(GL_LINES, 36, GL_UNSIGNED_INT, (void*)(354 * sizeof(unsigned int)));
            glDrawElements(GL_LINES, 8, GL_UNSIGNED_INT, (void*)(390 * sizeof(unsigned int)));

            // tallo
            glLineWidth(5.0f);
            shaderProgram.setVec3("colour", 0.7, 0.8, 0.9);
            glDrawElements(GL_LINE_STRIP, 9,
                GL_UNSIGNED_INT, (void*)(237 * sizeof(unsigned int)));

            // hojas
            glBindVertexArray(VAO_flor1[2]);
            shaderProgram.setVec3("colour", 0.27, 0.75, 0.24);
            // hoja derecha
            //glDrawElements(GL_TRIANGLES, 40, GL_UNSIGNED_INT, 0);
            //glDrawElements(GL_TRIANGLES, 40, GL_UNSIGNED_INT, (void*)(40 * sizeof(unsigned int)));
            // hoja izquierda
            //glDrawElements(GL_TRIANGLES, 40, GL_UNSIGNED_INT, (void*)(122 * sizeof(unsigned int)));
            //glDrawElements(GL_TRIANGLES, 40, GL_UNSIGNED_INT, (void*)(162 * sizeof(unsigned int)));

            // flor 2
            // cuadrantes
            glBindVertexArray(VAO_flor2[0]);
            shaderProgram.setVec3("colour", 0.91, 0.92, 0.84);
            glDrawElements(GL_LINES, 68, GL_UNSIGNED_INT, (void*)(42 * sizeof(unsigned int)));
            // tallo
            glDrawElements(GL_LINES, 8, GL_UNSIGNED_INT, (void*)(110 * sizeof(unsigned int)));

            // pétalos
            glBindVertexArray(VAO_flor2[1]);
            shaderProgram.setVec3("colour", 0.75, 0.81, 0.15);
            glDrawElements(GL_LINES, 60, GL_UNSIGNED_INT, 0);
            glDrawElements(GL_LINES, 60, GL_UNSIGNED_INT, (void*)(60 * sizeof(unsigned int)));
            glDrawElements(GL_LINES, 60, GL_UNSIGNED_INT, (void*)(120 * sizeof(unsigned int)));
            glDrawElements(GL_LINES, 60, GL_UNSIGNED_INT, (void*)(180 * sizeof(unsigned int)));

            // hojas
            glBindVertexArray(VAO_flor2[2]);
            shaderProgram.setVec3("colour", 0.14, 0.87, 0.29);
            glDrawElements(GL_LINES, 60, GL_UNSIGNED_INT, 0);
            glDrawElements(GL_LINES, 60, GL_UNSIGNED_INT, (void*)(60 * sizeof(unsigned int)));
            glDrawElements(GL_LINES, 60, GL_UNSIGNED_INT, (void*)(120 * sizeof(unsigned int)));


            break;
        }
        case PRIMITIVES::LINE_STRIP:
        {
            // flor 1
            // pétalos y cuadros
            glBindVertexArray(VAO_flor1[0]);
            shaderProgram.setVec3("colour", 0.91, 0.92, 0.84);
            //cuadrados
            glDrawElements(GL_LINE_STRIP, 5, GL_UNSIGNED_INT, (void*)(398 * sizeof(unsigned int)));
            glDrawElements(GL_LINE_STRIP, 5, GL_UNSIGNED_INT, (void*)(403 * sizeof(unsigned int)));
            glDrawElements(GL_LINE_STRIP, 5, GL_UNSIGNED_INT, (void*)(408 * sizeof(unsigned int)));
            glDrawElements(GL_LINE_STRIP, 5, GL_UNSIGNED_INT, (void*)(413 * sizeof(unsigned int)));
            // rectángulos
            glDrawElements(GL_LINE_STRIP, 5, GL_UNSIGNED_INT, (void*)(418 * sizeof(unsigned int)));
            glDrawElements(GL_LINE_STRIP, 5, GL_UNSIGNED_INT, (void*)(423 * sizeof(unsigned int)));
            glDrawElements(GL_LINE_STRIP, 5, GL_UNSIGNED_INT, (void*)(428 * sizeof(unsigned int)));
            glDrawElements(GL_LINE_STRIP, 5, GL_UNSIGNED_INT, (void*)(433 * sizeof(unsigned int)));

            // pétalos
            shaderProgram.setVec3("colour", 0.96, 0.04, 0.05);
            glDrawElements(GL_LINE_STRIP, 11, GL_UNSIGNED_INT, (void*)(438 * sizeof(unsigned int)));
            glDrawElements(GL_LINE_STRIP, 11, GL_UNSIGNED_INT, (void*)(449 * sizeof(unsigned int)));
            glDrawElements(GL_LINE_STRIP, 11, GL_UNSIGNED_INT, (void*)(460 * sizeof(unsigned int)));
            glDrawElements(GL_LINE_STRIP, 19, GL_UNSIGNED_INT, (void*)(471 * sizeof(unsigned int)));
            glDrawElements(GL_LINE_STRIP, 5, GL_UNSIGNED_INT, (void*)(490 * sizeof(unsigned int)));
            // tallo
            glLineWidth(5.0f);
            shaderProgram.setVec3("colour", 0.7, 0.8, 0.9);
            glDrawElements(GL_LINE_STRIP, 9,
                GL_UNSIGNED_INT, (void*)(237 * sizeof(unsigned int)));

            // flor 2
            // cuadrantes
            glBindVertexArray(VAO_flor2[0]);
            shaderProgram.setVec3("colour", 0.91, 0.92, 0.84);
            // cuadrados
            glDrawElements(GL_LINE_STRIP, 5, GL_UNSIGNED_INT, 0);
            glDrawElements(GL_LINE_STRIP, 5, GL_UNSIGNED_INT, (void*)(5 * sizeof(unsigned int)));
            glDrawElements(GL_LINE_STRIP, 5, GL_UNSIGNED_INT, (void*)(10 * sizeof(unsigned int)));
            glDrawElements(GL_LINE_STRIP, 5, GL_UNSIGNED_INT, (void*)(15 * sizeof(unsigned int)));
            // rectángulos
            glDrawElements(GL_LINE_STRIP, 5, GL_UNSIGNED_INT, (void*)(20 * sizeof(unsigned int)));
            glDrawElements(GL_LINE_STRIP, 7, GL_UNSIGNED_INT, (void*)(25 * sizeof(unsigned int)));
            glDrawElements(GL_LINE_STRIP, 5, GL_UNSIGNED_INT, (void*)(32 * sizeof(unsigned int)));
            glDrawElements(GL_LINE_STRIP, 5, GL_UNSIGNED_INT, (void*)(37 * sizeof(unsigned int)));
            // tallo
            glDrawElements(GL_LINE_STRIP, 5, GL_UNSIGNED_INT, (void*)(118 * sizeof(unsigned int)));
            // pétalos
            glBindVertexArray(VAO_flor2[1]);
            shaderProgram.setVec3("colour", 0.75, 0.81, 0.15);
            glDrawElements(GL_LINE_STRIP, 31, GL_UNSIGNED_INT, (void*)(240 * sizeof(unsigned int)));
            glDrawElements(GL_LINE_STRIP, 31, GL_UNSIGNED_INT, (void*)(271 * sizeof(unsigned int)));
            glDrawElements(GL_LINE_STRIP, 31, GL_UNSIGNED_INT, (void*)(302 * sizeof(unsigned int)));
            glDrawElements(GL_LINE_STRIP, 31, GL_UNSIGNED_INT, (void*)(333 * sizeof(unsigned int)));
            // hojas
            glBindVertexArray(VAO_flor2[2]);
            shaderProgram.setVec3("colour", 0.14, 0.87, 0.29);
            glDrawElements(GL_LINE_STRIP, 31, GL_UNSIGNED_INT, (void*)(180 * sizeof(unsigned int)));
            glDrawElements(GL_LINE_STRIP, 31, GL_UNSIGNED_INT, (void*)(211 * sizeof(unsigned int)));
            glDrawElements(GL_LINE_STRIP, 31, GL_UNSIGNED_INT, (void*)(242 * sizeof(unsigned int)));

            break;
        }
        case PRIMITIVES::TRIANGLES:
        {
            // FLOR 1
            // drawing hojas con triangulos
            glBindVertexArray(VAO_flor1[1]);
            shaderProgram.setVec3("colour", 0.27, 0.75, 0.24);
            glDrawElements(GL_TRIANGLES, indices_hojas_flor_1.size(),
                GL_UNSIGNED_INT, 0);

            glBindVertexArray(VAO_flor1[0]);
            // pétalos de la flor
            shaderProgram.setVec3("colour", 0.96, 0.04, 0.05);
            glDrawElements(GL_TRIANGLES, 33 + 27 + 48 + 24 + 51,
                GL_UNSIGNED_INT, (void*)(54 * sizeof(unsigned int)));
            // tallo
            glLineWidth(5.0f);
            shaderProgram.setVec3("colour", 0.09, 0.04, 0.05);
            glDrawElements(GL_LINE_STRIP, 9,
                GL_UNSIGNED_INT, (void*)(237 * sizeof(unsigned int)));
            // cuadrados menores
            shaderProgram.setVec3("colour", 0.72, 0.89, 0.24);
            glDrawElements(GL_TRIANGLES, 24,
                GL_UNSIGNED_INT, 0);
            // rectángulos menores
            shaderProgram.setVec3("colour", 0.93, 0.96, 0.86);
            glDrawElements(GL_TRIANGLES, 24,
                GL_UNSIGNED_INT, (void*)(24 * sizeof(unsigned int)));
            // rectángulo central
            shaderProgram.setVec3("colour", 0.45, 0.71, 0.95);
            glDrawElements(GL_TRIANGLES, 6,
                GL_UNSIGNED_INT, (void*)(48 * sizeof(unsigned int)));
            

            // flor 2
// cuadrantes
            glBindVertexArray(VAO_flor2[0]);
            shaderProgram.setVec3("colour", 0.91, 0.92, 0.84);
            // cuadrados
            glDrawElements(GL_LINE_STRIP, 5, GL_UNSIGNED_INT, 0);
            glDrawElements(GL_LINE_STRIP, 5, GL_UNSIGNED_INT, (void*)(5 * sizeof(unsigned int)));
            glDrawElements(GL_LINE_STRIP, 5, GL_UNSIGNED_INT, (void*)(10 * sizeof(unsigned int)));
            glDrawElements(GL_LINE_STRIP, 5, GL_UNSIGNED_INT, (void*)(15 * sizeof(unsigned int)));
            // rectángulos
            glDrawElements(GL_LINE_STRIP, 5, GL_UNSIGNED_INT, (void*)(20 * sizeof(unsigned int)));
            glDrawElements(GL_LINE_STRIP, 7, GL_UNSIGNED_INT, (void*)(25 * sizeof(unsigned int)));
            glDrawElements(GL_LINE_STRIP, 5, GL_UNSIGNED_INT, (void*)(32 * sizeof(unsigned int)));
            glDrawElements(GL_LINE_STRIP, 5, GL_UNSIGNED_INT, (void*)(37 * sizeof(unsigned int)));
            // tallo
            glDrawElements(GL_LINE_STRIP, 5, GL_UNSIGNED_INT, (void*)(118 * sizeof(unsigned int)));
            // pétalos
            glBindVertexArray(VAO_flor2[1]);
            shaderProgram.setVec3("colour", 0.75, 0.81, 0.15);
            glDrawElements(GL_LINE_STRIP, 31, GL_UNSIGNED_INT, (void*)(240 * sizeof(unsigned int)));
            glDrawElements(GL_LINE_STRIP, 31, GL_UNSIGNED_INT, (void*)(271 * sizeof(unsigned int)));
            glDrawElements(GL_LINE_STRIP, 31, GL_UNSIGNED_INT, (void*)(302 * sizeof(unsigned int)));
            glDrawElements(GL_LINE_STRIP, 31, GL_UNSIGNED_INT, (void*)(333 * sizeof(unsigned int)));
            // hojas
            glBindVertexArray(VAO_flor2[2]);
            shaderProgram.setVec3("colour", 0.14, 0.87, 0.29);
            glDrawElements(GL_LINE_STRIP, 31, GL_UNSIGNED_INT, (void*)(180 * sizeof(unsigned int)));
            glDrawElements(GL_LINE_STRIP, 31, GL_UNSIGNED_INT, (void*)(211 * sizeof(unsigned int)));
            glDrawElements(GL_LINE_STRIP, 31, GL_UNSIGNED_INT, (void*)(242 * sizeof(unsigned int)));


            break;
        }
        case PRIMITIVES::QUADS:
            break;
        case PRIMITIVES::POLYGON:
        {
            
            glBindVertexArray(VAO_flor1[0]);
            // pétalos de la flor con modo de dibujo: polígonos
            shaderProgram.setVec3("colour", 0.96, 0.04, 0.05);
            //pétalo central
            glDrawElements(GL_POLYGON, 22, GL_UNSIGNED_INT, (void*)(495 * sizeof(unsigned int)));
            //pétalo derecho
            glDrawElements(GL_POLYGON, 23, GL_UNSIGNED_INT, (void*)(517 * sizeof(unsigned int)));
            //pétalo izquierdo
            glDrawElements(GL_POLYGON, 20, GL_UNSIGNED_INT, (void*)(540 * sizeof(unsigned int)));

            break;
        }
        default:
            break;
        }

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(N_CONT_F1, VAO_flor1);
    glDeleteBuffers(N_CONT_F1, VBO_flor1);
    glDeleteBuffers(N_CONT_F1, EBO_flor1);

    glDeleteVertexArrays(N_CONT_F2, VAO_flor2);
    glDeleteBuffers(N_CONT_F2, VBO_flor2);
    glDeleteBuffers(N_CONT_F2, EBO_flor2);

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
        drawMode = PRIMITIVES::POINTS;
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
        drawMode = PRIMITIVES::LINE;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        drawMode = PRIMITIVES::LINE_STRIP;
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
        drawMode = PRIMITIVES::TRIANGLES;
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        drawMode = PRIMITIVES::QUADS;
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
        drawMode = PRIMITIVES::POLYGON;

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

