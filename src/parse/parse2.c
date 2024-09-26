/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmakario <cmakario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:03:43 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/09/26 14:59:45 by cmakario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_ambient(char **d)
{
	t_color	c;

	c = parse_color(d[2]);
	if (ft_atof(d[1]) >= 0 && ft_atof(d[1]) <= 1)
		c.brightness = ft_atof(d[1]);
	else
	{
		free_split_arr(d);
		exit_on_error("'A':ambient lighting ratio must be in range [0.0,1.0]");
	}
	state()->ambient.color = c;
}

void	parse_camera(char **d)
{
	t_point	vp;
	t_vec	orientation;

	vp = parse_vector(d[1], 0);
	orientation = parse_vector(d[2], 1);
	if (ft_atof(d[3]) >= 0 && ft_atof(d[3]) <= 180)
		state()->cam.fov_deg = ft_atof(d[3]);
	else
	{
		free_split_arr(d);
		exit_on_error("Horizontal field of view must me in range [0,180]");
	}
	state()->cam.fov = (float)state()->cam.fov_deg * (M_PI / 180.0f);
	state()->cam.view_point = vp;
	state()->cam.orientation = orientation;
	normalize(&state()->cam.orientation);
	set_camera_vectors();
}

void	parse_light(char **d)
{
	t_light	*light;

	light = ft_calloc(1, sizeof(t_light));
	light->pos = parse_vector(d[1], 0);
	light->color = parse_color(d[3]);
	if (ft_atof(d[2]) >= 0 && ft_atof(d[2]) <= 1)
		light->color.brightness = ft_atof(d[2]);
	else
	{
		free_split_arr(d);
		exit_on_error("Light brightness ratio must be in range [0.0,1.0]");
	}
	put_light_node(light);
}

void	parse_cylinder(char **d)
{
	t_point		cylinder_pos;
	t_vec		cylinder_axis;
	float		h;
	t_shape		*s;
	t_cylinder	*c;

	if (ft_atof(d[4]) <= 0)
	{
		free_split_arr(d);
		exit_on_error("Cylinder's height must be a positive number!");
	}
	h = ft_atof(d[4]);
	cylinder_pos = parse_vector(d[1], 0);
	cylinder_axis = parse_vector(d[2], 1);
	if (ft_atof(d[3]) <= 0)
	{
		free_split_arr(d);
		exit_on_error("Cylinder's diameter must be a positive number!");
	}
	c = get_cylinder(cylinder_pos, cylinder_axis, ft_atof(d[3]), h);
	s = put_cylinder(c, parse_color(d[5]));
	put_shape_node(s);
}

void	parse_sphere(char **d)
{
	t_color	color;
	t_point	sphere_pos;
	float	diameter;
	t_shape	*s;

	sphere_pos = parse_vector(d[1], 0);
	if (ft_atof(d[2]) <= 0)
	{
		free_split_arr(d);
		exit_on_error("Shere's diameter must be a positive number!");
	}
	diameter = ft_atof(d[2]);
	color = parse_color(d[3]);
	s = put_sphere(sphere_pos, color, diameter / 2.f);
	put_shape_node(s);
}
