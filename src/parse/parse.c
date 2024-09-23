/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmakario <cmakario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:09:55 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/09/23 19:13:33 by cmakario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_element(char **words, t_counter *counter)
{
	if (ft_str_equal(words[0], "A"))
	{
		parse_ambient(words);
		counter->count_a += 1;
		return (1);
	}
	else if (ft_str_equal(words[0], "C"))
	{
		parse_camera(words);
		counter->count_c += 1;
		return (1);
	}
	else if (ft_str_equal(words[0], "L"))
	{
		parse_light(words);
		counter->count_l += 1;
		return (1);
	}
	return (0);
}

void	parse_input_line(char *line, t_counter *counter)
{
	char	**words;

	words = ft_split(line, ' ');
	if (parse_element(words, counter))
	{
		free_split_arr(words);
		return ;
	}
	else if (ft_str_equal(words[0], "cy"))
		parse_cylinder(words);
	else if (ft_str_equal(words[0], "sp"))
		parse_sphere(words);
	else if (ft_str_equal(words[0], "pl"))
		parse_plane(words);
	else if (words[0][0] == 10)
	{
		free_split_arr(words);
		return ;
	}
	else
	{
		free_split_arr(words);
		exit_on_error("Only 'A','C','L','cy','sp','pl' allowed");
	}
	free_split_arr(words);
}

void	exit_on_error(char *str)
{
	printf("Error\n%s\n", str);
	exit(EXIT_FAILURE);
}

void	parse_input(int argc, char **argv, t_counter *count)
{
	int		fd;
	char	*line;

	*count = (t_counter){.count_a = 0, .count_c = 0, .count_l = 0};
	if (argc != 2)
		exit_on_error("Correct usage: ./miniRT <image file>");
	if (ft_strncmp((argv[1] + (ft_strlen(argv[1]) - 3)), ".rt", 3) != 0)
		exit_on_error("Correct usage: ./miniRT <image file>.rt");
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		exit_on_error("Unable to open file.");
	line = get_next_line(fd);
	parse_input_line(line, count);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		if (line)
			parse_input_line(line, count);
		if (count->count_a > 1 || count->count_c > 1 || count->count_l > 1)
			exit_on_error("A,C,L can only be declared once in the scene");
	}
	close(fd);
}
