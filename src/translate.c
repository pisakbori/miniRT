/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:43:36 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/09/16 15:15:02 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	translate_camera(t_vec v)
{
	add(&state()->cam.view_point, v);
}

void	translate_light(int i, t_vec v)
{
	t_list	*s;
	t_light	*o;
	int		j;

	j = -1;
	s = state()->lights;
	while (++j <= i && s)
	{
		if (j == i)
		{
			o = (t_light *)s->content;
			add(&o->pos, v);
		}
		s = s->next;
	}
}

void	translate_object(int i, t_vec v)
{
	t_list	*s;
	t_shape	*o;
	int		j;

	j = -1;
	s = state()->shapes;
	while (++j <= i && s)
	{
		if (j == i)
		{
			o = (t_shape *)s->content;
			if (o->sphere)
				add(&o->sphere->pos, v);
			else if (o->plane)
				add(&o->plane->r0, v);
			else if (o->cylinder)
				translate_cylinder(o->cylinder, v);
		}
		s = s->next;
	}
}
