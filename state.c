/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:47:59 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/09/04 17:25:58 by bpisak-l         ###   ########.fr       */
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
	normalize(&state->cam.orientation);
	state->dim.w = 1000;
	aspect_ratio = 16.f / 9.f;
	state->dim.h = state->dim.w / aspect_ratio;
	if (state->dim.h < 1)
		state->dim.h = 1;
	*get_state_ptr() = state;
}

void	print_state(void)
{
	t_state	*s;
	int		i;
	t_shape	*shape;

	s = state();
	printf("Image dimensions W=%d H=%d\n", s->dim.w, s->dim.h);
	printf("Camera: \n");
	printf("	pos: %.2f %.2f %.2f\n", s->cam.view_point.x,
				s->cam.view_point.y, s->cam.view_point.z);
	printf("	Orientation: ");
	print(s->cam.orientation);
	printf("	X ");
	print(s->cam_x);
	printf("	Y ");
	print(s->cam_y);
	printf("	Z ");
	print(s->cam_z);
	i = -1;
	printf("\n");
	while (++i < state()->n_shapes)
	{
		shape = state()->shapes[i];
		printf("%d Shape. Color %d %d %d center: ", i, shape->color.r,
				shape->color.g, shape->color.b);
		if (shape->sphere)
			print(shape->sphere->pos);
		else if (shape->plane)
			print(shape->plane->r0);
		else if (shape->cylinder)
			print(shape->cylinder->pos);
	}
}
