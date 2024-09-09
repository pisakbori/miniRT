/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:27:05 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/09/09 19:21:45 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

float	get_length_squared(t_vec v)
{
	if (isnan(v.x) || isnan(v.y) || isnan(v.z))
		return (NAN);
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

float	get_length(t_vec v)
{
	return (sqrtf(get_length_squared(v)));
}

void	scale(t_vec *v, float s)
{
	v->x = s * v->x;
	v->y = s * v->y;
	v->z = s * v->z;
}

void	divide_by_scalar(t_vec *v, float s)
{
	scale(v, 1.f / s);
}
