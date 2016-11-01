/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arochard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/31 20:41:36 by arochard          #+#    #+#             */
/*   Updated: 2016/10/31 20:41:37 by arochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"

static void			m_m(t_data *data, float *min_max, float *min_max_z)
{
	int				i;

	i = 0;
	while (data->final_buffer_tab[i])
	{
		data->final_buffer_tab[i] -= (data->x[0] + data->x[1]) / 2;
		data->final_buffer_tab[i + 1] -= (data->y[0] + data->y[1]) / 2;
		data->final_buffer_tab[i + 2] -= (data->z[0] + data->z[1]) / 2;
		data->final_buffer_tab[i] = (((data->final_buffer_tab[i] - min_max[0]))
			* (1 - -1) / (min_max[1] - min_max[0])) + min_max[0];
		data->final_buffer_tab[i + 1] = (((data->final_buffer_tab[i + 1]
			- min_max[0])) * (1 - -1) / (min_max[1] - min_max[0])) + min_max[0];
		data->final_buffer_tab[i + 2] = (((data->final_buffer_tab[i + 2]
			- min_max_z[0])) * (1 - -1) / (min_max_z[1] - min_max_z[0]))
			+ min_max_z[0];
		i += 6;
	}
}

void				scale_range(t_data *d)
{
	int				i;
	float			mm[2];
	float			mm_z[2];

	mm[0] = 0.0f;
	mm[1] = 0.0f;
	mm_z[0] = 0.0f;
	mm_z[1] = 0.0f;
	i = 0;
	while (d->v_tab[i])
	{
		mm[1] = (d->v_tab[i] > mm[1]) ? d->v_tab[i] : mm[1];
		mm[0] = (d->v_tab[i] < mm[0]) ? d->v_tab[i] : mm[0];
		mm[1] = (d->v_tab[i + 1] > mm[1]) ? d->v_tab[i + 1] : mm[1];
		mm[0] = (d->v_tab[i + 1] < mm[0]) ? d->v_tab[i + 1] : mm[0];
		mm_z[1] = (d->v_tab[i + 2] > mm_z[1]) ? d->v_tab[i + 2] : mm_z[1];
		mm_z[0] = (d->v_tab[i + 2] < mm_z[0]) ? d->v_tab[i + 2] : mm_z[0];
		i += 3;
	}
	m_m(d, mm, mm_z);
}
