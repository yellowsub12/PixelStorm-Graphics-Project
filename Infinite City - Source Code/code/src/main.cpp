//  COMP 371 - Summer 2 2022 
//  Project Infinite City - August 8th, 2022
// 
//  Team Members:
//  40040127 - Anas Peerzada     
//  40032669 - Kevin Ve          
//  40133493 - Samaninder Singh  
//  40111059 - Ali Turkman       
//  40007224 - Ye Tun            

#include <iostream>
#include <Shader.h>
#include <textures.h>
#include <shapes.h>
#include <Camera.h>
#include <InfiniteCity.h>
#include <constants.hpp>

#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL
#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler

#include <GLFW/glfw3.h> // cross-platform interface for creating a graphical context,
                        // initializing OpenGL and binding inputs

#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include <glm/gtc/matrix_transform.hpp> // include this to create transformation matrices
#include <glm/common.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;
using namespace std;

int main(int argc, char* argv[])
{
    // Initialize GLFW and OpenGL version
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Create Window and rendering context using GLFW
    GLFWwindow* window = glfwCreateWindow(constant::SCREEN_WIDTH, constant::SCREEN_HEIGHT, "Infinite City", NULL, NULL);
    if (window == NULL)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    } 
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to create GLEW" << std::endl;
        glfwTerminate();
        return -1;
    }

    Camera mainCamera; // The main camera that will 
    int cityStartingLength = 5; // How many blocks long is the city at the start of the program (before the city grows as we move around)?
    int cityStartingWidth = 5;  // How many blocks wide is the city at the start of the program (before the city grows as we move around)?
    int blockSize = 50; // Size of each block in the city, a block will contain elements on it such as buildings, parks, trees, etc. A building block of the city. 

    cout << "Current Seed: " << constant::PROCEDURAL_SEED << endl; // Prints the seed to the console for later reference 

    InfiniteCity city(cityStartingWidth, cityStartingLength, blockSize, mainCamera, (int)constant::PROCEDURAL_SEED); // Creating a new City object that will hold every single element and function of the city

    // Creating simple string variables to hold the path strings for the folders that contain the shaders and textures
    string shaderPathPrefix = "assets/shaders/"; 
    string texturesPathPrefix = "assets/textures/";

    // Compiling and linking the two shaders here ...
    GLuint texturedShaderProgram = CreateShader(shaderPathPrefix + "TexturedVertexShader.glsl", shaderPathPrefix + "TexturedFragmentShader.glsl");
    GLuint shadowShaderProgram = CreateShader(shaderPathPrefix + "ShadowVertexShader.glsl", shaderPathPrefix + "ShadowFragmentShader.glsl");

    // The actual main render loop of the program. The city object has a DrawCity method that will initiate the render window and begin the program. 
    // Begins the program.
    city.DrawCity(window, texturedShaderProgram, shadowShaderProgram);

    // Shutdown GLFW when the render loop in the DrawCity method above is over, meaning the program has begun exiting. 
    glfwTerminate();

    return 0; // Return 0 cause this is int main and not void main ;)
}