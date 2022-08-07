#pragma once

#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL
#include <GL/glew.h> 

#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include <glm/gtc/matrix_transform.hpp> // include this to create transformation matrices
#include <glm/common.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GLFW/glfw3.h> 

using namespace glm;

class Camera {
public:
	static vec3 position;
	static vec3 movementVector;
	static vec3 lookAt;
	static float fov;
	static vec3 cameraUp;
	static float cameraAngularSpeed;
	static float cameraSpeed;
	static float cameraVerticalLimits;
	static float cameraHorizontalAngle;
	static float cameraVerticalAngle;
	static vec3 cameraPreCollisionPosition;
	static vec3 cameraCollisionLocation;
	static vec3 cameraCollisionScale;
	static float collisionObjectYScale;
	static float fallVelocity;
	static bool isColliding;

	Camera(); // Default Construtor
	Camera(Camera &copyCam); // Copy Constructor 


	void setCameraPosition(vec3 newPosition);
	void setCameraLookAt(vec3 newLookAt);
	void setCameraHorizontalAngle(float cameraHorizontalAngle);
	void setCameraVerticleAngle(float cameraVerticleAngle);
	void updateCamera(GLuint viewMatrixLocation, GLuint projMatrixLocation, GLFWwindow* currentWindow);
	void cameraCollisionCheck();
};

