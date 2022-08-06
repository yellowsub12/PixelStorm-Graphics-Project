#include "Model.h"
#include <iostream>
#include <textures.h>
#include <shapes.h>

using namespace std;

string texturesPathPrefix = "assets/textures/";

GLuint cubeModelVAO = 0;
GLuint planeVAO = 0;

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
GLuint redTexture = 0;
GLuint blackTexture = 0;
GLuint whiteTexture = 0;
GLuint headlightTexture = 0;
GLuint glassTexture = 0;
GLuint tireTexture = 0;


void Initialize()
{
	cubeModelVAO = createUnitCube(false);
	planeVAO = createUnitPlane();

	buildingTexture = loadTexture((texturesPathPrefix+"building.jpg").c_str());
	treeTexture = loadTexture((texturesPathPrefix + "wood.jpg").c_str());
	leavesTexture = loadTexture((texturesPathPrefix + "leaves.png").c_str());
	soilTexture = loadTexture((texturesPathPrefix + "soil.jpg").c_str());
	benchTexture = loadTexture((texturesPathPrefix + "benchwood.png").c_str());
	ironTexture = loadTexture((texturesPathPrefix + "iron.jpg").c_str());
	fabricsTexture = loadTexture((texturesPathPrefix + "fabrics.png").c_str());
	fabricsarmsTexture = loadTexture((texturesPathPrefix + "fabricsarms.png").c_str());
	jeanslegTexture = loadTexture((texturesPathPrefix + "jeansleg.jpg").c_str());
	towerTexture = loadTexture((texturesPathPrefix + "SpaceTower.jpg").c_str());
	redTexture = loadTexture((texturesPathPrefix + "red.jpg").c_str());
	blackTexture = loadTexture((texturesPathPrefix + "black.jpg").c_str());
	whiteTexture = loadTexture((texturesPathPrefix + "white.jpg").c_str());
	headlightTexture = loadTexture((texturesPathPrefix + "headlight.jpg").c_str());
	glassTexture = loadTexture((texturesPathPrefix + "glass.jpg").c_str());
	tireTexture = loadTexture((texturesPathPrefix + "tire.jpg").c_str());
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
			DrawTree(position, tileSize, worldMatrixLocation, textureLocation);
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
			DrawTree(position, tileSize, worldMatrixLocation, textureLocation);
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

	glBindVertexArray(planeVAO);

	glBindTexture(GL_TEXTURE_2D, soilTexture);
	mat4 soilWorldMatrix = translate(mat4(1.0f), vec3(position.x, (position.y+0.05), position.z))
		* scale(mat4(1.0f), vec3(tileSize, 0.525 , tileSize)); //(0.5*(1+randomFactor))+scaleOffset

	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &soilWorldMatrix[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 6);

 }


