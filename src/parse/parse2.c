/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:03:43 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/09/11 18:41:22 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	put_shape_node(t_shape *shape)
{
	t_list	*shape_node;

	shape_node = ft_lstnew(shape);
	ft_lstadd_back(&state()->shapes, shape_node);
}

void	put_light_node(t_light *light)
{
	t_list	*light_node;

	light_node = ft_lstnew(light);
	ft_lstadd_back(&state()->lights, light_node);
}

t_vec	parse_vector(char *str)
{
	char	**words;
	t_vec	res;

	words = ft_split(str, ',');
	res.x = atof(words[0]);
	res.y = atof(words[1]);
	res.z = atof(words[2]);
	return (res);
}

t_color	parse_color(char *str)
{
	char	**words;
	t_color	res;

	words = ft_split(str, ',');
	res.r = atoi(words[0]);
	res.g = atoi(words[1]);
	res.b = atoi(words[2]);
	free_split_arr(words);
	return (res);
}

void	parse_ambient(char **d)
{
	t_color	c;

	c = parse_color(d[2]);
	c.brightness = atof(d[1]);
	state()->ambient[0].color = c;
}

void	parse_camera(char **d)
{
	t_point	vp;
	t_vec	orientation;

	vp = parse_vector(d[1]);
	orientation = parse_vector(d[2]);
	state()->cam.fov_deg = atof(d[3]);
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
	light->color.brightness = atof(d[2]);
	put_light_node(light);
}

void	parse_cylinder(char **d)
{
	t_point		cylinder_pos;
	t_vec		cylinder_axis;
	float		h;
	t_shape		*s;
	t_cylinder	*c;

	h = atof(d[4]);
	cylinder_pos = parse_vector(d[1]);
	cylinder_axis = parse_vector(d[2]);
	c = get_cylinder(cylinder_pos, cylinder_axis, atof(d[3]), h);
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
	diameter = atof(d[2]);
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

void	parse_input_line(char *line)
{
	char	**words;

	words = ft_split(line, ' ');
	if (ft_str_equal(words[0], "A"))
		parse_ambient(words);
	else if (ft_str_equal(words[0], "C"))
		parse_camera(words);
	else if (ft_str_equal(words[0], "L"))
		parse_light(words);
	else if (ft_str_equal(words[0], "cy"))
		parse_cylinder(words);
	else if (ft_str_equal(words[0], "sp"))
		parse_sphere(words);
	else if (ft_str_equal(words[0], "pl"))
		parse_plane(words);
	free_split_arr(words);
}
