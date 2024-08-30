/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:37:30 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/08/29 14:27:27 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	asc(float a, float b)
{
	return (a - b < 0);
}

int	desc(float a, float b)
{
	return (a - b > 0);
}

float	compare(float a, float b, float c, int (*compare)(float, float))
{
	float	res;

	res = a;
	if (compare(b, res))
		res = b;
	if (compare(c, res))
		res = c;
	return (res);
}
