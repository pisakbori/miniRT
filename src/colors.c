/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:19:51 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/09/23 15:48:19 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	multiply_color(t_color *dst, t_color src)
{
	dst->r = (float)dst->r * ((float)src.r / 255.f);
	dst->g = (float)dst->g * ((float)src.g / 255.f);
	dst->b = (float)dst->b * ((float)src.b / 255.f);
}

t_color	sum_color(t_color c1, t_color c2)
{
	t_color	res;

	res.r = c1.r + c2.r * c2.brightness;
	res.g = c1.g + c2.g * c2.brightness;
	res.b = c1.b + c2.b * c2.brightness;
	res.brightness = c1.brightness + c2.brightness;
	if (res.r > 255)
		res.r = 255;
	if (res.g > 255)
		res.g = 255;
	if (res.b > 255)
		res.b = 255;
	if (res.brightness > 1.f)
		res.brightness = 1.f;
	return (res);
}

void	scale_color(t_color *color, float s)
{
	color->r *= s;
	color->g *= s;
	color->b *= s;
	color->brightness *= s;
}

int	rgb_to_int(t_color c)
{
	int	final_c;

	final_c = c.r << 16;
	final_c += c.g << 8;
	final_c += c.b;
	return (final_c);
}

void	gamma_correct(t_color *c)
{
	float	temp;

	temp = powf((float)c->b / 255.f, 0.8f);
	c->b = roundf(temp * 255.f);
	temp = powf((float)c->r / 255.f, 0.8f);
	c->r = roundf(temp * 255.f);
	temp = powf((float)c->g / 255.f, 0.8f);
	c->g = roundf(temp * 255.f);
}
