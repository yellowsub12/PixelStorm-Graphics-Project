#include "Model.h"
#include <iostream>
#include <textures.h>
#include <shapes.h>
#include <Camera.h>
#include <constants.hpp>

using namespace std;

string texturesPathPrefix = "assets/textures/";

GLuint cubeModelVAO = 0;
GLuint planeVAO = 0;

GLuint buildingTexture = 0;
GLuint buildingTexture2 = 0;
GLuint treeTexture = 0;
GLuint leavesTexture = 0;
GLuint grassTexture = 0;
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
GLuint frontTexture = 0;
GLuint trashTexture = 0;
GLuint trashbinTexture = 0;
GLuint phoneboothTexture = 0;
GLuint upperphoneboothTexture = 0;
GLuint busfrontTexture = 0;
GLuint busbackTexture = 0;
GLuint busbottomTexture = 0;
GLuint bustopTexture = 0;
GLuint busleftTexture = 0;
GLuint busrightTexture = 0;
GLuint wheelTexture = 0;
GLuint rimTexture = 0;
GLuint antennaTexture = 0;
GLuint antenna2Texture = 0;

GLuint cloth1Texture = 0;
GLuint cloth2Texture = 0;
GLuint cloth3Texture = 0;
GLuint cloth4Texture = 0;

unsigned int humanHeadTexture1;
unsigned int cubeBuildingTexture1;
unsigned int cubeBuildingTexture2;
unsigned int cubeBuildingTexture3;

vec3 playerPosition = vec3(0.0f);
bool isPlayerColliding = false;

vector<std::string> returnBuildingVector(int index)
{
	std::string sIndex = std::to_string(index);
	vector<std::string> buildingTextureVector = {
		texturesPathPrefix + "Buildings/right" + sIndex + ".png",
		texturesPathPrefix + "Buildings/left" + sIndex + ".png",
		texturesPathPrefix + "Buildings/top" + sIndex + ".png",
		texturesPathPrefix + "Buildings/bottom" + sIndex + ".png",
		texturesPathPrefix + "Buildings/front" + sIndex + ".png",
		texturesPathPrefix + "Buildings/back" + sIndex + ".png"
	};

	return buildingTextureVector;
}

void Initialize()
{
	vector<std::string> humanHead1{
		texturesPathPrefix + "HumanHead/right.png",
		texturesPathPrefix + "HumanHead/left.png",
		texturesPathPrefix + "HumanHead/top.png",
		texturesPathPrefix + "HumanHead/bottom.png",
		texturesPathPrefix + "HumanHead/front.png",
		texturesPathPrefix + "HumanHead/back.png"
	};


	humanHeadTexture1 = loadCubemap(humanHead1);
	cubeBuildingTexture1 = loadCubemap(returnBuildingVector(1));
	cubeBuildingTexture2 = loadCubemap(returnBuildingVector(2));
	cubeBuildingTexture3 = loadCubemap(returnBuildingVector(3));


	cubeModelVAO = createUnitCube(false);
	planeVAO = createUnitPlane();

	buildingTexture = loadTexture((texturesPathPrefix+"building.jpg").c_str());
	buildingTexture2 = loadTexture((texturesPathPrefix + "building2.jpg").c_str());
	treeTexture = loadTexture((texturesPathPrefix + "wood.jpg").c_str());
	leavesTexture = loadTexture((texturesPathPrefix + "leaves.png").c_str());
	grassTexture = loadTexture((texturesPathPrefix + "ground.png").c_str());
	soilTexture = loadTexture((texturesPathPrefix + "soil.jpg").c_str());
	benchTexture = loadTexture((texturesPathPrefix + "benchwood.png").c_str());
	ironTexture = loadTexture((texturesPathPrefix + "iron.jpg").c_str());
	fabricsTexture = loadTexture((texturesPathPrefix + "fabrics.png").c_str());
	fabricsarmsTexture = loadTexture((texturesPathPrefix + "fabricsarms.png").c_str());
	jeanslegTexture = loadTexture((texturesPathPrefix + "jeansleg.jpg").c_str());
	frontTexture = loadTexture((texturesPathPrefix + "front.png").c_str());
	trashTexture = loadTexture((texturesPathPrefix + "trash.jpg").c_str());
	trashbinTexture = loadTexture((texturesPathPrefix + "trashbin.jpg").c_str());
	phoneboothTexture = loadTexture((texturesPathPrefix + "phonebooth.jpg").c_str());
	upperphoneboothTexture = loadTexture((texturesPathPrefix + "upperphonebooth.jpg").c_str());
	busfrontTexture = loadTexture((texturesPathPrefix + "busfront.png").c_str());
	busbackTexture = loadTexture((texturesPathPrefix + "busback.png").c_str());
	bustopTexture = loadTexture((texturesPathPrefix + "bustop.png").c_str());
	busbottomTexture = loadTexture((texturesPathPrefix + "busbottom.jpg").c_str());
	busleftTexture = loadTexture((texturesPathPrefix + "busleft.png").c_str());
	busrightTexture = loadTexture((texturesPathPrefix + "busright.png").c_str());
	wheelTexture = loadTexture((texturesPathPrefix + "wheel.png").c_str());
	rimTexture = loadTexture((texturesPathPrefix + "rim.png").c_str());
	antennaTexture = loadTexture((texturesPathPrefix + "antenna.png").c_str());
	antenna2Texture = loadTexture((texturesPathPrefix + "antenna2.png").c_str());

	cloth1Texture = loadTexture((texturesPathPrefix + "cloth1.jpg").c_str());;
	cloth2Texture = loadTexture((texturesPathPrefix + "cloth2.jpg").c_str());;
	cloth3Texture = loadTexture((texturesPathPrefix + "cloth3.jpg").c_str());;
	cloth4Texture = loadTexture((texturesPathPrefix + "cloth4.jpg").c_str());;



	towerTexture = loadTexture((texturesPathPrefix + "SpaceTower.jpg").c_str());
	redTexture = loadTexture((texturesPathPrefix + "red.jpg").c_str());
	blackTexture = loadTexture((texturesPathPrefix + "black.jpg").c_str());
	whiteTexture = loadTexture((texturesPathPrefix + "white.jpg").c_str());
	headlightTexture = loadTexture((texturesPathPrefix + "headlight.jpg").c_str());
	glassTexture = loadTexture((texturesPathPrefix + "glass.jpg").c_str());
	tireTexture = loadTexture((texturesPathPrefix + "tire.jpg").c_str());

}

