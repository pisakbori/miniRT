/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 14:37:26 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/09/11 14:14:48 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_shape	*put_plane(t_point pos, t_vec normal, t_color color)
{
	t_plane	*p;
	t_shape	*shape;

	shape = ft_calloc(1, sizeof(t_shape));
	p = ft_calloc(1, sizeof(t_plane));
	shape->plane = p;
	p->r0 = pos;
	p->v = normal;
	shape->color = color;
	return (shape);
}

// n(r_0 + v* t - rp) = 0
t_hit	hit_plane(t_plane plane, t_ray ray)
{
	t_hit	res;

	res.t = dot(plane.v, plane.r0) - dot(plane.v, ray.r0);
	res.t = res.t / dot(plane.v, ray.v);
	if (res.t < 0)
		res.t = NAN;
	res.hit_point = ray_in_t(ray, res.t);
	res.surface_to_light = ray.v;
	scale(&res.surface_to_light, -1.f);
	res.normal = plane.v;
	return (res);
}
