/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:11:45 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/09/04 16:24:05 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	put_y_infinite_cyliner(int i)
{
	t_color	color;
	t_point	cylinder_pos;
	t_vec	cylinder_axis;
	float	ray;

	color = (t_color){.r = 0, .g = 255, .b = 0};
	cylinder_pos = (t_point){.x = 2.f, .y = 1.f, .z = 0.f};
	cylinder_axis = (t_vec){.x = 0.0f, .y = 1, .z = 0.f};
	normalize(&cylinder_axis);
	ray = 0.3f;
	state()->shapes[i] = put_cylinder(cylinder_pos, cylinder_axis, color, ray);
}

static void	put_x_infinite_cyliner(int i)
{
	t_color	color;
	t_point	cylinder_pos;
	t_vec	cylinder_axis;
	float	ray;

	color = (t_color){.r = 0, .g = 0, .b = 255};
	cylinder_pos = (t_point){.x = 0.f, .y = 0.f, .z = 0.f};
	cylinder_axis = (t_vec){.x = 0.1f, .y = 0, .z = 0.f};
	normalize(&cylinder_axis);
	ray = 0.3f;
	state()->shapes[i] = put_cylinder(cylinder_pos, cylinder_axis, color, ray);
}

void	put_test2_view(void)
{
	state()->n_shapes = 4;
	state()->shapes = ft_calloc(state()->n_shapes, sizeof(t_shape *));
	// put_camera_above();
	put_camera_diagonal();
	put_light_above();
	put_bottom_plane(0);
	put_red_sphere_x(1);
	put_y_infinite_cyliner(2);
	put_x_infinite_cyliner(3);
}
