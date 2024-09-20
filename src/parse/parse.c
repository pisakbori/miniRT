/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmakario <cmakario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:09:55 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/09/20 18:53:36 by cmakario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	exit_on_error(char *str)
{
	printf("Error\n%s\n", str);
	exit(EXIT_FAILURE);
}

void	parse_input(int argc, char **argv)
{
	int		fd;
	char	*line;

	if (argc != 2)
		exit_on_error("Correct usage: ./miniRT <image file>");
	if (ft_strncmp((argv[1] + (ft_strlen(argv[1]) - 3)), ".rt", 3) != 0)
		exit_on_error("Correct usage: ./miniRT <image file>.rt");
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		exit_on_error("Unable to open file.");
	line = get_next_line(fd);
	parse_input_line(line);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		if (line)
			parse_input_line(line);
	}
	close(fd);
}