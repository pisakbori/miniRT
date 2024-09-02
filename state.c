/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:47:59 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/09/02 11:43:28 by bpisak-l         ###   ########.fr       */
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

void	put_bottom_plane(void)
{
	t_point	plane_pos;
	t_vec	normal;
	t_color	grey;

	plane_pos = (t_point){.x = 0, .y = 0, .z = -1.f};
	normal = (t_vec){.x = 0, .y = 0, .z = 1};
	grey = (t_color){.r = 105, .g = 105, .b = 105};
	state()->shapes[0] = put_plane(plane_pos, normal, grey);
}

void	put_red_sphere_x(void)
{
	t_color	color;
	t_point	sphere_pos;

	sphere_pos = (t_point){.x = 0, .y = 0, .z = 0};
	state()->shapes[1] = put_sphere(sphere_pos, color, 1.f);
	state()->shapes[1]->color = (t_color){.r = 255, .g = 0, .b = 0};
	sphere_pos.x += 0.0f;
	sphere_pos.y += 0.0f;
	sphere_pos.z += 0.0f;
}

void	put_blue_sphere_y(void)
{
}

void	put_camera_diagonal(void)
{
}

void	put_camera_above(void)
{
	state()->cam.view_point = (t_point){.x = 10, .y = 0, .z = 0};
	state()->cam.orientation = (t_vec){.x = -1, .y = 0, .z = 0};
	set_camera_vectors();
}

void	init_state(void)
{
	t_state	*state;
	float	aspect_ratio;

	state = ft_calloc(1, sizeof(t_state));
	normalize(&state->cam.orientation);
	state->cam.fov = 120.f * (M_PI / 180.0f);
	state->dim.w = 1000;
	aspect_ratio = 16.f / 9.f;
	state->dim.h = state->dim.w / aspect_ratio;
	if (state->dim.h < 1)
		state->dim.h = 1;
	*get_state_ptr() = state;
	state->n_shapes = 2;
	state->shapes = ft_calloc(state->n_shapes, sizeof(t_shape *));
	put_camera_above();
	put_bottom_plane();
	put_red_sphere_x();
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
