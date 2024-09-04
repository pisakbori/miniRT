/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:44:20 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/09/04 15:00:43 by bpisak-l         ###   ########.fr       */
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

// (r_0 + v*t - r_center) ^2 = R^2
t_hit	hit_sphere(t_sphere sphere, t_ray ray)
{
	float	a;
	float	b;
	float	c;
	t_hit	res;

	a = dot(ray.v, ray.v);
	scale(&sphere.pos, -1.f);
	add(&sphere.pos, ray.r0);
	b = 2.f * dot(sphere.pos, ray.v);
	c = dot(sphere.pos, sphere.pos) - sphere.r * sphere.r;
	res.distance = solve_quadratic(a, b, c);
	res.hit_point = ray_in_t(ray, res.distance);
	res.lambert = dot(ray.v, sphere.pos);
	if (res.lambert < 0)
		res.lambert = 0;
	return (res);
}
