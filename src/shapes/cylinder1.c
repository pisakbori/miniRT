/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:58:50 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/09/11 16:08:10 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// ra0 =  s x (r0 - rc) x s
t_vec	get_ra0(t_vec s, t_vec r0, t_vec rc)
{
	t_vec	ra0;

	subtract(&r0, rc);
	ra0 = cross(s, r0);
	ra0 = cross(ra0, s);
	return (ra0);
}

int	is_outside_bounds(t_vec hit_point, t_cylinder cylinder)
{
	t_vec	center_to_hit_point;
	float	proj;

	center_to_hit_point = hit_point;
	subtract(&center_to_hit_point, cylinder.pos);
	proj = dot(center_to_hit_point, cylinder.axis);
	if (proj < -cylinder.h || proj > cylinder.h)
		return (1);
	else
		return (0);
}

t_hit	hit_tube(t_cylinder cylinder, t_ray ray)
{
	t_hit	res;
	t_vec	ra0;
	t_vec	v_a;

	ra0 = get_ra0(cylinder.axis, ray.r0, cylinder.pos);
	v_a = cross(cylinder.axis, ray.v);
	v_a = cross(v_a, cylinder.axis);
	res.t = get_t(v_a, ra0, cylinder);
	res.hit_point = ray_in_t(ray, res.t);
	if (is_outside_bounds(res.hit_point, cylinder))
		res.t = NAN;
	if (!isnan(res.t))
	{
		res.normal = v_a;
		scale(&res.normal, res.t);
		add(&res.normal, ra0);
		normalize(&res.normal);
		res.surface_to_light = ray.v;
		scale(&res.surface_to_light, -1.f);
	}
	return (res);
}

t_hit	hit_face(t_cylinder cylinder, t_ray ray, t_plane face)
{
	t_hit	hit;

	hit = hit_plane(face, ray);
	if (d_sq(hit.hit_point, face.r0) > cylinder.r_square)
		hit.t = NAN;
	return (hit);
}

t_hit	hit_cylinder(t_cylinder cylinder, t_ray ray)
{
	t_hit	hit[3];
	int		index;

	hit[0] = hit_tube(cylinder, ray);
	hit[1] = hit_face(cylinder, ray, cylinder.top);
	hit[2] = hit_face(cylinder, ray, cylinder.bottom);
	index = index_of_closest(hit, 3);
	if (index != -1)
		return (hit[index]);
	return (hit[1]);
}
