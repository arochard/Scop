#version 400

layout (location = 0) in vec3 VertexPosition;

uniform mat4	projectionMatrix;
uniform mat4	viewMatrix;
uniform mat4	modelMatrix;

void main ()
{
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(VertexPosition, 1.0);
}