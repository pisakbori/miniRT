/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_csprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:34:13 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/05/31 15:33:24 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

int	ft_cprint(char arg, int *counter)
{
	int	*fd;

	fd = get_printf_fd();
	if (write(*fd, &arg, 1) != -1)
		(*counter)++;
	else
		*counter = -1;
	return (*counter);
}

int	ft_sprint(char *arg, int *counter)
{
	if (!arg)
	{
		ft_sprint("(null)", counter);
		return (*counter);
	}
	while (*arg)
	{
		if (ft_cprint(*arg, counter) == -1)
			return (-1);
		arg++;
	}
	return (*counter);
}
