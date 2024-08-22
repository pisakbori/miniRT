/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_garbage.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 12:26:57 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/05/07 12:55:19 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	pts_free(t_dim pts_dim, t_p ***pts)
{
	int	i;

	i = -1;
	if (!pts)
		return ;
	while (++i < pts_dim.y)
		free((*pts)[i]);
	free(*pts);
}

void	collect_pts_garbage(t_vars *v)
{
	free(v->img.addr);
	free(v->img.img);
	pts_free(v->set->size, v->set->pts);
	pts_free(v->set->size, v->set->pts_0);
	free(v->set->pts_0);
	free(v->set->pts);
	free(v->set->dr);
	free(v->set);
}

int	count_size_and_free(char **words)
{
	int	i;

	i = 0;
	while (words[i])
	{
		free(words[i]);
		i++;
	}
	return (i);
}

void	free_line_params(t_line_params *var)
{
	free(var->d);
	free(var->s);
	free(var->p0);
	free(var->error);
}
