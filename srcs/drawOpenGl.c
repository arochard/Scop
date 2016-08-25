#include "../includes/scop.h"

void			loading_buffer(t_data *data)
{
	float 		points[] = {
		0.0f,  0.5f,  0.0f, 
		0.5f, -0.5f,  0.0f, 
		-0.5f, -0.5f,  0.0f
	};

	glGenBuffers(1, &data->vbo);
	glBindBuffer (GL_ARRAY_BUFFER, data->vbo);
	glBufferData (GL_ARRAY_BUFFER, 9 * sizeof (float), points, GL_STATIC_DRAW);

	glGenVertexArrays (1, &data->vao);
	glBindVertexArray (data->vao);
	glEnableVertexAttribArray (0);
	glBindBuffer (GL_ARRAY_BUFFER, data->vbo);
	glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	data->vertex_shader =
		"#version 400\n"
		"in vec3 vp;"
		"void main () {"
		"  gl_Position = vec4 (vp, 1.0);"
		"}";

	data->fragment_shader =
		"#version 400\n"
		"out vec4 frag_colour;"
		"void main () {"
		"  frag_colour = vec4 (0.5, 0.0, 0.5, 1.0);"
		"}";

	data->vs = glCreateShader (GL_VERTEX_SHADER);
	glShaderSource (data->vs, 1, &data->vertex_shader, NULL);
	glCompileShader (data->vs);
	data->fs = glCreateShader (GL_FRAGMENT_SHADER);
	glShaderSource (data->fs, 1, &data->fragment_shader, NULL);
	glCompileShader (data->fs);

	data->shader_programme = glCreateProgram ();
	glAttachShader (data->shader_programme, data->fs);
	glAttachShader (data->shader_programme, data->vs);
	glLinkProgram (data->shader_programme);
}

void			draw(t_data *data)
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram (data->shader_programme);
	glBindVertexArray (data->vao);
	// draw points 0-3 from the currently bound VAO with current in-use shader
	glDrawArrays (GL_TRIANGLES, 0, 3);
	// update other events like input handling 
	// put the stuff we've been drawing onto the display
	mlx_opengl_swap_buffers(data->ptr_win);
}