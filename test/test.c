/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:22:05 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/08/30 14:57:40 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	ray_hit(t_shape *s, t_ray *ray)
{
	if (s->sphere)
		return (hit_sphere(*s->sphere, *ray));
	else if (s->plane)
		return (hit_plane(*s->plane, *ray));
	return (NAN);
}
// -1 if nothing was hit
int	minimum_distance(float *distances, int n)
{
	float	min_value;
	int		index;
	int		i;

	min_value = INFINITY;
	index = -1;
	i = -1;
	while (++i < n)
	{
		if (!isnan(distances[i]) && distances[i] < min_value)
		{
			index = i;
			min_value = distances[i];
		}
	}
	return (index);
}

void	ray_color(t_ray *ray, t_color *color)
{
	float	*distances;
	int		i;

	i = -1;
	distances = ft_calloc(state()->n_shapes, sizeof(float));
	while (++i < state()->n_shapes)
	{
		distances[i] = ray_hit(state()->shapes[i], ray);
	}
	i = minimum_distance(distances, state()->n_shapes);
	if (i != -1)
	{
		copy_color(color, state()->shapes[i]->color);
		return ;
	}
	color->r = 255;
	color->g = 255;
	color->b = 255;
	// color->b = 255 * (1 - ray->v.z);
	// normalize_color(color);
	return ;
}

void	img_mlx_pixel_put(t_vars v, int x, int y, int color)
{
	char	*dst;

	dst = v.img.addr + (y * v.img.ll + x * (v.img.bpp / 8));
	*(unsigned int *)dst = color;
}

void	paint_pixels(t_vars *v)
{
	t_color	color;
	t_ray	*ray;
	int		i;
	int		j;

	j = -1;
	while (++j < state()->dim.h)
	{
		i = -1;
		while (++i < state()->dim.w)
		{
			ray = create_camera_ray(i, j);
			ray_color(ray, &color);
			img_mlx_pixel_put(*v, i, j, rgb_to_int(color));
			free(ray);
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
	mlx_destroy_window(vars->mlx, vars->window);
	collect_pts_garbage(vars);
	exit(0);
}

int	main(int argc, char *argv[])
{
	t_data	img;
	t_vars	v;

	// if (argc != 2)
	// {
	// 	ft_printf("Correct usage: ./fdf <filename>");
	// 	return (1);
	// }
	(void)argc;
	(void)argv;
	init_state();
	print_state();
	v.mlx = mlx_init();
	v.window = mlx_new_window(v.mlx, state()->dim.w, state()->dim.h, "miniRT");
	img.img = mlx_new_image(v.mlx, state()->dim.w, state()->dim.h);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.ll, &img.endian);
	v.img = img;
	put_picture_to_window(&v);
	// mlx_hook(v.window, 2, 1L << 0, handle_key_press, &v);
	mlx_hook(v.window, ON_DESTROY, 0, close_win, &v);
	mlx_loop(v.mlx);
}
