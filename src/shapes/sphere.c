/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:44:20 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/09/11 14:51:50 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_shape	*put_sphere(t_point pos, t_color color, float r)
{
	t_sphere	*s;
	t_shape		*shape;

	shape = ft_calloc(1, sizeof(t_shape));
	s = ft_calloc(1, sizeof(t_sphere));
	shape->sphere = s;
	s->pos = pos;
	s->r = r;
	shape->color = color;
	return (shape);
}

void	set_hitpoint(t_hit *res, t_vec v, t_vec hit_point, t_vec r)
{
	res->normal = hit_point;
	subtract(&res->normal, r);
	normalize(&res->normal);
	res->surface_to_light = v;
	scale(&res->surface_to_light, -1.f);
}

// (r_0 + v*t - r_center) ^2 = R^2
t_hit	hit_sphere(t_sphere sphere, t_ray ray)
{
	float	a;
	float	b;
	float	c;
	t_hit	res;
	t_vec	r;

	a = dot(ray.v, ray.v);
	r = sphere.pos;
	scale(&sphere.pos, -1.f);
	add(&sphere.pos, ray.r0);
	b = 2.f * dot(sphere.pos, ray.v);
	c = dot(sphere.pos, sphere.pos) - sphere.r * sphere.r;
	res.t = solve_quadratic(a, b, c);
	res.hit_point = ray_in_t(ray, res.t);
	set_hitpoint(&res, ray.v, res.hit_point, r);
	return (res);
}
