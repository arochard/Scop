#ifndef SCOP_H
# define SCOP_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "glew.h"
#include "glfw3.h"

#define 			VS "Shaders/VertexShader.vs"
#define				FS "Shaders/FragmentShader.fs"

typedef struct		s_data
{
	int				width;
	int 			height;
	float			ratio;
	char			*fileObj;
	char			*fileMtl;
	GLFWwindow		*win_ptr;
	GLuint			vbo;
	GLuint			vao;
	GLuint			vs;
	GLuint			fs;
	GLuint			shader_programme;
	GLuint			indice_buffer;
	GLfloat			*final_buffer_tab;
	GLfloat			*vertex_tab;
	int				size_tab_indice;
	int 			size_tab_vertex;
	const char*		vertex_shader;
	const char* 	fragment_shader;
	GLfloat			*modelMatrix;
	GLfloat			*viewMatrix;
	GLfloat			*projectionMatrix;
	GLuint			texture;
	float			x[2];
	float			y[2];
	float			z[2];
	float			object_center[3];
}					t_data;

typedef struct 		s_bmp
{
	char		header[54];
	int			dataPos;
	int			width;
	int			height;
	int 		imgSize;
	char		*data;
	FILE 		*fp;
}				t_bmp;

extern GLfloat		g_modelMatrix[];



void 				key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void				parserObj(t_data *data);
void				read_shaders(const char **str, char *file);
void				init_window(t_data *data);
void				loading_buffer(t_data *data);
void				draw(t_data *data);
void				scaleRange(t_data *data);
float				*normalise(float v[3]);
GLuint				load_bmp(const char *path);
#endif