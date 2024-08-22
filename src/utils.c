/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:37:30 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/05/07 12:46:05 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	asc(float a, float b)
{
	return (a < b);
}

int	desc(float a, float b)
{
	return (a > b);
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

int	get_z_max(t_pt_set set)
{
	int	i;
	int	j;
	int	res;

	res = 0;
	i = -1;
	while (++i < set.size.y)
	{
		j = -1;
		while (++j < set.size.x)
		{
			if ((*set.pts_0)[i][j].z > res)
				res = (*set.pts_0)[i][j].z;
		}
	}
	return (res);
}

int	arr_len(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}
