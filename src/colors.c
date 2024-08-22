/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:09:44 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/05/07 12:47:14 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	pair_min(float a, float b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

int	get_color(float z, float z_min, float z_max, t_vars v)
{
	t_hsv	color;
	t_hsv	min;
	t_rgb	c;
	float	r;

	if (z_max == z_min)
		return (rgb_to_int(hsv_to_rgb(v.c_min)));
	r = (z - z_min) / (z_max - z_min);
	min.h = pair_min(v.c_min.h, v.c_max.h);
	min.s = pair_min(v.c_min.s, v.c_max.s);
	min.v = pair_min(v.c_min.v, v.c_max.v);
	color.h = r * fabs(v.c_max.h - v.c_min.h) + min.h;
	color.s = r * fabs(v.c_max.s - v.c_min.s) + min.s;
	color.v = r * fabs(v.c_max.v - v.c_min.v) + min.v;
	c = hsv_to_rgb(color);
	return (rgb_to_int(c));
}
