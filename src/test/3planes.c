/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3planes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:58:16 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/09/11 17:47:33 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	put_green_sphere_origin(void)
{
	t_color	color;
	t_point	sphere_pos;
	t_shape	*s;

	color = (t_color){.r = 0, .g = 255, .b = 0};
	sphere_pos = (t_point){.x = 0, .y = 0, .z = 0};
	s = put_sphere(sphere_pos, color, 1.f);
	put_shape_node(s);
}

void	put_test1_view(void)
{
	put_camera_diagonal();
	put_light_above();
	put_bottom_plane();
	put_yz_plane();
	put_red_sphere_x();
	put_blue_sphere_y();
	put_green_sphere_origin();
}
