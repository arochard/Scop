/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arochard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/31 20:43:15 by arochard          #+#    #+#             */
/*   Updated: 2016/10/31 20:43:18 by arochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# include "glew.h"
# include "glfw3.h"

# define VS "Shaders/VertexShader.vs"
# define FS "Shaders/FragmentShader.fs"

typedef struct		s_data
{
	int				width;
	int				height;
	float			ratio;
	char			*file_obj;
	GLFWwindow		*win_ptr;
	GLuint			vbo;
	GLuint			vao;
	GLuint			shader_programme;
	GLfloat			*final_buffer_tab;
	GLfloat			*v_tab;
	int				size_tab_indice;
	int				size_tab_vertex;
	const char		*vertex_shader;
	const char		*fragment_shader;
	GLuint			texture;
	float			x[2];
	float			y[2];
	float			z[2];
	GLint			loc_mat;
	GLint			loc_pct;
}					t_data;

typedef struct		s_bmp
{
	char			header[54];
	int				data_pos;
	int				width;
	int				height;
	int				img_size;
	char			*data;
	FILE			*fp;
}					t_bmp;

extern GLfloat		g_model_matrix[];
extern int			g_is_texture;
extern GLfloat		g_color[];

void				key_callback(GLFWwindow *window, int key, int scancode,
						int action, int mods);
void				read_shaders(const char **str, char *file);
void				init_window(t_data *data);
void				loading_buffer(t_data *data);
void				draw(t_data *data);
void				scale_range(t_data *data);
float				*normalise(float v[3]);
GLuint				load_bmp(const char *path);
void				read(FILE *fp, t_data *data);
int					read_nb_line(FILE *fp, char del);
#endif
