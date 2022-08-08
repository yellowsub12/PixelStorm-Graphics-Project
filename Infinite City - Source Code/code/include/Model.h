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

void Initialize();

void Draw(vec3 position, float tileSize, int blockType, bool roadType, int orientation, GLuint worldMatrixLoction, GLuint textureLocation, GLuint shaderProgram);

void DrawTile(vec3 position, float tileSize, int blockType, GLuint worldMatrixLocation, GLuint textureLocation, GLuint shaderProgram);

void DrawBuilding(vec3 position, float tileSize, GLuint worldMatrixLocation, GLuint textureLocation, GLuint shaderProgram);

void DrawTree(vec3 position, float tileSize, GLuint worldMatrixLocation, GLuint textureLocation);

void DrawSpaceTower(vec3 position, float tileSize, GLuint worldMatrixLocation, GLuint textureLocation);

void DrawBench(vec3 position, float tileSize, GLuint worldMatrixLocation, GLuint textureLocation);

void DrawHuman(vec3 position, float tileSize, GLuint worldMatrixLocation, GLuint textureLocation, GLuint shaderProgram);

void DrawCar(vec3 position, float tileSize, int orientation, GLuint worldMatrixLocation, GLuint textureLocation);

void DrawTrashBin(vec3 position, float tileSize, GLuint worldMatrixLocation, GLuint textureLocation);

void DrawPhonebooth(vec3 position, float tileSize, GLuint worldMatrixLocation, GLuint textureLocation);

void DrawBus(vec3 position, float tileSize, int orientation, GLuint worldMatrixLocation, GLuint textureLocation);

void CollisionCheck(vec3 objectPosition, vec3 objectScale, GLuint worldMatrixLocation);

void DrawLamp(vec3 position, float tileSize, GLuint worldMatrixLocation, GLuint textureLocation);

#endif MODEL_H