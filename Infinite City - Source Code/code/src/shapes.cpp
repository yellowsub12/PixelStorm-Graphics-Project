#include <shapes.h>


#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL
#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler

#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include <glm/gtc/matrix_transform.hpp> // include this to create transformation matrices
#include <glm/common.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>



using namespace std;
using namespace glm;

//Creates a VBO of a 100 unit long line and adds it to the GPU
int createLine()
{
    vec3 vertexArray[] = {
        vec3(0.0f, 0.0f, 50.0f),
        vec3(0.0f, 0.0f,-50.0f),
    };

    // Create a vertex array
    GLuint vertexArrayObject;
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);


    // Upload Vertex Buffer to the GPU, keep a reference to it (vertexBufferObject)
    GLuint vertexBufferObject;
    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexArray), vertexArray, GL_STATIC_DRAW);

    glVertexAttribPointer(0,                   // attribute 0 matches aPos in Vertex Shader
        3,                   // size
        GL_FLOAT,            // type
        GL_FALSE,            // normalized?
        sizeof(vec3),        // stride - each vertex contain 2 vec3 (position, color)
        (void*)0             // array buffer offset
    );
    glEnableVertexAttribArray(0);

    return vertexBufferObject;
}

//Creates a VBO of a unit cube and adds it to the GPU
int createUnitCube(bool frontFaceOpaque)
{
    float frontFaceOpacity = 0;

    if (frontFaceOpaque)
        frontFaceOpacity = 0.5;
    else
        frontFaceOpacity = 1.0f;

    vec3 vertexArray[] = {

        vec3(-0.5f, 0.5f,-0.5f),  vec3(-1.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 1.0f), // back face
        vec3(-0.5f, -0.5f,-0.5f), vec3(-1.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f),
        vec3(-0.5f, -0.5f, 0.5f), vec3(-1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 1.0f),

        vec3(-0.5f, 0.5f, 0.5f), vec3(-1.0f, 0.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f), 
        vec3(-0.5f, 0.5f,-0.5f), vec3(-1.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 1.0f),
        vec3(-0.5f,-0.5f, 0.5f), vec3(-1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 1.0f),

        vec3(0.5f, 0.5f,-0.5f),  vec3(0.0f, 0.0f, -1.0f), vec3(1.0f, 1.0f, 1.0f), // right face
        vec3(-0.5f,-0.5f,-0.5f), vec3(0.0f, 0.0f, -1.0f), vec3(0.0f, 0.0f, 1.0f),
        vec3(-0.5f, 0.5f,-0.5f), vec3(0.0f, 0.0f, -1.0f), vec3(0.0f, 1.0f, 1.0f),

        vec3(0.5f, 0.5f,-0.5f),  vec3(0.0f, 0.0f, -1.0f), vec3(1.0f, 1.0f, 1.0f),
        vec3(0.5f,-0.5f,-0.5f),  vec3(0.0f, 0.0f, -1.0f), vec3(1.0f, 0.0f, 1.0f),
        vec3(-0.5f,-0.5f,-0.5f), vec3(0.0f, 0.0f, -1.0f), vec3(0.0f, 0.0f, 1.0f),

        vec3(0.5f,-0.5f, 0.5f),  vec3(0.0f,-1.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f), // bottom face
        vec3(-0.5f,-0.5f,-0.5f), vec3(0.0f,-1.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f),
        vec3(0.5f,-0.5f,-0.5f),  vec3(0.0f,-1.0f, 0.0f), vec3(1.0f, 0.0f, 1.0f),

        vec3(0.5f,-0.5f, 0.5f),  vec3(0.0f,-1.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f),
        vec3(-0.5f,-0.5f, 0.5f), vec3(0.0f,-1.0f, 0.0f), vec3(0.0f, 1.0f, 1.0f),
        vec3(-0.5f,-0.5f,-0.5f), vec3(0.0f,-1.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f),

        vec3(-0.5f, 0.5f, 0.5f), vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 1.0f, frontFaceOpacity), // left face
        vec3(-0.5f,-0.5f, 0.5f), vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 0.0f, frontFaceOpacity),
        vec3(0.5f,-0.5f, 0.5f),  vec3(0.0f, 0.0f, 1.0f), vec3(1.0f, 0.0f, frontFaceOpacity),

        vec3(0.5f, 0.5f, 0.5f),  vec3(0.0f, 0.0f, 1.0f), vec3(1.0f, 1.0f, frontFaceOpacity),
        vec3(-0.5f, 0.5f, 0.5f), vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 1.0f, frontFaceOpacity),
        vec3(0.5f,-0.5f, 0.5f),  vec3(0.0f, 0.0f, 1.0f), vec3(1.0f, 0.0f, frontFaceOpacity),

        vec3(0.5f, 0.5f, 0.5f),  vec3(1.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 1.0f), // front face
        vec3(0.5f,-0.5f, 0.5f),  vec3(1.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f),
        vec3(0.5f,-0.5f,-0.5f),  vec3(1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 1.0f),

        vec3(0.5f, 0.5f,-0.5f),  vec3(1.0f, 0.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f), 
        vec3(0.5f, 0.5f, 0.5f),  vec3(1.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 1.0f),
        vec3(0.5f,-0.5f,-0.5f),  vec3(1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 1.0f),

        vec3(0.5f, 0.5f, 0.5f),  vec3(0.0f, 1.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f), // top face
        vec3(0.5f, 0.5f,-0.5f),  vec3(0.0f, 1.0f, 0.0f), vec3(1.0f, 0.0f, 1.0f),
        vec3(-0.5f, 0.5f,-0.5f), vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f),

        vec3(0.5f, 0.5f, 0.5f),  vec3(0.0f, 1.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f),
        vec3(-0.5f, 0.5f,-0.5f), vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f),
        vec3(-0.5f, 0.5f, 0.5f), vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, 1.0f, 1.0f),
    };


    // Create a vertex array
    GLuint vertexArrayObject;
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);


    // Upload Vertex Buffer to the GPU, keep a reference to it (vertexBufferObject)
    GLuint vertexBufferObject;
    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexArray), vertexArray, GL_STATIC_DRAW);

    glVertexAttribPointer(0,                   // attribute 0 matches aPos in Vertex Shader
        3,                   // size
        GL_FLOAT,            // type
        GL_FALSE,            // normalized?
        3 * sizeof(vec3), // stride - each vertex contain 2 vec3 (position, color)
        (void*)0             // array buffer offset
    );
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,                   // attribute 0 matches aPos in Vertex Shader
        3,                   // size
        GL_FLOAT,            // type
        GL_FALSE,            // normalized?
        3 * sizeof(vec3), // stride - each vertex contain 2 vec3 (position, color)
        (void*)sizeof(vec3)             // array buffer offset
    );
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2,                   // attribute 0 matches aPos in Vertex Shader
        3,                   // size
        GL_FLOAT,            // type
        GL_FALSE,            // normalized?
        3 * sizeof(vec3), // stride - each vertex contain 2 vec3 (position, color)
        (void*)(2 * sizeof(vec3))            // array buffer offset
    );
    glEnableVertexAttribArray(2);

    return vertexBufferObject;
}

