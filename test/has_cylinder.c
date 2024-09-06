/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:11:45 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/09/06 14:25:46 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	put_blue_cyliner(int i)
{
	t_color	color;
	t_point	cylinder_pos;
	t_vec	cylinder_axis;
	float	r;
	float	h;

	h = 2.f;
	color = (t_color){.r = 0., .g = 255, .b = 255};
	cylinder_pos = (t_point){.x = 0.f, .y = 0.f, .z = 0.f};
	cylinder_axis = (t_vec){.x = 0.0f, .y = 0.f, .z = 1.f};
	normalize(&cylinder_axis);
	r = 2.f;
	state()->shapes[i] = put_cylinder(cylinder_pos, cylinder_axis, color, r, h);
}

void	put_magenta_cyliner(int i)
{
	t_color	color;
	t_point	cylinder_pos;
	t_vec	cylinder_axis;
	float	r;
	float	h;

	h = 1.f;
	color = (t_color){.r = 255, .g = 25, .b = 255};
	cylinder_pos = (t_point){.x = -1.f, .y = 2.f, .z = 1.5f};
	cylinder_axis = (t_vec){.x = -2.0f, .y = 0.5f, .z = 2.f};
	normalize(&cylinder_axis);
	r = 1.f;
	state()->shapes[i] = put_cylinder(cylinder_pos, cylinder_axis, color, r, h);
}

void	put_little_sphere_x(int i)
{
	t_color	color;
	t_point	sphere_pos;

	color = (t_color){.r = 255, .g = 0, .b = 0};
	sphere_pos = (t_point){.x = 2, .y = -1, .z = 0};
	state()->shapes[i] = put_sphere(sphere_pos, color, 0.5f);
}

void	put_test2_view(void)
{
	state()->n_shapes = 4;
	state()->shapes = ft_calloc(state()->n_shapes, sizeof(t_shape *));
	// put_camera_above();
	put_camera_diagonal();
	put_light_above(0);
	put_light_x(1);
	put_bottom_plane(0);
	put_little_sphere_x(3);
	put_blue_cyliner(1);
	put_magenta_cyliner(2);
}
