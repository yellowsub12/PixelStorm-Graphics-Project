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
GLuint ironTexture = 0;
GLuint fabricsTexture = 0;
GLuint fabricsarmsTexture = 0;
GLuint jeanslegTexture = 0;
GLuint frontTexture = 0;


void Initialize()
{
	cubeModelVAO = createUnitCube(false);

	buildingTexture = loadTexture((texturesPathPrefix+"building.jpg").c_str());
	treeTexture = loadTexture((texturesPathPrefix + "wood.jpg").c_str());
	leavesTexture = loadTexture((texturesPathPrefix + "leaves.png").c_str());
	soilTexture = loadTexture((texturesPathPrefix + "soil.jpg").c_str());
	benchTexture = loadTexture((texturesPathPrefix + "benchwood.png").c_str());
	ironTexture = loadTexture((texturesPathPrefix + "iron.jpg").c_str());
	fabricsTexture = loadTexture((texturesPathPrefix + "fabrics.png").c_str());
	fabricsarmsTexture = loadTexture((texturesPathPrefix + "fabricsarms.png").c_str());
	jeanslegTexture = loadTexture((texturesPathPrefix + "jeansleg.jpg").c_str());
	frontTexture = loadTexture((texturesPathPrefix + "front.png").c_str());
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
		int random_integer;
		int lowest = 1, highest = 2;
		int range = (highest - lowest) + 1;
		random_integer = lowest + rand() % range;
		if (random_integer == 1) {
			DrawHuman(position, tileSize, worldMatrixLocation, textureLocation);
		}
		if (random_integer == 2)
		{
			DrawBench(position, tileSize, worldMatrixLocation, textureLocation);
		}
	}
	else 
	{
		int random_integer;
		int lowest = 1, highest = 2;
		int range = (highest - lowest) + 1;
		random_integer = lowest + rand() % range;
		if (random_integer == 1) {
			DrawHuman(position, tileSize, worldMatrixLocation, textureLocation);
		}
		if (random_integer == 2)
		{
			DrawBuilding(position, tileSize, worldMatrixLocation, textureLocation);
		}
	}
}

