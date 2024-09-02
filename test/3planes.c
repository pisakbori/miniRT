/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3planes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:58:16 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/09/02 13:13:43 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	put_bottom_plane(void)
{
	t_point	plane_pos;
	t_vec	normal;
	t_color	grey;

	plane_pos = (t_point){.x = 0, .y = 0, .z = -1.f};
	normal = (t_vec){.x = 0, .y = 0, .z = 1};
	grey = (t_color){.r = 105, .g = 105, .b = 105};
	state()->shapes[0] = put_plane(plane_pos, normal, grey);
}

void	put_yz_plane(void)
{
	t_point	plane_pos;
	t_vec	normal;
	t_color	grey;

	plane_pos = (t_point){.x = -1, .y = 0, .z = 0.f};
	normal = (t_vec){.x = 1, .y = 0, .z = 0};
	grey = (t_color){.r = 190, .g = 190, .b = 190};
	state()->shapes[2] = put_plane(plane_pos, normal, grey);
}

void	put_red_sphere_x(void)
{
	t_color	color;
	t_point	sphere_pos;

	color = (t_color){.r = 255, .g = 0, .b = 0};
	sphere_pos = (t_point){.x = 2, .y = 0, .z = 0};
	state()->shapes[1] = put_sphere(sphere_pos, color, 1.f);
}

void	put_blue_sphere_y(void)
{
	t_color	color;
	t_point	sphere_pos;

	color = (t_color){.r = 0, .g = 0, .b = 255};
	sphere_pos = (t_point){.x = 0, .y = 2, .z = 0};
	state()->shapes[3] = put_sphere(sphere_pos, color, 1.f);
}

void	put_green_sphere_origin(void)
{
	t_color	color;
	t_point	sphere_pos;

	color = (t_color){.r = 0, .g = 255, .b = 0};
	sphere_pos = (t_point){.x = 0, .y = 0, .z = 0};
	state()->shapes[4] = put_sphere(sphere_pos, color, 1.f);
}

void	put_camera_diagonal(void)
{
	state()->cam.fov = 100.f * (M_PI / 180.0f);
	state()->cam.view_point = (t_point){.x = 3, .y = 3, .z = 3};
	state()->cam.orientation = (t_vec){.x = -1, .y = -1, .z = -1};
	set_camera_vectors();
}

void	put_camera_above(void)
{
	state()->cam.fov = 100.f * (M_PI / 180.0f);
	state()->cam.view_point = (t_point){.x = 3, .y = 0, .z = 8};
	state()->cam.orientation = (t_vec){.x = -0.2, .y = 0, .z = -0.8f};
	set_camera_vectors();
}

void	put_test1_view(void)
{
	state()->n_shapes = 5;
	state()->shapes = ft_calloc(state()->n_shapes, sizeof(t_shape *));
	put_camera_above();
	// put_camera_diagonal();
	put_bottom_plane();
	put_yz_plane();
	put_red_sphere_x();
	put_blue_sphere_y();
	put_green_sphere_origin();
}
