/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_source.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:23:03 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/09/05 14:19:24 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	light_to_shape(float time, t_ray ray, t_light light_src)
{
	t_ray	new_ray;
	t_vec	dir;
	t_vec	end;

	// new_ray.r0 = ray.v;
	// scale(&new_ray.r0, time);
	// add(&new_ray.r0, ray.r0);
	// dir = new_ray.r0;
	// scale(&dir, -1.f);
	// add(&dir, light_src.pos);
	// normalize(&dir);
	// new_ray.v = dir;
	// return (new_ray);
	new_ray.r0 = light_src.pos;
	end = ray_in_t(ray, time);
	dir = end;
	subtract(&dir, light_src.pos);
	normalize(&dir);
	new_ray.v = dir;
	return (new_ray);
}
