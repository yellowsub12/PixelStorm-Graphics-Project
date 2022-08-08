#pragma once

#ifndef TEXTURES_H
#define TEXTURES_H

#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL
#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler

#include <GLFW/glfw3.h> 
#include <vector>
#include <string>

GLuint loadTexture(const char* filename);

unsigned int loadCubemap(std::vector<std::string> faces);


#endif TEXTURES_H
