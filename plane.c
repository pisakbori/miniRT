/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 14:37:26 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/08/30 14:58:04 by bpisak-l         ###   ########.fr       */
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
float	hit_plane(t_plane plane, t_ray ray)
{
	t_vec	*temp;
	float	t;

	temp = clone(ray.r0);
	scale(temp, -1.f);
	add(temp, plane.v);
	t = dot(plane.v, *temp);
	free(temp);
	t = t / dot(plane.v, ray.v);
	if (t < 0)
		return (NAN);
	return (t);
}
