/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmakario <cmakario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:38:42 by cmakario          #+#    #+#             */
/*   Updated: 2024/09/19 20:54:23 by cmakario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>

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
	double		p1;
	double		p2;
	double		final;

	int1 = 0;
	frct2 = 0;
	i = 0;
	while (str[int1] != '.' && str[int1] != '\0')
		int1++;
	if (str[int1] != '.')
	{
		// printf("Error: Decimal point '.' not found in input string.\n");
		printf("Epistrefei %f\n", (double)ft_atoi(str));
		return (ft_atoi(str));
	}
	prt1 = (char *)malloc(sizeof(char) * int1);
	while (i < int1)
	{
		prt1[i] = str[i];
		i++;
	}
	prt1[int1] = '\0';
	p1 = ft_atoi(prt1);
	printf("To prwto meros p1 %f\n", p1);
	// free(prt1);
	if (str[int1] == '.')
	{
		i = 0;
		frct2 = ft_strlen(str) - int1 - 1;
		prt2 = (char *)malloc(sizeof(char) * (frct2 + 1));
		while (i < frct2)
		{
			prt2[i] = str[i + int1 + 1];
			i++;
		}
		prt2[frct2] = '\0';
		p2 = ft_atoi(prt2);
		printf("To 2o merosss p2 %f\n", (double)p2/pow(10,frct2));
		// free(prt2);
	}

	final = p1 + p2 / pow(10, frct2);
	printf("finale %f\n", final);
	free(prt1);
	free(prt2);
	
	return (0);
}

int	main()
{
	char	*a;

	a = "-0.001.3we";
	ft_atof(a);
	return (0);
}