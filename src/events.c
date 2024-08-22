/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:17:44 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/05/08 12:43:18 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	handle_rotate(int k, t_vars *vars)
{
	if (k == 13)
		rotate(vars, 1, 0, 0);
	else if (k == 7)
		rotate(vars, -1, 0, 0);
	else if (k == 2)
		rotate(vars, 0, 1, 0);
	else if (k == 0)
		rotate(vars, 0, -1, 0);
	else if (k == 8)
		rotate(vars, 0, 0, 1);
	else if (k == 14)
		rotate(vars, 0, 0, -1);
	else if (k == 1)
		rotate(vars, 0, 0, 0);
	return (0);
}

int	handle_shift(int k, t_vars *v)
{
	if (k == 123)
		shift(v, -1, 0);
	else if (k == 124)
		shift(v, 1, 0);
	else if (k == 125)
		shift(v, 0, 1);
	else if (k == 126)
		shift(v, 0, -1);
	return (0);
}

int	close_win(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->window);
	collect_pts_garbage(vars);
	free(vars);
	exit (0);
}

int	handle_key_press(int k, t_vars *vars)
{
	if (k == 53)
		close_win(vars);
	if (k >= 0 && k < 15 && vars->set->size.x)
		handle_rotate(k, vars);
	else if (k >= 123 && k <= 126 && vars->set->size.x)
		handle_shift(k, vars);
	put_map_to_window(vars);
	return (0);
}
