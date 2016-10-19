#version 400

in vec2 texCoord;
out vec4 color;

uniform sampler2D myTexture;

void main ()
{
	color = texture(myTexture, texCoord);
}