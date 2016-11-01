/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_opengl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arochard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/31 20:40:50 by arochard          #+#    #+#             */
/*   Updated: 2016/10/31 20:40:52 by arochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"

static void			send_data_in_shader(t_data *data)
{
	static double	angle = 0.0;
	static float	pct = 0.0f;

	if (g_is_texture)
	{
		if (pct < 1.0)
			pct += 0.01;
	}
	else
	{
		if (pct > 0.0)
			pct -= 0.01;
	}
	g_model_matrix[0] = cos(angle);
	g_model_matrix[8] = -sin(angle);
	g_model_matrix[2] = sin(angle);
	g_model_matrix[10] = cos(angle);
	angle += 0.02;
	glUseProgram(data->shader_programme);
	if (data->loc_pct > -1)
		glUniform1fv(data->loc_pct, 1, &pct);
	if (data->loc_mat > -1)
		glUniformMatrix4fv(data->loc_mat, 1, GL_FALSE, g_model_matrix);
}

static void			create_shaders(t_data *data)
{
	GLuint			vs;
	GLuint			fs;

	vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &(data->vertex_shader), NULL);
	glCompileShader(vs);
	fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &(data->fragment_shader), NULL);
	glCompileShader(fs);
	data->shader_programme = glCreateProgram();
	glAttachShader(data->shader_programme, fs);
	glAttachShader(data->shader_programme, vs);
	glDeleteShader(vs);
	glDeleteShader(fs);
	glLinkProgram(data->shader_programme);
	data->loc_pct = glGetUniformLocation(data->shader_programme, "bend");
	data->loc_mat = glGetUniformLocation(data->shader_programme, "modelMatrix");
	glUseProgram(0);
}

void				loading_buffer(t_data *data)
{
	GLint			location;

	glGenVertexArrays(1, &(data->vao));
	glBindVertexArray(data->vao);
	glGenBuffers(1, &(data->vbo));
	glBindBuffer(GL_ARRAY_BUFFER, data->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) *
		data->size_tab_indice, data->final_buffer_tab, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
		6 * sizeof(GLfloat), (GLvoid*)((sizeof(GLfloat) * 3)));
	glBindVertexArray(0);
	data->texture = load_bmp("./texture/pony");
	location = glGetUniformLocation(data->shader_programme, "myTexture");
	if (location > -1)
		glUniform1i(location, data->texture);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, data->width, data->height);
	glDepthRangef(0.5, 5);
	create_shaders(data);
}

void				draw(t_data *data)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glfwSetKeyCallback(data->win_ptr, key_callback);
	glfwPollEvents();
	glUseProgram(data->shader_programme);
	glBindVertexArray(data->vao);
	glDrawArrays(GL_TRIANGLES, 0, data->size_tab_indice / 6);
	glBindVertexArray(0);
	send_data_in_shader(data);
	glfwSwapBuffers(data->win_ptr);
	glUseProgram(0);
}
