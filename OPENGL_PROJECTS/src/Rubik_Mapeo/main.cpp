// OpenGL
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Textures
#include "stb_image.h"
// Rubik cube
#include "RubikCube.h"

// STD libraries
#include <iostream>
#include <random>
#include <vector>
// learnopenGL libraries
#include "shader.h"
#include "camera.h"
#include "defineRubik.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

void manual() {
    std::cout << "COMANDOS PARA MOVER EL CUBO\n";
    std::cout << "PAD 0: Cara Frontal (front) sentido horario\n";
    std::cout << "PAD 1: Cara Frontal (front) sentido antihorario\n";
    std::cout << "PAD 2: Cara Derecha (right) sentido horario\n";
    std::cout << "PAD 3: Cara Derecha (right) sentido antihorario\n";
    std::cout << "PAD 4: Cara Superior (up) sentido horario\n";
    std::cout << "PAD 5: Cara Superior (up) sentido antihorario\n";
    std::cout << "PAD 6: Cara Trasera (back) sentido horario\n";
    std::cout << "PAD 7: Cara Trasera (back) sentido antihorario\n";
    std::cout << "PAD 8: Cara Izquierda (left) sentido horario\n";
    std::cout << "PAD 9: Cara Izquierda (left) sentido antihorario\n";
    std::cout << "PAD +: Cara Abajo (down) sentido horario\n";
    std::cout << "PAD -: Cara Abajo (down) sentido antihorario\n";
    std::cout << "SPACE: RESOLVER CUBO\n";

    std::cout << "COMANDOS PARA LAS ANIMACIONES\n";
    std::cout << "B/b: Respiración (Breathe) constante\n";
    std::cout << "V/v: Detener respiración (Static)\n";

    std::cout << "COMANDOS PARA LAS PROYECCIONES\n";
    std::cout << "O: Proyeccion ortogonal\n";
    std::cout << "P: Proyeccion en perspectiva\n";
    
    std::cout << "Esc: Salir del programa\n";
}

float random(float a, float b);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 10.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
bool pressedSolve = false;
// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

// rubik cube
RubikCube3x3::STATE_ANIMATION animation_state = RubikCube3x3::STATE_ANIMATION::NONE;
RubikCube3x3::FLUENT_ANIMATION fluent_animation = RubikCube3x3::FLUENT_ANIMATION::BREATHE;
enum class PROYECTION_TYPE { PERSPECTIVE, ORTHOGONAL };
PROYECTION_TYPE proy_type = PROYECTION_TYPE::PERSPECTIVE;

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
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Rubik Cube", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    //Shader program("vertexShader.glsl", "fragmentShader.glsl");

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

    Shader LightProgram("vertexShaderLight.glsl", "fragmentShaderLight.glsl");
    // set up vertex data (and buffer(s)) and configure vertex attributes
