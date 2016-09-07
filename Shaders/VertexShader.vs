#version 400

layout (location = 0) in vec3 VertexPosition;

uniform mat4	projectionMatrix;
uniform mat4	modelMatrix;
uniform mat4	viewMatrix;

//in vec3 VertexPosition;

void main ()
{
	//gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(VertexPosition, 1.0);
	gl_Position = modelMatrix * vec4(VertexPosition, 1.0);
}