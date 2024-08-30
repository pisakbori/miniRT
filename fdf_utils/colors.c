/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:19:51 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/08/30 14:26:35 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	copy_color(t_color *dst, t_color src)
{
	dst->r = src.r;
	dst->g = src.g;
	dst->b = src.b;
	dst->brightness = src.brightness;
}

// Divide r, g, b by 255
// Compute cmax, cmin, difference
// Hue calculation :
// if cmax and cmin are equal, then h = 0
// if cmax equal r then compute h = (60 * ((g – b) / diff) + 360) % 360
// if cmax equal g then compute h = (60 * ((b – r) / diff) + 120) % 360
// if cmax equal b then compute h = (60 * ((r – g) / diff) + 240) % 360
// Saturation computation :
// if cmax = 0, then s = 0
// if cmax does not equal 0 then compute s = (diff/cmax)*100
// Value computation :
// v = cmax*100
t_hsv	rgb_to_hsv(t_color rgb_c)
{
	float	min;
	float	max;
	float	delta;
	t_hsv	c;

	min = compare(rgb_c.r, rgb_c.g, rgb_c.b, asc);
	max = compare(rgb_c.r, rgb_c.g, rgb_c.b, desc);
	c.v = max;
	delta = max - min;
	c.s = delta / max;
	if (delta < 0.001)
		return ((t_hsv){.h = 0, .s = 0, .v = max});
	if (rgb_c.r == max)
		c.h = (rgb_c.g - rgb_c.b) / delta;
	else if (rgb_c.g == max)
		c.h = 2.0 + (rgb_c.b - rgb_c.r) / delta;
	else
		c.h = 4.0 + (rgb_c.r - rgb_c.g) / delta;
	c.h *= 60.0;
	if (c.h < 0.0)
		c.h += 360.0;
	return (c);
}

t_color	hsv_to_rgb(t_hsv c)
{
	int		i;
	t_color	rgb_c;
	float	hh;
	t_color	var;

	hh = c.h / 60.0;
	i = (long)hh;
	var.b = c.v * (1.0 - c.s);
	var.g = c.v * (1.0 - (c.s * (float)(hh - i)));
	var.r = c.v * (1.0 - (c.s * (1.0 - (float)(hh - i))));
	rgb_c = (t_color){.r = 0, .g = 0, .b = 0};
	if (i == 0)
		return ((t_color){.r = c.v, .g = var.r, .b = var.b});
	else if (i == 1)
		return ((t_color){.r = var.g, .g = c.v, .b = var.b});
	else if (i == 2)
		return ((t_color){.r = var.b, .g = c.v, .b = var.r});
	else if (i == 3)
		return ((t_color){.r = var.b, .g = var.g, .b = c.v});
	else if (i == 4)
		return ((t_color){.r = var.r, .g = var.b, .b = c.v});
	else if (i == 5)
		return ((t_color){.r = c.v, .g = var.b, .b = var.g});
	return (rgb_c);
}

t_color	int_to_rgb(int color)
{
	t_color	rgb_c;

	rgb_c.r = (color >> 16) / 255.f;
	rgb_c.g = (color >> 8 & 0xFF) / 255.f;
	rgb_c.b = (color & 0xFF) / 255.f;
	return (rgb_c);
}

int	rgb_to_int(t_color c)
{
	int	final_c;

	final_c = c.r << 16;
	final_c += c.g << 8;
	final_c += c.b;
	return (final_c);
}

void	normalize_color(t_color *c)
{
	if (c->r > 255)
		c->r = 255;
	if (c->r < 0)
		c->r = 0;
	if (c->g > 255)
		c->g = 255;
	if (c->g < 0)
		c->g = 0;
	if (c->b > 255)
		c->b = 255;
	if (c->b < 0)
		c->b = 0;
}
