/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:47:59 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/09/28 23:07:56 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_state	**get_state_ptr(void)
{
	static t_state	*state;

	return (&state);
}

t_state	*state(void)
{
	return (*get_state_ptr());
}

void	init_state(void)
{
	t_state	*state;
	float	aspect_ratio;

	state = ft_calloc(1, sizeof(t_state));
	state->dim.w = WIN_WIDTH;
	aspect_ratio = 16.f / 10.f;
	state->dim.h = state->dim.w / aspect_ratio;
	if (state->dim.h < 1)
		state->dim.h = 1;
	state->garbage.words1 = NULL;
	state->garbage.words2 = NULL;
	state->garbage.line = NULL;
	*get_state_ptr() = state;
}
