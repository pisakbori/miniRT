/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 15:56:33 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/09/16 12:53:06 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

void	subtract(t_vec *v1, t_vec v2)
{
	v1->x -= v2.x;
	v1->y -= v2.y;
	v1->z -= v2.z;
}

void	add(t_vec *v1, t_vec v2)
{
	v1->x += v2.x;
	v1->y += v2.y;
	v1->z += v2.z;
}

float	dot(t_vec v1, t_vec v2)
{
	float	res;

	res = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	return (res);
}

t_vec	cross(t_vec u, t_vec v)
{
	t_vec	res;

	res.x = u.y * v.z - u.z * v.y;
	res.y = u.z * v.x - u.x * v.z;
	res.z = u.x * v.y - u.y * v.x;
	return (res);
}

float	d_sq(t_point a, t_point b)
{
	float	d;

	d = (a.x - b.x) * (a.x - b.x);
	d += (a.y - b.y) * (a.y - b.y);
	d += (a.z - b.z) * (a.z - b.z);
	return (d);
}
