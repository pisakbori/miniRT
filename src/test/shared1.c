/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:02:54 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/09/09 14:14:04 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	put_camera_above(void)
{
	t_point	vp;
	t_vec	orientation;

	orientation = (t_vec){.x = -0.2, .y = 0, .z = -0.8f};
	vp = (t_point){.x = 3, .y = 0, .z = 8};
	state()->cam.fov_deg = 100;
	state()->cam.fov = (float)state()->cam.fov_deg * (M_PI / 180.0f);
	state()->cam.view_point = vp;
	state()->cam.orientation = orientation;
	normalize(&state()->cam.orientation);
	set_camera_vectors();
}

void	put_camera_diagonal(void)
{
	t_point	vp;
	t_vec	orientation;

	orientation = (t_vec){.x = -1, .y = -1, .z = -1};
	vp = (t_point){.x = 4, .y = 2, .z = 4};
	state()->cam.fov_deg = 80;
	state()->cam.fov = (float)state()->cam.fov_deg * (M_PI / 180.0f);
	state()->cam.view_point = vp;
	state()->cam.orientation = orientation;
	normalize(&state()->cam.orientation);
	set_camera_vectors();
}

void	put_red_sphere_x(int i)
{
	t_color	color;
	t_point	sphere_pos;
	t_shape	*s;

	color = (t_color){.r = 255, .g = 0, .b = 0, .brightness = 1};
	sphere_pos = (t_point){.x = 2, .y = 0, .z = 0};
	s = put_sphere(sphere_pos, color, 1.f);
	state()->shapes[i] = s;
}

void	put_blue_sphere_y(int i)
{
	t_color	color;
	t_point	sphere_pos;
	t_shape	*s;

	color = (t_color){.r = 0, .g = 0, .b = 255, .brightness = 1};
	sphere_pos = (t_point){.x = 0, .y = 2, .z = 0};
	s = put_sphere(sphere_pos, color, 1.f);
	state()->shapes[i] = s;
}

void	put_yz_plane(int i)
{
	t_point	plane_pos;
	t_vec	normal;
	t_color	grey;
	t_shape	*s;

	plane_pos = (t_point){.x = -1, .y = 0, .z = 0.f};
	normal = (t_vec){.x = 1, .y = 0, .z = 0};
	normalize(&normal);
	grey = (t_color){.r = 250, .g = 250, .b = 250, .brightness = 1};
	s = put_plane(plane_pos, normal, grey);
	state()->shapes[i] = s;
}
