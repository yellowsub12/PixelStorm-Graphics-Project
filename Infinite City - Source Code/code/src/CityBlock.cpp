#include "CityBlock.h"
#include <string>
#include <random>
#include <textures.h>


CityBlock::CityBlock(int size, int numTiles, vec3 location, GLuint texture)
{
	blockSize = size;
	numOfTiles = numTiles;
	blockLocation = location;
    mainTexture = texture;
}

void CityBlock::GenerateTiles()
{

}

void CityBlock::DrawBlock(GLuint shaderProgram, GLuint worldMatrixLocation)
{
    glActiveTexture(GL_TEXTURE0 + 1);
    GLuint textureLocation1 = glGetUniformLocation(shaderProgram, "actualTexture");
    glBindTexture(GL_TEXTURE_2D, mainTexture);
    glUniform1i(textureLocation1, 1);

    mat4 blockWorldMatrix = translate(mat4(1.0f), blockLocation)
        * scale(mat4(1.0f), vec3(blockSize, 1.0f, blockSize));
    glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &blockWorldMatrix[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 6);
}