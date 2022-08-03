#include "Camera.h"
#include <algorithm>
#define GLEW_STATIC 1
#include <GL/glew.h>   
#include <iostream>


Camera::Camera(float camSpeed) {
	position = vec3(0.0f, 10.0f, 0.0f);
	lookAt = vec3(0.0f);
	fov = 70.0f;
    cameraAngularSpeed = 10.0f;
    cameraUp = vec3(0.0f, 1.0f, 0.0f);
    cameraSpeed = camSpeed;
    cameraVerticalLimits = 85.0f;
}

Camera::Camera(Camera &copyCam) {
    position = copyCam.position;
    lookAt = copyCam.lookAt;
    fov = copyCam.fov;
    cameraAngularSpeed = copyCam.cameraAngularSpeed;
    cameraUp = vec3(0.0f, 1.0f, 0.0f);
    cameraSpeed = copyCam.cameraSpeed;
}

void Camera::UpdateCamera(GLuint viewMatrixLocation, GLuint projMatrixLocation, GLFWwindow* currentWindow) {
    float dt = 0.02f;
    float cameraHorizontalAngle = 0.0f;
    float cameraVerticalAngle = 0.0f;

    double mousePosX, mousePosY, lastMousePosX = 0.0, lastMousePosY = 0.0;
    glfwGetCursorPos(currentWindow, &mousePosX, &mousePosY);

    float dx = static_cast<float>(mousePosX - lastMousePosX);
    float dy = static_cast<float>(mousePosY - lastMousePosY);

    // Convert to spherical coordinates
    cameraHorizontalAngle -= dx * cameraAngularSpeed * dt;
    cameraVerticalAngle -= dy * cameraAngularSpeed * dt;

    // Clamp vertical angle to [-85, 85] degrees
    cameraVerticalAngle = std::max(-cameraVerticalLimits, std::min(cameraVerticalLimits, cameraVerticalAngle));

    // Clamp horizontal angle between 0 and 360
    cameraHorizontalAngle = std::fmod(cameraHorizontalAngle, 360.0f);

    float theta = radians(cameraHorizontalAngle);
    float phi = radians(cameraVerticalAngle);

    lookAt = vec3(cosf(phi) * cosf(theta), sinf(phi), -cosf(phi) * sinf(theta));

    vec3 frontVector = normalize(lookAt);
    vec3 sideVector = normalize(cross(frontVector, cameraUp));
    //std::cout << frontVector.x << std::endl;

    if (glfwGetKey(currentWindow, GLFW_KEY_A) == GLFW_PRESS) // move camera to the left
    {
        position -= sideVector * cameraSpeed * dt;

    }

    if (glfwGetKey(currentWindow, GLFW_KEY_D) == GLFW_PRESS) // move camera to the right
    {
        position += sideVector * cameraSpeed * dt;
    }

    if (glfwGetKey(currentWindow, GLFW_KEY_S) == GLFW_PRESS) // move camera up
    {
        position -= frontVector * cameraSpeed * dt;
    }

    if (glfwGetKey(currentWindow, GLFW_KEY_W) == GLFW_PRESS) // move camera down
    {
        position += frontVector * cameraSpeed * dt;
    }

    if (glfwGetKey(currentWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) // close program
    {
        glfwSetWindowShouldClose(currentWindow, true);
    }
    
    int dWidth, dHeight;
    glfwGetFramebufferSize(currentWindow, &dWidth, &dHeight);

    // SETTING THE VIEW MATRIX
    mat4 viewMatrix = glm::lookAt(position, position + lookAt, cameraUp);
    mat4 projectionMatrix = glm::perspective(fov,
        dWidth * 1.0f / dHeight,
        0.01f, 800.0f);

    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
    glUniformMatrix4fv(projMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]);

    lastMousePosX = mousePosX;
    lastMousePosY = mousePosY;
}