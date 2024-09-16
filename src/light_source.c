/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_source.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:23:03 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/09/06 14:57:45 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	light_to_shape(float time, t_ray ray, t_vec light_pos)
{
	t_ray	new_ray;
	t_vec	dir;
	t_vec	end;

	new_ray.r0 = light_pos;
	end = ray_in_t(ray, time);
	dir = end;
	subtract(&dir, light_pos);
	normalize(&dir);
	new_ray.v = dir;
	return (new_ray);
}
