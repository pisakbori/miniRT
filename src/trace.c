/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:59:07 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/09/29 20:13:03 by bpisak-l         ###   ########.fr       */
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

int	is_shadow(t_vec light_pos, t_hit this_hit)
{
	t_hit	other_hit;
	t_list	*shape_lst;
	t_shape	*s;
	t_ray	ray;
	float	d_this_to_light;

	shape_lst = state()->shapes;
	ray.r0 = this_hit.hit_point;
	ray.v = this_hit.surface_to_light;
	while (shape_lst)
	{
		s = (t_shape *)shape_lst->content;
		other_hit = ray_hit(*s, ray);
		if (!isnan(other_hit.t))
		{
			d_this_to_light = d_sq(light_pos, this_hit.hit_point);
			if (other_hit.t > 0.0005f && other_hit.t < sqrtf(d_this_to_light))
				return (1);
		}
		shape_lst = shape_lst->next;
	}
	(void)light_pos;
	return (0);
}

t_color	color_from_shape(t_light light, t_ray camera_ray, t_hit this_hit,
		t_shape shape)
{
	float	illumination;

	this_hit.surface_to_light = light.pos;
	subtract(&this_hit.surface_to_light, this_hit.hit_point);
	normalize(&this_hit.surface_to_light);
	multiply_color(&light.color, shape.color);
	if (is_shadow(light.pos, this_hit))
		light.color.brightness = 0.f;
	else
	{
		illumination = get_illumination(camera_ray.v, this_hit);
		light.color.brightness *= illumination;
	}
	return (light.color);
}

t_color	sum_lights(t_shape *shape_pt, t_ray camera_ray, t_hit min_value)
{
	t_color	sum;
	t_list	*light_lst;
	t_color	c;
	t_light	*l;

	sum = (t_color){.r = 0, .g = 0, .b = 0, .brightness = 0.f};
	if (!shape_pt)
		return (sum);
	sum = sum_color(sum, state()->ambient.color);
	multiply_color(&sum, shape_pt->color);
	light_lst = state()->lights;
	while (light_lst)
	{
		l = (t_light *)light_lst->content;
		c = color_from_shape(*l, camera_ray, min_value, *shape_pt);
		sum = sum_color(sum, c);
		light_lst = light_lst->next;
	}
	return (sum);
}

void	ray_color(t_ray *camera_ray)
{
	t_list	*shape_lst;
	t_hit	h;
	t_hit	min_value;
	t_shape	*shape_pt;
	t_shape	*s;

	shape_lst = state()->shapes;
	min_value.t = INFINITY;
	shape_pt = NULL;
	while (shape_lst)
	{
		s = (t_shape *)shape_lst->content;
		h = ray_hit(*s, *camera_ray);
		if (!isnan(h.t) && h.t < min_value.t)
		{
			shape_pt = (t_shape *)shape_lst->content;
			min_value = h;
		}
		shape_lst = shape_lst->next;
	}
	camera_ray->color = sum_lights(shape_pt, *camera_ray, min_value);
}
