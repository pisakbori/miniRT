/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:47:59 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/08/29 11:42:59 by bpisak-l         ###   ########.fr       */
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

void	set_camera_vectors(void)
{
	t_vec	*temp;
	t_vec	up;

	assign(&state()->cam_z, state()->cam.orientation);
	up = (t_vec){.x = 0.f, .y = 0.f, .z = 1.f};
	temp = cross(state()->cam.orientation, up);
	normalize(temp);
	assign(&state()->cam_x, *temp);
	free(temp);
	temp = cross(state()->cam_z, state()->cam_x);
	normalize(temp);
	assign(&state()->cam_y, *temp);
	free(temp);
}

void	init_state(void)
{
	t_state	*state;
	float	aspect_ratio;

	state = ft_calloc(1, sizeof(t_state));
	state->cam.view_point = (t_point){.x = -50, .y = 0, .z = 20};
	state->cam.orientation = (t_vec){.x = 1, .y = 0, .z = 0};
	state->cam.fov = 70 * (M_PI / 180.0f);
	state->dim.w = 400;
	aspect_ratio = 16.f / 9.f;
	state->dim.h = state->dim.w / aspect_ratio;
	if (state->dim.h < 1)
		state->dim.h = 1;
	*get_state_ptr() = state;
	set_camera_vectors();
}

void	print_state(void)
{
	t_state	*s;

	s = state();
	printf("Image dimensions W=%d H=%d\n", s->dim.w, s->dim.h);
	printf("Camera: \n");
	printf("	position: %.2f %.2f %.2f\n", s->cam.view_point.x,
				s->cam.view_point.y, s->cam.view_point.z);
	printf("	X ");
	print(s->cam_x);
	printf("	Y ");
	print(s->cam_y);
	printf("	Z ");
	print(s->cam_z);
}
