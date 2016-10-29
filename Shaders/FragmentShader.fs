#version 400

in vec2 			texCoord;
in vec3 			Color;
in float 		pctf;

out vec4 			outColor;

uniform sampler2D 	myTexture;


void main ()
{

	// finalColor = mix(tmpC, Color, pct);
	// vec4 t = vec4(tmpC, 1.0 - pct);
	// outColor = t * vec4(Color, pct);
	outColor = vec4(Color, pctf);

	// outColor = ( 1.0 - pct ) * texture(myTexture, texCoord) + pct * vec4(Color, 1.0);
	// if (is_texture == 1)
	// 	outColor = texture(myTexture, texCoord);
	// else if (is_texture == 0)
	// 	outColor = vec4(Color, 0.0);
}