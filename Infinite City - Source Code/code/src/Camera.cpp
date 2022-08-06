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
float Camera::cameraAngularSpeed = constant::CAMERA_ANGULAR_SPEED;
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
    mat4 projectionMatrix = perspective(fov,
                                        dWidth * 1.0f / dHeight,
                                        0.1f, 200.0f); //near, far plane

    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
    glUniformMatrix4fv(projMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]);
}