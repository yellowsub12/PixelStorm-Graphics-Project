// This file handles all keyboard inputs

#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL
#include <GL/glew.h> 

#include <glm/glm.hpp>

#include <algorithm>
#include "Controls.h"
#include "Camera.h"  
#include <constants.hpp>

double Controls::lastMousePosX = 0.0f;
double Controls::lastMousePosY = 0.0f;

// universal controls that should always happen
void Controls::globalControls(GLFWwindow* window){
    // ESC to close program
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    // reset camera to (0,0,0)
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        Camera::position = vec3(0.0f, 2.5f, 0.0f);
    }
}

void Controls::firstPersonControls(GLFWwindow* window, float dt) {
    double mousePosX, mousePosY;
    glfwGetCursorPos(window, &mousePosX, &mousePosY);

    float dx = static_cast<float>(mousePosX - lastMousePosX);
    float dy = static_cast<float>(mousePosY - lastMousePosY);
    vec3 frontVector = normalize(Camera::lookAt);
    frontVector.y = 0.0f;
    vec3 sideVector = normalize(cross(frontVector, Camera::cameraUp));
    
    // Convert to spherical coordinates
    Camera::cameraHorizontalAngle -= dx * Camera::cameraAngularSpeed * dt;
    Camera::cameraVerticalAngle -= dy * Camera::cameraAngularSpeed * dt;

    // Clamp vertical angle to [-85, 85] degrees
    Camera::cameraVerticalAngle = std::max(-Camera::cameraVerticalLimits, std::min(Camera::cameraVerticalLimits, Camera::cameraVerticalAngle));

    // Clamp horizontal angle between 0 and 360
    Camera::cameraHorizontalAngle = std::fmod(Camera::cameraHorizontalAngle, 360.0f);
    
    float theta = radians(Camera::cameraHorizontalAngle);
    float phi = radians(Camera::cameraVerticalAngle);

    Camera::lookAt = vec3(cosf(phi) * cosf(theta), sinf(phi), -cosf(phi) * sinf(theta));
    
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) // forward
    {
        Camera::position += frontVector * Camera::cameraSpeed * dt;
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) // backward
    {
        Camera::position -= frontVector * Camera::cameraSpeed * dt;
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) // left
    {
        Camera::position -= sideVector * Camera::cameraSpeed * dt;

    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) // right
    {
        Camera::position += sideVector * Camera::cameraSpeed * dt;
    }

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) { //go up
        Camera::position.y = std::min(constant::CAMERA_MAX_HEIGHT, Camera::position.y + Camera::cameraSpeed * dt);

    }

    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) { //sprint
        Camera::position.y = std::max(constant::CAMERA_MIN_HEIGHT, Camera::position.y - Camera::cameraSpeed * dt);
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) { //sprint
        Camera::cameraSpeed = constant::FAST_CAMERA_SPEED;
    } else {
        Camera::cameraSpeed = constant::SLOW_CAMERA_SPEED;
    }

    // right click to zoom
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS) { //sprint
        Camera::fov = 69.4f;
        Camera::cameraSpeed = constant::SLOW_CAMERA_SPEED * 0.5f;
        Camera::cameraAngularSpeed = constant::CAMERA_ANGULAR_SPEED * 0.3f;
    } else {
        Camera::fov = 70.0f;
        Camera::cameraAngularSpeed = constant::CAMERA_ANGULAR_SPEED;
    }

    lastMousePosX = mousePosX;
    lastMousePosY = mousePosY;
}