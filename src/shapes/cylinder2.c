/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:14:30 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/09/17 18:53:15 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	translate_cylinder(t_cylinder *c, t_vec v)
{
	add(&c->pos, v);
	add(&c->bottom.r0, v);
	add(&c->top.r0, v);
}

void	rotate_cylinder(t_cylinder *c, t_vec axis, int deg)
{
	t_vec	top_center;
	t_vec	bottom_center;
	t_vec	c_axis;

	rotate_vec(&c->axis, axis, deg);
	c_axis = c->axis;
	scale(&c_axis, c->h);
	top_center = c->pos;
	bottom_center = c->pos;
	add(&top_center, c_axis);
	subtract(&bottom_center, c_axis);
	scale(&c->axis, -1.f);
	c->bottom = (t_plane){.r0 = bottom_center, .v = c->axis};
	scale(&c->axis, -1.f);
	c->top = (t_plane){.r0 = top_center, .v = c->axis};
}

t_cylinder	*get_cylinder(t_point pos, t_vec axis, float d, float h)
{
	t_vec		top_center;
	t_vec		bottom_center;
	t_cylinder	*s;

	s = ft_calloc(1, sizeof(t_cylinder));
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
	s->bottom = (t_plane){.r0 = bottom_center, .v = s->axis};
	scale(&axis, -1.f);
	s->top = (t_plane){.r0 = top_center, .v = s->axis};
	return (s);
}

t_shape	*put_cylinder(t_cylinder *s, t_color color)
{
	t_shape	*shape;

	shape = ft_calloc(1, sizeof(t_shape));
	shape->cylinder = s;
	shape->color = color;
	return (shape);
}

float	get_t(t_vec v_a, t_vec ra0, t_cylinder cylinder)
{
	float	a;
	float	b;
	float	c;

	a = dot(v_a, v_a);
	b = 2.f * dot(ra0, v_a);
	c = dot(ra0, ra0) - cylinder.r_square;
	return (solve_quadratic(a, b, c));
}
