/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:49:49 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/09/17 14:22:25 by bpisak-l         ###   ########.fr       */
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
			// gamma_correct(&ray.color);
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

void	do_translation_rotation(void)
{
	// t_vec	v;
	// v = (t_vec){.x = 10.0f, .y = 0.0f, .z = 0.0f};
	// translate_camera(v);
	// translate_object(0, v);
	// translate_object(1, v);
	// translate_object(2, v);
	// translate_object(3, v);
	// translate_light(0, v);
	// translate_light(1, v);
	// translate_light(-88, v);
	// 	translate(index, vector);
	// normalize(&v);
	// rotate_object(1, v, -45);
}

void	check_leaks(void)
{
	system("leaks miniRT");
}

// atexit(check_leaks);
int	main(int argc, char *argv[])
{
	t_data	img;
	t_vars	v;

	init_state();
	parse_input(argc, argv);
	print_state();
	do_translation_rotation();
	print_state();
	v.mlx = mlx_init();
	v.window = mlx_new_window(v.mlx, state()->dim.w, state()->dim.h, "miniRT");
	img.img = mlx_new_image(v.mlx, state()->dim.w, state()->dim.h);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.ll, &img.endian);
	v.img = img;
	put_picture_to_window(&v);
	mlx_hook(v.window, ON_DESTROY, 0, close_win, &v);
	mlx_hook(v.window, 2, 1L << 0, handle_key_press, &v);
	mlx_loop(v.mlx);
}
