#version 420 core
out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube skyboxDay;
uniform samplerCube skyboxNight;

uniform float time;

void main()
{   

	FragColor = texture(skyboxDay, TexCoords)* time 
	+ texture(skyboxNight, TexCoords) * (1.0f - time);
}