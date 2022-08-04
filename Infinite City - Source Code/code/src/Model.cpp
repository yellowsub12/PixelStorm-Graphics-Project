#include "Model.h"
#include <iostream>
#include <textures.h>
#include <shapes.h>

using namespace std;

string texturesPathPrefix = "assets/textures/";

GLuint cubeModelVAO = 0;

GLuint buildingTexture = 0;
GLuint treeTexture = 0;
GLuint leavesTexture = 0;
GLuint soilTexture = 0;
GLuint towerTexture = 0;
GLuint benchTexture = 0;


void Initialize()
{
	cubeModelVAO = createUnitCube(false);

	buildingTexture = loadTexture((texturesPathPrefix+"building.jpg").c_str());
	treeTexture = loadTexture((texturesPathPrefix + "wood.jpg").c_str());
	leavesTexture = loadTexture((texturesPathPrefix + "leaves.png").c_str());
	soilTexture = loadTexture((texturesPathPrefix + "soil.jpg").c_str());
	benchTexture = loadTexture((texturesPathPrefix + "benchwood.png").c_str());


	towerTexture = loadTexture((texturesPathPrefix + "SpaceTower.jpg").c_str());
}

void Draw(vec3 position, float tileSize, int blockType, GLuint worldMatrixLocation, GLuint textureLocation)
{
	if (blockType == 5)
	{
		DrawSpaceTower(position, tileSize, worldMatrixLocation, textureLocation);
	}
	else if (blockType == 4)
	{
		DrawTree(position, tileSize, worldMatrixLocation, textureLocation);
	}
	else 
	{
    int random_integer;
	  int lowest = 1, highest = 3;
	  int range = (highest - lowest) + 1;
	  random_integer = lowest + rand() % range;
	  if (random_integer == 1) {
	  	DrawTree(position, tileSize, worldMatrixLocation, textureLocation);
	  }
	  if (random_integer == 2)
	  {
		DrawBuilding(position, tileSize, worldMatrixLocation, textureLocation);
	  }
	  else 
	  {
		  DrawBench(position, tileSize, worldMatrixLocation, textureLocation);
	  }
	}
}

