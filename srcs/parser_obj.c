/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arochard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/31 20:41:21 by arochard          #+#    #+#             */
/*   Updated: 2016/10/31 20:41:22 by arochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"

GLfloat				g_color[5] = {0.827f, 0.753f, 0.663f, 0.502f, 0.412f};

static void			fill_tab(t_data *data, int x, GLfloat color)
{
	static int		index = 0;

	data->final_buffer_tab[index] = data->v_tab[(x * 3) - 3];
	data->final_buffer_tab[index + 1] = data->v_tab[(x * 3) - 2];
	data->final_buffer_tab[index + 2] = data->v_tab[(x * 3) - 1];
	data->final_buffer_tab[index + 3] = color;
	data->final_buffer_tab[index + 4] = color;
	data->final_buffer_tab[index + 5] = color;
	index += 6;
}

static void			final_buffer(char *line, t_data *data)
{
	char			letter;
	int				r[4];
	int				rdn;
	static int		index_color = 0;

	if (index_color == 4)
		index_color = 0;
	rdn = sscanf(line, "%c %d %d %d %d", &letter, &r[0], &r[1], &r[2], &r[3]);
	if (rdn < 4 || letter != 'f')
	{
		printf("Error read: v format\n");
		exit(0);
	}
	fill_tab(data, r[0], g_color[index_color]);
	fill_tab(data, r[1], g_color[index_color]);
	fill_tab(data, r[2], g_color[index_color]);
	if (rdn == 5 && letter == 'f')
	{
		fill_tab(data, r[0], g_color[index_color]);
		fill_tab(data, r[2], g_color[index_color]);
		fill_tab(data, r[3], g_color[index_color]);
	}
	index_color++;
}

static void			fill_vtab(char *line, t_data *data)
{
	char			letter;
	int				read;
	static int		index = 0;

	read = sscanf(line, "%c %f %f %f", &letter, &(data->v_tab[index]),
		&(data->v_tab[index + 1]), &(data->v_tab[index + 2]));
	if (data->v_tab[index] < data->x[0])
		data->x[0] = data->v_tab[index];
	if (data->v_tab[index] > data->x[1])
		data->x[1] = data->v_tab[index];
	if (data->v_tab[index + 1] < data->y[0])
		data->y[0] = data->v_tab[index + 1];
	if (data->v_tab[index + 1] > data->y[1])
		data->y[1] = data->v_tab[index + 1];
	if (data->v_tab[index + 2] < data->z[0])
		data->z[0] = data->v_tab[index + 2];
	if (data->v_tab[index + 2] > data->z[1])
		data->z[1] = data->v_tab[index + 2];
	index += 3;
	if (read != 4 || letter != 'v')
	{
		printf("Error read: v format\n");
		exit(0);
	}
}

void				read(FILE *fp, t_data *data)
{
	size_t			buffer;
	char			*line_ptr;
	int				flag;

	flag = 0;
	buffer = 256;
	while (flag == 0 && getline(&line_ptr, &buffer, fp) > 0)
	{
		if (line_ptr[0] == 'v')
			fill_vtab(line_ptr, data);
		if (line_ptr[0] == 'f')
			final_buffer(line_ptr, data);
	}
}

int					read_nb_line(FILE *fp, char del)
{
	size_t			buffer;
	char			*line_ptr;
	int				count;
	int				read[5];
	char			letter;

	count = 0;
	buffer = 128;
	while (getline(&line_ptr, &buffer, fp) > 0)
	{
		if (del == 'v' && line_ptr[0] == del)
			count++;
		if (del == 'f' && line_ptr[0] == del)
		{
			read[0] = sscanf(line_ptr, "%c %d %d %d %d", &letter,
				&read[1], &read[2], &read[3], &read[4]);
			if (read[0] == 4 && letter == 'f')
				count++;
			else if (read[0] == 5 && letter == 'f')
				count += 2;
		}
	}
	rewind(fp);
	return (count);
}
