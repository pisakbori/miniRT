/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmakario <cmakario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:38:42 by cmakario          #+#    #+#             */
/*   Updated: 2024/09/20 14:22:00 by cmakario         ###   ########.fr       */
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

double	scientific_notation(const char **str)
{
	double	expo_sign;
	double	expo;

	expo_sign = 1.0;
	expo = 0.0;
	if (**str == 'e' || **str == 'E')
	{
		(*str)++;
		if (**str == '-')
		{
			expo_sign = -1;
			(*str)++;
		}
		else if (**str == '+')
			(*str)++;
	}
	while (ft_isdigit(**str))
	{
		expo = expo * 10 + (**str - '0');
		(*str)++;
	}
	printf("exposing * expo %f\n", expo_sign * expo);
	return (expo_sign * expo);
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
	result *= pow(10, scientific_notation(&str));
	return (sign * result);
}

/* ----------TEST-------------- */
/* int main() {
	printf("%f\n", ft_atof(" -123.456e-2"));	// Should print: -0.000000
	printf("%f\n", ft_atof("14e2"));
	printf("%f\n", atof("14e2"));
	printf("%f\n", ft_atof("-0"));	// Should print: -0.000000
	printf("%f\n", ft_atof("-0.0"));  // Should print: -0.000000
	printf("%f\n", ft_atof("0.0"));   // Should print: 0.000000
	printf("%f\n", ft_atof("123.456"));// Should print: 123.456000
	printf("%f\n", ft_atof("-123.456"));// Should print: -123.456000
	return 0;
} */
