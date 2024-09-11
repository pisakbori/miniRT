/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:59:07 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/09/11 17:50:17 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hit	ray_hit(t_shape s, t_ray ray)
{
	t_hit	res;

	if (s.sphere)
		return (hit_sphere(*s.sphere, ray));
	else if (s.plane)
		return (hit_plane(*s.plane, ray));
	else if (s.cylinder)
		return (hit_cylinder(*s.cylinder, ray));
	res.t = NAN;
	return (res);
}

int	is_shadow(t_vec light_pos, t_ray ray, t_hit this_hit)
{
	t_hit	other_hit;
	float	other_t;
	float	this_t;
	t_list	*shape_lst;
	t_shape	*s;

	shape_lst = state()->shapes;
	while (shape_lst)
	{
		s = (t_shape *)shape_lst->content;
		other_hit = ray_hit(*s, ray);
		if (!isnan(other_hit.t))
		{
			other_t = d_sq(light_pos, other_hit.hit_point);
			this_t = d_sq(light_pos, this_hit.hit_point);
			if (other_t + 0.015f < this_t)
				return (1);
		}
		shape_lst = shape_lst->next;
	}
	return (0);
}

t_color	color_from_shape(t_light light, t_ray camera_ray, float t,
		t_shape shape)
{
	t_ray	ray_light_to_shape;
	t_hit	this_hit;

	ray_light_to_shape = light_to_shape(t, camera_ray, light.pos);
	this_hit = ray_hit(shape, ray_light_to_shape);
	this_hit.hit_point = ray_in_t(camera_ray, t);
	multiply_color(&light.color, shape.color);
	if (is_shadow(light.pos, ray_light_to_shape, this_hit))
		light.color.brightness = 0.f;
	else
		light.color.brightness *= get_illumination(camera_ray.v, this_hit);
	return (light.color);
}

void	ray_color(t_ray *camera_ray)
{
	t_list	*light_lst;
	t_list	*shape_lst;
	t_color	sum;
	t_color	c;
	t_light	*l;
	t_hit	h;
	float	min_value;
	t_shape	*shape_pt;
	t_shape	*s;

	shape_lst = state()->shapes;
	min_value = INFINITY;
	shape_pt = NULL;
	while (shape_lst)
	{
		s = (t_shape *)shape_lst->content;
		h = ray_hit(*s, *camera_ray);
		if (!isnan(h.t) && h.t < min_value)
		{
			shape_pt = (t_shape *)shape_lst->content;
			min_value = h.t;
		}
		shape_lst = shape_lst->next;
	}
	sum = (t_color){.r = 0, .g = 0, .b = 0, .brightness = 0.f};
	sum = sum_color(sum, state()->ambient[0].color);
	light_lst = state()->lights;
	while (light_lst && shape_pt)
	{
		l = (t_light *)light_lst->content;
		c = color_from_shape(*l, *camera_ray, min_value, *shape_pt);
		sum = sum_color(sum, c);
		light_lst = light_lst->next;
	}
	camera_ray->color = sum;
	// free(hits);
}
