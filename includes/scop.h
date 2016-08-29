#ifndef SCOP_H
# define SCOP_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <OpenGL/gl3.h>
#include "../minilibix/mlx.h"
#include "../minilibix/mlx_opengl.h"

#define ESCAPE 53

typedef struct	s_data
{
	char		*fileObj;
	char		*fileMtl;
	void		*ptr_mlx;
	void		*ptr_win;
	GLuint		vbo;
	GLuint		vao;
	GLuint		vs;
	GLuint		fs;
	GLuint		shader_programme;
	float		*pointsTab;
	const char*	vertex_shader;
	const char* fragment_shader;
}				t_data;


void			parserObj(t_data *data);
void			init_window(t_data *data);
void			loading_buffer(t_data *data);
void			draw(t_data *data);

#endif