/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:13:37 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/09/11 14:52:45 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	put_bottom_plane(int i)
{
	t_point	plane_pos;
	t_vec	normal;
	t_color	grey;
	t_shape	*s;

	plane_pos = (t_point){.x = 0, .y = 0, .z = -1.f};
	normal = (t_vec){.x = 0, .y = 0, .z = 1};
	normalize(&normal);
	grey = (t_color){.r = 105, .g = 105, .b = 105, .brightness = 1};
	s = put_plane(plane_pos, normal, grey);
	state()->shapes[i] = s;
}

void	put_light_x(int i)
{
	t_light	light;

	light.pos = (t_point){.x = 2, .y = 7, .z = 8};
	light.color = (t_color){.r = 255, .g = 255, .b = 255};
	light.color.brightness = 0.4f;
	state()->lights[i] = light;
}

void	put_light_above(int i)
{
	t_light	light;

	light.pos = (t_point){.x = 7, .y = 0, .z = 8};
	light.color = (t_color){.r = 255, .g = 255, .b = 255};
	light.color.brightness = 0.5f;
	state()->lights[i] = light;
}

void	put_ambient(void)
{
	t_color	c;

	c = (t_color){.r = 0, .g = 0, .b = 0, .brightness = 0.1f};
	state()->ambient[0].color = c;
}
