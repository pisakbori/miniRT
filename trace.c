/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:59:07 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/09/02 12:00:37 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	ray_hit(t_shape *s, t_ray *ray)
{
	if (s->sphere)
		return (hit_sphere(*s->sphere, *ray));
	else if (s->plane)
		return (hit_plane(*s->plane, *ray));
	return (NAN);
}

// -1 if nothing was hit
int	minimum_distance(float *distances, int n)
{
	float	min_value;
	int		index;
	int		i;

	min_value = INFINITY;
	index = -1;
	i = -1;
	while (++i < n)
	{
		if (!isnan(distances[i]) && distances[i] < min_value)
		{
			index = i;
			min_value = distances[i];
		}
	}
	return (index);
}

void	ray_color(t_ray *ray, t_color *color)
{
	float	*distances;
	int		i;

	i = -1;
	distances = ft_calloc(state()->n_shapes, sizeof(float));
	while (++i < state()->n_shapes)
	{
		distances[i] = ray_hit(state()->shapes[i], ray);
	}
	i = minimum_distance(distances, state()->n_shapes);
	if (i != -1)
	{
		copy_color(color, state()->shapes[i]->color);
		return ;
	}
	color->r = 0;
	color->g = 0;
	color->b = 0;
	// color->b = 255 * (1 - ray->v.z);
	// normalize_color(color);
	return ;
}
