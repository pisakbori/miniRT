/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:27:05 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/08/23 16:07:12 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

void	print(t_vec v)
{
	printf("Vector, x:%f y:%f z:%f\n", v.x, v.y, v.z);
}

float	get_length(t_vec v)
{
	float	res;

	res = v.x * v.x + v.y * v.y + v.z * v.z;
	return (sqrtf(res));
}

t_vec	*new_vector(float x, float y, float z)
{
	t_vec	*r;

	r = ft_calloc(1, sizeof(t_vec));
	r->x = x;
	r->y = y;
	r->z = z;
	return (r);
}

void	vec_times_scalar(t_vec *v, float s)
{
	v->x = s * v->x;
	v->y = s * v->y;
	v->z = s * v->z;
}

void	divide_by_scalar(t_vec *v, float s)
{
	vec_times_scalar(v, 1 / s);
}
