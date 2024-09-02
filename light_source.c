/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_source.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:23:03 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/09/02 16:41:05 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	shape_to_light(float time, t_ray ray, t_light light_src)
{
	t_ray	new_ray;
	t_vec	dir;

	new_ray.r0 = ray.v;
	scale(&new_ray.r0, time);
	add(&new_ray.r0, ray.r0);
	dir = new_ray.r0;
	scale(&dir, -1.f);
	add(&dir, light_src.position);
	normalize(&dir);
	new_ray.v = dir;
	return (new_ray);
}
