//  COMP 371 - Summer 2 2022 
//
//  Project Infinite City - August 8th, 2022
// 
//  Team Members:
//  Anas Peerzada - 40040127
//  Kevin Ve - 40032669
//  Samaninder Singh - 40133493
//  Ali Turkman - 40111059
//  Ye Tun - 40007224
//

#include <iostream>
#include <Shader.h>
#include <textures.h>
#include <shapes.h>
#include <Camera.h>
#include <InfiniteCity.h>

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

    int WIDTH = 1920, HEIGHT = 1080;

    // Create Window and rendering context using GLFW, resolution is 1024x768
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Infinite City", NULL, NULL);
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

    Camera mainCamera; 

    InfiniteCity city(5, 5, 5, mainCamera);

    string shaderPathPrefix = "assets/shaders/";
    string texturesPathPrefix = "assets/textures/";

    // Compile and link shaders here ...
    GLuint texturedShaderProgram = CreateShader(shaderPathPrefix + "TexturedVertexShader.glsl", shaderPathPrefix + "TexturedFragmentShader.glsl");
    GLuint shadowShaderProgram = CreateShader(shaderPathPrefix + "ShadowVertexShader.glsl", shaderPathPrefix + "ShadowFragmentShader.glsl");

    city.DrawCity(window, texturedShaderProgram, shadowShaderProgram);

    // Shutdown GLFW
    glfwTerminate();

    return 0;
}

