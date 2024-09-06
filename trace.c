/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:59:07 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/09/06 14:23:11 by bpisak-l         ###   ########.fr       */
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

float	reflected_light(t_light l, t_ray ray, float distance, int i)
{
	int		j;
	t_hit	this_hit;
	t_hit	other_hit;
	t_ray	ray2;
	float	hit_other_distance;
	float	hit_this_distance;

	ray2 = light_to_shape(distance, ray, l);
	this_hit = ray_hit(state()->shapes[i], ray2);
	this_hit.hit_point = ray_in_t(ray, distance);
	j = -1;
	while (++j < state()->n_shapes)
	{
		other_hit = ray_hit(state()->shapes[j], ray2);
		if (!isnan(other_hit.distance))
		{
			hit_other_distance = d_sq(l.pos, other_hit.hit_point);
			hit_this_distance = d_sq(l.pos, this_hit.hit_point);
			if (hit_other_distance + 0.02 < hit_this_distance)
				return (0.f);
		}
	}
	return (this_hit.lambert);
}

void	ray_color(t_ray *ray)
{
	t_hit	*distances;
	int		i;
	int		j;
	float	c;
	t_color	accumulated_light;
	t_color	light_color;

	// t_color	reflected;
	j = -1;
	i = -1;
	distances = ft_calloc(state()->n_shapes, sizeof(t_hit));
	while (++i < state()->n_shapes)
	{
		distances[i] = ray_hit(state()->shapes[i], *ray);
	}
	i = minimum_distance(distances, state()->n_shapes);
	accumulated_light = ray->color;
	while (++j < 2 && i != -1)
	{
		light_color = state()->lights[j].color;
		c = reflected_light(state()->lights[j], *ray, distances[i].distance, i);
		scale_color(&light_color, c);
		multiply_color(&light_color, state()->shapes[i]->color);
		accumulated_light = sum_color(accumulated_light, light_color);
	}
	scale_color(&accumulated_light, 0.5f);
	ray->color = accumulated_light;
	free(distances);
}
