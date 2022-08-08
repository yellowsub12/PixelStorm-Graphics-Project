#version 420 core
layout (location = 0) in vec3 position;

uniform mat4 lightViewProjMatrix;
uniform mat4 worldMatrix;

void main()
{
    mat4 scaleBiasMatrix = mat4(vec4(0.5, 0.0, 0.0, 0.0),
                                    vec4(0.0, 0.5, 0.0, 0.0),
                                    vec4(0.0, 0.0, 0.5, 0.0),
                                    vec4(0.5, 0.5, 0.5, 1.0));
    gl_Position = 
					scaleBiasMatrix * // bias the depth map coordinates
                    lightViewProjMatrix * worldMatrix * vec4(position, 1.0);
}