#ifndef SCOP_H
# define SCOP_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "glew.h"
#include "glfw3.h"

#define ESCAPE 53

typedef struct	s_data
{
	char		*fileObj;
	char		*fileMtl;
	GLFWwindow	*win_ptr;
	GLuint		vbo;
	GLuint		vao;
	GLuint		vs;
	GLuint		fs;
	GLuint		shader_programme;
	float		*pointsTab;
	int			size_tab;
	const char*	vertex_shader;
	const char* fragment_shader;
	GLuint 		*arrays_f;
	GLsizei 	arrays_f_size;
}				t_data;


void			parserObj(t_data *data);
void			init_window(t_data *data);
void			loading_buffer(t_data *data);
void			draw(t_data *data);

#endif