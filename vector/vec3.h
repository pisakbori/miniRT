/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:29:11 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/08/23 12:40:59 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}			t_vec3;

void		multiply(t_vec3 *v1, float s);

#endif