/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 11:20:51 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/09/11 16:00:04 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	ray_in_t(t_ray r, float t)
{
	t_vec	res;

	res = r.v;
	scale(&res, t);
	add(&res, r.r0);
	return (res);
}

// -1 if nothing was hit
int	index_of_closest(t_hit *arr, int n)
{
	float	min_value;
	int		index;
	int		i;

	min_value = INFINITY;
	index = -1;
	i = -1;
	while (++i < n)
	{
		if (!isnan(arr[i].t) && arr[i].t < min_value)
		{
			index = i;
			min_value = arr[i].t;
		}
	}
	return (index);
}

float	get_illumination(t_vec from_camera, t_hit hit)
{
	t_vec	to_camera;
	float	diffuse;
	float	specular;
	t_vec	reflected;

	to_camera = from_camera;
	scale(&to_camera, -1.f);
	diffuse = K_DIFFUSE * dot(hit.surface_to_light, hit.normal);
	if (diffuse < 0)
		diffuse = 0;
	reflected = hit.normal;
	scale(&hit.normal, 2.f * dot(hit.surface_to_light, hit.normal));
	subtract(&hit.normal, hit.surface_to_light);
	specular = K_SPECULAR * powf(dot(reflected, to_camera), 10.f);
	return (diffuse + specular);
}
