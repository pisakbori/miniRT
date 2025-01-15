/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:07:25 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/09/29 19:52:12 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	put_shape_node(t_shape *shape)
{
	t_list	*shape_node;

	shape_node = ft_lstnew(shape);
	ft_lstadd_back(&state()->shapes, shape_node);
}

void	put_light_node(t_light *light)
{
	t_list	*light_node;

	light_node = ft_lstnew(light);
	ft_lstadd_back(&state()->lights, light_node);
}
