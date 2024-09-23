/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmakario <cmakario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 22:47:06 by cmakario          #+#    #+#             */
/*   Updated: 2024/09/23 23:40:11 by cmakario         ###   ########.fr       */
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
	printf("x--->%f\n",res.x);
	res.y = ft_atof(words[1]);
	printf("y--->%f\n",res.y);
	res.z = ft_atof(words[2]);
	printf("z--->%f\n",res.z);
	free_split_arr(words);
	if ((res.x >= -1 && res.x <= 1) && (res.y >= -1 && res.y <= 1) && \
	(res.z >= -1 && res.z <= 1))
		return (res);
	else
	{
		exit_on_error("3D normalized orientation vector with x,y,z axis \
must be in range [-1,1]");
		return (res);
	}
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
