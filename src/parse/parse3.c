/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmakario <cmakario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 22:47:06 by cmakario          #+#    #+#             */
/*   Updated: 2024/09/25 22:38:16 by cmakario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_plane(char **d)
{
	t_point	plane_pos;
	t_vec	normal;
	t_color	color;
	t_shape	*s;

	plane_pos = parse_vector(d[1], 0);
	normal = parse_vector(d[2], 1);
	normalize(&normal);
	color = parse_color(d[3]);
	s = put_plane(plane_pos, normal, color);
	put_shape_node(s);
}

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

t_vec	parse_vector(char *str, int c)
{
	char	**words;
	t_vec	res;

	words = ft_split(str, ',');
	res.x = ft_atof(words[0]);
	res.y = ft_atof(words[1]);
	res.z = ft_atof(words[2]);
	free_split_arr(words);
	if (c == 1)
	{
		if (!((res.x >= -1 && res.x <= 1) && (res.y >= -1 && res.y <= 1) \
		&& (res.z >= -1 && res.z <= 1)))
			exit_on_error("3D normalized orientation vector with x,y,z axis \
must be in range [-1,1]");
	}
	return (res);
}

t_color	parse_color(char *str)
{
	char	**words;
	t_color	res;

	words = ft_split(str, ',');
	res.r = ft_atoi(words[0]);
	res.g = ft_atoi(words[1]);
	res.b = ft_atoi(words[2]);
	free_split_arr(words);
	if ((res.r >= 0 && res.r <= 255) && (res.b >= 0 && res.b <= 255) && \
	(res.g >= 0 && res.g <= 255))
		return (res);
	else
	{
		exit_on_error("'R','G','B', colours ratio must be in range [0,255]");
		return (res);
	}
}