// ------------------------------------------------------------------
    GLfloat sun_vertices[] = {
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
    };

    // LIGHT VAO
    GLuint lightVAO, lightVBO;
    glGenVertexArrays(1, &lightVAO);
    glGenBuffers(1, &lightVBO);
    glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(sun_vertices), sun_vertices, GL_STATIC_DRAW);
    glBindVertexArray(lightVAO);
    // configurar los atributos de los vertices
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);



    // build and compile our shader zprogram
    // ------------------------------------
    GLuint VBO[1], VAO[1], EBO[1];
    glGenVertexArrays(1, VAO);
    glGenBuffers(1, VBO);
    glGenBuffers(1, EBO);

    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_fill_vertices), cube_fill_vertices, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(GLfloat)));
    //glEnableVertexAttribArray(1);
    // textures attributes
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    // wire mode color attribute


    Shader program("vertexShader.glsl", "fragmentShader.glsl");
    std::vector<std::string> myTextures = { "fluidColouredTexture.jpg" , "pandaTexture.jpg" };
    RubikCube3x3 rubik(program, myTextures);
    //asociamos el VAO correspondiente
    rubik.AssociateVAO(VAO[0]);

    manual();
    
    glLineWidth(10.0f);
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Primero configuramos el color de la luz para el cubo
        program.use();
        program.setVec3("lightColor", 1.0f, 1.0f, 1.0f);


        // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix(); // make sure to initialize matrix to identity matrix first
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        if(proy_type == PROYECTION_TYPE::ORTHOGONAL)
            projection = glm::ortho(-4.0f, 4.0f, -3.0f, 3.0f, 0.1f, 100.0f);

        // dibujamos el cubo de rubik
        if (animation_state == RubikCube3x3::STATE_ANIMATION::SOLVE) rubik.Solve(animation_state);
        rubik.HandleDrawing(view, projection, animation_state, fluent_animation);

        // Ahora configuramos las matrices para la luz
        LightProgram.use();
        LightProgram.setMat4("view", view);
        LightProgram.setMat4("projection", projection);
        glm::mat4 lightmodel(1.0f);
        glm::vec3 lightPos(3.0f, 3.0f, 0.0f);
        lightmodel = glm::translate(lightmodel, lightPos);
        lightmodel = glm::scale(lightmodel, glm::vec3(0.2f)); // un cubo pequeño
        LightProgram.setMat4("model", lightmodel);
        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, VAO);
    glDeleteVertexArrays(1, &lightVAO);
    glDeleteBuffers(1, VBO);
    glDeleteBuffers(1, &lightVBO);
    glDeleteBuffers(1, EBO);

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
    
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (animation_state == RubikCube3x3::STATE_ANIMATION::NONE) {
        if (key == GLFW_KEY_KP_0 && action == GLFW_PRESS)
            animation_state = RubikCube3x3::STATE_ANIMATION::F;
        if (key == GLFW_KEY_KP_1 && action == GLFW_PRESS)
            animation_state = RubikCube3x3::STATE_ANIMATION::f;
        if (key == GLFW_KEY_KP_2 && action == GLFW_PRESS)
            animation_state = RubikCube3x3::STATE_ANIMATION::R;
        if (key == GLFW_KEY_KP_3 && action == GLFW_PRESS)
            animation_state = RubikCube3x3::STATE_ANIMATION::r;
        if (key == GLFW_KEY_KP_4 && action == GLFW_PRESS)
            animation_state = RubikCube3x3::STATE_ANIMATION::U;
        if (key == GLFW_KEY_KP_5 && action == GLFW_PRESS)
            animation_state = RubikCube3x3::STATE_ANIMATION::u;
        if (key == GLFW_KEY_KP_6 && action == GLFW_PRESS)
            animation_state = RubikCube3x3::STATE_ANIMATION::B;
        if (key == GLFW_KEY_KP_7 && action == GLFW_PRESS)
            animation_state = RubikCube3x3::STATE_ANIMATION::b;
        if (key == GLFW_KEY_KP_8 && action == GLFW_PRESS)
            animation_state = RubikCube3x3::STATE_ANIMATION::L;
        if (key == GLFW_KEY_KP_9 && action == GLFW_PRESS)
            animation_state = RubikCube3x3::STATE_ANIMATION::l;
        if (key == GLFW_KEY_KP_ADD && action == GLFW_PRESS)
            animation_state = RubikCube3x3::STATE_ANIMATION::D;
        if (key == GLFW_KEY_KP_SUBTRACT && action == GLFW_PRESS)
            animation_state = RubikCube3x3::STATE_ANIMATION::d;
        if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
            animation_state = RubikCube3x3::STATE_ANIMATION::SOLVE;
    }

    if (key == GLFW_KEY_O && action == GLFW_PRESS)
        proy_type = PROYECTION_TYPE::ORTHOGONAL;
    if (key == GLFW_KEY_P && action == GLFW_PRESS)
        proy_type = PROYECTION_TYPE::PERSPECTIVE;

    // animacion continuas
    if (key == GLFW_KEY_B && action == GLFW_PRESS)
        fluent_animation = RubikCube3x3::FLUENT_ANIMATION::BREATHE;
    if (key == GLFW_KEY_V && action == GLFW_PRESS)
        fluent_animation = RubikCube3x3::FLUENT_ANIMATION::STATIC;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }


    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll sheel scrolls, this callback is called
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}

float random(float a, float b) 
{
    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<float> dis(a, b);
    return dis(gen);
}