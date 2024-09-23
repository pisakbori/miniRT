/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_split_arr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:01:02 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/09/11 18:01:23 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_split_arr(char **res)
{
	int	i;

	if (!res)
		return ;
	i = -1;
	while (res[++i])
	{
		free(res[i]);
		res[i] = NULL;
	}
	free(res);
	res = NULL;
}
