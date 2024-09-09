/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 11:57:12 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/09/02 17:18:57 by bpisak-l         ###   ########.fr       */
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
	assign(&r.v, state()->cam_z);
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

void	set_camera_vectors(void)
{
	t_vec	temp;
	t_vec	up;

	normalize(&state()->cam.orientation);
	assign(&state()->cam_z, state()->cam.orientation);
	up = (t_vec){.x = 0.f, .y = 0.f, .z = 1.f};
	temp = cross(state()->cam.orientation, up);
	normalize(&temp);
	scale(&temp, tanf(state()->cam.fov / 2.f));
	assign(&state()->cam_x, temp);
	temp = cross(state()->cam_z, state()->cam_x);
	normalize(&temp);
	scale(&temp, get_length(state()->cam_x) / (float)(state()->dim.w)
			* (float)(state()->dim.h));
	assign(&state()->cam_y, temp);
}
