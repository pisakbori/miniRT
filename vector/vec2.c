/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 15:56:33 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/08/23 16:08:31 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

t_vec	*add(t_vec v1, t_vec v2)
{
	t_vec	*v3;

	v3 = ft_calloc(1, sizeof(t_vec));
	v3->x = v1.x + v2.x;
	v3->y = v1.y + v2.y;
	v3->z = v1.z + v2.z;
	return (v3);
}

float	dot(t_vec v1, t_vec v2)
{
	float	res;

	res = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	return (res);
}

t_vec	*cross(t_vec u, t_vec v)
{
	t_vec	*res;

	res = ft_calloc(1, sizeof(t_vec));
	res->x = u.y * v.z - u.z * v.y;
	res->y = u.z * v.x - u.x * v.z;
	res->z = u.x * v.y - u.y * v.x;
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

t_vec	*unit_vec(t_vec v)
{
	t_vec	*r;

	r = clone(v);
	divide_by_scalar(r, get_length(v));
	return (r);
}
