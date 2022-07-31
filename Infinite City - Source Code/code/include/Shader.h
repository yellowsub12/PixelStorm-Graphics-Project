#pragma once

#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <iostream>

#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL
#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler

#include <GLFW/glfw3.h> // cross-platform interface for creating a graphical context,
// initializing OpenGL and binding inputs

#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include <glm/gtc/matrix_transform.hpp> // include this to create transformation matrices
#include <glm/common.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

string readShader(const char* fileName);

// Function that adds any shader (provided as a parameter) to the program
void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);

// This is the function that does the following:
// 1) Creates a program
// 2) Reads 2 shaders from 2 files and compiles + adds them to the program
// 3) Links and validates the program 
GLuint CreateShader(string vertexShaderPath, string fragmentShaderPath);

#endif
