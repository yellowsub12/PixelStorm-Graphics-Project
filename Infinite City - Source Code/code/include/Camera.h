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
	vec3 cameraUp;
	float cameraAngularSpeed;
	float cameraSpeed;
	float cameraVerticalLimits;

	Camera(); // Default Construtor
	Camera(Camera &copyCam); // Copy Constructor 

	// Method to linearly interpolate between two floats
	float Lerp(float a, float b, float f);

	// Method that updates the camera data and actually helps us control the camera. Contains all data and input handling related to Camera movement
	void UpdateCamera(GLuint viewMatrixLocation, GLuint projMatrixLocation, GLFWwindow* currentWindow);
	GLFWscrollfun mouseWheel(int, int, int, int);
};

