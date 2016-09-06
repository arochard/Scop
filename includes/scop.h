#ifndef SCOP_H
# define SCOP_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "glew.h"
#include "glfw3.h"

#define VS 			"Shaders/VertexShader.vs"
#define FS 			"Shaders/FragmentShader.fs"

// typedef struct		s_faces
// {
// 	float			one[3];
// 	float			two[3];
// 	float			three[3];
// 	struct s_faces	*next;
// }					t_faces;

typedef struct		s_data
{
	char			*fileObj;
	char			*fileMtl;
	GLFWwindow		*win_ptr;
	GLuint			vbo;
	GLuint			vao;
	GLuint			vs;
	GLuint			fs;
	GLuint			shader_programme;
	GLuint			indice_buffer;
	unsigned short	*indice_tab;
	float			*vertex_tab;
	int				size_tab_indice;
	int 			size_tab_vertex;
	const char*		vertex_shader;
	const char* 	fragment_shader;
	GLuint 			*arrays_f;
	GLsizei 		arrays_f_size;
	//t_faces			*faces;
}					t_data;


void 				key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void				parserObj(t_data *data);
void				read_shaders(const char **str, char *file);
void				init_window(t_data *data);
void				loading_buffer(t_data *data);
void				draw(t_data *data);
void				fill_list(t_data *data, int	f[3]);

#endif