/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_garbage.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:12:10 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/09/27 13:57:53 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	clear_shape(void *shape)
{
	t_shape	*s;

	s = (t_shape *)shape;
	free(s->cylinder);
	free(s->plane);
	free(s->sphere);
	free(s);
}

void	clear_light(void *s)
{
	free(s);
}

void	free_state(void)
{
	free_split_arr(state()->garbage.words2);
	free_split_arr(state()->garbage.words1);
	free(state()->garbage.line);
	ft_lstclear(&state()->lights, clear_light);
	ft_lstclear(&state()->shapes, clear_shape);
	free(state());
}

void	collect_mlx_garbage(t_vars *v)
{
	mlx_destroy_window(v->mlx, v->window);
	free_state();
}

void	exit_on_error(char *str)
{
	printf("Error: %s\n", str);
	free_state();
	exit(EXIT_FAILURE);
}