void DrawBuilding(vec3 position, float tileSize, GLuint worldMatrixLocation, GLuint textureLocation)
{
	int probabilityCheck = rand() % 100; // Variable to help us adjust what numbers spawn more often and what numbers spawn less often. 
	int randomFactor = 0; // The random factor which affects the scale of the building.// = rand() % 11; 
	if (probabilityCheck < 2) randomFactor = 15; // less than 2% of buildings will be 15 units tall
	if (probabilityCheck >= 2 && probabilityCheck < 30) randomFactor = 1 + rand() % 2; // around 28% of the city will be buildings that are between 3 to 5 units tall
	if (probabilityCheck >= 30 && probabilityCheck < 50) randomFactor = rand() % 2 + 4; // around 20% of the city will be buildings that are between 4 to 6 units tall
	if (probabilityCheck >= 50) randomFactor = rand() % 2 + 3; // Lastly, the remaining 50% of buildings will be about 1 to 2 units tall. 

	glBindVertexArray(cubeModelVAO);

	// Assign texture to the building
	glBindTexture(GL_TEXTURE_2D, buildingTexture);
	glUniform1i(textureLocation, 1);

	vec3 finalPosition = vec3(position.x, position.y + (0.5 * (1 + randomFactor)) / 2, position.z);

	mat4 tileWorldMatrix = translate(mat4(1.0f), finalPosition)
		* scale(mat4(1.0f), vec3(tileSize, randomFactor*tileSize, tileSize)); //(0.5*(1+randomFactor))+scaleOffset

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
		* scale(mat4(1.0f), vec3(tileSize * 0.05, (0.1 * (5 + randomFactor))*tileSize, tileSize * 0.05)); //(0.5*(1+randomFactor))+scaleOffset

	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &tileWorldMatrix[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	glBindTexture(GL_TEXTURE_2D, leavesTexture);
	mat4 leavesWorldMatrix = translate(mat4(1.0f), vec3(position.x, (position.y + (0.1 * (5 + randomFactor))*tileSize/2), position.z))
		* rotate(mat4(1.0f), 0.05f*sinf(2*glfwGetTime()), vec3(0.0f, 1.0f, 0.0f))
		* scale(mat4(1.0f), vec3(tileSize * 0.2 + (0.05 * ( randomFactor)), tileSize * 0.2 + (0.025 * ( randomFactor)), tileSize * 0.2 + (0.05 * ( randomFactor)))); //(0.5*(1+randomFactor))+scaleOffset

	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &leavesWorldMatrix[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	// Upper part
	glBindTexture(GL_TEXTURE_2D, leavesTexture);
	mat4 leavesUpperWorldMatrix = translate(mat4(1.0f), vec3(position.x, (position.y + (0.1 * (7 + randomFactor)) * tileSize / 2), position.z))
		* rotate(mat4(1.0f), 0.05f * sinf((2 * glfwGetTime()) + (3.14159f/2)), vec3(0.0f, 1.0f, 0.0f))
		* scale(mat4(1.0f), vec3(tileSize * 0.15 + (0.05 * (randomFactor)), tileSize * 0.15 + (0.025 * (randomFactor)), tileSize * 0.15 + (0.05 * (randomFactor)))); //(0.5*(1+randomFactor))+scaleOffset

	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &leavesUpperWorldMatrix[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	// Upper upper part
	glBindTexture(GL_TEXTURE_2D, leavesTexture);
	mat4 leavesUpperUpperWorldMatrix = translate(mat4(1.0f), vec3(position.x, (position.y + (0.1 * (9 + randomFactor)) * tileSize / 2), position.z))
		* rotate(mat4(1.0f), 0.05f * sinf((2 * glfwGetTime()) + (3.14159f/3)), vec3(0.0f, 1.0f, 0.0f))
		* scale(mat4(1.0f), vec3(tileSize * 0.075 + (0.05 * (randomFactor)), tileSize * 0.075 + (0.025 * (randomFactor)), tileSize * 0.075 + (0.05 * (randomFactor)))); //(0.5*(1+randomFactor))+scaleOffset

	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &leavesUpperUpperWorldMatrix[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	glBindTexture(GL_TEXTURE_2D, soilTexture);
	mat4 soilWorldMatrix = translate(mat4(1.0f), vec3(position.x, (position.y), position.z))
		* scale(mat4(1.0f), vec3(tileSize, 0.07 , tileSize)); //(0.5*(1+randomFactor))+scaleOffset

	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &soilWorldMatrix[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);

 }


void DrawBench(vec3 position, float tileSize, GLuint worldMatrixLocation, GLuint textureLocation)
{
	int probabilityCheck = rand() % 100; // Variable to help us adjust what numbers spawn more often and what numbers spawn less often. 
	int randomBenchFactor = 0; // The random factor which affects the scale of the building.// = rand() % 11; 
	if (probabilityCheck < 2) randomBenchFactor = 3+3; // less than 2% of buildings will be 15 units tall
	if (probabilityCheck >= 2 && probabilityCheck < 30) randomBenchFactor = rand() % 4 + 3; // around 28% of the city will be buildings that are between 3 to 5 units tall
	if (probabilityCheck >= 30 && probabilityCheck < 50) randomBenchFactor = rand() % 5 + 3; // around 20% of the city will be buildings that are between 4 to 6 units tall
	if (probabilityCheck >= 50) randomBenchFactor = rand() % 4 + 3; // Lastly, the remaining 50% of buildings will be about 1 to 2 units tall. 

	glBindVertexArray(cubeModelVAO);

	// Assign texture to the bench
	glBindTexture(GL_TEXTURE_2D, benchTexture);
	glUniform1i(textureLocation, 1);

	vec3 finalPosition = vec3(position.x, position.y + 0.2, position.z);

	mat4 benchWorldMatrix = translate(mat4(1.0f), vec3(position.x, (position.y + 0.5), position.z))
		* scale(mat4(1.0f), vec3( randomBenchFactor, 0.25, 2.0 )); //(0.5*(1+randomFactor))+scaleOffset

	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &benchWorldMatrix[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	// Assign texture to the iron
	glBindTexture(GL_TEXTURE_2D, ironTexture);
	glUniform1i(textureLocation, 1);

	mat4 benchLegWorldMatrix = translate(mat4(1.0f), vec3(position.x, (position.y + 0.25), position.z))
		* scale(mat4(1.0f), vec3(randomBenchFactor * 0.9, 0.5, 1.5)); //(0.5*(1+randomFactor))+scaleOffset

	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &benchLegWorldMatrix[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);




	
}



void DrawHuman(vec3 position, float tileSize, GLuint worldMatrixLocation, GLuint textureLocation)
{
	int probabilityCheck = rand() % 100; // Variable to help us adjust what numbers spawn more often and what numbers spawn less often. 
	int randomHumanFactor = 9; // The random factor which affects the scale of the building.// = rand() % 11; 
	int randomFactor = 6;
	if (probabilityCheck < 2) randomHumanFactor = 7; // less than 2% of buildings will be 15 units tall
	if (probabilityCheck >= 2 && probabilityCheck < 30) randomHumanFactor = rand() % 9; // around 28% of the city will be buildings that are between 3 to 5 units tall
	if (probabilityCheck >= 30 && probabilityCheck < 50) randomHumanFactor = rand() % 10; // around 20% of the city will be buildings that are between 4 to 6 units tall
	if (probabilityCheck >= 50) randomHumanFactor = rand() % 8; // Lastly, the remaining 50% of buildings will be about 1 to 2 units tall. 

	glBindVertexArray(cubeModelVAO);

	mat4 initialPosition = mat4(1.0);
	mat4 initialScale = mat4(1.0);
	mat4 initialRotation = mat4(1.0);



	// GLuint fabricsTexture
	// GLuint fabricsarmsTexture 
	// GLuint jeanslegTexture 

	vec3 finalPosition = vec3(position.x, position.y, position.z);

	// Chest
	glBindTexture(GL_TEXTURE_2D, fabricsTexture);
	glUniform1i(textureLocation, 1);



	mat4 BodyMatrix = initialPosition * translate(mat4(1.0f), vec3(position.x, position.y + 1.0, position.z)) * initialRotation
		* scale(mat4(1.0f), vec3(0.35, 0.5, 0.15)) * initialScale; //(0.5*(1+randomFactor))+scaleOffset

	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &BodyMatrix[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);


	// Arms 1 Left
	glBindTexture(GL_TEXTURE_2D, fabricsarmsTexture);
	glUniform1i(textureLocation, 1);

	mat4 armLeftWorldMatrix = BodyMatrix * translate(mat4(1.0f), vec3(0.65, -0.03, 0))
		* scale(mat4(1.0f), vec3(0.29, 1.03, 1.0)); //(0.5*(1+randomFactor))+scaleOffset

	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &armLeftWorldMatrix[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	// Arms 2 Right
	glBindTexture(GL_TEXTURE_2D, fabricsarmsTexture);
	glUniform1i(textureLocation, 1);

	mat4 armRightWorldMatrix = BodyMatrix * translate(mat4(1.0f), vec3(-0.65, -0.03, 0))
		* scale(mat4(1.0f), vec3(0.29, 1.03, 1.0)); //(0.5*(1+randomFactor))+scaleOffset

	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &armRightWorldMatrix[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	// Legs 1 Left
	glBindTexture(GL_TEXTURE_2D, jeanslegTexture);
	glUniform1i(textureLocation, 1);

	mat4 legLeftWorldMatrix = BodyMatrix * translate(mat4(1.0f), vec3(0.26, -1.02, 0)) *  rotate(mat4(1.0f), 3.14159f, vec3(1.0f, 0.0f, 0.0f))
		* scale(mat4(1.0f), vec3(0.43, 1.03, 1.0)); //(0.5*(1+randomFactor))+scaleOffset


	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &legLeftWorldMatrix[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	// Legs 2 Right
	glBindTexture(GL_TEXTURE_2D, jeanslegTexture);
	glUniform1i(textureLocation, 1);

	mat4 legRightWorldMatrix = BodyMatrix * translate(mat4(1.0f), vec3(-0.26, -1.02, 0)) * rotate(mat4(1.0f), 3.14159f, vec3(1.0f, 0.0f, 0.0f))
		* scale(mat4(1.0f), vec3(0.43, 1.03, 1.0)); //(0.5*(1+randomFactor))+scaleOffset

	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &legRightWorldMatrix[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);


	// Head
	glBindTexture(GL_TEXTURE_2D, frontTexture);
	glUniform1i(textureLocation, 1);

	mat4 headWorldMatrix = BodyMatrix *  translate(mat4(1.0f), vec3(0, 0.75, -0.05))
		* scale(mat4(1.0f), vec3(0.8, 0.5, 1.6)); //(0.5*(1+randomFactor))+scaleOffset

	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &headWorldMatrix[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);




}



void DrawSpaceTower(vec3 position, float tileSize, GLuint worldMatrixLocation, GLuint textureLocation)
{
	glBindVertexArray(cubeModelVAO);

	// Assign texture to the building
	glBindTexture(GL_TEXTURE_2D, towerTexture);
	glUniform1i(textureLocation, 1);

	vec3 finalPosition = vec3(position.x, position.y + 20.0f/ 2, position.z);

	mat4 tileWorldMatrix = translate(mat4(1.0f), finalPosition)
		* scale(mat4(1.0f), vec3(tileSize/2, 20.0f*tileSize, tileSize/2)); //(0.5*(1+randomFactor))+scaleOffset

	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &tileWorldMatrix[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);
}


