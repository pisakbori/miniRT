/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmakario <cmakario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:03:43 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/09/23 16:46:00 by cmakario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_camera(char **d)
{
	t_point	vp;
	t_vec	orientation;

	vp = parse_vector(d[1]);
	orientation = parse_vector(d[2]);
	state()->cam.fov_deg = ft_atof(d[3]);
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
	light->pos = parse_vector(d[1]);
	light->color = parse_color(d[3]);
	light->color.brightness = ft_atof(d[2]);
	put_light_node(light);
}

void	parse_cylinder(char **d)
{
	t_point		cylinder_pos;
	t_vec		cylinder_axis;
	float		h;
	t_shape		*s;
	t_cylinder	*c;

	h = ft_atof(d[4]);
	cylinder_pos = parse_vector(d[1]);
	cylinder_axis = parse_vector(d[2]);
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

	sphere_pos = parse_vector(d[1]);
	diameter = ft_atof(d[2]);
	color = parse_color(d[3]);
	s = put_sphere(sphere_pos, color, diameter / 2.f);
	put_shape_node(s);
}

void	parse_plane(char **d)
{
	t_point	plane_pos;
	t_vec	normal;
	t_color	color;
	t_shape	*s;

	plane_pos = parse_vector(d[1]);
	normal = parse_vector(d[2]);
	normalize(&normal);
	color = parse_color(d[3]);
	s = put_plane(plane_pos, normal, color);
	put_shape_node(s);
}
