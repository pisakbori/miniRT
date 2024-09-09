/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 16:12:07 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/09/09 14:17:46 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_color(t_color color)
{
	printf("%d,%d,%d", color.r, color.g, color.b);
}

void	print_vec(t_vec vector)
{
	printf("%.2f,%.2f,%.2f", vector.x, vector.y, vector.z);
}

void	print_ambient(t_ambient_light a)
{
	printf("A");
	printf(" %.2f ", a.color.brightness);
	print_color(a.color);
	printf("\n");
}

void	print_camera(t_camera c)
{
	printf("C ");
	print_vec(c.view_point);
	printf(" ");
	print_vec(c.orientation);
	printf(" ");
	printf("%d", c.fov_deg);
	printf("\n");
}

void	print_light(t_light c)
{
	printf("L ");
	print_vec(c.pos);
	printf(" ");
	printf("%.2f", c.color.brightness);
	printf(" ");
	print_color(c.color);
	printf("\n");
}
