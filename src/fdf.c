/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:46:55 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/05/08 12:43:38 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char const *argv[])
{
	int		border;
	t_data	img;
	t_vars	*v;

	if (argc != 2)
	{
		ft_printf("Correct usage: ./fdf <filename>");
		return (1);
	}
	v = ft_calloc(1, sizeof(t_vars));
	v->w_dims = (t_dim){.x = 1000, .y = 1000, .z = 30};
	v->c_min = rgb_to_hsv(int_to_rgb(0x4278F5));
	v->c_max = rgb_to_hsv(int_to_rgb(0xF542DD));
	border = 20;
	get_map(argv[1], v, border);
	v->mlx = mlx_init();
	v->window = mlx_new_window(v->mlx, v->w_dims.x, v->w_dims.y, "fdf");
	img.img = mlx_new_image(v->mlx, v->w_dims.x, v->w_dims.y);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.ll, &img.endian);
	v->img = img;
	put_map_to_window(v);
	mlx_hook(v->window, 2, 1L << 0, handle_key_press, v);
	mlx_hook(v->window, ON_DESTROY, 0, close_win, v);
	mlx_loop(v->mlx);
}
