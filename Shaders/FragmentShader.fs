#version 400

in vec2 texCoord;
in vec3 Color;

out vec4 outColor;

uniform sampler2D myTexture;

void main ()
{
	//color = texture(myTexture, texCoord);
	outColor = vec4(Color, 1.0);
}