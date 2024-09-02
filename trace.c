/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:59:07 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/09/02 17:04:03 by bpisak-l         ###   ########.fr       */
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
char	is_shadowed(t_light l, t_ray ray, float distance, int i)
{
	t_point	hit_point;
	int		j;
	float	t;
	t_ray	ray2;

	if (i == -1)
		return (0);
	ray2 = shape_to_light(distance, ray, l);
	j = -1;
	while (++j < state()->n_shapes)
	{
		t = ray_hit(state()->shapes[j], ray2);
		if (j != i && !isnan(t))
		{
			hit_point = ray_in_t(ray2, t);
			if (d_sq(l.position, ray2.r0) > d_sq(l.position, hit_point))
				return (1);
		}
	}
	return (0);
}

void	ray_color(t_ray *ray)
{
	float	*distances;
	int		i;

	i = -1;
	distances = ft_calloc(state()->n_shapes, sizeof(float));
	while (++i < state()->n_shapes)
	{
		distances[i] = ray_hit(state()->shapes[i], *ray);
	}
	i = minimum_distance(distances, state()->n_shapes);
	if (i != -1)
	{
		if (is_shadowed(state()->lights[0], *ray, distances[i], i))
			ray->color = (t_color){.r = 0, .g = 0, .b = 0};
		else
		{
			multiply_color(&ray->color, state()->shapes[i]->color);
			multiply_color(&ray->color, state()->lights[0].color);
		}
	}
	free(distances);
}
