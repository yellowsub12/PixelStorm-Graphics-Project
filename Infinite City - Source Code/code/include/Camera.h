#pragma once

#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL
#include <GL/glew.h> 

#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include <glm/gtc/matrix_transform.hpp> // include this to create transformation matrices
#include <glm/common.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GLFW/glfw3.h> 

using namespace glm;

class Camera
{
public:
	vec3 position;
	vec3 lookAt;
	float fov;
	vec3 newPosition;
	vec3 newLookAt;
	vec3 cameraUp;
	float cameraAngularSpeed;
	float cameraSpeed;

	Camera();

	float Lerp(float a, float b, float f);

	void UpdateCamera(GLuint viewMatrixLocation, GLuint projMatrixLocation, GLFWwindow* currentWindow);
};
