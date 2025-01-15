/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 17:42:18 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/09/16 18:17:07 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

void	rotate_vec(t_vec *v, t_vec u, int deg)
{
	float	t;
	t_vec	res;
	t_vec	temp2;

	t = (float)deg * (M_PI / 180.0f);
	res = u;
	scale(&res, dot(u, *v));
	temp2 = cross(u, *v);
	scale(&temp2, cosf(t));
	add(&res, cross(temp2, u));
	temp2 = cross(u, *v);
	scale(&temp2, sinf(t));
	add(&res, temp2);
	*v = res;
}
