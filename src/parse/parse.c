/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmakario <cmakario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:09:55 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/09/26 22:24:28 by cmakario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	check_for_invalid_input(char **words)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (words[i])
	{
		j = 0;
		while (words[i][j])
		{
			if (!((words[i][j] >= '0' && words[i][j] <= '9') || \
			words[i][j] == '-' || words[i][j] == '+' || words[i][j] == '.' \
			|| words[i][j] == ',' || words[i][j] == ' ' || words[i][j] == '\t' \
			|| words[i][j] == '\n') || \
			(words[i][j] == '.' && words[i][j + 1] == '.') || \
			(words[i][j] == ',' && words[i][j + 1] == ','))
			{
				exit_on_error("Invalind input in arguments.", words);
			}
			j++;
		}
		i++;
	}
}


int	parse_element(char **words, t_counter *counter)
{
	check_for_invalid_input(words);
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
		if (BONUS == 0)
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
	else if (words[0][0] == 10 || (words[0][0] == '#'))
	{
		free_split_arr(words);
		return ;
	}
	else
		exit_on_error("Only 'A','C','L','cy','sp','pl' allowed.", words);
	free_split_arr(words);
}

void	exit_on_error(char *str, char**d)
{
	printf("Error: %s\n", str);
	free_split_arr(d);
	exit(EXIT_FAILURE);
}

void	parse_input_split(int fd, char *line, t_counter *count)
{
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		if (line && line[0] == '#')
			continue ;
		if (line)
			parse_input_line(line, count);
		if (count->count_a > 1 || count->count_c > 1 || count->count_l > 1)
			exit_on_error("A,C,L can only be declared once in the scene", NULL);
	}
	close(fd);
}

void	parse_input(int argc, char **argv, t_counter *count)
{
	int		fd;
	char	*line;

	*count = (t_counter){.count_a = 0, .count_c = 0, .count_l = 0};
	if (argc != 2)
		exit_on_error("Correct usage: ./miniRT <image file>", NULL);
	if (ft_strncmp((argv[1] + (ft_strlen(argv[1]) - 3)), ".rt", 3) != 0)
		exit_on_error("Correct usage: ./miniRT <image file>.rt", NULL);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		exit_on_error("Unable to open file.", NULL);
	line = get_next_line(fd);
	if (!line)
	{
		close(fd);
		exit_on_error("Empty file given!", NULL);
	}
	parse_input_line(line, count);
	parse_input_split(fd, line, count);
}
