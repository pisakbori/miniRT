/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:59:07 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/09/04 17:41:27 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hit	ray_hit(t_shape *s, t_ray ray)
{
	t_hit	res;

	if (s->sphere)
		return (hit_sphere(*s->sphere, ray));
	else if (s->plane)
		return (hit_plane(*s->plane, ray));
	else if (s->cylinder)
		return (hit_cylinder(*s->cylinder, ray));
	res.distance = NAN;
	return (res);
}

// -1 if nothing was hit
int	minimum_distance(t_hit *arr, int n)
{
	float	min_value;
	int		index;
	int		i;

	min_value = INFINITY;
	index = -1;
	i = -1;
	while (++i < n)
	{
		if (!isnan(arr[i].distance) && arr[i].distance < min_value)
		{
			index = i;
			min_value = arr[i].distance;
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

float	has_reflected_light(t_light l, t_ray ray, float distance, int i)
{
	int		j;
	t_hit	shape_by_light;
	t_hit	other_hit;
	t_ray	ray2;
	float	hit_other_distance;

	if (i == -1)
		return (0.f);
	ray2 = shape_to_light(distance, ray, l);
	shape_by_light = ray_hit(state()->shapes[i], ray2);
	j = -1;
	while (++j < state()->n_shapes)
	{
		other_hit = ray_hit(state()->shapes[j], ray2);
		if (!isnan(other_hit.distance))
		{
			hit_other_distance = d_sq(l.pos, other_hit.hit_point);
			if (d_sq(l.pos, ray2.r0) - 0.001 > hit_other_distance)
				return (0.f);
		}
	}
	return (shape_by_light.lambert);
}

void	ray_color(t_ray *ray)
{
	t_hit	*distances;
	int		i;
	int		j;
	float	c;
	t_color	reflected;

	j = -1;
	i = -1;
	distances = ft_calloc(state()->n_shapes, sizeof(t_hit));
	while (++i < state()->n_shapes)
	{
		distances[i] = ray_hit(state()->shapes[i], *ray);
	}
	i = minimum_distance(distances, state()->n_shapes);
	while (++j < 1 && i != -1)
	{
		c = has_reflected_light(state()->lights[j], *ray, distances[i].distance,
				i);
		copy_color(&ray->color, state()->shapes[i]->color);
		reflected = (t_color){.r = c * 255.f, .g = c * 255.f, .b = c * 255.f};
		multiply_color(&reflected, state()->lights[j].color);
		multiply_color(&ray->color, reflected);
	}
	free(distances);
}
