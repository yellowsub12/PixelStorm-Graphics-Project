#pragma once

#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL
#include <GL/glew.h>   

#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include <glm/gtc/matrix_transform.hpp> // include this to create transformation matrices
#include <glm/common.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <shapes.h>

using namespace glm;

class CityBlock
{
public:
	int blockSize;
	int numOfTileRows;
	vec3 blockLocation;
	GLuint mainTexture;
	int blockSeed;
	int blockType; // Type of the block is an int value. Values of 0 to 3 means the block is a road type with one of 4 road textures on it, whereas a type of 4 means the block is a grass type and has a grass texture on it. 

	// Parameterized constructor
	CityBlock(int type, int size, int numTilesRows, vec3 location, GLuint texture, int seed);

	// Generates the actual elements on each block such as buildings, trees, etc
	void GenerateTiles(GLuint worldMatrixLocation, GLuint textureLocation);

	// Draw this block in the world
	void DrawBlock(GLuint shaderProgram, GLuint worldMatrixLocation, GLuint textureLocation);

};

