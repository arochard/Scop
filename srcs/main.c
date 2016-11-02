/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arochard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/31 20:41:13 by arochard          #+#    #+#             */
/*   Updated: 2016/10/31 20:41:14 by arochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"

GLfloat				g_model_matrix[16] = {
	1.0, 0.0, 0.0, 0.0,
	0.0, 1.0, 0.0, 0.0,
	0.0, 0.0, 1.0, 0.0,
	0.0, 0.0, 3.0f, 1.0};
int					g_is_texture = 0;

static void			parser_obj(t_data *data)
{
	FILE			*fp;

	data->x[0] = 0.0f;
	data->x[1] = 0.0f;
	data->y[0] = 0.0f;
	data->y[1] = 0.0f;
	data->z[0] = 0.0f;
	data->z[1] = 0.0f;
	fp = fopen(data->file_obj, "r");
	if (fp == NULL)
	{
		printf("Error read obj file\n");
		exit(0);
	}
	data->size_tab_vertex = read_nb_line(fp, 'v') * 3;
	data->size_tab_indice = read_nb_line(fp, 'f') * 18;
	data->v_tab = (float*)malloc(sizeof(float) * data->size_tab_vertex);
	data->final_buffer_tab = (GLfloat*)malloc(sizeof(GLfloat)
		* data->size_tab_indice);
	fclose(fp);
	fp = fopen(data->file_obj, "r");
	read(fp, data);
	fclose(fp);
	scale_range(data);
}

int					main(int argc, char **argv)
{
	t_data			data;

	data.width = 1920;
	data.height = 1080;
	data.ratio = data.width / data.height;
	if (argc == 2)
		data.file_obj = argv[1];
	else
	{
		printf("Usage: ./Scop [obj file]\n");
		exit(0);
	}
	read_shaders(&data.vertex_shader, VS);
	read_shaders(&data.fragment_shader, FS);
	parser_obj(&data);
	init_window(&data);
	loading_buffer(&data);
	glfwSetKeyCallback(data.win_ptr, key_callback);
	while (!glfwWindowShouldClose(data.win_ptr))
		draw(&data);
	glfwTerminate();
	return (0);
}
