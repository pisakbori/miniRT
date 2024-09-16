/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:04:40 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/09/16 12:44:02 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	solve_quadratic(float a, float b, float c)
{
	float	x1;
	float	x2;
	float	delta;

	delta = b * b - 4.f * a * c;
	if (delta < 0.0001f && delta > -0.0001)
		delta = 0.0f;
	if (delta < 0.0f)
		return (NAN);
	x1 = (-b + sqrtf(delta)) / (2.f * a);
	x2 = (-b - sqrtf(delta)) / (2.f * a);
	if (x2 > 0)
		return (x2);
	if (x1 > 0)
		return (x1);
	return (NAN);
}
