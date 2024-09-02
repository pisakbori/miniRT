/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3planes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:58:16 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/09/02 16:50:18 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	put_bottom_plane(int i)
{
	t_point	plane_pos;
	t_vec	normal;
	t_color	grey;

	plane_pos = (t_point){.x = 0, .y = 0, .z = -1.f};
	normal = (t_vec){.x = 0, .y = 0, .z = 1};
	grey = (t_color){.r = 105, .g = 105, .b = 105};
	state()->shapes[i] = put_plane(plane_pos, normal, grey);
}

void	put_yz_plane(int i)
{
	t_point	plane_pos;
	t_vec	normal;
	t_color	grey;

	plane_pos = (t_point){.x = -1, .y = 0, .z = 0.f};
	normal = (t_vec){.x = 1, .y = 0, .z = 0};
	grey = (t_color){.r = 190, .g = 190, .b = 190};
	state()->shapes[i] = put_plane(plane_pos, normal, grey);
}

void	put_red_sphere_x(int i)
{
	t_color	color;
	t_point	sphere_pos;

	color = (t_color){.r = 255, .g = 0, .b = 0};
	sphere_pos = (t_point){.x = 2, .y = 0, .z = 0};
	state()->shapes[i] = put_sphere(sphere_pos, color, 1.f);
}

void	put_blue_sphere_y(int i)
{
	t_color	color;
	t_point	sphere_pos;

	color = (t_color){.r = 0, .g = 0, .b = 255};
	sphere_pos = (t_point){.x = 0, .y = 2, .z = 0};
	state()->shapes[i] = put_sphere(sphere_pos, color, 1.f);
}

void	put_green_sphere_origin(int i)
{
	t_color	color;
	t_point	sphere_pos;

	color = (t_color){.r = 0, .g = 255, .b = 0};
	sphere_pos = (t_point){.x = 0, .y = 0, .z = 0};
	state()->shapes[i] = put_sphere(sphere_pos, color, 1.f);
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

void	put_light_above(void)
{
	t_light	light;

	ft_bzero(state()->lights, sizeof(state()->lights));
	light.position = (t_point){.x = 3, .y = 0, .z = 8};
	light.color = (t_color){.r = 255, .g = 255, .b = 255};
	state()->lights[0] = light;
}

void	put_test1_view(void)
{
	state()->n_shapes = 5;
	state()->shapes = ft_calloc(state()->n_shapes, sizeof(t_shape *));
	// put_camera_above();
	put_camera_diagonal();
	put_light_above();
	put_bottom_plane(0);
	put_yz_plane(4);
	put_red_sphere_x(1);
	put_blue_sphere_y(2);
	put_green_sphere_origin(3);
}
