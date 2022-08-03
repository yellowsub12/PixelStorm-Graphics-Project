#include "CityBlock.h"
#include <string>
#include <random>
#include <textures.h>
#include <shapes.h>


CityBlock::CityBlock(int type, int size, int numTilesRows, vec3 location, GLuint texture, int seed)
{
	blockSize = size;
	numOfTileRows = numTilesRows;
	blockLocation = location;
    mainTexture = texture;
    cubeVAO = createUnitCube(false);
    blockSeed = seed;
    blockType = type;
}

void CityBlock::GenerateTiles(GLuint worldMatrixLocation, GLuint textureLocation, GLuint buildingTexture)
{
    // This is a work in progress method for drawing objects on each tile. (Sam and Ali can take a look at it)
    // As of now, this method renders only buildings on top of the blocks and nothing else. But this should and will be expanded later on. 

    if (blockType == 4) return; // Do not draw anything if the block texture is the grass texture

    // Seed the generator again with a unique seed for each block, such that every block is unique in terms of what is on it. 
    srand(blockSeed + (blockLocation.x * blockLocation.z * 100)); 

    glBindVertexArray(cubeVAO); // Bind the cube VAO to be used for drawing
    float tileSize = blockSize/4; // horizontal size of each building

    // Assign texture to the building
    glBindTexture(GL_TEXTURE_2D, buildingTexture);
    glUniform1i(textureLocation, 1);
    
    // Nested for loop to generate the buildings on the block  in the format of a 3x3 board.
    // This for loop works by considering each block as a 2d square grid in the format of 3x3, 4x4, etc. 
    for (int i = 0; i < numOfTileRows; i++)
    {
        for (int j = 0; j < numOfTileRows; j++)
        {
            //if (rand() % 11 > 5) continue;
           
            // The following if-statements will ensure that no building is actually placed on the roads. 
            // Buildings will only be placed on the part of the block that has no road and only has empty dark gray space. 
            if (blockType == 0)
            {
                if (i == 1) continue;
            }
            else if (blockType == 1)
            {
                if (j == 1)
                    if (i == 0 || i == 1)
                        continue;
                if (i == 1 && j == 0) continue;
            }
            else if (blockType == 2)
            {
                if (i == 1 || j == 1) continue;          
            }
            else if (blockType == 3)
            {
                if (j == 1) continue;
                if (i == 1 && j == 0) continue;
            }

            // Adjusting the probability of getting certain numbers from the random generator
            // We don't necessarily want the random numbers to be too close to each other all the time. 
            // We want some variety but we also want to ensure certain numbers repeat more often than others, and certain numbers are rarer than others. 
            // For example, let's say a building in the city can be between 1 and 10 units tall.
            // Since it's inaccurate/unrealistic for most buildings in a city to be super tall skyscrapers, 
            // we need to ensure only about 10% of the building are 10 units tall. Similarly, we need to ensure about 50% of the buildings 
            // in the city are between 3-6 units tall.

            // We do this by adjusting probabilities of certain numbers spawning. We change how frequently a certain number is generated by the random 
            // number generator. 

            int probabilityCheck = rand() % 100; // Variable to help us adjust what numbers spawn more often and what numbers spawn less often. 
            int randomFactor = 0; // The random factor which affects the scale of the building.// = rand() % 11; 
            if (probabilityCheck < 2) randomFactor = 15; // less than 2% of buildings will be 15 units tall
            if (probabilityCheck >= 2 && probabilityCheck < 30) randomFactor = rand() % 5 + 3; // around 28% of the city will be buildings that are between 3 to 5 units tall
            if (probabilityCheck >= 30 && probabilityCheck < 50) randomFactor = rand() % 6 + 4; // around 20% of the city will be buildings that are between 4 to 6 units tall
            if(probabilityCheck >= 50) randomFactor = rand() % 2; // Lastly, the remaining 50% of buildings will be about 1 to 2 units tall. 

            // Calculating position of new object on the blocks (building, tree, whatever)
            vec3 position = vec3(blockLocation.x + (1 - i) * (blockSize / 2.5), 
               blockLocation.y + (0.5*(1+randomFactor)) / 2.0f,
               blockLocation.z + (1 - j) * (blockSize / 2.5));

            // Assigning the world matrix for this tile using the calculated location above. 
            mat4 tileWorldMatrix = translate(mat4(1.0f), position)
                * scale(mat4(1.0f), vec3(tileSize, (0.5 * (1 + randomFactor)), tileSize)); //(0.5*(1+randomFactor))+scaleOffset

            glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &tileWorldMatrix[0][0]);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
    }
}

void CityBlock::DrawBlock(GLuint shaderProgram, GLuint worldMatrixLocation, GLuint textureLocation, GLuint buildingTexture)
{
    // Set the texture of the block plane
    glActiveTexture(GL_TEXTURE0 + 1);
    glBindTexture(GL_TEXTURE_2D, mainTexture);
    glUniform1i(textureLocation, 1);

    // Set world matrix for the block plane
    mat4 blockWorldMatrix = translate(mat4(1.0f), blockLocation)
        * scale(mat4(1.0f), vec3(blockSize, 1.0f, blockSize));
    glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &blockWorldMatrix[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 6);

    // Call the method that will populate this block with stuff on it, such as buildings, tree, cars, etc (in progress)
    GenerateTiles(worldMatrixLocation, textureLocation, buildingTexture);
}