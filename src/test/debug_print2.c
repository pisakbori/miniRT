/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:16:41 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/09/11 18:38:21 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_sphere(t_sphere sp, t_color c)
{
	printf("sp");
	printf(" ");
	print_vec(sp.pos);
	printf(" ");
	printf("%.2f", sp.r * 2.f);
	printf(" ");
	print_color(c);
	printf("\n");
}

void	print_plane(t_plane pl, t_color c)
{
	printf("pl");
	printf(" ");
	print_vec(pl.r0);
	printf(" ");
	print_vec(pl.v);
	printf(" ");
	print_color(c);
	printf("\n");
}

void	print_cy(t_cylinder cy, t_color c)
{
	printf("cy");
	printf(" ");
	print_vec(cy.pos);
	printf(" ");
	print_vec(cy.axis);
	printf(" ");
	printf("%.2f", cy.r * 2.f);
	printf(" ");
	printf("%.2f", cy.h * 2.f);
	printf(" ");
	print_color(c);
	printf("\n");
}

void	print_state(void)
{
	t_state	s;
	t_shape	*shape;

	s = *state();
	print_ambient(s.ambient[0]);
	print_camera(s.cam);
	while (s.lights)
	{
		print_light(*((t_light *)s.lights->content));
		s.lights = s.lights->next;
	}
	while (s.shapes)
	{
		shape = (t_shape *)s.shapes->content;
		if (shape->sphere)
			print_sphere(*shape->sphere, shape->color);
		if (shape->plane)
			print_plane(*shape->plane, shape->color);
		if (shape->cylinder)
			print_cy(*shape->cylinder, shape->color);
		s.shapes = s.shapes->next;
	}
}
