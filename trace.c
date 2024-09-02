/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:59:07 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/09/02 16:45:03 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	ray_hit(t_shape *s, t_ray ray)
{
	if (s->sphere)
		return (hit_sphere(*s->sphere, ray));
	else if (s->plane)
		return (hit_plane(*s->plane, ray));
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

t_vec	ray_in_t(t_ray r, float t)
{
	t_vec	res;

	res = r.v;
	scale(&res, t);
	add(&res, r.r0);
	return (res);
}

void	ray_color(t_ray *ray)
{
	float	*distances;
	int		i;
	t_ray	ray2;
	int		j;
	float	t;
	t_point	hit_point;
	t_light	light;

	light = state()->lights[0];
	i = -1;
	distances = ft_calloc(state()->n_shapes, sizeof(float));
	while (++i < state()->n_shapes)
	{
		distances[i] = ray_hit(state()->shapes[i], *ray);
	}
	i = minimum_distance(distances, state()->n_shapes);
	if (i != -1)
	{
		ray2 = shape_to_light(distances[i], *ray, light);
		j = -1;
		while (++j < state()->n_shapes)
		{
			t = ray_hit(state()->shapes[j], ray2);
			if (j != i && !isnan(t))
			{
				hit_point = ray_in_t(ray2, t);
				if (d_sq(light.position, ray2.r0) > d_sq(light.position,
						hit_point))
				{
					multiply_color(&ray->color, (t_color){.r = 0, .g = 0,
							.b = 0});
					return ;
				}
			}
		}
		multiply_color(&ray->color, state()->shapes[i]->color);
		multiply_color(&ray->color, light.color);
		free(distances);
		return ;
	}
	free(distances);
	ray->color = (t_color){.r = 0, .g = 0, .b = 0};
	return ;
}
