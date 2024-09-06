/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:58:50 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/09/06 11:14:56 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_shape	*put_cylinder(t_point pos, t_vec axis, t_color color, float d, float h)
{
	t_cylinder	*s;
	t_shape		*shape;
	t_vec		top_center;
	t_vec		bottom_center;

	shape = ft_calloc(1, sizeof(t_shape));
	s = ft_calloc(1, sizeof(t_cylinder));
	shape->cylinder = s;
	s->pos = pos;
	s->r = d / 2.f;
	s->axis = axis;
	s->h = h / 2.0f;
	s->r_square = s->r * s->r;
	scale(&axis, s->h);
	top_center = pos;
	bottom_center = pos;
	add(&top_center, axis);
	subtract(&bottom_center, axis);
	scale(&axis, -1.f);
	s->bottom = (t_plane){.r0 = bottom_center, .v = axis};
	scale(&axis, -1.f);
	s->top = (t_plane){.r0 = top_center, .v = axis};
	shape->color = color;
	return (shape);
}
// rA0 =  s x (r0 - rc) x s
t_vec	get_rA0(t_vec s, t_vec r0, t_vec rc)
{
	t_vec	rA0;

	subtract(&r0, rc);
	rA0 = cross(s, r0);
	rA0 = cross(rA0, s);
	return (rA0);
}

t_hit	hit_tube(t_cylinder cylinder, t_ray ray)
{
	float	a;
	float	b;
	float	c;
	t_hit	res;
	t_vec	rA0;
	t_vec	vA;
	t_vec	center_to_hit_point;
	float	proj;
	t_vec	normal;

	rA0 = get_rA0(cylinder.axis, ray.r0, cylinder.pos);
	vA = cross(cylinder.axis, ray.v);
	vA = cross(vA, cylinder.axis);
	a = dot(vA, vA);
	b = 2.f * dot(rA0, vA);
	c = dot(rA0, rA0) - cylinder.r_square;
	res.distance = solve_quadratic(a, b, c);
	res.hit_point = ray_in_t(ray, res.distance);
	center_to_hit_point = res.hit_point;
	subtract(&center_to_hit_point, cylinder.pos);
	proj = dot(center_to_hit_point, cylinder.axis);
	if (proj < -cylinder.h || proj > cylinder.h)
		res.distance = NAN;
	else if (!isnan(res.distance))
	{
		normal = vA;
		scale(&normal, res.distance);
		add(&normal, rA0);
		normalize(&normal);
		scale(&ray.v, -1.f);
		res.lambert = dot(ray.v, normal);
		if (res.lambert < 0)
			res.lambert = 0;
	}
	return (res);
}

t_hit	hit_face(t_cylinder cylinder, t_ray ray, t_plane face)
{
	t_hit	hit;

	hit = hit_plane(face, ray);
	if (d_sq(hit.hit_point, face.r0) > cylinder.r_square)
		hit.distance = NAN;
	if (isnan(hit.distance))
		hit.lambert = 0;
	return (hit);
}

t_hit	hit_cylinder(t_cylinder cylinder, t_ray ray)
{
	t_hit	hit[3];
	int		index;

	hit[0] = hit_tube(cylinder, ray);
	hit[1] = hit_face(cylinder, ray, cylinder.top);
	hit[2] = hit_face(cylinder, ray, cylinder.bottom);
	index = minimum_distance(hit, 3);
	if (index != -1)
		return (hit[index]);
	return (hit[0]);
}
