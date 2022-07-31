#include <Shader.h>

#include <string>
#include <fstream>
#include <iostream>

#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL
#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler

#include <GLFW/glfw3.h> // cross-platform interface for creating a graphical context,
// initializing OpenGL and binding inputs

using namespace std;

string readShader(const char* fileName)
{
    ifstream meInput(fileName);
    if (!meInput.good())
    {
        cout << "Shader file " << fileName << " not found!";
        exit(1);
    }

    string shaderCode = "";

    while (meInput.peek() != EOF)
    {
        shaderCode += meInput.get();
    }

    return shaderCode;
}

// Function that adds any shader (provided as a parameter) to the program
void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType)
{
    GLuint theShader = glCreateShader(shaderType);

    const GLchar* theCode[1];
    theCode[0] = shaderCode;

    GLint codeLength[1];
    codeLength[0] = strlen(shaderCode);

    glShaderSource(theShader, 1, theCode, codeLength);
    glCompileShader(theShader);

    GLint result = 0;
    GLchar eLog[1024] = { 0 };

    glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);

    if (!result)
    {
        glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
        cout << "Error compiling " << shaderType << " shader: \n" << eLog;
        return;
    }

    glAttachShader(theProgram, theShader);

}

// This is the function that does the following:
// 1) Creates a program
// 2) Reads 2 shaders from 2 files and compiles + adds them to the program
// 3) Links and validates the program 
GLuint CreateShader(string vertexShaderPath, string fragmentShaderPath)
{
    GLuint shader = glCreateProgram();

    if (!shader)
    {
        cout << "Error Creating shader program!";
        return 0;
    }

    string vShader = readShader(vertexShaderPath.c_str());
    string fShader = readShader(fragmentShaderPath.c_str());

    AddShader(shader, vShader.c_str(), GL_VERTEX_SHADER);
    AddShader(shader, fShader.c_str(), GL_FRAGMENT_SHADER);

    GLint result = 0;
    GLchar eLog[1024] = { 0 };

    glLinkProgram(shader);
    glGetProgramiv(shader, GL_LINK_STATUS, &result);

    if (!result)
    {
        glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
        cout << "Error Linking program: \n" << eLog;
        return 0;
    }

    glValidateProgram(shader);

    glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);

    if (!result)
    {
        glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
        cout << "Error Validating program: \n" << eLog;
        return 0;
    }

    return shader;
}

void bingo() {
    cout << "props!";
}
