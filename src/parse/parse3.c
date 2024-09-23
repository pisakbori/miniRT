/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmakario <cmakario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 22:47:06 by cmakario          #+#    #+#             */
/*   Updated: 2024/09/23 16:46:00 by cmakario         ###   ########.fr       */
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
	res.x = ft_atof(words[0]);
	res.y = ft_atof(words[1]);
	res.z = ft_atof(words[2]);
	free_split_arr(words);
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
	c.brightness = ft_atof(d[1]);
	state()->ambient.color = c;
}
