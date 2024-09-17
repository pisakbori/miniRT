/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_garbage.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:12:10 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/09/17 14:15:59 by bpisak-l         ###   ########.fr       */
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

void	collect_mlx_garbage(t_vars *v)
{
	mlx_destroy_window(v->mlx, v->window);
	ft_lstclear(&state()->lights, clear_light);
	ft_lstclear(&state()->shapes, clear_shape);
	free(state());
}

// Process 34852: 21158 nodes malloced for 10496 KB
// Process 34852: 60 leaks for 1360 total leaked bytes.