void DrawBench(vec3 position, float tileSize, GLuint worldMatrixLocation, GLuint textureLocation)
{
	int probabilityCheck = rand() % 100; // Variable to help us adjust what numbers spawn more often and what numbers spawn less often. 
	int randomBenchFactor = 9; // The random factor which affects the scale of the building.// = rand() % 11; 
	if (probabilityCheck < 2) randomBenchFactor = 7; // less than 2% of buildings will be 15 units tall
	if (probabilityCheck >= 2 && probabilityCheck < 30) randomBenchFactor = rand() % 9; // around 28% of the city will be buildings that are between 3 to 5 units tall
	if (probabilityCheck >= 30 && probabilityCheck < 50) randomBenchFactor = rand() % 10; // around 20% of the city will be buildings that are between 4 to 6 units tall
	if (probabilityCheck >= 50) randomBenchFactor = rand() % 8; // Lastly, the remaining 50% of buildings will be about 1 to 2 units tall. 

	glBindVertexArray(cubeModelVAO);

	// Assign texture to the building
	glBindTexture(GL_TEXTURE_2D, benchTexture);
	glUniform1i(textureLocation, 1);

	vec3 finalPosition = vec3(position.x, position.y + 0.075, position.z);

	mat4 benchWorldMatrix = translate(mat4(1.0f), vec3(position.x, (position.y + 0.5), position.z))
		* scale(mat4(1.0f), vec3(tileSize * 0.09 + (0.05 * (randomBenchFactor)), 0.025 + (0.0025 * (randomBenchFactor * tileSize)), tileSize * 0.075 )); //(0.5*(1+randomFactor))+scaleOffset

	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &benchWorldMatrix[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	// Assign texture to the building
	glBindTexture(GL_TEXTURE_2D, ironTexture);
	glUniform1i(textureLocation, 1);

	mat4 benchLegWorldMatrix = translate(mat4(1.0f), vec3(position.x, (position.y + 0.04 + (0.005 * (randomBenchFactor)/2)), position.z))
		* scale(mat4(1.0f), vec3(tileSize * 0.06 + (0.05 * (randomBenchFactor)), (0.05 +(0.005 * (randomBenchFactor * tileSize))), tileSize * 0.06)); //(0.5*(1+randomFactor))+scaleOffset

	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &benchLegWorldMatrix[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);




	
}



void DrawHuman(vec3 position, float tileSize, GLuint worldMatrixLocation, GLuint textureLocation)
{
	int probabilityCheck = rand() % 100; // Variable to help us adjust what numbers spawn more often and what numbers spawn less often. 
	int randomBenchFactor = 9; // The random factor which affects the scale of the building.// = rand() % 11; 
	int randomFactor = 0;
	if (probabilityCheck < 2) randomBenchFactor = 7; // less than 2% of buildings will be 15 units tall
	if (probabilityCheck >= 2 && probabilityCheck < 30) randomBenchFactor = rand() % 9; // around 28% of the city will be buildings that are between 3 to 5 units tall
	if (probabilityCheck >= 30 && probabilityCheck < 50) randomBenchFactor = rand() % 10; // around 20% of the city will be buildings that are between 4 to 6 units tall
	if (probabilityCheck >= 50) randomBenchFactor = rand() % 8; // Lastly, the remaining 50% of buildings will be about 1 to 2 units tall. 

	glBindVertexArray(cubeModelVAO);


	// GLuint fabricsTexture
	// GLuint fabricsarmsTexture 
	// GLuint jeanslegTexture 

	vec3 finalPosition = vec3(position.x, position.y + 0.075, position.z);

	// Chest
	glBindTexture(GL_TEXTURE_2D, fabricsTexture);
	glUniform1i(textureLocation, 1);

	mat4 chestWorldMatrix = translate(mat4(1.0f), vec3(position.x, (position.y + 0.04 + (0.005 * (randomFactor) / 2)), position.z))
		* scale(mat4(1.0f), vec3(tileSize * 0.06 + (0.05 * (randomBenchFactor)), 0.05 + (0.005 * (randomBenchFactor)), tileSize * 0.06)); //(0.5*(1+randomFactor))+scaleOffset

	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &chestWorldMatrix[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);


	// Arms 1 Left
	glBindTexture(GL_TEXTURE_2D, fabricsarmsTexture);
	glUniform1i(textureLocation, 1);

	mat4 armLeftWorldMatrix = translate(mat4(1.0f), vec3(position.x, (position.y + 0.04 + (0.005 * (randomBenchFactor) / 2)), position.z))
		* scale(mat4(1.0f), vec3(tileSize * 0.06 + (0.05 * (randomBenchFactor)), 0.05 + (0.005 * (randomBenchFactor)), tileSize * 0.06)); //(0.5*(1+randomFactor))+scaleOffset

	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &armLeftWorldMatrix[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	// Arms 2 Right
	glBindTexture(GL_TEXTURE_2D, fabricsarmsTexture);
	glUniform1i(textureLocation, 1);

	mat4 armRightWorldMatrix = translate(mat4(1.0f), vec3(position.x, (position.y + 0.04 + (0.005 * (randomBenchFactor) / 2)), position.z))
		* scale(mat4(1.0f), vec3(tileSize * 0.06 + (0.05 * (randomBenchFactor)), 0.05 + (0.005 * (randomBenchFactor)), tileSize * 0.06)); //(0.5*(1+randomFactor))+scaleOffset

	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &armRightWorldMatrix[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	// Legs 1 Left
	glBindTexture(GL_TEXTURE_2D, jeanslegTexture);
	glUniform1i(textureLocation, 1);

	mat4 legLeftWorldMatrix = translate(mat4(1.0f), vec3(position.x, (position.y + 0.04 + (0.005 * (randomBenchFactor) / 2)), position.z))
		* scale(mat4(1.0f), vec3(tileSize * 0.06 + (0.05 * (randomBenchFactor)), 0.05 + (0.005 * (randomBenchFactor)), tileSize * 0.06)); //(0.5*(1+randomFactor))+scaleOffset

	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &legLeftWorldMatrix[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	// Legs 2 Right
	glBindTexture(GL_TEXTURE_2D, jeanslegTexture);
	glUniform1i(textureLocation, 1);

	mat4 legRightWorldMatrix = translate(mat4(1.0f), vec3(position.x, (position.y + 0.04 + (0.005 * (randomBenchFactor) / 2)), position.z))
		* scale(mat4(1.0f), vec3(tileSize * 0.06 + (0.05 * (randomBenchFactor)), 0.05 + (0.005 * (randomBenchFactor)), tileSize * 0.06)); //(0.5*(1+randomFactor))+scaleOffset

	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &legRightWorldMatrix[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);



	/*vec3 finalPosition = vec3(position.x, position.y + 0.075, position.z);*/

	//mat4 benchWorldMatrix = translate(mat4(1.0f), vec3(position.x, (position.y + 0.09), position.z))
	//	* scale(mat4(1.0f), vec3(tileSize * 0.09 + (0.05 * (randomBenchFactor)), 0.025 + (0.0025 * (randomBenchFactor)), tileSize * 0.075)); //(0.5*(1+randomFactor))+scaleOffset

	//glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &benchWorldMatrix[0][0]);

	//glDrawArrays(GL_TRIANGLES, 0, 36);

	//// Assign texture to the building
	//glBindTexture(GL_TEXTURE_2D, ironTexture);
	//glUniform1i(textureLocation, 1);


	//mat4 benchLegWorldMatrix = translate(mat4(1.0f), vec3(position.x, (position.y + 0.04 + (0.005 * (randomBenchFactor) / 2)), position.z))
	//	* scale(mat4(1.0f), vec3(tileSize * 0.06 + (0.05 * (randomBenchFactor)), 0.05 + (0.005 * (randomBenchFactor)), tileSize * 0.06)); //(0.5*(1+randomFactor))+scaleOffset

	//glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &benchLegWorldMatrix[0][0]);

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
		* scale(mat4(1.0f), vec3(tileSize/2, 20.0f*tileSize, tileSize/2)); //(0.5*(1+randomFactor))+scaleOffset

	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &tileWorldMatrix[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);
}


void DrawCar(vec3 position, float tileSize, GLuint worldMatrixLocation, GLuint textureLocation)
{
	int probabilityCheck = rand() % 100; // Variable to help us adjust what numbers spawn more often and what numbers spawn less often. 
	int randomFactor = 0; // The random factor which affects the scale of the building.// = rand() % 11; 
	if (probabilityCheck < 2) randomFactor = 9; // less than 2% of buildings will be 15 units tall
	if (probabilityCheck >= 2 && probabilityCheck < 30) randomFactor = rand() % 7; // around 28% of the city will be buildings that are between 3 to 5 units tall
	if (probabilityCheck >= 30 && probabilityCheck < 50) randomFactor = rand() % 6; // around 20% of the city will be buildings that are between 4 to 6 units tall
	if (probabilityCheck >= 50) randomFactor = rand() % 5; // Lastly, the remaining 50% of buildings will be about 1 to 2 units tall. 

	glBindVertexArray(cubeModelVAO);

	// Assign texture to the car body
	glBindTexture(GL_TEXTURE_2D, redTexture);
	glUniform1i(textureLocation, 1);

	vec3 finalPosition = vec3(position.x, position.y + (0.1 * (1 + randomFactor)) / 2, position.z);

	//Car Base
	mat4 carBase = translate(mat4(1.0f), finalPosition) 
		* scale(mat4(1.0f), vec3(tileSize / 2, 0.25f, tileSize / 3));
	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &carBase[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36); // 36 vertices, starting at index 0

	glBindTexture(GL_TEXTURE_2D, blackTexture);

	//Car Hood
	mat4 carHood = carBase * translate(mat4(1.0f), vec3(-0.15f, 1.4f, 0.0f)) * scale(mat4(1.0f), vec3(0.6f, 0.2f, 1.0f));
	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &carHood[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36); // 36 vertices, starting at index 0

	glBindTexture(GL_TEXTURE_2D, whiteTexture);

	//Wheel rim front
	mat4 wheels = carBase * translate(mat4(1.0f), vec3(0.35f, 0.06f, 0.0f)) * scale(mat4(1.0f), vec3(0.1f, 0.4f, 1.12f));
	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &wheels[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36); // 36 vertices, starting at index 0

	//Wheel rim back
	wheels = carBase * translate(mat4(1.0f), vec3(-0.35f, 0.06f, 0.0f)) * scale(mat4(1.0f), vec3(0.1f, 0.4f, 1.12f));
	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &wheels[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36); // 36 vertices, starting at index 0

	//Mirrors
	wheels = carBase * translate(mat4(1.0f), vec3(0.1f, 0.22f, 0.0f)) * scale(mat4(1.0f), vec3(0.1f, 0.4f, 1.2f));
	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &wheels[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36); // 36 vertices, starting at index 0

	//strip R
	wheels = carBase * translate(mat4(1.0f), vec3(0.35f, 0.35f, 0.2f)) * scale(mat4(1.0f), vec3(0.25f, 0.4f, 0.1f));
	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &wheels[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36); // 36 vertices, starting at index 0

	//strip L
	wheels = carBase * translate(mat4(1.0f), vec3(0.35f, 0.35f, -0.2f)) * scale(mat4(1.0f), vec3(0.25f, 0.4f, 0.1f));
	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &wheels[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36); // 36 vertices, starting at index 0

	glBindTexture(GL_TEXTURE_2D, headlightTexture);

	//Headlights R
	wheels = carBase * translate(mat4(1.0f), vec3(0.48f, 0.2f, 0.35f)) * scale(mat4(1.0f), vec3(0.1f, 0.4f, 0.15f));
	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &wheels[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36); // 36 vertices, starting at index 0

	//Headlights L
	wheels = carBase * translate(mat4(1.0f), vec3(0.48f, 0.2f, -0.35f)) * scale(mat4(1.0f), vec3(0.1f, 0.4f, 0.15f));
	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &wheels[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36); // 36 vertices, starting at index 0

	glBindTexture(GL_TEXTURE_2D, glassTexture);

	//SkateBase3
	 carHood = carBase * translate(mat4(1.0f), vec3(-0.15f, 0.9f, 0.0f)) * scale(mat4(1.0f), vec3(0.6f, 0.8f, 1.0f));
	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &carHood[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36); // 36 vertices, starting at index 0
	
	glBindTexture(GL_TEXTURE_2D, tireTexture);

	//Wheel front
	 wheels = carBase * translate(mat4(1.0f), vec3(0.35f, -0.05f, 0.0f)) * scale(mat4(1.0f), vec3(0.2f, 1.0f, 1.1f));
	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &wheels[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36); // 36 vertices, starting at index 0

	//Wheel back
	wheels = carBase * translate(mat4(1.0f), vec3(-0.35f, -0.05f, 0.0f)) * scale(mat4(1.0f), vec3(0.2f, 1.0f, 1.1f));
	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &wheels[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36); // 36 vertices, starting at index 0

	glBindTexture(GL_TEXTURE_2D, blackTexture);

	//rim up
	wheels = carBase * translate(mat4(1.0f), vec3(0.47f, 0.16f, 0.0f)) * scale(mat4(1.0f), vec3(0.1f, 0.15f, 0.5f));
	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &wheels[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36); // 36 vertices, starting at index 0

	//rim down
	wheels = carBase * translate(mat4(1.0f), vec3(0.47f, -0.2f, 0.0f)) * scale(mat4(1.0f), vec3(0.1f, 0.1f, 0.5f));
	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &wheels[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36); // 36 vertices, starting at index 0
}

void DrawLamp(vec3 position, float tileSize, GLuint worldMatrixLocation, GLuint textureLocation)
{

	int probabilityCheck = rand() % 100; // Variable to help us adjust what numbers spawn more often and what numbers spawn less often. 
	int randomFactor = 0; // The random factor which affects the scale of the building.// = rand() % 11; 
	if (probabilityCheck < 2) randomFactor = 9; // less than 2% of buildings will be 15 units tall
	if (probabilityCheck >= 2 && probabilityCheck < 30) randomFactor = rand() % 7; // around 28% of the city will be buildings that are between 3 to 5 units tall
	if (probabilityCheck >= 30 && probabilityCheck < 50) randomFactor = rand() % 6; // around 20% of the city will be buildings that are between 4 to 6 units tall
	if (probabilityCheck >= 50) randomFactor = rand() % 5; // Lastly, the remaining 50% of buildings will be about 1 to 2 units tall. 

	glBindVertexArray(cubeModelVAO);

	vec3 finalPosition = vec3(position.x, position.y + (0.1 * (1 + randomFactor)) / 2, position.z);

	// Assign texture to the building
	glBindTexture(GL_TEXTURE_2D, blackTexture);
	glUniform1i(textureLocation, 1);

	//Lamp Base
	mat4 lampBase = translate(mat4(1.0f), finalPosition)
		* scale(mat4(1.0f), vec3(tileSize / 12, 3.4f, tileSize / 12));
	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &lampBase[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	glBindTexture(GL_TEXTURE_2D, headlightTexture);

	//Lamp Hood
	mat4 carHood = lampBase * translate(mat4(1.0f), vec3(0.0f, 0.45f, 0.0f)) * scale(mat4(1.0f), vec3(3.0f, 0.15f, 3.0f));
	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &carHood[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);

}