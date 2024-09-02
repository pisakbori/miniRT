/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 15:56:33 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/09/02 11:30:32 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

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

t_vec	*clone(t_vec v)
{
	t_vec	*r;

	r = ft_calloc(1, sizeof(t_vec));
	r->x = v.x;
	r->y = v.y;
	r->z = v.z;
	return (r);
}

void	assign(t_vec *dest, t_vec src)
{
	dest->x = src.x;
	dest->y = src.y;
	dest->z = src.z;
}

void	normalize(t_vec *v)
{
	divide_by_scalar(v, get_length(*v));
}
