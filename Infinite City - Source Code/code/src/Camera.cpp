#include "Camera.h"
#include <algorithm>
#define GLEW_STATIC 1
#include <GL/glew.h>   
#include <iostream>
#include <constants.hpp>

vec3  Camera::position = vec3(0.0f, 2.5f, 0.0f);
vec3  Camera::lookAt = vec3(0.0f);
float Camera::fov = 70.0f;
vec3  Camera::cameraUp = vec3(0.0f, 1.0f, 0.0f);
float Camera::cameraAngularSpeed = 10.0f;
float Camera::cameraSpeed = constant::SLOW_CAMERA_SPEED;
float Camera::cameraVerticalLimits = 89.0f;
float Camera::cameraHorizontalAngle = 0.0f;
float Camera::cameraVerticalAngle = 0.0f;

Camera::Camera() {}

void Camera::updateCamera(GLuint viewMatrixLocation, GLuint projMatrixLocation, GLFWwindow* window) {
    int dWidth, dHeight;
    glfwGetFramebufferSize(window, &dWidth, &dHeight);
    
    // set view and projection matrices
    mat4 viewMatrix = glm::lookAt(position, position + lookAt, cameraUp);
    mat4 projectionMatrix = glm::perspective(fov,
        constant::SCREEN_WIDTH * 1.0f / constant::SCREEN_HEIGHT,
        0.1f, 10000.0f);

    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
    glUniformMatrix4fv(projMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]);
}