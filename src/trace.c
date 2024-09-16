/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:59:07 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/09/11 15:56:35 by bpisak-l         ###   ########.fr       */
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
	res.t = NAN;
	return (res);
}

int	is_shadow(t_vec light_pos, t_ray ray, t_hit this_hit)
{
	t_hit	other_hit;
	float	other_t;
	float	this_t;
	int		i;

	i = -1;
	while (++i < state()->n_shapes)
	{
		other_hit = ray_hit(state()->shapes[i], ray);
		if (!isnan(other_hit.t))
		{
			other_t = d_sq(light_pos, other_hit.hit_point);
			this_t = d_sq(light_pos, this_hit.hit_point);
			if (other_t + 0.015f < this_t)
				return (1);
		}
	}
	return (0);
}

t_color	color_from_shape(t_light light, t_ray camera_ray, float t, int i)
{
	t_color	shape_color;
	t_ray	ray_light_to_shape;
	t_hit	this_hit;

	ray_light_to_shape = light_to_shape(t, camera_ray, light.pos);
	this_hit = ray_hit(state()->shapes[i], ray_light_to_shape);
	this_hit.hit_point = ray_in_t(camera_ray, t);
	shape_color = state()->shapes[i]->color;
	multiply_color(&light.color, shape_color);
	if (is_shadow(light.pos, ray_light_to_shape, this_hit))
		light.color.brightness = 0.f;
	else
		light.color.brightness *= get_illumination(camera_ray.v, this_hit);
	return (light.color);
}

void	ray_color(t_ray *camera_ray)
{
	t_hit	*hits;
	int		i;
	int		j;
	t_color	sum;
	t_color	c;

	j = -1;
	i = -1;
	hits = ft_calloc(state()->n_shapes, sizeof(t_hit));
	while (++i < state()->n_shapes)
		hits[i] = ray_hit(state()->shapes[i], *camera_ray);
	i = index_of_closest(hits, state()->n_shapes);
	sum = (t_color){.r = 0, .g = 0, .b = 0, .brightness = 0.f};
	sum = sum_color(sum, state()->ambient[0].color);
	while (++j < state()->n_lights && i != -1)
	{
		c = color_from_shape(state()->lights[j], *camera_ray, hits[i].t, i);
		sum = sum_color(sum, c);
	}
	camera_ray->color = sum;
	free(hits);
}
