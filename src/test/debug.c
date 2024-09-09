/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 16:12:07 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/09/09 11:59:25 by bpisak-l         ###   ########.fr       */
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

void	print_camara(t_camera c)
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

	s = *state();
	print_ambient(s.ambient[0]);
	print_camara(s.cam);
	for (int i = 0; i < 2; i++)
	{
		print_light(s.lights[i]);
	}
	for (int i = 0; i < s.n_shapes; i++)
	{
		if (s.shapes[i]->sphere)
			print_sphere(*s.shapes[i]->sphere, s.shapes[i]->color);
		if (s.shapes[i]->plane)
			print_plane(*s.shapes[i]->plane, s.shapes[i]->color);
		if (s.shapes[i]->cylinder)
			print_cy(*s.shapes[i]->cylinder, s.shapes[i]->color);
	}
}
