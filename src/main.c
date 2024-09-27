/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:49:49 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/09/27 13:51:12 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// example to rotate/translate. doesn't change original config
void	do_translation_rotation(void)
{
	t_vec	v;
	t_vec	o_x;
	float	angle;

	v = (t_vec){.x = 0.0f, .y = 0.0f, .z = 0.0f};
	o_x = (t_vec){.x = 1.0f, .y = 0.0f, .z = 0.0f};
	angle = 360;
	translate_object(0, v);
	translate_light(0, v);
	translate_camera(v);
	rotate_object(0, o_x, angle);
}

void	check_leaks(void)
{
	*get_state_ptr() = NULL;
	system("leaks miniRT");
}

int	main(int argc, char *argv[])
{
	t_data		img;
	t_vars		v;
	t_counter	counter;

	atexit(check_leaks);
	init_state();
	parse_input(argc, argv, &counter);
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
