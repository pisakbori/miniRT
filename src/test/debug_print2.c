/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_shapes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:16:41 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/09/09 14:17:51 by bpisak-l         ###   ########.fr       */
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
	int		i;

	i = -1;
	s = *state();
	print_ambient(s.ambient[0]);
	print_camera(s.cam);
	while (++i < 2)
		print_light(s.lights[i]);
	i = -1;
	while (++i < s.n_shapes)
	{
		if (s.shapes[i]->sphere)
			print_sphere(*s.shapes[i]->sphere, s.shapes[i]->color);
		if (s.shapes[i]->plane)
			print_plane(*s.shapes[i]->plane, s.shapes[i]->color);
		if (s.shapes[i]->cylinder)
			print_cy(*s.shapes[i]->cylinder, s.shapes[i]->color);
	}
}
