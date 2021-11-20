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
    std::cout << "Teclas\n";
    std::cout << "PAD 0: Cara Frontal (front) sentido horario\n";
    std::cout << "PAD 1: Cara Frontal (front) sentido antihorario\n";
    std::cout << "PAD 2: Cara Derecha (right) sentido horario\n";
    std::cout << "PAD 3: Cara Derecha (right) sentido antihorario\n";
    std::cout << "PAD 4: Cara Superior (up) sentido horario\n";
    std::cout << "PAD 5: Cara Superior (up) sentido antihorario\n";
    std::cout << "PAD 6: Cara Detras (back) sentido horario\n";
    std::cout << "PAD 7: Cara Detras (back) sentido antihorario\n";
    std::cout << "PAD 8: Cara Izquierda (left) sentido horario\n";
    std::cout << "PAD 9: Cara Izquierda (left) sentido antihorario\n";
    std::cout << "PAD +: Cara Abajo (down) sentido horario\n";
    std::cout << "PAD -: Cara Abajo (down) sentido antihorario\n";
    std::cout << "SPACE: RESOLVER CUBO\n";
    std::cout << "TAB: stop animation of the camera\n";
    std::cout << "x/X: animate horizontal\n";
    std::cout << "y/Y: animate vertical\n";
    std::cout << "Esc: Salir del programa\n";
}
char showSteps(RubikCube3x3::STATE_ANIMATION s) {
    switch (s)
    {
    case RubikCube3x3::STATE_ANIMATION::NONE:
        return 'N';
        break;
    case RubikCube3x3::STATE_ANIMATION::F:
        return 'F';
        break;
    case RubikCube3x3::STATE_ANIMATION::f:
        return 'f';
        break;
    case RubikCube3x3::STATE_ANIMATION::U:
        return 'U';
        break;
    case RubikCube3x3::STATE_ANIMATION::u:
        return 'u';
        break;
    case RubikCube3x3::STATE_ANIMATION::L:
        return 'L';
        break;
    case RubikCube3x3::STATE_ANIMATION::l:
        return 'l';
        break;
    case RubikCube3x3::STATE_ANIMATION::R:
        return 'R';
        break;
    case RubikCube3x3::STATE_ANIMATION::r:
        return 'r';
        break;
    case RubikCube3x3::STATE_ANIMATION::B:
        return 'B';
        break;
    case RubikCube3x3::STATE_ANIMATION::b:
        return 'b';
        break;
    case RubikCube3x3::STATE_ANIMATION::D:
        return 'D';
        break;
    case RubikCube3x3::STATE_ANIMATION::d:
        return 'd';
        break;
    case RubikCube3x3::STATE_ANIMATION::SOLVE:
        return 'S';
        break;
    default:
        return 'P';
        break;
    }
}

float random(float a, float b);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 5.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
bool pressedSolve = false;
// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

// rubik cube
RubikCube3x3::STATE_ANIMATION animation_state = RubikCube3x3::STATE_ANIMATION::NONE;

// animation camera controls
bool cam_animation_h = false;
bool cam_animation_v = false;
bool stop_cam_animation = true;

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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    // textures attributes
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);
    // wire mode color attribute

    RubikCube3x3 rubik("vertexShader.glsl", "fragmentShader.glsl", "steelTexture.jpg");
    //asociamos el VAO correspondiente
    rubik.AssociateVAO(VAO[0]);
    
    solver::Rubik myrubik;
    
    manual();

    glLineWidth(10.0f);
    const float radius = 10.0f;
    // render loop
    float angle = 0.0f;
    float last_CAMX = 0.0f;
    float last_CAMY = 0.0f;
    float last_CAMZ = radius;

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


        // camera/view transformation
        //glm::mat4 view = camera.GetViewMatrix(); // make sure to initialize matrix to identity matrix first

        float camX = last_CAMX;
        float camY = last_CAMY;
        float camZ = last_CAMZ;
        if (cam_animation_h) {
            last_CAMX = sin(angle) * radius;
            last_CAMZ = cos(angle) * radius;
        }
        else if (cam_animation_v) {
            last_CAMY = sin(angle) * radius;
            last_CAMZ = cos(angle) * radius;
        }

        glm::mat4 view = glm::lookAt(glm::vec3(camX, camY, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
        if(!stop_cam_animation) angle += 0.002f;
        if (angle >= 360) angle = 0.0f;
        /*last_CAMX = camX;
        last_CAMY = camY;
        last_CAMZ = camZ;*/

        glm::mat4 projection = glm::perspective(glm::radians(45.f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

        // dibujamos el cubo de rubik
        if (animation_state == RubikCube3x3::STATE_ANIMATION::SOLVE) rubik.Solve(animation_state);
		//std::cout << showSteps(animation_state) << "\n";
        rubik.HandleDrawing(view, projection, animation_state);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, VAO);
    glDeleteBuffers(1, VBO);
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
        if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
            animation_state = RubikCube3x3::STATE_ANIMATION::SOLVE;
        }
        if (key == GLFW_KEY_X && action == GLFW_PRESS) {
            cam_animation_h = true;
            cam_animation_v = false;
            stop_cam_animation = false;
        }
        if (key == GLFW_KEY_Y && action == GLFW_PRESS) {
            cam_animation_h = false;
            cam_animation_v = true;
            stop_cam_animation = false;
        }
        if (key == GLFW_KEY_TAB && action == GLFW_PRESS) {
            cam_animation_h = false;
            cam_animation_v = false;
            stop_cam_animation = true;
        }
    }
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