#version 420 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aUV;

uniform mat4 worldMatrix;
uniform mat4 worldOrientationMatrix = mat4(1.0);
uniform mat4 viewMatrix = mat4(1.0);
uniform mat4 projectionMatrix = mat4(1.0);
uniform mat4 lightViewProjMatrix;
uniform vec4 customColor = vec4(1.0);
uniform int uvMultiplier;


out vec3 fragmentNormal;
out vec3 fragmentPosition;
out vec4 fragmentPositionLightSpace;

out vec4 vertexColor;
out vec3 vertexPosition;
out vec3 uv;

void main()
{
	vertexColor = customColor;
	vertexPosition = aPos;
	uv = aUV * uvMultiplier;
	
	mat4 modelViewProjection = projectionMatrix * viewMatrix * worldOrientationMatrix * worldMatrix;
	mat4 mvp = worldMatrix;
	
	fragmentNormal = mat3(mvp) * aNormal;
	fragmentPosition = vec3(mvp * vec4(aPos, 1.0));
	fragmentPositionLightSpace =  lightViewProjMatrix * vec4(fragmentPosition, 1.0);
	
	gl_Position = modelViewProjection * vec4(aPos, 1.0);
}