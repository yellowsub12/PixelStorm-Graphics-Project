#pragma once

#ifndef MODEL_H
#define MODEL_H

#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL
#include <GL/glew.h>  

#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include <glm/gtc/matrix_transform.hpp> // include this to create transformation matrices
#include <glm/common.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

extern GLuint cubeModelVAO;
extern GLuint buildingTexture;

void Initialize();

void Draw(vec3 position, float tileSize, int blockType, GLuint worldMatrixLoction, GLuint textureLocation);

void DrawBuilding(vec3 position, float tileSize, GLuint worldMatrixLocation, GLuint textureLocation);

void DrawTree(vec3 position, float tileSize, GLuint worldMatrixLocation, GLuint textureLocation);

void DrawCar(vec3 position, float tileSize, GLuint worldMatrixLocation);

#endif MODEL_H