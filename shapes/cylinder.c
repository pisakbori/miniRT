/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:58:50 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/09/04 16:15:32 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_shape	*put_cylinder(t_point pos, t_vec axis, t_color color, float r)
{
	t_cylinder	*s;
	t_shape		*shape;

	shape = ft_calloc(1, sizeof(t_shape));
	s = ft_calloc(1, sizeof(t_cylinder));
	shape->cylinder = s;
	s->pos = pos;
	s->r = r;
	s->axis = axis;
	shape->color = color;
	return (shape);
}

t_hit	hit_cylinder(t_cylinder cylinder, t_ray ray)
{
	float	a;
	float	b;
	float	c;
	t_hit	res;
	t_vec	rA0;
	t_vec	vA;
	t_vec	r0c;

	r0c = ray.r0;
	subtract(&r0c, cylinder.pos);
	rA0 = cross(cylinder.axis, r0c);
	rA0 = cross(rA0, cylinder.axis);
	vA = cross(cylinder.axis, ray.v);
	vA = cross(vA, cylinder.axis);
	a = dot(vA, vA);
	b = 2.f * dot(rA0, vA);
	c = dot(rA0, rA0) - cylinder.r * cylinder.r;
	res.distance = solve_quadratic(a, b, c);
	res.hit_point = ray_in_t(ray, res.distance);
	res.lambert = dot(ray.v, rA0);
	if (res.lambert < 0)
		res.lambert = 0;
	return (res);
}
