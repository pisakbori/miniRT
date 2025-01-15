/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:03:22 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/09/23 16:04:11 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	img_mlx_pixel_put(t_vars v, int x, int y, int color)
{
	char	*dst;

	dst = v.img.addr + (y * v.img.ll + x * (v.img.bpp / 8));
	*(unsigned int *)dst = color;
}

void	paint_pixels(t_vars *v)
{
	t_ray	ray;
	int		i;
	int		j;

	j = -1;
	while (++j < state()->dim.h)
	{
		i = -1;
		while (++i < state()->dim.w)
		{
			ray = create_camera_ray(i, j);
			ray_color(&ray);
			gamma_correct(&ray.color);
			img_mlx_pixel_put(*v, i, j, rgb_to_int(ray.color));
		}
	}
}

int	put_picture_to_window(t_vars *vars)
{
	t_data	*i;

	i = &vars->img;
	mlx_destroy_image(vars->mlx, vars->img.img);
	vars->img.img = mlx_new_image(vars->mlx, state()->dim.w, state()->dim.h);
	vars->img.addr = mlx_get_data_addr(i->img, &i->bpp, &i->ll, &i->endian);
	paint_pixels(vars);
	mlx_put_image_to_window(vars->mlx, vars->window, vars->img.img, 0, 0);
	return (0);
}

int	close_win(t_vars *vars)
{
	collect_mlx_garbage(vars);
	exit(0);
}

int	handle_key_press(int k, t_vars *vars)
{
	if (k == 53)
		close_win(vars);
	return (0);
}
