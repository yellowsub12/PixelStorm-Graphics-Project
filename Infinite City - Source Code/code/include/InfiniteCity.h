#pragma once

#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL
#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include <glm/gtc/matrix_transform.hpp> // include this to create transformation matrices
#include <glm/common.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "CityBlock.h"
#include <shapes.h>
#include <vector>
#include <Camera.h>

using namespace glm;
class InfiniteCity
{
public:
	int cityWidth;
	int cityLength;
	float zSpawnFrontLocation; //Point along the z axis; When the camera goes beyond this point on the z axis, the city generator will generator a new row
	float xSpawnFrontLocation; //Point along the x axis; When the camera goes beyond this point on the x axis, the city generator will generator a new row
	float zSpawnBackLocation; //Point along the z axis; When the camera goes beyond this point on the z axis, the city generator will generator a new row
	float xSpawnBackLocation; //Point along the x axis; When the camera goes beyond this point on the x axis, the city generator will generator a new row
	int blockSize;
	std::vector<CityBlock> totalBlocks;
	GLuint planeVAO;
	Camera mainCamera;
	GLuint cityBlockTextures[6];

	InfiniteCity(int width, int length, int sizeBlock, Camera newCam);

	void SpawnStartingBlocks();

	void SpawnRowBlocks(int rowNumber, int direction, int frontColumns, int backColumns);
	void SpawnColumnBlocks(int columnNumber, int direction, int frontRows, int backRows);

	void GenerateTextureArray();

	void DrawCity(GLFWwindow* window, GLuint sceneShaderProgram, GLuint shadowShaderProgram);

	void UpdateZSpawnLocation(float newPoint);
	void UpdateXSpawnLocation(float newPoint);
};

