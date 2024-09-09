/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3planes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:58:16 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/09/09 14:13:04 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	put_green_sphere_origin(int i)
{
	t_color	color;
	t_point	sphere_pos;
	t_shape	*s;

	color = (t_color){.r = 0, .g = 255, .b = 0};
	sphere_pos = (t_point){.x = 0, .y = 0, .z = 0};
	s = put_sphere(sphere_pos, color, 1.f);
	state()->shapes[i] = s;
}

void	put_test1_view(void)
{
	state()->n_shapes = 5;
	state()->shapes = ft_calloc(state()->n_shapes, sizeof(t_shape *));
	put_camera_diagonal();
	put_light_above(0);
	put_bottom_plane(0);
	put_yz_plane(4);
	put_red_sphere_x(1);
	put_blue_sphere_y(2);
	put_green_sphere_origin(3);
}