void DrawBuilding(vec3 position, float tileSize, GLuint worldMatrixLocation, GLuint textureLocation)
{
	int probabilityCheck = rand() % 100; // Variable to help us adjust what numbers spawn more often and what numbers spawn less often. 
	int randomFactor = 0; // The random factor which affects the scale of the building.// = rand() % 11; 
	if (probabilityCheck < 2) randomFactor = 15; // less than 2% of buildings will be 15 units tall
	if (probabilityCheck >= 2 && probabilityCheck < 30) randomFactor = rand() % 12; // around 28% of the city will be buildings that are between 3 to 5 units tall
	if (probabilityCheck >= 30 && probabilityCheck < 50) randomFactor = rand() % 13; // around 20% of the city will be buildings that are between 4 to 6 units tall
	if (probabilityCheck >= 50) randomFactor = rand() % 14; // Lastly, the remaining 50% of buildings will be about 1 to 2 units tall. 

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

void DrawTree(vec3 position, float tileSize, GLuint worldMatrixLocation, GLuint textureLocation)
{
	int probabilityCheck = rand() % 100; // Variable to help us adjust what numbers spawn more often and what numbers spawn less often. 
	int randomFactor = 0; // The random factor which affects the scale of the building.// = rand() % 11; 
	if (probabilityCheck < 2) randomFactor = 9; // less than 2% of buildings will be 15 units tall
	if (probabilityCheck >= 2 && probabilityCheck < 30) randomFactor = rand() % 8; // around 28% of the city will be buildings that are between 3 to 5 units tall
	if (probabilityCheck >= 30 && probabilityCheck < 50) randomFactor = rand() % 7; // around 20% of the city will be buildings that are between 4 to 6 units tall
	if (probabilityCheck >= 50) randomFactor = rand() % 8; // Lastly, the remaining 50% of buildings will be about 1 to 2 units tall. 

	glBindVertexArray(cubeModelVAO);

	// Assign texture to the building
	glBindTexture(GL_TEXTURE_2D, treeTexture);
	glUniform1i(textureLocation, 1);

	vec3 finalPosition = vec3(position.x, position.y + (0.1 * (3 + randomFactor)) / 2, position.z);

	mat4 tileWorldMatrix = translate(mat4(1.0f), finalPosition)
		* scale(mat4(1.0f), vec3(tileSize * 0.05, (0.1 * (5 + randomFactor)), tileSize * 0.05)); //(0.5*(1+randomFactor))+scaleOffset

	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &tileWorldMatrix[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);




	glBindTexture(GL_TEXTURE_2D, leavesTexture);
	mat4 leavesWorldMatrix = translate(mat4(1.0f), vec3(position.x, (position.y + (0.1 * (5 + randomFactor))), position.z))
		* scale(mat4(1.0f), vec3(tileSize * 0.2 + (0.05 * ( randomFactor)), tileSize * 0.2 + (0.025 * ( randomFactor)), tileSize * 0.2 + (0.05 * ( randomFactor)))); //(0.5*(1+randomFactor))+scaleOffset

	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &leavesWorldMatrix[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	// Upper part
	glBindTexture(GL_TEXTURE_2D, leavesTexture);
	mat4 leavesUpperWorldMatrix = translate(mat4(1.0f), vec3(position.x, (position.y + (0.1 * (7 + randomFactor))), position.z))
		* scale(mat4(1.0f), vec3(tileSize * 0.15 + (0.05 * (randomFactor)), tileSize * 0.15 + (0.025 * (randomFactor)), tileSize * 0.15 + (0.05 * (randomFactor)))); //(0.5*(1+randomFactor))+scaleOffset

	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &leavesUpperWorldMatrix[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	// Upper upper part
	glBindTexture(GL_TEXTURE_2D, leavesTexture);
	mat4 leavesUpperUpperWorldMatrix = translate(mat4(1.0f), vec3(position.x, (position.y + (0.1 * (9 + randomFactor))), position.z))
		* scale(mat4(1.0f), vec3(tileSize * 0.075 + (0.05 * (randomFactor)), tileSize * 0.075 + (0.025 * (randomFactor)), tileSize * 0.075 + (0.05 * (randomFactor)))); //(0.5*(1+randomFactor))+scaleOffset

	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &leavesUpperUpperWorldMatrix[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	glBindTexture(GL_TEXTURE_2D, soilTexture);
	mat4 soilWorldMatrix = translate(mat4(1.0f), vec3(position.x, (position.y), position.z))
		* scale(mat4(1.0f), vec3(tileSize * 0.1 + (0.05 * (randomFactor)), 0.025 , tileSize * 0.1 + (0.05 * (randomFactor)))); //(0.5*(1+randomFactor))+scaleOffset

	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &soilWorldMatrix[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);

 }


void DrawBench(vec3 position, float tileSize, GLuint worldMatrixLocation, GLuint textureLocation)
{
	//int probabilityCheck = rand() % 100; // Variable to help us adjust what numbers spawn more often and what numbers spawn less often. 
	//int randomFactor = 0; // The random factor which affects the scale of the building.// = rand() % 11; 
	//if (probabilityCheck < 2) randomFactor = 9; // less than 2% of buildings will be 15 units tall
	//if (probabilityCheck >= 2 && probabilityCheck < 30) randomFactor = rand() % 8; // around 28% of the city will be buildings that are between 3 to 5 units tall
	//if (probabilityCheck >= 30 && probabilityCheck < 50) randomFactor = rand() % 7; // around 20% of the city will be buildings that are between 4 to 6 units tall
	//if (probabilityCheck >= 50) randomFactor = rand() % 8; // Lastly, the remaining 50% of buildings will be about 1 to 2 units tall. 

	//glBindVertexArray(cubeModelVAO);

	//// Assign texture to the building
	//glBindTexture(GL_TEXTURE_2D, treeTexture);
	//glUniform1i(textureLocation, 1);

	//vec3 finalPosition = vec3(position.x, position.y + (0.1 * (3 + randomFactor)) / 2, position.z);

	//mat4 tileWorldMatrix = translate(mat4(1.0f), finalPosition)
	//	* scale(mat4(1.0f), vec3(tileSize * 0.05, (0.1 * (5 + randomFactor)), tileSize * 0.05)); //(0.5*(1+randomFactor))+scaleOffset

	//glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &tileWorldMatrix[0][0]);

	//glDrawArrays(GL_TRIANGLES, 0, 36);




	//glBindTexture(GL_TEXTURE_2D, leavesTexture);
	//mat4 leavesWorldMatrix = translate(mat4(1.0f), vec3(position.x, (position.y + (0.1 * (5 + randomFactor))), position.z))
	//	* scale(mat4(1.0f), vec3(tileSize * 0.2 + (0.05 * (randomFactor)), tileSize * 0.2 + (0.025 * (randomFactor)), tileSize * 0.2 + (0.05 * (randomFactor)))); //(0.5*(1+randomFactor))+scaleOffset

	//glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &leavesWorldMatrix[0][0]);

	//glDrawArrays(GL_TRIANGLES, 0, 36);


	//glBindTexture(GL_TEXTURE_2D, soilTexture);
	//mat4 soilWorldMatrix = translate(mat4(1.0f), vec3(position.x, (position.y), position.z))
	//	* scale(mat4(1.0f), vec3(tileSize * 0.1 + (0.05 * (randomFactor)), 0.025, tileSize * 0.1 + (0.05 * (randomFactor)))); //(0.5*(1+randomFactor))+scaleOffset

	//glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &soilWorldMatrix[0][0]);

	//glDrawArrays(GL_TRIANGLES, 0, 36);

}

void DrawSpaceTower(vec3 position, float tileSize, GLuint worldMatrixLocation, GLuint textureLocation)
{
	glBindVertexArray(cubeModelVAO);

	// Assign texture to the building
	glBindTexture(GL_TEXTURE_2D, towerTexture);
	glUniform1i(textureLocation, 1);

	vec3 finalPosition = vec3(position.x, position.y + 20.0f/ 2, position.z);

	mat4 tileWorldMatrix = translate(mat4(1.0f), finalPosition)
		* scale(mat4(1.0f), vec3(tileSize/2, 20.0f, tileSize/2)); //(0.5*(1+randomFactor))+scaleOffset

	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &tileWorldMatrix[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);
}


