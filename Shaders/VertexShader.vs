#version 400

layout (location = 0) in vec3 VertexPosition;

//uniform mat4	projectionMatrix;
uniform mat4	modelMatrix;

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
	gl_Position = perscpective(radians(30), 1920/1080, 0, 100)  * modelMatrix * vec4(VertexPosition, 1.0);
}