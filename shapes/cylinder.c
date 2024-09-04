/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:58:50 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/09/04 18:38:59 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_shape	*put_cylinder(t_point pos, t_vec axis, t_color color, float d, float h)
{
	t_cylinder	*s;
	t_shape		*shape;

	shape = ft_calloc(1, sizeof(t_shape));
	s = ft_calloc(1, sizeof(t_cylinder));
	shape->cylinder = s;
	s->pos = pos;
	s->r = d / 2.f;
	s->axis = axis;
	s->h = h / 2.0f;
	shape->color = color;
	return (shape);
}

t_hit	hit_tube(t_cylinder cylinder, t_ray ray)
{
	float	a;
	float	b;
	float	c;
	t_hit	res;
	t_vec	rA0;
	t_vec	vA;
	t_vec	r0c;
	t_vec	center_to_hit_point;
	float	proj;

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
	center_to_hit_point = res.hit_point;
	subtract(&center_to_hit_point, cylinder.pos);
	proj = dot(center_to_hit_point, cylinder.axis);
	if (proj < -cylinder.h || proj > cylinder.h)
	{
		res.distance = NAN;
		res.lambert = 0;
	}
	else
		res.lambert = dot(ray.v, rA0);
	if (res.lambert < 0)
		res.lambert = 0;
	return (res);
}

t_hit	hit_cylinder(t_cylinder cylinder, t_ray ray)
{
	return (hit_tube(cylinder, ray));
}
