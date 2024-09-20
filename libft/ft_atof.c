/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmakario <cmakario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:38:42 by cmakario          #+#    #+#             */
/*   Updated: 2024/09/20 07:12:38 by cmakario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>

double	parse_interger_part(const char **str)
{
	double	result;

	result = 0.0;
	while (ft_isdigit(**str))
	{
		result = result * 10.0 + (**str - '0');
		(*str)++;
	}
	return (result);
}

double	parse_fractional_part(const char **str)
{
	double	result;
	double	fraction;

	result = 0.0;
	fraction = 1.0;
	if (**str == '.')
	{
		(*str)++;
		while (ft_isdigit(**str))
		{
			result = result * 10.0 + (**str - '0');
			fraction *= 10.0;
			(*str)++;
		}
	}
	return (result / fraction);
}

double	ft_atof(const char *str)
{
	double	result;
	int		sign;

	result = 0;
	sign = 1;

	while (ft_is_space(*str))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	result = parse_interger_part(&str);
	result += parse_fractional_part(&str);
	return (sign * result);
}


/* // Too big to make it smaller 
double	ft_atof(const char *str)
{
	double	result;
	double	fraction;
	int		sign;

	result = 0.0;
	fraction = 1.0;
	sign = 1;

	while (ft_is_space(*str))
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (ft_isdigit(*str))
	{
		result = result * 10.0 + (*str - '0');
		str++;
	}
	if (*str == '.')
	{
		str++;
		while (ft_isdigit(*str))
		{
			result = result * 10.0 + (*str - '0');
			fraction *= 10.0;
			str++;
		}
	}
	result = sign * result / fraction;
	if (result == 0.0 && sign == -1)
		return (-0.0);
	return (result);
} */



int main() {
	printf("%f\n", ft_atof("-0"));	// Should print: -0.000000
	printf("%f\n", ft_atof("-0.0"));  // Should print: -0.000000
	printf("%f\n", ft_atof("0.0"));   // Should print: 0.000000
	printf("%f\n", ft_atof("123.456"));// Should print: 123.456000
	printf("%f\n", ft_atof("-123.456"));// Should print: -123.456000
	return 0;
}

// new idea with the ft atoi implementation with ft_atoi TOO BIG
// double	ft_atof(const char *str)
// {
// 	int		int1;
// 	int		frct2;
// 	char	*prt1;
// 	char	*prt2;
// 	int		i;
// 	double		p1;
// 	double		p2;
// 	double		final;

// 	int1 = 0;
// 	frct2 = 0;
// 	i = 0;
// 	while (str[int1] != '.' && str[int1] != '\0')
// 		int1++;
// 	if (str[int1] != '.')
// 	{
// 		// printf("Error: Decimal point '.' not found in input string.\n");
// 		printf("Epistrefei %f\n", (double)ft_atoi(str));
// 		return (ft_atoi(str));
// 	}
// 	prt1 = (char *)malloc(sizeof(char) * int1);
// 	while (i < int1)
// 	{
// 		prt1[i] = str[i];
// 		i++;
// 	}
// 	prt1[int1] = '\0';
// 	p1 = ft_atoi(prt1);
// 	printf("To prwto meros p1 %f\n", p1);
// 	// free(prt1);
// 	if (str[int1] == '.')
// 	{
// 		i = 0;
// 		frct2 = ft_strlen(str) - int1 - 1;
// 		prt2 = (char *)malloc(sizeof(char) * (frct2 + 1));
// 		while (i < frct2)
// 		{
// 			prt2[i] = str[i + int1 + 1];
// 			i++;
// 		}
// 		prt2[frct2] = '\0';
// 		p2 = ft_atoi(prt2);
// 		printf("To 2o merosss p2 %f\n", (double)p2/pow(10,frct2));
// 		// free(prt2);
// 	}
// 	if (p1 >= 0)
// 		final = p1 + p2 / pow(10, frct2);
// 	else
// 		final = p1 - p2 / pow(10, frct2);
// 	printf("finale %f\n", final);
// 	free(prt1);
// 	free(prt2);

// 	return (0);
// }

// int	main()
// {
// 	char	*a;

// 	a = "-0";
// 	ft_atof(a);
// 	printf("------real atof------ %f\n", atof(a));
// 	printf("... %d\n", ft_atoi(a));
// 	printf("------real---- %d\n", atoi(a));
// 	return (0);
// }