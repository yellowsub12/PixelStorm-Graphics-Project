#include "Camera.h"
#include <algorithm>
#define GLEW_STATIC 1
#include <GL/glew.h>   
#include <iostream>


Camera::Camera(float camSpeed) {
	position = vec3(0.0f, 10.0f, 0.0f);
	lookAt = vec3(0.0f);
	fov = 70.0f;
	newPosition = position;
	newLookAt = lookAt;
    cameraAngularSpeed = 10.0f;
    cameraUp = vec3(0.0f, 1.0f, 0.0f);
    cameraSpeed = camSpeed;
}

Camera::Camera(Camera &copyCam) {

    position = copyCam.position;
    lookAt = copyCam.lookAt;
    fov = copyCam.fov;
    newPosition = position;
    newLookAt = lookAt;
    cameraAngularSpeed = copyCam.cameraAngularSpeed;
    cameraUp = vec3(0.0f, 1.0f, 0.0f);
    cameraSpeed = copyCam.cameraSpeed;
}

float Camera::Lerp(float a, float b, float f)
{

	if (abs(a - b) < 0.05) return a;
	return a + f * (b - a);

}

void Camera::UpdateCamera(GLuint viewMatrixLocation, GLuint projMatrixLocation, GLFWwindow* currentWindow)
{
    
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
    cameraVerticalAngle = std::max(-85.0f, std::min(85.0f, cameraVerticalAngle));

    // Clamp horizontal angle between 0 and 360
    cameraHorizontalAngle = std::fmod(cameraHorizontalAngle, 360.0f);

    float theta = radians(cameraHorizontalAngle);
    float phi = radians(cameraVerticalAngle);

    newLookAt = vec3(cosf(phi) * cosf(theta), sinf(phi), -cosf(phi) * sinf(theta));


    vec3 frontVector = normalize(newLookAt);
    vec3 sideVector = normalize(cross(frontVector, cameraUp));
    //std::cout << frontVector.x << std::endl;

    if (length(newPosition) <= 1000)
    {
        if (glfwGetKey(currentWindow, GLFW_KEY_A) == GLFW_PRESS) // move camera to the left
        {
            newPosition -= sideVector * cameraSpeed * dt;

        }

        if (glfwGetKey(currentWindow, GLFW_KEY_D) == GLFW_PRESS) // move camera to the right
        {
            newPosition += sideVector * cameraSpeed * dt;
        }

        if (glfwGetKey(currentWindow, GLFW_KEY_S) == GLFW_PRESS) // move camera up
        {
            newPosition -= frontVector * cameraSpeed * dt;
        }

        if (glfwGetKey(currentWindow, GLFW_KEY_W) == GLFW_PRESS) // move camera down
        {
            newPosition += frontVector * cameraSpeed * dt;
        }
    }
    else
        newPosition *= 0.99;
    

    if (glfwGetKey(currentWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) // move camera to the left
    {
        glfwSetWindowShouldClose(currentWindow, true);
    }

    // Camera Zoom In/Out
    if (glfwGetMouseButton(currentWindow, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS) {
        fov = 70.0f + dy * 0.001f;
        fov = std::max(69.2f, std::min(71.3f, fov));
    }

    // Smoothly update camera position and look direction
    position = vec3(Lerp(position.x, newPosition.x, 0.1), Lerp(position.y, newPosition.y, 0.1), Lerp(position.z, newPosition.z, 0.1));
    lookAt = vec3(Lerp(lookAt.x, newLookAt.x, 0.1), Lerp(lookAt.y, newLookAt.y, 0.1), Lerp(lookAt.z, newLookAt.z, 0.1));

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
