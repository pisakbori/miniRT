/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:29:11 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/08/23 16:10:39 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_H
# define VEC_H

# include "libft.h"
# include <math.h>
# include <stdio.h>

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}			t_vec;

t_vec		*new_vector(float x, float y, float z);
void		print(t_vec v);
float		get_length(t_vec v);
float		get_length_squared(t_vec v);
void		vec_times_scalar(t_vec *v1, float s);
void		divide_by_scalar(t_vec *v, float s);
t_vec		*add(t_vec v1, t_vec v2);
float		dot(t_vec v1, t_vec v2);
t_vec		*cross(t_vec u, t_vec v);
t_vec		*unit_vec(t_vec v);

#endif