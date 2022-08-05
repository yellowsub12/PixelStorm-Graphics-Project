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
	int blockSize; // Size of each individual block in the city
	int citySeed; // The overall seed of the city for random generation
	std::vector<CityBlock> totalBlocks; // Vector that will contain all the blocks of the city, with it's respective properties
	GLuint planeVAO; // Plane VAO that will help us draw the block plane
	Camera mainCamera; // The main "player" camera through which we see the Infinite City
	GLuint cityBlockTextures[6]; // Array of textures for the block planes of the city
	GLuint testTexture;

	int InfinitePathRowFStartNumber;
	int InfinitePathRowFEndNumber;

	int InfinitePathRowBStartNumber;
	int InfinitePathRowBEndNumber;

	int InfinitePathColumnFStartNumber;
	int InfinitePathColumnFEndNumber;

	int InfinitePathColumnBStartNumber;
	int InfinitePathColumnBEndNumber;


	InfiniteCity(int width, int length, int sizeBlock, int seed);

	// Method to spawn the starting series of blocks in the city when the program starts
	void SpawnStartingBlocks(); 

	// Spawn blocks along the z axis when the player crosses the city limits along the x-axis
	void SpawnRowBlocks(int rowNumber, int direction, int frontColumns, int backColumns); 

	// Spawn blocks along the x axis when the player crosses the city limits along the z-axis
	void SpawnColumnBlocks(int columnNumber, int direction, int frontRows, int backRows);

	void GenerateTextureArray(); //Initialize the populate the texture array cityBlockTextures with the textures that will be on each block of the city

	void DrawCity(GLFWwindow* window, GLuint sceneShaderProgram, GLuint shadowShaderProgram); //The method that contains the actual render loop of the whole program along with all its necessary data

	// The following two methods will increase the city threshold as the player moves further along the city. The city threshold is the threshold that when crossed, spawns more blocks in the city. 
	void UpdateZSpawnLocation(float newPoint);
	void UpdateXSpawnLocation(float newPoint);
};

