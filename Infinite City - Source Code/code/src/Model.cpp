#include "Model.h"
#include <iostream>
#include <textures.h>
#include <shapes.h>

using namespace std;

string texturesPathPrefix = "assets/textures/";

GLuint cubeModelVAO = 0;
GLuint buildingTexture = 0;

void Initialize()
{
	cubeModelVAO = createUnitCube(false);
	buildingTexture = loadTexture((texturesPathPrefix+"building.jpg").c_str());
}

void Draw(vec3 position, float tileSize, int blockType, GLuint worldMatrixLocation, GLuint textureLocation)
{
	DrawBuilding(position, tileSize, worldMatrixLocation, textureLocation);
}

void DrawBuilding(vec3 position, float tileSize, GLuint worldMatrixLocation, GLuint textureLocation)
{
	int probabilityCheck = rand() % 100; // Variable to help us adjust what numbers spawn more often and what numbers spawn less often. 
	int randomFactor = 0; // The random factor which affects the scale of the building.// = rand() % 11; 
	if (probabilityCheck < 2) randomFactor = 15; // less than 2% of buildings will be 15 units tall
	if (probabilityCheck >= 2 && probabilityCheck < 30) randomFactor = rand() % 5 + 3; // around 28% of the city will be buildings that are between 3 to 5 units tall
	if (probabilityCheck >= 30 && probabilityCheck < 50) randomFactor = rand() % 6 + 4; // around 20% of the city will be buildings that are between 4 to 6 units tall
	if (probabilityCheck >= 50) randomFactor = rand() % 2; // Lastly, the remaining 50% of buildings will be about 1 to 2 units tall. 

	glBindVertexArray(cubeModelVAO);

	// Assign texture to the building
	glBindTexture(GL_TEXTURE_2D, buildingTexture);
	glUniform1i(textureLocation, 1);

	vec3 finalPosition = vec3(position.x, position.y + (0.5 * (1 + randomFactor)) / 2, position.z);

	mat4 tileWorldMatrix = translate(mat4(1.0f), finalPosition)
		* scale(mat4(1.0f), vec3(tileSize, (0.5 * (1 + randomFactor)), tileSize)); //(0.5*(1+randomFactor))+scaleOffset

	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &tileWorldMatrix[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);
}