#version 400

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;

out vec2 texCoord;
out vec3 Color;
out float pctf;

uniform mat4	modelMatrix;
uniform float   pct;

mat4 perspective(float angle_of_view, float aspect_ratio, float z_near, float z_far)
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
    pctf = pct;
    Color = color;
	vec4 eyepos = perspective(radians(45), 1920/1080, 0, 100)  * modelMatrix * vec4(position, 1.0);
	gl_Position = vec4(eyepos.xy, -eyepos.z, eyepos.w);
	texCoord = position.xy;
}