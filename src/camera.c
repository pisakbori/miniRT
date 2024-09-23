/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 11:57:12 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/09/23 16:20:00 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	create_camera_ray(int i, int j)
{
	t_ray	r;
	t_vec	temp;
	float	half_size;
	float	x;
	float	y;

	r.r0 = state()->cam.view_point;
	r.v = state()->cam_z;
	temp = state()->cam_x;
	half_size = (float)state()->dim.w / 2.f;
	x = ((float)i - half_size) / half_size;
	scale(&temp, x);
	add(&r.v, temp);
	temp = state()->cam_y;
	half_size = (float)state()->dim.h / 2.f;
	y = ((float)j - half_size) / half_size;
	scale(&temp, y);
	add(&r.v, temp);
	normalize(&(r.v));
	r.color = (t_color){.r = 0, .g = 0, .b = 0};
	return (r);
}

int	is_upward(t_vec v)
{
	if (v.x == 0 && v.y == 0 && v.z == 1)
		return (1);
	else
		return (0);
}

void	set_camera_vectors_vertical_view(float ratio)
{
	t_vec	temp;

	if (state()->cam.orientation.z > 0)
		temp = (t_vec){.x = 1, .y = 0, .z = 0};
	else
		temp = (t_vec){.x = -1, .y = 0, .z = 0};
	scale(&temp, tanf(state()->cam.fov / 2.f));
	state()->cam_x = temp;
	temp = (t_vec){.x = 0, .y = 1, .z = 0};
	scale(&temp, get_length(state()->cam_x) / ratio);
	state()->cam_y = temp;
}

void	set_camera_vectors(void)
{
	t_vec	temp;
	t_vec	up;
	float	ratio;

	normalize(&state()->cam.orientation);
	state()->cam_z = state()->cam.orientation;
	up = (t_vec){.x = 0.f, .y = 0.f, .z = 1.f};
	temp = cross(state()->cam.orientation, up);
	ratio = (float)(state()->dim.w) / (float)(state()->dim.h);
	if (get_length(temp) > 0.f)
	{
		normalize(&temp);
		scale(&temp, tanf(state()->cam.fov / 2.f));
		state()->cam_x = temp;
		temp = cross(state()->cam_z, state()->cam_x);
		normalize(&temp);
		scale(&temp, get_length(state()->cam_x) / ratio);
		state()->cam_y = temp;
	}
	else
		set_camera_vectors_vertical_view(ratio);
}
