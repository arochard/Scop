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
	// location = glGetUniformLocation(data->shader_programme, "viewMatrix");
	// if (!location)
	// 	glUniformMatrix4fv(location, 1, GL_FALSE, g_viewMatrix);
}


void _print_shader_info_log(GLuint shader_index) {
  int max_length = 2048;
  int actual_length = 0;
  char shader_log[2048];
  glGetShaderInfoLog(shader_index, max_length, &actual_length, shader_log);
  printf("shader info log for GL index %u:\n%s\n", shader_index, shader_log);
}

void			loading_buffer(t_data *data)
{
	GLuint 		location;
	int			floatSize = 4;
	int 		posAttrib;
	int			colAttrib;
	GLintptr	color_pos;


	data->vs = glCreateShader (GL_VERTEX_SHADER);
	glShaderSource (data->vs, 1, &(data->vertex_shader), NULL);
	glCompileShader (data->vs);
	data->fs = glCreateShader (GL_FRAGMENT_SHADER);
	glShaderSource (data->fs, 1, &(data->fragment_shader), NULL);
	glCompileShader (data->fs);
	//temp
	int params = -1;
	GLuint shader_index = data->fs;
	glGetShaderiv(shader_index, GL_COMPILE_STATUS, &params);
	if (GL_TRUE != params)
	{
		fprintf(stderr, "ERROR: GL shader index %i did not compile\n", shader_index);
		_print_shader_info_log(shader_index);
	}

	data->shader_programme = glCreateProgram ();
	glAttachShader (data->shader_programme, data->fs);
	glAttachShader (data->shader_programme, data->vs);
	glDeleteShader(data->vs);
	glDeleteShader(data->fs);
	glLinkProgram (data->shader_programme);
	glUseProgram (data->shader_programme);



	glGenVertexArrays (1, &(data->vao));
	glBindVertexArray (data->vao);

	glGenBuffers(1, &(data->vbo));
	glBindBuffer (GL_ARRAY_BUFFER, data->vbo);
	glBufferData (GL_ARRAY_BUFFER, data->size_tab_indice * sizeof (GLfloat), data->final_buffer_tab, GL_STATIC_DRAW);



	posAttrib = glGetAttribLocation(data->shader_programme, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 6 * floatSize, 0);

	colAttrib = glGetAttribLocation(data->shader_programme, "color");
	glEnableVertexAttribArray(colAttrib);
	color_pos = 3 * floatSize;
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 6 * floatSize, (GLvoid*)color_pos);

	//glBindVertexArray(0);





	data->texture = load_bmp("/Users/arochard/goinfre/scop/texture/pony"); //changer chemin en relatif
	location = glGetUniformLocation(data->shader_programme, "myTexture");
	if (!location)
		glUniform1i(location, data->texture);
	//glEnable(GL_CULL_FACE);
	// glEnable(GL_DEPTH_TEST);
	// glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	//glCullFace(GL_FRONT);
	//glFrontFace(GL_CCW);
}

void			draw(t_data *data)
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.9, 0.9, 0.9, 1.0);
	glViewport (0, 0, data->width, data->height);
	glfwSetKeyCallback(data->win_ptr, key_callback);
	glfwPollEvents ();
	glBindVertexArray (data->vao);
	glDrawArrays(GL_TRIANGLES, 0, data->size_tab_indice / 6);

	// check OpenGL error
    for(GLenum err; (err = glGetError()) != GL_NO_ERROR;)
	{
	  printf("%u\n", err);
	}

	glBindVertexArray(0);
	sendMatrix(data);
	glfwSwapBuffers(data->win_ptr);
}