void Draw(vec3 position, float tileSize, int blockType, bool roadTile, int orientation, GLuint worldMatrixLocation, GLuint textureLocation, GLuint shaderProgram)
{
	if (blockType == 5)
	{
		DrawSpaceTower(position, tileSize, worldMatrixLocation, textureLocation);
	}
	else if (blockType == 4)
	{
		int random_integer;
		int lowest = 1, highest = 3;
		int range = (highest - lowest) + 1;
		random_integer = lowest + rand() % range;
		if (random_integer == 1) {
			//DrawPhonebooth(position, tileSize, worldMatrixLocation, textureLocation);
			DrawHuman(position, tileSize, worldMatrixLocation, textureLocation, shaderProgram);
		}
		if (random_integer == 2)
		{
			DrawBench(position, tileSize, worldMatrixLocation, textureLocation);
		}
		if (random_integer == 3)
		{
			DrawTree(position, tileSize, worldMatrixLocation, textureLocation);
		}
	}
	else 
	{
		int random_integer;
		int lowest = 1, highest = 2;
		int range = (highest - lowest) + 1;
		random_integer = lowest + rand() % range;
		if (roadTile)
		{
			if (random_integer == 2)
			{
				if (orientation != 0)
				{
					int r2 = rand() % 10;
					if (r2 <= 2)
						DrawCar(position, tileSize, orientation, worldMatrixLocation, textureLocation);
					else if (r2 <= 5)
						DrawBus(position, tileSize, orientation, worldMatrixLocation, textureLocation);
				}
			}
		}
		else
		{
			if (rand() % 5 <= 2)
				DrawTile(position, tileSize, blockType, worldMatrixLocation, textureLocation, shaderProgram);
			else
				DrawBuilding(position, tileSize, worldMatrixLocation, textureLocation, shaderProgram);
		}
		
	}
}

void DrawTile(vec3 position, float tileSize, int blockType, GLuint worldMatrixLocation, GLuint textureLocation, GLuint shaderProgram)
{
	glBindVertexArray(planeVAO);
	int r1 = rand() % 2;
	if(r1 == 0)
		glBindTexture(GL_TEXTURE_2D, soilTexture);
	else
		glBindTexture(GL_TEXTURE_2D, grassTexture);

	mat4 soilWorldMatrix = translate(mat4(1.0f), vec3(position.x, (position.y + 0.05 + 0.01*(r1)), position.z))
		* scale(mat4(1.0f), vec3(tileSize, 0.525, tileSize)); //(0.5*(1+randomFactor))+scaleOffset

	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &soilWorldMatrix[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindVertexArray(cubeModelVAO);

	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			
			vec3 finalPosition = vec3(position.x + i*(5+rand()%5), position.y, position.z + j * (5 + rand() % 5));
			int randomFactor = rand() % 18;
		
				if (randomFactor < 2)
					DrawHuman(finalPosition, tileSize, worldMatrixLocation, textureLocation, shaderProgram);
				else if (randomFactor >= 2  && randomFactor < 4)
					DrawTrashBin(finalPosition, tileSize, worldMatrixLocation, textureLocation);
				else if (randomFactor >= 4 && randomFactor <= 5)
					DrawBench(finalPosition, tileSize, worldMatrixLocation, textureLocation);
				else if (randomFactor > 5 && randomFactor < 9)
					DrawTree(finalPosition, tileSize, worldMatrixLocation, textureLocation);
				else if (randomFactor >= 9 && randomFactor < 11)
					DrawPhonebooth(finalPosition, tileSize, worldMatrixLocation, textureLocation);
				else if (randomFactor == 12)
					DrawLamp(finalPosition, tileSize, worldMatrixLocation, textureLocation);

		}
	}
}

