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

void				scaleRange(t_data *data)
{
	int				i;
	float			max;
	float			min;

	min = 0.0f;
	max = 0.0f;
	min_max(data, &min, &max);
	i = 0;
	while (data->final_buffer_tab[i])
	{
		data->final_buffer_tab[i] = (((data->final_buffer_tab[i] - min)) * (1 - -1) / (max - min)) + min;
		data->final_buffer_tab[i+1] = (((data->final_buffer_tab[i] - min)) * (1 - -1) / (max - min)) + min;
		data->final_buffer_tab[i+2] = (((data->final_buffer_tab[i] - min)) * (1 - -1) / (max - min)) + min;
		i += 6;
	}
}