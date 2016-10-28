#include "../includes/scop.h"

static void			min_max(t_data *data, float *min, float *max)
{
	int				i;

	i = 0;
	while (data->vertex_tab[i])
	{
		if (data->vertex_tab[i] > *max)
			*max = data->vertex_tab[i];
		if (data->vertex_tab[i] < *min)
			*min = data->vertex_tab[i];
		i++;
	}
}

// static	void		min_max_coord(float *x, float *y, float *z)
// {
// 	int				i;

// 	i = 0;
// 	while (data->vertex_tab[i])
// 	{
// 		if (data->vertex_tab[i] > *max)
// 			*max = data->vertex_tab[i];
// 		if (data->vertex_tab[i] < *min)
// 			*min = data->vertex_tab[i];
// 		i++;
// 	}
// }

void				scaleRange(t_data *data)
{
	int				i;
	float			max;
	float			min;

	min = 0.0f;
	max = 0.0f;
	min_max(data, &min, &max);
	data->object_center[0] = (data->x[0] + data->x[1]) / 2;
	data->object_center[1] = (data->y[0] + data->y[1]) / 2;
	data->object_center[2] = (data->z[0] + data->z[1]) / 2;
	printf("x min = %f  x max = %f\n", data->x[0], data->x[1]);
	printf("y min = %f  y max = %f\n", data->y[0], data->y[1]);
	printf("z min = %f  z max = %f\n", data->z[0], data->z[1]);
	printf("min = %f, max = %f ; center x = %f y = %f z = %f\n", min, max, data->object_center[0], data->object_center[1], data->object_center[2]);
	i = 0;
	while (data->final_buffer_tab[i])
	{
		data->final_buffer_tab[i] -= data->object_center[0];
		data->final_buffer_tab[i + 1] -= data->object_center[1];
		data->final_buffer_tab[i + 2] -= data->object_center[2];

		// data->final_buffer_tab[i] = (data->final_buffer_tab[i] - min) / (max - min);
		// data->final_buffer_tab[i + 1] = (data->final_buffer_tab[i + 1] - min) / (max - min);
		// data->final_buffer_tab[i + 2] = (data->final_buffer_tab[i + 2] - min) / (max - min);

		// data->final_buffer_tab[i] = (((data->final_buffer_tab[i] - min)) * (1 - -1) / (max - min)) + min;
		// data->final_buffer_tab[i + 1] = (((data->final_buffer_tab[i + 1] - min)) * (1 - -1) / (max - min)) + min;
		// data->final_buffer_tab[i + 2] = (((data->final_buffer_tab[i + 2] - min)) * (1 - -1) / (max - min)) + min;

		i += 6;
	}
}