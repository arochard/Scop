#version 400

layout (location = 0) in vec3 VertexPosition;

uniform mat4	projectionMatrix;
uniform mat4	modelMatrix;
uniform mat4	viewMatrix;

//in vec3 VertexPosition;

mat4 perscpective(float angle_of_view, float aspect_ratio, float z_near, float z_far)
{
    return mat4(
        vec4(1.0/tan(angle_of_view),           0.0, 0.0, 0.0),
        vec4(0.0, aspect_ratio/tan(angle_of_view),  0.0, 0.0),
        vec4(0.0, 0.0,    (z_far+z_near)/(z_far-z_near), 1.0),
        vec4(0.0, 0.0, -2.0*z_far*z_near/(z_far-z_near), 0.0)
    );
}

void main ()
{
	//vec4 	eyepos;
	//gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(VertexPosition, 1.0);
	// eyepos = modelMatrix * vec4(VertexPosition, 1.0);
	//gl_Position = vec4(eyepos.xy, -eyepos.z, eyepos.w);
	//perscpective(radians(30.0), 1920/1080, 0.5, 10)
	gl_Position = projectionMatrix * modelMatrix * vec4(VertexPosition.x, VertexPosition.y, VertexPosition.z, 1.0);
}