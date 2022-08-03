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
	GLuint buildingTexture;
	GLuint cubeVAO;
	int blockSeed;
	int blockType;

	// Parameterized constructor
	CityBlock(int type, int size, int numTilesRows, vec3 location, GLuint texture, int seed);

	// Generates the actual elements on each block such as buildings, trees, etc
	void GenerateTiles(GLuint worldMatrixLocation, GLuint textureLocation, GLuint buildingTexture);

	// Draw this block in the world
	void DrawBlock(GLuint shaderProgram, GLuint worldMatrixLocation, GLuint textureLocation, GLuint buildingTexture);

};

