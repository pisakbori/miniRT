/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 22:47:06 by cmakario          #+#    #+#             */
/*   Updated: 2024/09/27 14:07:34 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

size_t	ft_array_length(char **ar)
{
	size_t	count;

	count = 0;
	while (ar[count] != NULL && ar[count][0] != '\n')
		count++;
	return (count);
}

void	parse_plane(char **d)
{
	t_point	plane_pos;
	t_vec	normal;
	t_color	color;
	t_shape	*s;

	if (ft_array_length(d) != 4)
		exit_on_error("Wrong number of arguments given in Plane");
	plane_pos = parse_vector(d[1], 0);
	normal = parse_vector(d[2], 1);
	normalize(&normal);
	color = parse_color(d[3]);
	s = put_plane(plane_pos, normal, color);
	put_shape_node(s);
}

t_vec	parse_vector(char *str, int c)
{
	char	**words;
	t_vec	res;

	words = ft_split(str, ',');
	state()->garbage.words2 = words;
	if (ft_array_length(words) != 3)
		exit_on_error("Invalid file content.Check coordinates.");
	res.x = ft_atof(words[0]);
	res.y = ft_atof(words[1]);
	res.z = ft_atof(words[2]);
	free_split_arr(words);
	state()->garbage.words2 = NULL;
	if (c == 1)
	{
		if (get_length(res) > 1.00001f || get_length(res) < 0.999999f)
			exit_on_error("Vector is not normalized");
	}
	return (res);
}

t_color	parse_color(char *str)
{
	char	**words;
	t_color	res;
	int		i;

	i = -1;
	words = ft_split(str, ',');
	state()->garbage.words2 = words;
	if (ft_array_length(words) != 3)
		exit_on_error("Invalid file content.Check colours.");
	while (++i <= 2)
	{
		if (ft_atof(words[i]) - ft_atoi(words[i]) != 0)
			exit_on_error("Decimals are forbiden in R,B,G values.");
	}
	res.r = ft_atoi(words[0]);
	res.g = ft_atoi(words[1]);
	res.b = ft_atoi(words[2]);
	free_split_arr(words);
	state()->garbage.words2 = NULL;
	if (!((res.r >= 0 && res.r <= 255) && (res.b >= 0 && res.b <= 255)
			&& (res.g >= 0 && res.g <= 255)))
		exit_on_error("'R','G','B', colour must be in range [0,255]");
	return (res);
}