int createUnitCubeReversed() //for the skybox cube
{
    vec3 vertexArray[] = {
        vec3(-0.5f,-0.5f,-0.5f), vec3(1.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f), // back face
        vec3(-0.5f,-0.5f, 0.5f), vec3(1.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 1.0f),
        vec3(-0.5f, 0.5f, 0.5f), vec3(1.0f, 0.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f),

        vec3(-0.5f,-0.5f,-0.5f), vec3(1.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f),
        vec3(-0.5f, 0.5f, 0.5f), vec3(1.0f, 0.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f),
        vec3(-0.5f, 0.5f,-0.5f), vec3(1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 1.0f),

        vec3(0.5f, 0.5f,-0.5f),  vec3(0.0f, 0.0f, 1.0f), vec3(1.0f, 1.0f, 1.0f), // right face
        vec3(-0.5f,-0.5f,-0.5f), vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 0.0f, 1.0f),
        vec3(-0.5f, 0.5f,-0.5f), vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 1.0f, 1.0f),

        vec3(0.5f, 0.5f,-0.5f),  vec3(0.0f, 0.0f, 1.0f), vec3(1.0f, 1.0f, 1.0f),
        vec3(0.5f,-0.5f,-0.5f),  vec3(0.0f, 0.0f, 1.0f), vec3(1.0f, 0.0f, 1.0f),
        vec3(-0.5f,-0.5f,-0.5f), vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 0.0f, 1.0f),

        vec3(0.5f,-0.5f, 0.5f),  vec3(0.0f, 1.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f), // bottom face
        vec3(-0.5f,-0.5f,-0.5f), vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f),
        vec3(0.5f,-0.5f,-0.5f),  vec3(0.0f, 1.0f, 0.0f), vec3(1.0f, 0.0f, 1.0f),

        vec3(0.5f,-0.5f, 0.5f),  vec3(0.0f, 1.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f),
        vec3(-0.5f,-0.5f, 0.5f), vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, 1.0f, 1.0f),
        vec3(-0.5f,-0.5f,-0.5f), vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f),

        vec3(-0.5f, 0.5f, 0.5f), vec3(0.0f, 0.0f, -1.0f), vec3(0.0f, 1.0f, 1.0f), // left face
        vec3(-0.5f,-0.5f, 0.5f), vec3(0.0f, 0.0f, -1.0f), vec3(0.0f, 0.0f, 1.0f),
        vec3(0.5f,-0.5f, 0.5f),  vec3(0.0f, 0.0f, -1.0f), vec3(1.0f, 0.0f, 1.0f),

        vec3(0.5f, 0.5f, 0.5f),  vec3(0.0f, 0.0f, -1.0f), vec3(1.0f, 1.0f, 1.0f),
        vec3(-0.5f, 0.5f, 0.5f), vec3(0.0f, 0.0f, -1.0f), vec3(0.0f, 1.0f, 1.0f),
        vec3(0.5f,-0.5f, 0.5f),  vec3(0.0f, 0.0f, -1.0f), vec3(1.0f, 0.0f, 1.0f),

        vec3(0.5f, 0.5f, 0.5f),  vec3(-1.0f, 0.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f), // front face
        vec3(0.5f,-0.5f,-0.5f),  vec3(-1.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f),
        vec3(0.5f, 0.5f,-0.5f),  vec3(-1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 1.0f),

        vec3(0.5f,-0.5f,-0.5f),  vec3(-1.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f),
        vec3(0.5f, 0.5f, 0.5f),  vec3(-1.0f, 0.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f),
        vec3(0.5f,-0.5f, 0.5f),  vec3(-1.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 1.0f),

        vec3(0.5f, 0.5f, 0.5f),  vec3(0.0f, -1.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f), // top face
        vec3(0.5f, 0.5f,-0.5f),  vec3(0.0f, -1.0f, 0.0f), vec3(1.0f, 0.0f, 1.0f),
        vec3(-0.5f, 0.5f,-0.5f), vec3(0.0f, -1.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f),

        vec3(0.5f, 0.5f, 0.5f),  vec3(0.0f, -1.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f),
        vec3(-0.5f, 0.5f,-0.5f), vec3(0.0f, -1.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f),
        vec3(-0.5f, 0.5f, 0.5f), vec3(0.0f, -1.0f, 0.0f), vec3(0.0f, 1.0f, 1.0f),
    };


    // Create a vertex array
    GLuint vertexArrayObject;
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);


    // Upload Vertex Buffer to the GPU, keep a reference to it (vertexBufferObject)
    GLuint vertexBufferObject;
    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexArray), vertexArray, GL_STATIC_DRAW);

    glVertexAttribPointer(0,                   // attribute 0 matches aPos in Vertex Shader
        3,                   // size
        GL_FLOAT,            // type
        GL_FALSE,            // normalized?
        3 * sizeof(vec3),   // stride - each vertex contain 3 vec3 (position, normal, UV)
        (void*)0             // array buffer offset
    );
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,                   // attribute 0 matches aNormal in Vertex Shader
        3,                   // size
        GL_FLOAT,            // type
        GL_FALSE,            // normalized?
        3 * sizeof(vec3), // stride - each vertex contain 3 vec3 (position, normal, UV)
        (void*)sizeof(vec3)             // array buffer offset
    );
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2,                   // attribute 0 matches aUV in Vertex Shader
        3,                   // size
        GL_FLOAT,            // type
        GL_FALSE,            // normalized?
        3 * sizeof(vec3), // stride - each vertex contain 3 vec3 (position, normal, UV)
        (void*)(2 * sizeof(vec3))            // array buffer offset
    );
    glEnableVertexAttribArray(2);

    return vertexBufferObject;
}

