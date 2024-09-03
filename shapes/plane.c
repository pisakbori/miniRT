/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 14:37:26 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/09/03 11:36:59 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_shape	*put_plane(t_point position, t_vec normal, t_color color)
{
	t_plane	*p;
	t_shape	*shape;

	shape = ft_calloc(1, sizeof(t_shape));
	p = ft_calloc(1, sizeof(t_plane));
	shape->plane = p;
	p->r0 = position;
	p->v = normal;
	shape->color = color;
	return (shape);
}

// n(r_0 + v* t - rp) = 0
t_hit	hit_plane(t_plane plane, t_ray ray)
{
	t_hit	res;

	res.distance = dot(plane.v, plane.r0) - dot(plane.v, ray.r0);
	res.distance = res.distance / dot(plane.v, ray.v);
	if (res.distance < 0)
		res.distance = NAN;
	res.hit_point = ray_in_t(ray, res.distance);
	res.lambert = dot(ray.v, plane.v);
	if (res.lambert < 0)
		res.lambert = 0;
	return (res);
}
