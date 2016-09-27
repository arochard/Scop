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

//tmp funct

static float		length(float v[3])
{
	return (sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]));
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
	while (data->vertex_tab[i])
	{
		data->vertex_tab[i] = (((data->vertex_tab[i] - min)) * (1 - -1) / (max - min)) + min;
		i++;
	}
	i = 0;
	while (data->indice_tab[i])
	{
		data->indice_tab[i] -= 1;
		i++;
	}
}

// tmp funct
float				*normalise(float v[3])
{
	float 			l;
	float			*vb;

	vb = (float*)malloc(sizeof(float) * 3);

	l = length(v);

	if (l == 0.0f)
	{
		v[0] = 0.0f;
		v[1] = 0.0f;
		v[2] = 0.0f;
		return (v);
	}
	vb[0] = v[0] / l;
	vb[1] = v[1] / l;
	vb[2] = v[2] / l;
	return (vb);
}