int createUnitPlane()
{
    vec3 planeVertexArray[] = {
        vec3(0.5f, 0.0f, 0.5f),  vec3(0.0f, 1.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f),
        vec3(0.5f, 0.0f,-0.5f),  vec3(0.0f, 1.0f, 0.0f), vec3(1.0f, 0.0f, 1.0f),
        vec3(-0.5f, 0.0f,-0.5f), vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f),

        vec3(0.5f, 0.0f, 0.5f),  vec3(0.0f, 1.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f),
        vec3(-0.5f, 0.0f,-0.5f), vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f),
        vec3(-0.5f, 0.0f, 0.5f), vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, 1.0f, 1.0f)
    };


    // Create a vertex array
    GLuint vertexArrayObject;
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);


    // Upload Vertex Buffer to the GPU, keep a reference to it (vertexBufferObject)
    GLuint vertexBufferObject;
    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertexArray), planeVertexArray, GL_STATIC_DRAW);

    glVertexAttribPointer(0, // attribute 0 matches aPos in Vertex Shader
        3,                   // size
        GL_FLOAT,            // type
        GL_FALSE,            // normalized?
        3 * sizeof(vec3),    // stride - each vertex contain 3 vec3 (position, normal, UV)
        (void*)0             // array buffer offset
    );
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1,                   // attribute 1 matches aNormal in Vertex Shader
        3,                   // size
        GL_FLOAT,            // type
        GL_FALSE,            // normalized?
        3 * sizeof(vec3), // stride - each vertex contain 3 vec3 (position, normal, UV)
        (void*)sizeof(vec3)             // array buffer offset
    );
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2,                   // attribute 2 matches aUV in Vertex Shader
        3,                   // size
        GL_FLOAT,            // type
        GL_FALSE,            // normalized?
        3 * sizeof(vec3), // stride - each vertex contain 3 vec3 (position, normal, UV)
        (void*)(2 * sizeof(vec3))             // array buffer offset
    );
    glEnableVertexAttribArray(2);

    return vertexArrayObject;
}

