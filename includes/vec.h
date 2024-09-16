/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:29:11 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/09/16 15:23:19 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_H
# define VEC_H

# include "libft.h"
# include <math.h>
# include <stdio.h>

typedef struct s_vec
{
	float		x;
	float		y;
	float		z;
}				t_vec;

typedef t_vec	t_point;

float			get_length(t_vec v);
float			get_length_squared(t_vec v);
void			scale(t_vec *v1, float s);
void			divide_by_scalar(t_vec *v, float s);
void			add(t_vec *v1, t_vec v2);
void			subtract(t_vec *v1, t_vec v2);
float			dot(t_vec v1, t_vec v2);
t_vec			cross(t_vec u, t_vec v);
void			normalize(t_vec *v);
float			d_sq(t_point a, t_point b);
void			rotate_vec(t_vec *v, t_vec axis, int deg);

#endif