void DrawBuilding(vec3 position, float tileSize, GLuint worldMatrixLocation, GLuint textureLocation, GLuint shaderProgram)
{
	int probabilityCheck = rand() % 100; // Variable to help us adjust what numbers spawn more often and what numbers spawn less often. 
	int randomFactor = 0; // The random factor which affects the scale of the building.// = rand() % 11; 
	if (probabilityCheck < 2) randomFactor = 15; // less than 2% of buildings will be 15 units tall
	if (probabilityCheck >= 2 && probabilityCheck < 30) randomFactor = 1 + rand() % 2; // around 28% of the city will be buildings that are between 3 to 5 units tall
	if (probabilityCheck >= 30 && probabilityCheck < 50) randomFactor = rand() % 2 + 2; // around 20% of the city will be buildings that are between 4 to 6 units tall
	if (probabilityCheck >= 50) randomFactor = rand() % 2 + 1; // Lastly, the remaining 50% of buildings will be about 1 to 2 units tall. 

	glBindVertexArray(cubeModelVAO);

	// Assign texture to the building
	glActiveTexture(GL_TEXTURE0 + 2);
	GLuint textureLocationCube = glGetUniformLocation(shaderProgram, "actualCubeTexture");

	int randomChoice = rand() % 5;
	if(randomChoice < 2)
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubeBuildingTexture1);
	else if (randomChoice < 4)
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubeBuildingTexture2);
	else if (randomChoice == 4)
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubeBuildingTexture3);
	
	glUniform1i(textureLocationCube, 2);

	glUniform1i(glGetUniformLocation(shaderProgram, "applyCubeTexture"), true);

	vec3 finalPosition = vec3(position.x, position.y + (randomFactor * tileSize) / 2, position.z);

	mat4 tileWorldMatrix = translate(mat4(1.0f), finalPosition)
		* scale(mat4(1.0f), vec3(tileSize, randomFactor*tileSize, tileSize)); //(0.5*(1+randomFactor))+scaleOffset

	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &tileWorldMatrix[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	glActiveTexture(GL_TEXTURE0 + 1);
	glUniform1i(glGetUniformLocation(shaderProgram, "applyCubeTexture"), false);

	CollisionCheck(finalPosition, vec3(tileSize, randomFactor * tileSize + 10, tileSize), worldMatrixLocation);
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

	int random_integer;
	int lowest = 1, highest = 8;
	int range = (highest - lowest) + 1;
	random_integer = lowest + rand() % range;

	// Assign texture to the building
	glBindTexture(GL_TEXTURE_2D, treeTexture);
	glUniform1i(textureLocation, 1);

	vec3 finalPosition = vec3(position.x, position.y + (0.1 * (3 + randomFactor)) / 2, position.z);

	mat4 tileWorldMatrix = translate(mat4(1.0f), finalPosition)
		* scale(mat4(1.0f), vec3(tileSize * 0.05, (0.1 * (5 + randomFactor)) * tileSize, tileSize * 0.05)); //(0.5*(1+randomFactor))+scaleOffset

	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &tileWorldMatrix[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	glBindTexture(GL_TEXTURE_2D, leavesTexture);
	mat4 leavesWorldMatrix = translate(mat4(1.0f), vec3(position.x, (position.y + (0.1 * (5 + randomFactor)) * tileSize / 2), position.z))
		* rotate(mat4(1.0f), 0.05f * sinf(2 * glfwGetTime()), vec3(0.0f, 1.0f, 0.0f))
		* scale(mat4(1.0f), vec3(tileSize * 0.2 + (0.05 * (randomFactor)), tileSize * 0.2 + (0.025 * (randomFactor)), tileSize * 0.2 + (0.05 * (randomFactor)))); //(0.5*(1+randomFactor))+scaleOffset

	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &leavesWorldMatrix[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	// Upper part
	glBindTexture(GL_TEXTURE_2D, leavesTexture);
	mat4 leavesUpperWorldMatrix = translate(mat4(1.0f), vec3(position.x, (position.y + (0.1 * (7 + randomFactor)) * tileSize / 2), position.z))
		* rotate(mat4(1.0f), 0.05f * sinf((2 * glfwGetTime()) + (3.14159f / 2)), vec3(0.0f, 1.0f, 0.0f))
		* scale(mat4(1.0f), vec3(tileSize * 0.15 + (0.05 * (randomFactor)), tileSize * 0.15 + (0.025 * (randomFactor)), tileSize * 0.15 + (0.05 * (randomFactor)))); //(0.5*(1+randomFactor))+scaleOffset

	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &leavesUpperWorldMatrix[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	if (random_integer >= 2) {
		// Upper upper part
		glBindTexture(GL_TEXTURE_2D, leavesTexture);
		mat4 leavesUpperUpperWorldMatrix = translate(mat4(1.0f), vec3(position.x, (position.y + (0.1 * (9 + randomFactor)) * tileSize / 2), position.z))
			* rotate(mat4(1.0f), 0.05f * sinf((2 * glfwGetTime()) + (3.14159f / 3)), vec3(0.0f, 1.0f, 0.0f))
			* scale(mat4(1.0f), vec3(tileSize * 0.075 + (0.05 * (randomFactor)), tileSize * 0.075 + (0.025 * (randomFactor)), tileSize * 0.075 + (0.05 * (randomFactor)))); //(0.5*(1+randomFactor))+scaleOffset

		glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &leavesUpperUpperWorldMatrix[0][0]);

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	if (random_integer >= 3) {
		// Lower part
		glBindTexture(GL_TEXTURE_2D, leavesTexture);
		mat4 leavesLowerWorldMatrix = translate(mat4(1.0f), vec3(position.x, (position.y + (0.1 * (3 + randomFactor)) * tileSize / 2), position.z))
			* rotate(mat4(1.0f), 0.05f * sinf((2 * glfwGetTime()) + (3.14159f / 2)), vec3(0.0f, 1.0f, 0.0f))
			* scale(mat4(1.0f), vec3(tileSize * 0.15 + (0.05 * (randomFactor)), tileSize * 0.16 + (0.025 * (randomFactor)), tileSize * 0.15 + (0.05 * (randomFactor)))); //(0.5*(1+randomFactor))+scaleOffset

		glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &leavesLowerWorldMatrix[0][0]);

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}


	if (random_integer >= 4) {
		glBindTexture(GL_TEXTURE_2D, leavesTexture);
		mat4 leavesMiddleWorldMatrix = translate(mat4(1.0f), vec3(position.x, (position.y + (0.1 * (5 + randomFactor)) * tileSize / 2), position.z))
			* rotate(mat4(1.0f), 0.05f * sinf((2 * glfwGetTime()) + (3.14159f / 2)), vec3(0.0f, 1.0f, 0.0f))
			* scale(mat4(1.0f), vec3(tileSize * 0.28 + (0.08 * (randomFactor)), tileSize * 0.10 + (0.012 * (randomFactor)), tileSize * 0.28 + (0.08 * (randomFactor)))); //(0.5*(1+randomFactor))+scaleOffset

		glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &leavesMiddleWorldMatrix[0][0]);

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	if (random_integer >= 5) {
		glBindTexture(GL_TEXTURE_2D, leavesTexture);
		mat4 leavesCornerWorldMatrix = translate(mat4(1.0f), vec3(position.x + 2.0, (position.y + (0.1 * (8 + randomFactor)) * tileSize / 2), position.z + 0.5))
			* rotate(mat4(1.0f), 0.05f * sinf((2 * glfwGetTime()) + (3.14159f / 2)), vec3(0.0f, 1.0f, 0.0f))
			* scale(mat4(1.0f), vec3(tileSize * 0.13 + (0.012 * (randomFactor)), tileSize * 0.13 + (0.012 * (randomFactor)), tileSize * 0.13 + (0.012 * (randomFactor)))); //(0.5*(1+randomFactor))+scaleOffset

		glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &leavesCornerWorldMatrix[0][0]);

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	if (random_integer >= 6) {
		glBindTexture(GL_TEXTURE_2D, leavesTexture);
		mat4 leaveslowerCornerWorldMatrix = translate(mat4(1.0f), vec3(position.x - 2.0, (position.y + (0.1 * (3 + randomFactor)) * tileSize / 2), position.z - 0.5))
			* rotate(mat4(1.0f), 0.05f * sinf((2 * glfwGetTime()) + (3.14159f / 2)), vec3(0.0f, 1.0f, 0.0f))
			* scale(mat4(1.0f), vec3(tileSize * 0.11 + (0.012 * (randomFactor)), tileSize * 0.11 + (0.010 * (randomFactor)), tileSize * 0.11 + (0.012 * (randomFactor)))); //(0.5*(1+randomFactor))+scaleOffset

		glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &leaveslowerCornerWorldMatrix[0][0]);

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}


	if (random_integer >= 7) {
		glBindTexture(GL_TEXTURE_2D, leavesTexture);
		mat4 leavesSideMiddleWorldMatrix = translate(mat4(1.0f), vec3(position.x, (position.y + (0.1 * (5 + randomFactor)) * tileSize / 2), position.z + 2))
			* rotate(mat4(1.0f), 0.05f * sinf((2 * glfwGetTime()) + (3.14159f / 2)), vec3(0.0f, 1.0f, 0.0f))
			* scale(mat4(1.0f), vec3(tileSize * 0.2 + (0.08 * (randomFactor)), tileSize * 0.09 + (0.012 * (randomFactor)), tileSize * 0.2 + (0.08 * (randomFactor)))); //(0.5*(1+randomFactor))+scaleOffset

		glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &leavesSideMiddleWorldMatrix[0][0]);

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	CollisionCheck(finalPosition, vec3(tileSize * 0.05, (0.1 * (5 + randomFactor)) * tileSize, tileSize * 0.05), 0);



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

	CollisionCheck(vec3(position.x, (position.y - 2.0f), position.z), vec3(randomBenchFactor, 4.0, 2.0), 0);

	// Assign texture to the iron
	glBindTexture(GL_TEXTURE_2D, ironTexture);
	glUniform1i(textureLocation, 1);

	mat4 benchLegWorldMatrix = translate(mat4(1.0f), vec3(position.x, (position.y + 0.25), position.z))
		* scale(mat4(1.0f), vec3(randomBenchFactor * 0.9, 0.5, 1.5)); //(0.5*(1+randomFactor))+scaleOffset

	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &benchLegWorldMatrix[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);


}

void DrawTrashBin(vec3 position, float tileSize, GLuint worldMatrixLocation, GLuint textureLocation)
{
	int probabilityCheck = rand() % 100; // Variable to help us adjust what numbers spawn more often and what numbers spawn less often. 
	int randomTrashFactor = 0; // The random factor which affects the scale of the building.// = rand() % 11; 
	if (probabilityCheck < 2) randomTrashFactor = 3 + 3; // less than 2% of buildings will be 15 units tall
	if (probabilityCheck >= 2 && probabilityCheck < 30) randomTrashFactor = rand() % 4 + 3; // around 28% of the city will be buildings that are between 3 to 5 units tall
	if (probabilityCheck >= 30 && probabilityCheck < 50) randomTrashFactor = rand() % 5 + 3; // around 20% of the city will be buildings that are between 4 to 6 units tall
	if (probabilityCheck >= 50) randomTrashFactor = rand() % 4 + 3; // Lastly, the remaining 50% of buildings will be about 1 to 2 units tall. 

	glBindVertexArray(cubeModelVAO);

	// Assign texture to the bench
	glBindTexture(GL_TEXTURE_2D, trashbinTexture);
	glUniform1i(textureLocation, 1);

	vec3 finalPosition = vec3(position.x, position.y, position.z);

	mat4 trashWorldMatrix = translate(mat4(1.0f), vec3(position.x, position.y+(1.25/2), position.z))
		* scale(mat4(1.0f), vec3(1.1, 1.5, 1.1)); //(0.5*(1+randomFactor))+scaleOffset

	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &trashWorldMatrix[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	

	// Assign texture to the iron
	glBindTexture(GL_TEXTURE_2D, trashTexture);
	glUniform1i(textureLocation, 1);

	mat4 trashBinWorldMatrix = translate(mat4(1.0f), vec3(position.x, (position.y + 0.75), position.z))
		* scale(mat4(1.0f), vec3(1.0, 1.5, 1.0)); //(0.5*(1+randomFactor))+scaleOffset

	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &trashBinWorldMatrix[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	CollisionCheck(vec3(position.x, (position.y), position.z), vec3(1.0, 3.0, 1.0), 0);

}


void DrawPhonebooth(vec3 position, float tileSize, GLuint worldMatrixLocation, GLuint textureLocation)
{
	int probabilityCheck = rand() % 100; // Variable to help us adjust what numbers spawn more often and what numbers spawn less often. 
	int randomTrashFactor = 0; // The random factor which affects the scale of the building.// = rand() % 11; 
	if (probabilityCheck < 2) randomTrashFactor = 3 + 3; // less than 2% of buildings will be 15 units tall
	if (probabilityCheck >= 2 && probabilityCheck < 30) randomTrashFactor = rand() % 4 + 3; // around 28% of the city will be buildings that are between 3 to 5 units tall
	if (probabilityCheck >= 30 && probabilityCheck < 50) randomTrashFactor = rand() % 5 + 3; // around 20% of the city will be buildings that are between 4 to 6 units tall
	if (probabilityCheck >= 50) randomTrashFactor = rand() % 4 + 3; // Lastly, the remaining 50% of buildings will be about 1 to 2 units tall. 

	glBindVertexArray(cubeModelVAO);


	glBindTexture(GL_TEXTURE_2D, phoneboothTexture);
	glUniform1i(textureLocation, 1);

	vec3 finalPosition = vec3(position.x, position.y, position.z);

	mat4 phoneboothWorldMatrix = translate(mat4(1.0f), vec3(position.x, position.y+1.75, position.z)) * rotate(mat4(1.0f), 3.14159f, vec3(1.0f, 0.0f, 0.0f))
		* scale(mat4(1.0f), vec3(1.5, 3.5, 1.5)); //(0.5*(1+randomFactor))+scaleOffset

	CollisionCheck(vec3(position.x, position.y, position.z), vec3(1.5, 4.0, 1.5), 0);

	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &phoneboothWorldMatrix[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);






	glBindTexture(GL_TEXTURE_2D, upperphoneboothTexture);
	glUniform1i(textureLocation, 1);

	mat4 upperphoneboothWorldMatrix = translate(mat4(1.0f), vec3(position.x, (position.y + 3.5 + (0.3/2)), position.z)) * rotate(mat4(1.0f), 3.14159f, vec3(1.0f, 0.0f, 0.0f))
		* scale(mat4(1.0f), vec3(1.35, 0.3, 1.35)); //(0.5*(1+randomFactor))+scaleOffset

	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &upperphoneboothWorldMatrix[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);





}



void DrawHuman(vec3 position, float tileSize, GLuint worldMatrixLocation, GLuint textureLocation, GLuint shaderProgram)
{
	double randomHumanFactor;
	double lowest = 2, highest = 4;
	int range = (highest - lowest) + 1;
	randomHumanFactor = lowest + rand() % range;

	glBindVertexArray(cubeModelVAO);

	mat4 initialPosition = mat4(1.0);
	mat4 initialScale = mat4(1.0);
	mat4 initialRotation = mat4(1.0);


	vec3 finalPosition = vec3(position.x, position.y, position.z);



	// Chest
	switch (rand() % 5)
	{
	case 0:glBindTexture(GL_TEXTURE_2D, fabricsTexture); break;
	case 1:glBindTexture(GL_TEXTURE_2D, cloth1Texture); break;
	case 2:glBindTexture(GL_TEXTURE_2D, cloth2Texture); break;
	case 3:glBindTexture(GL_TEXTURE_2D, cloth3Texture); break;
	case 4:glBindTexture(GL_TEXTURE_2D, cloth4Texture); break;
	}
	glUniform1i(textureLocation, 1);

	int r1 = rand() % 4;

	initialRotation = rotate(mat4(1.0f), 1.5708f * (-1 + r1), vec3(0.0f, 1.0f, 0.0f));

	mat4 BodyMatrix = initialPosition * translate(mat4(1.0f), vec3(position.x, randomHumanFactor * 0.8 * 0.6 , position.z)) * initialRotation
		* scale(mat4(1.0f), vec3(0.35 * randomHumanFactor * 0.6, 0.5 * randomHumanFactor * 0.6, 0.15 * randomHumanFactor * 0.6)) * initialScale; //(0.5*(1+randomFactor))+scaleOffset

	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &BodyMatrix[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);


	// Arms 1 Left
	switch (rand() % 5)
	{
	case 0:glBindTexture(GL_TEXTURE_2D, fabricsTexture); break;
	case 1:glBindTexture(GL_TEXTURE_2D, cloth1Texture); break;
	case 2:glBindTexture(GL_TEXTURE_2D, cloth2Texture); break;
	case 3:glBindTexture(GL_TEXTURE_2D, cloth3Texture); break;
	case 4:glBindTexture(GL_TEXTURE_2D, cloth4Texture); break;
	}
	glUniform1i(textureLocation, 1);

	mat4 armLeftWorldMatrix = BodyMatrix * translate(mat4(1.0f), vec3(0.65, -0.03*sinf(2*glfwGetTime()), 0))
		* scale(mat4(1.0f), vec3(0.29, 1.03, 1.0)); //(0.5*(1+randomFactor))+scaleOffset

	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &armLeftWorldMatrix[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	// Arms 2 Right

	mat4 armRightWorldMatrix = BodyMatrix * translate(mat4(1.0f), vec3(-0.65, -0.03 * sinf(2 * glfwGetTime()), 0))
		* scale(mat4(1.0f), vec3(0.29, 1.03, 1.0)); //(0.5*(1+randomFactor))+scaleOffset

	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &armRightWorldMatrix[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	// Legs 1 Left
	switch (rand() % 5)
	{
	case 0:glBindTexture(GL_TEXTURE_2D, fabricsTexture); break;
	case 1:glBindTexture(GL_TEXTURE_2D, cloth1Texture); break;
	case 2:glBindTexture(GL_TEXTURE_2D, cloth2Texture); break;
	case 3:glBindTexture(GL_TEXTURE_2D, cloth3Texture); break;
	case 4:glBindTexture(GL_TEXTURE_2D, cloth4Texture); break;
	}
	glUniform1i(textureLocation, 1);

	mat4 legLeftWorldMatrix = BodyMatrix * translate(mat4(1.0f), vec3(0.26, -1.02, 0)) * rotate(mat4(1.0f), 3.14159f, vec3(1.0f, 0.0f, 0.0f))
		* scale(mat4(1.0f), vec3(0.43, 1.03, 1.0)); //(0.5*(1+randomFactor))+scaleOffset


	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &legLeftWorldMatrix[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	// Legs 2 Right

	mat4 legRightWorldMatrix = BodyMatrix * translate(mat4(1.0f), vec3(-0.26, -1.02, 0)) * rotate(mat4(1.0f), 3.14159f, vec3(1.0f, 0.0f, 0.0f))
		* scale(mat4(1.0f), vec3(0.43, 1.03, 1.0)); //(0.5*(1+randomFactor))+scaleOffset

	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &legRightWorldMatrix[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);


	// Head
	glActiveTexture(GL_TEXTURE0 + 2);
	GLuint textureLocationCube = glGetUniformLocation(shaderProgram, "actualCubeTexture");
	glBindTexture(GL_TEXTURE_CUBE_MAP, humanHeadTexture1);
	glUniform1i(textureLocationCube, 2);

	glUniform1i(glGetUniformLocation(shaderProgram, "applyCubeTexture"), true);

	mat4 headRotation = mat4(1.0f);

	//if (rand() % 2 == 0)
		headRotation = rotate(mat4(1.0f), 0.2f * sinf((rand() % 3) * glfwGetTime()), vec3(0.0f, 1.0f, 0.0f));

	mat4 headWorldMatrix = BodyMatrix * translate(mat4(1.0f), vec3(0, 0.75, -0.05))
		* scale(mat4(1.0f), vec3(0.8, 0.5, 1.6))
		* headRotation;//(0.5*(1+randomFactor))+scaleOffset


	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &headWorldMatrix[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	glActiveTexture(GL_TEXTURE0 + 1);
	glUniform1i(glGetUniformLocation(shaderProgram, "applyCubeTexture"), false);

	CollisionCheck(vec3(position.x, position.y, position.z), vec3(0.35, 2.0, 0.35) * 2.5f, 0);

}










void DrawBus(vec3 position, float tileSize, int orientation, GLuint worldMatrixLocation, GLuint textureLocation)
{
	if (orientation == 0 || orientation == -1) return;
	int probabilityCheck = rand() % 100; // Variable to help us adjust what numbers spawn more often and what numbers spawn less often. 
	int randomBusFactor = 9; // The random factor which affects the scale of the building.// = rand() % 11; 
	if (probabilityCheck < 2) randomBusFactor = 7; // less than 2% of buildings will be 15 units tall
	if (probabilityCheck >= 2 && probabilityCheck < 30) randomBusFactor = rand() % 9; // around 28% of the city will be buildings that are between 3 to 5 units tall
	if (probabilityCheck >= 30 && probabilityCheck < 50) randomBusFactor = rand() % 10; // around 20% of the city will be buildings that are between 4 to 6 units tall
	if (probabilityCheck >= 50) randomBusFactor = rand() % 8; // Lastly, the remaining 50% of buildings will be about 1 to 2 units tall. 

	glBindVertexArray(cubeModelVAO);

	mat4 initialPosition = mat4(1.0);
	mat4 initialScale = mat4(1.0);
	mat4 initialRotation = mat4(1.0);
	float xPosOffset = 0.0f;
	float yPosOffset = 0.0f;
	float zPosOffset = 0.0f;
	float rotation = 0.0f;


	/*GLuint busfrontTexture = 0;
	GLuint busbackTexture = 0;
	GLuint busbottomTexture = 0;
	GLuint bustopTexture = 0;
	GLuint busleftTexture = 0;
	GLuint busrightTexture = 0;*/


	vec3 finalPosition = vec3(position.x, position.y, position.z);

	mat4 carBase = mat4(1.0f);

	if (orientation == 1)
	{
		if (rand() % 1 == 0)
		{
			zPosOffset = 10.0f;
			rotation = 1.5708f;
		}
		else
		{
			zPosOffset = -10.0f;
			rotation = -1.5708f;
		}

	}

	// Front
	glBindTexture(GL_TEXTURE_2D, busfrontTexture);
	glUniform1i(textureLocation, 1);

	if (orientation == 1)
		initialRotation = rotate(mat4(1.0f), rotation, vec3(0.0f, 10.0f, 0.0f));

	mat4 frontBodyMatrix = initialPosition * translate(mat4(1.0f), vec3(position.x+xPosOffset, position.y + 3 + yPosOffset, position.z -6 + zPosOffset ))
		* rotate(mat4(1.0f), 3.14159f, vec3(1.0f, 0.0f, 0.0f))
		* initialRotation
		* scale(mat4(1.0f), vec3(5, 5,  0.2)) * initialScale; //(0.5*(1+randomFactor))+scaleOffset

	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &frontBodyMatrix[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	// Back 
	glBindTexture(GL_TEXTURE_2D, busbackTexture);
	glUniform1i(textureLocation, 1);

	mat4 busbackWorldMatrix = frontBodyMatrix * translate(mat4(1.0f), vec3(0, 0, -130 ))
		* scale(mat4(1.0f), vec3(1, 1, 1)); //(0.5*(1+randomFactor))+scaleOffset

	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &busbackWorldMatrix[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	// Top
	glBindTexture(GL_TEXTURE_2D, bustopTexture);
	glUniform1i(textureLocation, 1);

	mat4 bustopWorldMatrix = frontBodyMatrix * translate(mat4(1.0f), vec3(0, -0.5, -65))
		* scale(mat4(1.0f), vec3(1, 0.001, 131.0)); //(0.5*(1+randomFactor))+scaleOffset

	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &bustopWorldMatrix[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	// Bottom
	glBindTexture(GL_TEXTURE_2D, busbottomTexture);
	glUniform1i(textureLocation, 1);

	mat4 busbottomWorldMatrix = frontBodyMatrix * translate(mat4(1.0f), vec3(0, 0.5, -65))
		* scale(mat4(1.0f), vec3(1, 0.001, 131.0)); //(0.5*(1+randomFactor))+scaleOffset


	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &busbottomWorldMatrix[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	// Left
	glBindTexture(GL_TEXTURE_2D, busleftTexture);
	glUniform1i(textureLocation, 1);

	mat4 busleftWorldMatrix = frontBodyMatrix * translate(mat4(1.0f), vec3(-0.5, 0, -65)) 
		* scale(mat4(1.0f), vec3(0.001, 1, 131)); //(0.5*(1+randomFactor))+scaleOffset

	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &busleftWorldMatrix[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);


	// Right
	glBindTexture(GL_TEXTURE_2D, busrightTexture);
	glUniform1i(textureLocation, 1);

	mat4 busrightWorldMatrix = frontBodyMatrix * translate(mat4(1.0f), vec3(0.5, 0, -65))
		* scale(mat4(1.0f), vec3(0.001, 1, 131)); //(0.5*(1+randomFactor))+scaleOffset

	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &busrightWorldMatrix[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	// Wheel 1 

	glBindTexture(GL_TEXTURE_2D, wheelTexture);
	glUniform1i(textureLocation, 1);

	mat4 wheel1WorldMatrix = frontBodyMatrix * translate(mat4(1.0f), vec3(-0.505, 0.41, -28.5))
		* scale(mat4(1.0f), vec3(0.07, 0.30, 11.0)); //(0.5*(1+randomFactor))+scaleOffset

	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &wheel1WorldMatrix[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);


	// Wheel 2 

	glBindTexture(GL_TEXTURE_2D, wheelTexture);
	glUniform1i(textureLocation, 1);

	mat4 wheel2WorldMatrix = frontBodyMatrix * translate(mat4(1.0f), vec3(-0.505, 0.41, -94.5))
		* scale(mat4(1.0f), vec3(0.07, 0.30, 11.0)); //(0.5*(1+randomFactor))+scaleOffset

	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &wheel2WorldMatrix[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	// Wheel 3

	glBindTexture(GL_TEXTURE_2D, wheelTexture);
	glUniform1i(textureLocation, 1);

	mat4 wheel3WorldMatrix = frontBodyMatrix * translate(mat4(1.0f), vec3(0.505, 0.41, -28.5))
		* scale(mat4(1.0f), vec3(0.07, 0.30, 11.0)); //(0.5*(1+randomFactor))+scaleOffset

	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &wheel3WorldMatrix[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);


	// Wheel 4 

	glBindTexture(GL_TEXTURE_2D, wheelTexture);
	glUniform1i(textureLocation, 1);

	mat4 wheel4WorldMatrix = frontBodyMatrix * translate(mat4(1.0f), vec3(0.505, 0.41, -94.5))
		* scale(mat4(1.0f), vec3(0.07, 0.30, 11.0)); //(0.5*(1+randomFactor))+scaleOffset

	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &wheel4WorldMatrix[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	// rim 1 

	glBindTexture(GL_TEXTURE_2D, rimTexture);
	glUniform1i(textureLocation, 1);

	mat4 rim1WorldMatrix = frontBodyMatrix * translate(mat4(1.0f), vec3(-0.522, 0.41, -28.5))
		* scale(mat4(1.0f), vec3(0.04, 0.298, 10.9)); //(0.5*(1+randomFactor))+scaleOffset

	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &rim1WorldMatrix[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);


	// rim 2 

	glBindTexture(GL_TEXTURE_2D, rimTexture);
	glUniform1i(textureLocation, 1);

	mat4 rim2WorldMatrix = frontBodyMatrix * translate(mat4(1.0f), vec3(-0.522, 0.41, -94.5))
		* scale(mat4(1.0f), vec3(0.04, 0.298, 10.9)); //(0.5*(1+randomFactor))+scaleOffset

	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &rim2WorldMatrix[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	// rim 3

	glBindTexture(GL_TEXTURE_2D, rimTexture);
	glUniform1i(textureLocation, 1);

	mat4 rim3WorldMatrix = frontBodyMatrix * translate(mat4(1.0f), vec3(0.522, 0.41, -28.5))
		* scale(mat4(1.0f), vec3(0.04, 0.298, 10.9)); //(0.5*(1+randomFactor))+scaleOffset

	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &rim3WorldMatrix[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);


	// rim 4 

	glBindTexture(GL_TEXTURE_2D, rimTexture);
	glUniform1i(textureLocation, 1);

	mat4 rim4WorldMatrix = frontBodyMatrix * translate(mat4(1.0f), vec3(0.522, 0.41, -94.5))
		* scale(mat4(1.0f), vec3(0.04, 0.298, 10.9)); //(0.5*(1+randomFactor))+scaleOffset

	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &rim4WorldMatrix[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	// Antenna 

	glBindTexture(GL_TEXTURE_2D, antennaTexture);
	glUniform1i(textureLocation, 1);

	mat4 antennaWorldMatrix = frontBodyMatrix * translate(mat4(1.0f), vec3(0.35, -0.7, -110.5))
		* scale(mat4(1.0f), vec3(0.025, 0.38, 0.9)); //(0.5*(1+randomFactor))+scaleOffset

	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &antennaWorldMatrix[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	// Antenna 2

	glBindTexture(GL_TEXTURE_2D, antenna2Texture);
	glUniform1i(textureLocation, 1);

	mat4 antenna2WorldMatrix = frontBodyMatrix * translate(mat4(1.0f), vec3(0.42, -0.6, -110.5))
		* scale(mat4(1.0f), vec3(0.025, 0.33, 0.9)); //(0.5*(1+randomFactor))+scaleOffset

	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &antenna2WorldMatrix[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	
	CollisionCheck(vec3(position.x - 13.5, position.y, position.z - 6 + zPosOffset), vec3(26, 5, 5), 0);
	

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

	CollisionCheck(finalPosition, vec3(tileSize / 2, 20.0f * tileSize, tileSize / 2), 0);
}


void DrawCar(vec3 position, float tileSize, int orientation, GLuint worldMatrixLocation, GLuint textureLocation)
{
	if (orientation == 0) return;
	int probabilityCheck = rand() % 100; // Variable to help us adjust what numbers spawn more often and what numbers spawn less often. 
	int randomFactor = 0; // The random factor which affects the scale of the building.// = rand() % 11; 
	if (probabilityCheck < 2) randomFactor = 9; // less than 2% of buildings will be 15 units tall
	if (probabilityCheck >= 2 && probabilityCheck < 30) randomFactor = rand() % 7; // around 28% of the city will be buildings that are between 3 to 5 units tall
	if (probabilityCheck >= 30 && probabilityCheck < 50) randomFactor = rand() % 6; // around 20% of the city will be buildings that are between 4 to 6 units tall
	if (probabilityCheck >= 50) randomFactor = rand() % 5; // Lastly, the remaining 50% of buildings will be about 1 to 2 units tall. 

	glBindVertexArray(cubeModelVAO);

	// Assign texture to the car body
	switch (rand() % 5)
	{
	case 0:glBindTexture(GL_TEXTURE_2D, redTexture); break;
	case 1:glBindTexture(GL_TEXTURE_2D, blackTexture); break;
	case 2:glBindTexture(GL_TEXTURE_2D, cloth2Texture); break;
	case 3:glBindTexture(GL_TEXTURE_2D, cloth3Texture); break;
	case 4:glBindTexture(GL_TEXTURE_2D, cloth4Texture); break;
	}
	glUniform1i(textureLocation, 1);

	vec3 finalPosition = vec3(position.x, position.y + (1.0f), position.z);

	mat4 carBase = mat4(1.0f);

	//Car Base
	if (orientation == 1)
	{
		if (rand() % 1 == 0)
		{
			finalPosition.z += 7.5f;	
			carBase = translate(mat4(1.0f), finalPosition)
				* scale(mat4(1.0f), vec3(tileSize / 4, 2, tileSize / 9));
		}
		else
		{
			finalPosition.z -= 7.5f;
			mat4 rotation = rotate(mat4(1.0f), -3.14159f, vec3(0.0f, 1.0f, 0.0f));

			carBase = translate(mat4(1.0f), finalPosition)
				* scale(mat4(1.0f), vec3(tileSize / 4, 2, tileSize / 9))
				* rotation;
		}	
		
	}
	else if (orientation == -1)
	{
		if (rand() % 1 == 0)
		{
			finalPosition.x += 7.5f;
			mat4 rotation = rotate(mat4(1.0f), 1.5708f, vec3(0.0f, 1.0f, 0.0f));

			carBase = translate(mat4(1.0f), finalPosition)
				* scale(mat4(1.0f), vec3(tileSize / 9, 2, tileSize / 4))
				* rotation;
		}
		else
		{
			finalPosition.x -= 7.5f;
			mat4 rotation = rotate(mat4(1.0f), -1.5708f, vec3(0.0f, 1.0f, 0.0f));

			carBase = translate(mat4(1.0f), finalPosition)
				* scale(mat4(1.0f), vec3(tileSize / 9, 2, tileSize / 4))
				* rotation;
		}
	}
	

	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &carBase[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36); // 36 vertices, starting at index 0

	glBindTexture(GL_TEXTURE_2D, blackTexture);

	//Car Hood
	mat4 carHood = carBase * translate(mat4(1.0f), vec3(-0.15f, 1.4f, 0.0f)) * scale(mat4(1.0f), vec3(0.6f, 0.2f, 1.0f));
	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &carHood[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36); // 36 vertices, starting at index 0

	glBindTexture(GL_TEXTURE_2D, whiteTexture);

	//Wheel rim front
	mat4 wheels = carBase * translate(mat4(1.0f), vec3(0.35f, -0.40f, 0.0f)) * scale(mat4(1.0f), vec3(0.1f, 0.4f, 1.12f));
	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &wheels[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36); // 36 vertices, starting at index 0

	//Wheel rim back
	wheels = carBase * translate(mat4(1.0f), vec3(-0.35f, -0.40f, 0.0f)) * scale(mat4(1.0f), vec3(0.1f, 0.4f, 1.12f));
	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &wheels[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36); // 36 vertices, starting at index 0

	//Mirrors
	wheels = carBase * translate(mat4(1.0f), vec3(0.1f, 0.25f, 0.0f)) * scale(mat4(1.0f), vec3(0.1f, 0.4f, 1.2f));
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
	 wheels = carBase * translate(mat4(1.0f), vec3(0.35f, -0.45f, 0.0f)) * scale(mat4(1.0f), vec3(0.2f, 1.0f, 1.1f));
	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &wheels[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36); // 36 vertices, starting at index 0

	//Wheel back
	wheels = carBase * translate(mat4(1.0f), vec3(-0.35f, -0.45f, 0.0f)) * scale(mat4(1.0f), vec3(0.2f, 1.0f, 1.1f));
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

	vec3 collisionPos = vec3(finalPosition.x, finalPosition.y - 3.0f, finalPosition.z);

	if (orientation == -1)
		CollisionCheck(collisionPos, vec3(tileSize / 9, 10, tileSize / 4), worldMatrixLocation);
	else			   
		CollisionCheck(collisionPos, vec3(tileSize / 4, 10, tileSize / 9), worldMatrixLocation);
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
		* scale(mat4(1.0f), vec3(tileSize / 16, 26.4f, tileSize / 16));
	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &lampBase[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	CollisionCheck(finalPosition, vec3(tileSize / 16, 26.4f, tileSize / 16), 0);

	//Lamp Hat
	mat4 lampHat = lampBase * translate(mat4(1.0f), vec3(0.0f, 0.5f, 0.0f)) * scale(mat4(1.0f), vec3(3.0f, 0.02f, 3.0f));
	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &lampHat[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	//Lamp pike
	lampHat = lampBase * translate(mat4(1.0f), vec3(0.0f, 0.55f, 0.0f)) * scale(mat4(1.0f), vec3(0.5f, 0.08f, 0.5f));
	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &lampHat[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	//Lamp pike 2
	lampHat = lampBase * translate(mat4(1.0f), vec3(0.0f, 0.44f, 0.0f)) * scale(mat4(1.0f), vec3(2.5f, 0.01f, 2.5f));
	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &lampHat[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	glBindTexture(GL_TEXTURE_2D, headlightTexture);

	//Lamp Hood
	mat4 lampHood = lampBase * translate(mat4(1.0f), vec3(0.0f, 0.48f, 0.0f)) * scale(mat4(1.0f), vec3(2.0f, 0.058f, 2.0f));
	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &lampHood[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);



	

}


void CollisionCheck(vec3 position, vec3 scale, GLuint worldMatrixLocation)
{
	bool checkX, checkZ, checkY;
	float collisionOffset = 1.0f;
	vec3 futureCamPosition = Camera::position + Camera::movementVector;
	vec3 checkVector = vec3(futureCamPosition.x, futureCamPosition.y - 5.0f, futureCamPosition.z);
	checkX = checkVector.x < (position.x + (scale.x) / 2 + collisionOffset) && checkVector.x > (position.x - (scale.x) / 2 - collisionOffset);
	checkY = checkVector.y < (position.y + (scale.y) / 2 + collisionOffset) && checkVector.y > (position.y - (scale.y) / 2 - collisionOffset);
	checkZ = checkVector.z < (position.z + (scale.z) / 2 + collisionOffset) && checkVector.z > (position.z - (scale.z) / 2 - collisionOffset);

	//mat4 lampHood = translate(mat4(1.0f), position) * glm::scale(mat4(1.0f), scale);
	//glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &lampHood[0][0]);
	//
	//glDrawArrays(GL_TRIANGLES, 0, 36);

	if (checkX && checkY && checkZ)
	{
		Camera::cameraCollisionLocation = position;
		Camera::cameraCollisionScale = scale * 0.5f;
		Camera::isColliding = true;
	}
}