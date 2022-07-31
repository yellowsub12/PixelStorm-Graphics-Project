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
	int numOfTiles;
	vec3 blockLocation;
	GLuint mainTexture;

	CityBlock(int size, int numTiles, vec3 location, GLuint texture);

	void GenerateTiles();

	void DrawBlock(GLuint shaderProgram, GLuint worldMatrixLocation);

};

