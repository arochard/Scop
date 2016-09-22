#include "../includes/scop.h"

static void		sendMatrix(t_data *data)
{
	GLuint		location;
	static double		angle = 0.0;

	g_modelMatrix[0] = cos(angle);
	g_modelMatrix[8] = -sin(angle);
	g_modelMatrix[2] = sin(angle);
	g_modelMatrix[10] = cos(angle);
	angle += 0.02;
	location = glGetUniformLocation(data->shader_programme, "modelMatrix");
	if (!location)
		glUniformMatrix4fv(location, 1, GL_FALSE, g_modelMatrix);
	location = glGetUniformLocation(data->shader_programme, "viewMatrix");
	if (!location)
		glUniformMatrix4fv(location, 1, GL_FALSE, g_viewMatrix);
	// location = glGetUniformLocation(data->shader_programme, "projectionMatrix");
	// if (!location)
	// 	glUniformMatrix4fv(location, 1, GL_FALSE, g_projectionMatrix);
}

void			loading_buffer(t_data *data)
{
	int i = 0;
	while (data->vertex_tab[i])
	{
		printf("%f\n", data->vertex_tab[i]);
		i++;
	}

	glGenVertexArrays (1, &(data->vao));
	glBindVertexArray (data->vao);

	glGenBuffers(1, &(data->vbo));
	glBindBuffer (GL_ARRAY_BUFFER, data->vbo);
	glBufferData (GL_ARRAY_BUFFER, data->size_tab_vertex * sizeof (float), data->vertex_tab, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableClientState(GL_VERTEX_ARRAY);

	glGenBuffers(1, &(data->indice_buffer));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, data->indice_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data->size_tab_indice * sizeof(GLushort), data->indice_tab, GL_STATIC_DRAW);


	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	data->vs = glCreateShader (GL_VERTEX_SHADER);
	glShaderSource (data->vs, 1, &(data->vertex_shader), NULL);
	glCompileShader (data->vs);

	data->fs = glCreateShader (GL_FRAGMENT_SHADER);
	glShaderSource (data->fs, 1, &(data->fragment_shader), NULL);
	glCompileShader (data->fs);

	data->shader_programme = glCreateProgram ();
	glAttachShader (data->shader_programme, data->fs);
	glAttachShader (data->shader_programme, data->vs);
	glLinkProgram (data->shader_programme);
}

void			draw(t_data *data)
{
	//int size;
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram (data->shader_programme);
	sendMatrix(data);

	//glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);

	glfwSetKeyCallback(data->win_ptr, key_callback);
	// update other events like input handling
	glfwPollEvents ();

	glBindVertexArray (data->vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, data->indice_buffer);
	glDrawElements(GL_TRIANGLES, data->size_tab_indice, GL_UNSIGNED_SHORT, (void*)0);
	//sendMatrix(data);
	// put the stuff we've been drawing onto the display
	glfwSwapBuffers(data->win_ptr);
}