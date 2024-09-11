/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:11:45 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/09/11 16:07:54 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	put_cyliner1(int i, t_color color)
{
	t_point		cylinder_pos;
	t_vec		cylinder_axis;
	float		h;
	t_shape		*s;
	t_cylinder	*c;

	h = 2.f;
	cylinder_pos = (t_point){.x = 0.f, .y = 0.f, .z = 0.f};
	cylinder_axis = (t_vec){.x = 0.0f, .y = 0.f, .z = 1.f};
	normalize(&cylinder_axis);
	c = get_cylinder(cylinder_pos, cylinder_axis, 2.f, h);
	s = put_cylinder(c, color);
	state()->shapes[i] = s;
}

void	put_cyliner2(int i, t_color color)
{
	t_point		cylinder_pos;
	t_vec		cylinder_axis;
	float		h;
	t_shape		*s;
	t_cylinder	*c;

	h = 1.f;
	cylinder_pos = (t_point){.x = 3.f, .y = -1.f, .z = 1.5f};
	cylinder_axis = (t_vec){.x = -2.0f, .y = 0.f, .z = 2.f};
	normalize(&cylinder_axis);
	c = get_cylinder(cylinder_pos, cylinder_axis, 1.f, h);
	s = put_cylinder(c, color);
	state()->shapes[i] = s;
}

void	put_red_sphere(int i)
{
	t_color	color;
	t_point	sphere_pos;
	t_shape	*s;

	color = (t_color){.r = 255, .g = 0, .b = 0, .brightness = 1};
	sphere_pos = (t_point){.x = 2, .y = -1, .z = 0};
	s = put_sphere(sphere_pos, color, 1.f);
	state()->shapes[i] = s;
}

// put_yz_plane(3);
void	put_test2_view(void)
{
	t_color	teal;
	t_color	magenta;

	teal = (t_color){.r = 0., .g = 255, .b = 255, .brightness = 1};
	magenta = (t_color){.r = 255, .g = 25, .b = 255, .brightness = 1};
	state()->shapes = ft_calloc(state()->n_shapes, sizeof(t_shape *));
	put_ambient();
	put_camera_diagonal();
	put_light_above(0);
	put_light_x(1);
	state()->n_shapes = 4;
	state()->n_lights = 2;
	put_bottom_plane(0);
	put_cyliner1(1, teal);
	put_red_sphere(2);
	put_cyliner2(3, magenta);
}
