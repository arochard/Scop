#version 400

in vec2 			texCoord;
in vec3 			Color;

out vec4 			outColor;

uniform sampler2D 	myTexture;
uniform float   	bend;


void main ()
{
	vec3 finalColor = mix(Color, texture(myTexture, texCoord).rgb, bend);
	outColor = vec4(finalColor, 1.0);
}