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

void				normalize(t_data *data)
{
	int				i;
	float			max;
	float			min;

	min = 0.0f;
	max = 0.0f;
	min_max(data, &min, &max);
	//printf("min : %f    max : %f\n", min, max);
	i = 0;
	while (data->vertex_tab[i])
	{
		//data->vertex_tab[i] = (data->vertex_tab[i] - ((max + min) / 2)) / ((max - min) / 2);
		data->vertex_tab[i] = (((data->vertex_tab[i] - min)) * (1 - -1) / (max - min)) + min;
		//(((OldValue - OldMin) * (NewMax - NewMin)) / (OldMax - OldMin)) + NewMin
		//printf("Vertex %f\n", data->vertex_tab[i]);
		i++;
	}
	i = 0;
	while (data->indice_tab[i])
	{
		data->indice_tab[i] -= 1;
		i++;
	}
}