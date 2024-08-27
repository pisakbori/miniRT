/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 16:35:58 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/08/23 16:46:38 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_H
# define SHAPES_H

# include "vec.h"

typedef t_vec t_point;

typedef struct s_triangle
{
	t_point p1;
	t_point p2;
	t_point p3;
}	t_triangle;

#endif