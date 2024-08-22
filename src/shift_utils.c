/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shift_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:00:11 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/05/07 18:44:32 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	x_shift(t_pt_set *set, float d, t_p ***pts)
{
	int		i;
	int		j;
	t_p		p;

	j = -1;
	while (++j < set->size.y)
	{
		i = -1;
		while (++i < set->size.x)
		{
			p = (*pts)[j][i];
			(*pts)[j][i].x = p.x + d;
		}
	}
	set->dr->x += d;
}

void	y_shift(t_pt_set *set, float d, t_p ***pts)
{
	int		i;
	int		j;
	t_p		p;

	j = -1;
	while (++j < set->size.y)
	{
		i = -1;
		while (++i < set->size.x)
		{
			p = (*pts)[j][i];
			(*pts)[j][i].y = p.y + d;
		}
	}
	set->dr->y += d;
}

void	shift(t_vars *v, char sx, char sy)
{
	if (sx)
		x_shift(v->set, sx * 10, v->set->pts);
	if (sy)
		y_shift(v->set, sy * 10, v->set->pts);
}

void	shift_to_position(t_vars *v)
{
	int			ix;
	int			iy;
	t_p			center;
	t_p			temp_center;
	t_pt_set	*set;

	set = v->set;
	temp_center = *set->dr;
	ix = (int)round(set->size.x / 2);
	iy = (int)round(set->size.y / 2);
	center = (*set->pts)[iy][ix];
	x_shift(set, v->w_dims.x / 2.0f - center.x + set->dr->x, set->pts);
	y_shift(set, v->w_dims.y / 2.0f - center.y + set->dr->y, set->pts);
	*set->dr = temp_center;
}

void	center_origin(t_vars *vars)
{
	t_p	temp_center;

	temp_center = *vars->set->dr;
	x_shift(vars->set, -(float)vars->w_dims.x / 2.0f, vars->set->pts_0);
	y_shift(vars->set, -(float)vars->w_dims.y / 2.0f, vars->set->pts_0);
	*vars->set->dr = temp_center;
}
