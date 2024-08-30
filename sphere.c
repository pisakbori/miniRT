/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:44:20 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/08/30 14:28:54 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_shape	*put_sphere(t_point position, t_color color, float radius)
{
	t_sphere	*s;
	t_shape		*shape;

	shape = ft_calloc(1, sizeof(t_shape));
	s = ft_calloc(1, sizeof(t_sphere));
	shape->sphere = s;
	s->position = position;
	s->radius = radius;
	shape->color = color;
	return (shape);
}

float	solve_quadratic(float a, float b, float c)
{
	float	x1;
	float	x2;
	float	delta;

	delta = b * b - 4.f * a * c;
	if (delta < 0)
		return (NAN);
	x1 = (-b + sqrtf(delta)) / (2.f * a);
	x2 = (-b - sqrtf(delta)) / (2.f * a);
	if (x2 > 0)
		return (x2);
	if (x1 > 0)
		return (x1);
	return (NAN);
}

// (r_0 + v*t - r_center) ^2 = R^2
float	hit_sphere(t_sphere sphere, t_ray ray)
{
	float	a;
	float	b;
	float	c;
	t_vec	*temp;
	float	t;

	a = dot(ray.v, ray.v);
	temp = clone(sphere.position);
	scale(temp, -1.f);
	add(temp, ray.r0);
	b = 2.f * dot(*temp, ray.v);
	c = dot(*temp, *temp) - sphere.radius * sphere.radius;
	free(temp);
	t = solve_quadratic(a, b, c);
	return (t);
}
