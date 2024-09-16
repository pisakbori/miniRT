/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:22:05 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/08/29 11:46:41 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

t_ray	*create_camera_ray(int i, int j)
{
	t_ray	*r;
	t_vec	*temp;
	float	half_size;
	float	x;
	float	y;

	r = ft_calloc(1, sizeof(t_ray));
	r->r0 = state()->cam.view_point;
	assign(&r->v, state()->cam_z);
	temp = clone(state()->cam_x);
	half_size = (float)state()->dim.w / 2.f;
	x = ((float)i - half_size) / half_size;
	scale(temp, x);
	add(&r->v, *temp);
	free(temp);
	temp = clone(state()->cam_y);
	half_size = (float)state()->dim.h / 2.f;
	y = ((float)j - half_size) / half_size;
	scale(temp, y);
	add(&r->v, *temp);
	free(temp);
	return (r);
}

int	main(void)
{
	int		i;
	int		j;
	t_ray	*ray;

	init_state();
	print_state();
	j = -1;
	while (++j < state()->dim.h)
	{
		i = -1;
		while (++i < state()->dim.w)
		{
			ray = create_camera_ray(i, j);
			printf("i=%d , j=%d ", i, j);
			print(ray->v);
			free(ray);
		}
	}
	return (0);
}
