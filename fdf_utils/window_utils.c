/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:22:39 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/08/23 12:17:12 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	connect_all_pts(t_vars *vars)
{
	int			i;
	int			j;
	t_pt_set	set;

	set = *(vars->set);
	i = -1;
	while (++i < set.size.y)
	{
		j = -1;
		while (++j < set.size.x)
		{
			if (j < set.size.x - 1)
				paint_line((*set.pts)[i][j], (*set.pts)[i][j + 1], vars);
			if (i < set.size.y - 1)
				paint_line((*set.pts)[i][j], (*set.pts)[i + 1][j], vars);
		}
	}
}

int	put_map_to_window(t_vars *vars)
{
	t_data	*i;

	i = &vars->img;
	mlx_destroy_image(vars->mlx, vars->img.img);
	vars->img.img = mlx_new_image(vars->mlx, vars->w_dims.x, vars->w_dims.y);
	vars->img.addr = mlx_get_data_addr(i->img, &i->bpp, &i->ll, &i->endian);
	connect_all_pts(vars);
	mlx_put_image_to_window(vars->mlx, vars->window, vars->img.img, 0, 0);
	return (0);
}

int	is_within_limits(int x, int y, t_dim w_dims)
{
	return (x < w_dims.x && y < w_dims.y && x > 0 && y > 0);
}

void	img_mlx_pixel_put(t_vars v, t_p p, int color)
{
	char	*dst;
	int		x;
	int		y;

	x = (int)roundf(p.x);
	y = (int)roundf(p.y);
	if (!is_within_limits(x, y, v.w_dims))
		return ;
	dst = v.img.addr + (y * v.img.ll + x * (v.img.bpp / 8));
	*(unsigned int *)dst = color;
}
