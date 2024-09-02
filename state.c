/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:47:59 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/08/30 21:19:12 by bpisak-l         ###   ########.fr       */
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
	t_color	color;
	int		i;
	t_point	sphere_pos;
	t_point	plane_pos;
	t_vec	normal;
	t_color	grey;

	state = ft_calloc(1, sizeof(t_state));
	state->cam.view_point = (t_point){.x = 10, .y = 0, .z = 0};
	state->cam.orientation = (t_vec){.x = -1, .y = 0, .z = 0};
	// state->cam.view_point = (t_point){.x = 5, .y = 0, .z = -10.f};
	// state->cam.orientation = (t_vec){.x = -0.5f, .y = 0, .z = 1.f};
	normalize(&state->cam.orientation);
	state->cam.fov = 120.f * (M_PI / 180.0f);
	state->dim.w = 1000;
	aspect_ratio = 16.f / 9.f;
	state->dim.h = state->dim.w / aspect_ratio;
	if (state->dim.h < 1)
		state->dim.h = 1;
	*get_state_ptr() = state;
	set_camera_vectors();
	state->n_shapes = 5;
	state->shapes = ft_calloc(state->n_shapes, sizeof(t_shape *));
	sphere_pos = (t_point){.x = 0, .y = 0, .z = 0};
	color = (t_color){.r = 255, .g = 0, .b = 0};
	i = -1;
	while (++i < 3)
	{
		state->shapes[i] = put_sphere(sphere_pos, color, 1.f);
		state->shapes[i]->color.r -= 60 * i;
		sphere_pos.x += 0.0f;
		sphere_pos.y += 0.0f;
		sphere_pos.z += 0.0f;
	}
	plane_pos = (t_point){.x = 0, .y = 0, .z = -100000.0f};
	normal = (t_vec){.x = 0, .y = 0, .z = 1};
	grey = (t_color){.r = 105, .g = 105, .b = 105};
	state->shapes[3] = put_plane(plane_pos, normal, grey);
	plane_pos = (t_point){.x = 0, .y = 0, .z = 0};
	normal = (t_vec){.x = 0, .y = 1, .z = 0};
	grey = (t_color){.r = 180, .g = 180, .b = 180};
	state->shapes[4] = put_plane(plane_pos, normal, grey);
}

void	print_state(void)
{
	t_state	*s;
	int		i;
	t_shape	*shape;

	s = state();
	printf("Image dimensions W=%d H=%d\n", s->dim.w, s->dim.h);
	printf("Camera: \n");
	printf("	position: %.2f %.2f %.2f\n", s->cam.view_point.x,
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
			print(shape->sphere->position);
		else if (shape->plane)
			print(shape->plane->r0);
	}
}
