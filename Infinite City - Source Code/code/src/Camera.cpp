#include "Camera.h"
#include <algorithm>
#define GLEW_STATIC 1
#include <GL/glew.h>   
#include <iostream>
#include <constants.hpp>

vec3 Camera::position = vec3(30.0f, 3.5f, 0.0f);
vec3 Camera::movementVector = vec3(0.0f);
vec3 Camera::lookAt = vec3(0.0f);
float Camera::fov = 70.0f;
vec3 Camera::cameraUp = vec3(0.0f, 1.0f, 0.0f);
float Camera::cameraAngularSpeed = 10.0f;
float Camera::cameraSpeed = constant::SLOW_CAMERA_SPEED;
float Camera::cameraVerticalLimits = 89.0f;
float Camera::cameraHorizontalAngle = 0.0f;
float Camera::cameraVerticalAngle = 0.0f;
vec3 Camera::cameraCollisionLocation = vec3(0.0f, -100.0f, 0.0f);
float Camera::collisionObjectYScale = 0.0f;
vec3 Camera::cameraPreCollisionPosition = position;
float Camera::fallVelocity = 0.1f;
bool Camera::isColliding = false;

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

    cameraCollisionCheck();
}


void Camera::cameraCollisionCheck()
{
    if (cameraCollisionLocation.x == 0.0f && cameraCollisionLocation.y == -100.0f && cameraCollisionLocation.z == 0.0f)
        cameraPreCollisionPosition = position;
    else
    {
        isColliding = true;
        isColliding = false;
    }


    /*if (cameraCollisionLocation.x == 0.0f && cameraCollisionLocation.y == -100.0f && cameraCollisionLocation.z == 0.0f)
        cameraPreCollisionPosition = position;
    else
    {
        vec3 blockVector = cameraPreCollisionPosition - cameraCollisionLocation;
        vec3 blockVectorNorm = normalize(blockVector);
        if(blockVector.y > cameraCollisionLocation.y+collisionObjectYScale)
            position += vec3(blockVectorNorm.x, blockVectorNorm.y, blockVectorNorm.z);
        else
            position += vec3(blockVectorNorm.x, 0.0f, blockVectorNorm.z);
        cameraCollisionLocation = vec3(0.0f, -100.0f, 0.0f);
        collisionObjectYScale = 0.0f;
    }*/
}