int createUnitPyramid()
{
    vec3 pyramidVertexArray[] = {
        vec3(-0.5f, 0.0f, 0.5f), vec3(0.0f, -1.0f, 0.0f), vec3(0.0f, 1.0f, 1.0f), // D // Bottom Face
        vec3(-0.5f, 0.0f,-0.5f), vec3(0.0f, -1.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f), // C
        vec3(0.5f, 0.0f, 0.5f),  vec3(0.0f, -1.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f), // A

        vec3(-0.5f, 0.0f,-0.5f), vec3(0.0f, -1.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f), // C
        vec3(0.5f, 0.0f,-0.5f),  vec3(0.0f, -1.0f, 0.0f), vec3(1.0f, 0.0f, 1.0f), // B
        vec3(0.5f, 0.0f, 0.5f),  vec3(0.0f, -1.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f), // A

        vec3(0.5f, 0.0f, 0.5f),  vec3(0.0f, 0.5f, 0.5f), vec3(1.0f, 1.0f, 1.0f), // left face A
        vec3(0.0f, 0.5f, 0.0f),  vec3(0.0f, 0.5f, 0.5f), vec3(1.0f, 0.0f, 1.0f), // X
        vec3(-0.5f, 0.0f, 0.5f),  vec3(0.0f, 0.5f, 0.5f), vec3(1.0f, 1.0f, 1.0f),// D

        vec3(-0.5f, 0.0f,-0.5f), vec3(0.0f, 0.5f, -0.5f), vec3(0.0f, 0.0f, 1.0f), // right face C
        vec3(0.0f, 0.5f, 0.0f),  vec3(0.0f, 0.5f, -0.5f), vec3(1.0f, 0.0f, 1.0f), // X 
        vec3(0.5f, 0.0f,-0.5f), vec3(0.0f, 0.5f, -0.5f), vec3(0.0f, 0.0f, 1.0f), // B

        vec3(0.5f, 0.0f,-0.5f),  vec3(0.5f, 0.5f, 0.0f), vec3(1.0f, 1.0f, 1.0f), // Front face A
        vec3(0.0f, 0.5f, 0.0f),  vec3(0.5f, 0.5f, 0.0f), vec3(1.0f, 0.0f, 1.0f), // X
        vec3(0.5f, 0.0f, 0.5f),  vec3(0.5f, 0.5f, 0.0f), vec3(1.0f, 1.0f, 1.0f), // B

        vec3(-0.5f, 0.0f, 0.5f),  vec3(-0.5f, 0.5f, 0.0f), vec3(1.0f, 1.0f, 1.0f), // Back Face C
        vec3(0.0f, 0.5f, 0.0f),  vec3(-0.5f, 0.5f, 0.0f), vec3(1.0f, 0.0f, 1.0f), // X
        vec3(-0.5f, 0.0f,-0.5f),  vec3(-0.5f, 0.5f, 0.0f), vec3(1.0f, 1.0f, 1.0f), // D
    };


    // Create a vertex array
    GLuint vertexArrayObject;
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);


    // Upload Vertex Buffer to the GPU, keep a reference to it (vertexBufferObject)
    GLuint vertexBufferObject;
    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(pyramidVertexArray), pyramidVertexArray, GL_STATIC_DRAW);

    glVertexAttribPointer(0, // attribute 0 matches aPos in Vertex Shader
        3,                   // size
        GL_FLOAT,            // type
        GL_FALSE,            // normalized?
        3 * sizeof(vec3),    // stride - each vertex contain 3 vec3 (position, normal, UV)
        (void*)0             // array buffer offset
    );
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1,                   // attribute 1 matches aNormal in Vertex Shader
        3,                   // size
        GL_FLOAT,            // type
        GL_FALSE,            // normalized?
        3 * sizeof(vec3), // stride - each vertex contain 3 vec3 (position, normal, UV)
        (void*)sizeof(vec3)             // array buffer offset
    );
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2,                   // attribute 2 matches aUV in Vertex Shader
        3,                   // size
        GL_FLOAT,            // type
        GL_FALSE,            // normalized?
        3 * sizeof(vec3), // stride - each vertex contain 3 vec3 (position, normal, UV)
        (void*)(2 * sizeof(vec3))             // array buffer offset
    );
    glEnableVertexAttribArray(2);

    return vertexArrayObject;
}






