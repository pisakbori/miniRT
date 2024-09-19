/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmakario <cmakario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:38:42 by cmakario          #+#    #+#             */
/*   Updated: 2024/09/19 19:36:54 by cmakario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// double	atof(const char *str)
// {
// 	int	i;
// 	int	sign;

// 	i = 0;
// 	sign = 1;
// 	// skip whitespaces
// 	while (ft_is_space(str[i]))
// 		i++;

// 	// signal detection
// 	if (str[i] == "-")
// 	{
// 		sign = -1;
// 		i++;
// 	}
// 	else if (str[i] == "+")
// 		i++;
	
	
// }


// new idea with the ft atoi implementation
double	ft_atof(const char *str)
{
	int		int1;
	int		frct2;
	char	*prt1;
	char	*prt2;
	int		i;
	int		p1;
	int		p2;

	int1 = 0;
	frct2 = 0;
	i = 0;
	while (str[int1] != '.' && str[int1] != '\0')
		int1++;
	// if (str[int1] != '.')
	// {
	// 	printf("Error: Decimal point '.' not found in input string.\n");
	// 	return 0.0;
	// }
	prt1 = (char *)malloc(sizeof(char) * int1);
	while (i < int1)
	{
		prt1[i] = str[i];
		i++;
	}
	prt1[int1] = '\0';
	p1 = ft_atoi(prt1);
	printf("To prwto meros %d\n", p1);
	free(prt1);
	if (str[int1] == '.')
	{
		i = 0;
		// printf("megethos olou %zu\n", ft_strlen(str));
		// printf("megethos 1ou merous %d\n", int1);
		frct2 = ft_strlen(str) - int1 - 1;
		// printf("To 2o meros megethos %d\n", frct2);
		prt2 = (char *)malloc(sizeof(char) * (frct2 + 1));
		while (i < frct2)
		{
			prt2[i] = str[i + int1 + 1];
			i++;
		}
		prt2[frct2] = '\0';
		p2 = ft_atoi(prt2);
		printf("To 2o merosss %d\n", p2);
		free(prt2);
	}
	return (0);
}

int	main()
{
	char	*a;

	a = "123.123456";
	ft_atof(a);
	return (0);
}