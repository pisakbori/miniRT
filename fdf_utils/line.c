/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:51:59 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/05/07 19:08:39 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_min_max_colors(t_p p1, t_p p2, t_line_params *var)
{
	if (p1.z0 < p2.z0)
	{
		var->color_max = p2.color;
		var->color_min = p1.color;
		*var->p0 = p1;
	}
	else
	{
		var->color_max = p1.color;
		var->color_min = p2.color;
		*var->p0 = p2;
	}
}

void	init_s_d_p0(t_p p1, t_p p2, t_line_params *var)
{
	var->d = ft_calloc(1, sizeof(t_p));
	var->s = ft_calloc(1, sizeof(t_p));
	var->p0 = ft_calloc(1, sizeof(t_p));
	var->error = ft_calloc(1, sizeof(float *));
	var->d->x = fabsf(p2.x - p1.x);
	var->d->y = -fabsf(p2.y - p1.y);
	var->d->z = fabsf(p2.z0 - p1.z0);
	*var->error = var->d->x + var->d->y;
	set_min_max_colors(p1, p2, var);
	if (p1.x < p2.x)
		var->s->x = 1;
	else
		var->s->x = -1;
	if (p1.y < p2.y)
		var->s->y = 1;
	else
		var->s->y = -1;
}

int	step_coordinates(t_p *new_p, t_line_params	*var, t_p p2)
{
	if (round(new_p->x) == round(p2.x) && round(new_p->y) == round(p2.y))
		return (0);
	if (2 * *var->error >= var->d->y)
	{
		if (round(new_p->x) == round(p2.x))
			return (0);
		*var->error += var->d->y;
		new_p->x += var->s->x;
	}
	if (2 * *var->error <= var->d->x)
	{
		if (round(new_p->y) == round(p2.y))
			return (0);
		*var->error += var->d->x;
		new_p->y += var->s->y;
	}
	return (1);
}

void	put_pixel_w_color(t_p n_p, t_vars *v, t_line_params	*var)
{
	int		c;
	float	z_to;

	if (v->has_colors)
	{
		v->c_min = var->color_min;
		v->c_max = var->color_max;
		z_to = var->p0->z0 + var->d->z;
		c = (int) get_color(n_p.z, var->p0->z0, z_to, *v);
	}
	else
		c = (int) get_color(n_p.z, 0, (float)(v->w_dims.z), *v);
	img_mlx_pixel_put(*v, n_p, c);
}

void	paint_line(t_p p1, t_p p2, t_vars *v)
{
	t_p				n_p;
	t_p				d2;
	t_line_params	*var;
	float			dx2;
	float			dy2;

	var = ft_calloc(1, sizeof(t_line_params));
	init_s_d_p0(p1, p2, var);
	n_p = p1;
	while (1)
	{
		d2.x = (n_p.x - var->p0->x) * (n_p.x - var->p0->x);
		d2.y = (n_p.y - var->p0->y) * (n_p.y - var->p0->y);
		dx2 = var->d->x * var->d->x;
		dy2 = var->d->y * var->d->y;
		n_p.z = var->d->z * sqrt((d2.x + d2.y) / (dx2 + dy2)) + var->p0->z0;
		put_pixel_w_color(n_p, v, var);
		if (!step_coordinates(&n_p, var, p2))
			break ;
	}
	free_line_params(var);
	free(var);
}
