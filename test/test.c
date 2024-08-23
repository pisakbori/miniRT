/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 13:34:18 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/08/23 16:00:35 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int argc, char const *argv[])
{
	t_vec	a;
	float	f;

	f = 2.5;
	(void)argc;
	(void)argv;
	a.x = 1.0;
	a.y = 1.0;
	a.z = 1.0;
	print(a);
	vec_times_scalar(&a, f);
	print(a);
	// int		border;
	// t_data	img;
	// t_vars	*v;
	// if (argc != 2)
	// {
	// 	ft_printf("Correct usage: ./fdf <filename>");
	// 	return (1);
	// }
	// v = ft_calloc(1, sizeof(t_vars));
	// v->w_dims = (t_dim){.x = 1000, .y = 1000, .z = 30};
	// v->c_min = rgb_to_hsv(int_to_rgb(0x4278F5));
	// v->c_max = rgb_to_hsv(int_to_rgb(0xF542DD));
	// border = 20;
	// get_map(argv[1], v, border);
	// v->mlx = mlx_init();
	// v->window = mlx_new_window(v->mlx, v->w_dims.x, v->w_dims.y, "fdf");
	// img.img = mlx_new_image(v->mlx, v->w_dims.x, v->w_dims.y);
	// img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.ll, &img.endian);
	// v->img = img;
	// put_map_to_window(v);
	// mlx_hook(v->window, 2, 1L << 0, handle_key_press, v);
	// mlx_hook(v->window, ON_DESTROY, 0, close_win, v);
	// mlx_loop(v->mlx);
}
