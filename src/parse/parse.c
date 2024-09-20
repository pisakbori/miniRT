/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmakario <cmakario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:09:55 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/09/20 22:50:09 by cmakario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_input_line(char *line, t_counter *counter)
{
	char	**words;

	words = ft_split(line, ' ');
	if (ft_str_equal(words[0], "A"))
	{
		parse_ambient(words);
		counter->count_a += 1;
	}
	else if (ft_str_equal(words[0], "C"))
	{
		parse_camera(words);
		counter->count_c += 1;
	}
	else if (ft_str_equal(words[0], "L"))
	{
		parse_light(words);
		counter->count_l += 1;
	}
	else if (ft_str_equal(words[0], "cy"))
		parse_cylinder(words);
	else if (ft_str_equal(words[0], "sp"))
		parse_sphere(words);
	else if (ft_str_equal(words[0], "pl"))
		parse_plane(words);
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

	count->count_a = 0;
	count->count_c = 0;
	count->count_l = 0;
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
