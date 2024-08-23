/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:29:30 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/05/07 12:29:31 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	reset(t_vars *v)
{
	pts_cpy(v->set->size, *v->set->pts_0, v->set->pts);
	*v->set->dr = (t_p){.x = 0, .y = 0};
	shift_to_position(v);
}

int	z_rotate(t_vars *vars, float angle)
{
	int		i;
	int		j;
	t_p		**p;
	float	temp;

	j = -1;
	while (++j < vars->set->size.y)
	{
		i = -1;
		while (++i < vars->set->size.x)
		{
			p = *vars->set->pts;
			temp = p[j][i].x;
			p[j][i].x = p[j][i].x * cosf(angle) - p[j][i].y * sinf(angle);
			p[j][i].y = temp * sinf(angle) + p[j][i].y * cosf(angle);
		}
	}
	return (0);
}

int	x_rotate(t_vars *v, float angle)
{
	int		i;
	int		j;
	float	temp;
	t_p		**p;

	j = -1;
	while (++j < v->set->size.y)
	{
		i = -1;
		while (++i < v->set->size.x)
		{
			p = *v->set->pts;
			temp = p[j][i].y;
			p[j][i].y = p[j][i].y * cosf(angle) - p[j][i].z * sinf(angle);
			p[j][i].z = temp * sinf(angle) + p[j][i].z * cosf(angle);
		}
	}
	return (0);
}

int	y_rotate(t_vars *vars, float angle)
{
	int		i;
	int		j;
	t_p		**p;
	float	temp;

	j = -1;
	while (++j < vars->set->size.y)
	{
		i = -1;
		while (++i < vars->set->size.x)
		{
			p = *vars->set->pts;
			temp = p[j][i].z;
			p[j][i].z = p[j][i].z * cosf(angle) - p[j][i].x * sinf(angle);
			p[j][i].x = temp * sinf(angle) + p[j][i].x * cosf(angle);
		}
	}
	return (0);
}

// sx, sy, sz : +1 or -1 rotate d_alpha in that direction
void	rotate(t_vars *v, char sx, char sy, char sz)
{
	static float	al_x;
	static float	al_y;
	static float	al_z;
	float			d_alpha;

	d_alpha = 0.1f;
	al_x += d_alpha * (float) sx;
	al_y += d_alpha * (float) sy;
	al_z += d_alpha * (float) sz;
	if (!sx && !sy && !sz)
	{
		al_x = 0.0f;
		al_y = 0.0f;
		al_z = 0.0f;
		reset(v);
		return ;
	}
	pts_cpy(v->set->size, *v->set->pts_0, v->set->pts);
	if (sx || al_x)
		x_rotate(v, al_x);
	if (sy || al_y)
		y_rotate(v, al_y);
	if (sz || al_z)
		z_rotate(v, al_z);
	shift_to_position(v);
}