int createTexturedCubeVertexArrayObject()
{
    // Struct useful to layout structure of vertex array.
    struct TexturedColoredVertex
    {
        TexturedColoredVertex(vec3 _position, vec3 _color, vec2 _uv)
            : position(_position), color(_color), uv(_uv) {}

        vec3 position;
        vec3 color;
        vec2 uv;
    };

    // Textured Cube model
    const TexturedColoredVertex texturedCubeVertexArray[] = {  // position,                            color,   UV,
        TexturedColoredVertex(vec3(-0.5f,-0.5f,-0.5f), vec3(1.0f, 0.0f, 0.0f), vec2(0.0f, 0.0f)), //left - red
        TexturedColoredVertex(vec3(-0.5f,-0.5f, 0.5f), vec3(1.0f, 0.0f, 0.0f), vec2(0.0f, 1.0f)),
        TexturedColoredVertex(vec3(-0.5f, 0.5f, 0.5f), vec3(1.0f, 0.0f, 0.0f), vec2(1.0f, 1.0f)),

        TexturedColoredVertex(vec3(-0.5f,-0.5f,-0.5f), vec3(1.0f, 0.0f, 0.0f), vec2(0.0f, 0.0f)),
        TexturedColoredVertex(vec3(-0.5f, 0.5f, 0.5f), vec3(1.0f, 0.0f, 0.0f), vec2(1.0f, 1.0f)),
        TexturedColoredVertex(vec3(-0.5f, 0.5f,-0.5f), vec3(1.0f, 0.0f, 0.0f), vec2(1.0f, 0.0f)),

        TexturedColoredVertex(vec3(0.5f, 0.5f,-0.5f), vec3(0.0f, 0.0f, 1.0f), vec2(1.0f, 1.0f)), // far - blue
        TexturedColoredVertex(vec3(-0.5f,-0.5f,-0.5f), vec3(0.0f, 0.0f, 1.0f), vec2(0.0f, 0.0f)),
        TexturedColoredVertex(vec3(-0.5f, 0.5f,-0.5f), vec3(0.0f, 0.0f, 1.0f), vec2(0.0f, 1.0f)),

        TexturedColoredVertex(vec3(0.5f, 0.5f,-0.5f), vec3(0.0f, 0.0f, 1.0f), vec2(1.0f, 1.0f)),
        TexturedColoredVertex(vec3(0.5f,-0.5f,-0.5f), vec3(0.0f, 0.0f, 1.0f), vec2(1.0f, 0.0f)),
        TexturedColoredVertex(vec3(-0.5f,-0.5f,-0.5f), vec3(0.0f, 0.0f, 1.0f), vec2(0.0f, 0.0f)),

        TexturedColoredVertex(vec3(0.5f,-0.5f, 0.5f), vec3(0.0f, 1.0f, 1.0f), vec2(1.0f, 1.0f)), // bottom - turquoise
        TexturedColoredVertex(vec3(-0.5f,-0.5f,-0.5f), vec3(0.0f, 1.0f, 1.0f), vec2(0.0f, 0.0f)),
        TexturedColoredVertex(vec3(0.5f,-0.5f,-0.5f), vec3(0.0f, 1.0f, 1.0f), vec2(1.0f, 0.0f)),

        TexturedColoredVertex(vec3(0.5f,-0.5f, 0.5f), vec3(0.0f, 1.0f, 1.0f), vec2(1.0f, 1.0f)),
        TexturedColoredVertex(vec3(-0.5f,-0.5f, 0.5f), vec3(0.0f, 1.0f, 1.0f), vec2(0.0f, 1.0f)),
        TexturedColoredVertex(vec3(-0.5f,-0.5f,-0.5f), vec3(0.0f, 1.0f, 1.0f), vec2(0.0f, 0.0f)),

        TexturedColoredVertex(vec3(-0.5f, 0.5f, 0.5f), vec3(0.0f, 1.0f, 0.0f), vec2(0.0f, 1.0f)), // near - green
        TexturedColoredVertex(vec3(-0.5f,-0.5f, 0.5f), vec3(0.0f, 1.0f, 0.0f), vec2(0.0f, 0.0f)),
        TexturedColoredVertex(vec3(0.5f,-0.5f, 0.5f), vec3(0.0f, 1.0f, 0.0f), vec2(1.0f, 0.0f)),

        TexturedColoredVertex(vec3(0.5f, 0.5f, 0.5f), vec3(0.0f, 1.0f, 0.0f), vec2(1.0f, 1.0f)),
        TexturedColoredVertex(vec3(-0.5f, 0.5f, 0.5f), vec3(0.0f, 1.0f, 0.0f), vec2(0.0f, 1.0f)),
        TexturedColoredVertex(vec3(0.5f,-0.5f, 0.5f), vec3(0.0f, 1.0f, 0.0f), vec2(1.0f, 0.0f)),

        TexturedColoredVertex(vec3(0.5f, 0.5f, 0.5f), vec3(1.0f, 0.0f, 1.0f), vec2(1.0f, 1.0f)), // right - purple
        TexturedColoredVertex(vec3(0.5f,-0.5f,-0.5f), vec3(1.0f, 0.0f, 1.0f), vec2(0.0f, 0.0f)),
        TexturedColoredVertex(vec3(0.5f, 0.5f,-0.5f), vec3(1.0f, 0.0f, 1.0f), vec2(1.0f, 0.0f)),

        TexturedColoredVertex(vec3(0.5f,-0.5f,-0.5f), vec3(1.0f, 0.0f, 1.0f), vec2(0.0f, 0.0f)),
        TexturedColoredVertex(vec3(0.5f, 0.5f, 0.5f), vec3(1.0f, 0.0f, 1.0f), vec2(1.0f, 1.0f)),
        TexturedColoredVertex(vec3(0.5f,-0.5f, 0.5f), vec3(1.0f, 0.0f, 1.0f), vec2(0.0f, 1.0f)),

        TexturedColoredVertex(vec3(0.5f, 0.5f, 0.5f), vec3(1.0f, 1.0f, 0.0f), vec2(1.0f, 1.0f)), // top - yellow
        TexturedColoredVertex(vec3(0.5f, 0.5f,-0.5f), vec3(1.0f, 1.0f, 0.0f), vec2(1.0f, 0.0f)),
        TexturedColoredVertex(vec3(-0.5f, 0.5f,-0.5f), vec3(1.0f, 1.0f, 0.0f), vec2(0.0f, 0.0f)),

        TexturedColoredVertex(vec3(0.5f, 0.5f, 0.5f), vec3(1.0f, 1.0f, 0.0f), vec2(1.0f, 1.0f)),
        TexturedColoredVertex(vec3(-0.5f, 0.5f,-0.5f), vec3(1.0f, 1.0f, 0.0f), vec2(0.0f, 0.0f)),
        TexturedColoredVertex(vec3(-0.5f, 0.5f, 0.5f), vec3(1.0f, 1.0f, 0.0f), vec2(0.0f, 1.0f))
    };

    // Create a vertex array
    GLuint vertexArrayObject;
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);

    // Upload Vertex Buffer to the GPU, keep a reference to it (vertexBufferObject)
    GLuint vertexBufferObject;
    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texturedCubeVertexArray), texturedCubeVertexArray, GL_STATIC_DRAW);

    glVertexAttribPointer(0,                   // attribute 0 matches aPos in Vertex Shader
        3,                   // size
        GL_FLOAT,            // type
        GL_FALSE,            // normalized?
        sizeof(TexturedColoredVertex), // stride - each vertex contain 2 vec3 (position, color)
        (void*)0             // array buffer offset
    );
    glEnableVertexAttribArray(0);


    glVertexAttribPointer(1,                            // attribute 1 matches aColor in Vertex Shader
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(TexturedColoredVertex),
        (void*)sizeof(vec3)      // color is offseted a vec3 (comes after position)
    );
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2,                            // attribute 2 matches aUV in Vertex Shader
        2,
        GL_FLOAT,
        GL_FALSE,
        sizeof(TexturedColoredVertex),
        (void*)(2 * sizeof(vec3))      // uv is offseted by 2 vec3 (comes after position and color)
    );
    glEnableVertexAttribArray(2);

    return vertexArrayObject;
}