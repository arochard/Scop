#version 400

layout (location = 0) in vec3 VertexPosition;

uniform mat4	projectionMatrix;
uniform mat4	modelMatrix;
uniform mat4	viewMatrix;

//in vec3 VertexPosition;

void main ()
{
	//vec4 	eyepos;
	//gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(VertexPosition, 1.0);
	// eyepos = modelMatrix * vec4(VertexPosition, 1.0);
	//gl_Position = vec4(eyepos.xy, -eyepos.z, eyepos.w);
	gl_Position = modelMatrix * vec4(VertexPosition, 1.0);
}