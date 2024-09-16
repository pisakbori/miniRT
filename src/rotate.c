/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 17:43:43 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/09/16 17:46:26 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rotate_object(int i, t_vec v, int deg)
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
			if (o->plane)
				rotate_vec(&o->plane->v, v, deg);
			else if (o->cylinder)
				rotate_cylinder(o->cylinder, v, deg);
		}
		s = s->next;
	}
}

void	rotate_camera(t_vec v, int deg)
{
	rotate_vec(&state()->cam.orientation, v, deg);
	set_camera_vectors();
}
