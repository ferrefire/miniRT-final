/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utilities.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/10 21:37:59 by ferre         #+#    #+#                 */
/*   Updated: 2025/05/12 22:09:00 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utilities.h"
#include "vector.h"
#include "libft.h"

#include <stddef.h>
#include <stdio.h>

float	clamp(float value, float min, float max)
{
	if (value < min)
		return (min);
	else if (value > max)
		return (max);
	else
		return (value);
}

t_atof_setup	atof_setup(const char *str)
{
	t_atof_setup	setup;

	setup.result = 0.0;
	setup.sign = 1.0;
	setup.divisor = 10.0;
	if (*str == '-')
		setup.sign = -1.0;
	return (setup);
}

float	ft_atof(const char *str)
{
	t_atof_setup	s;

	s = atof_setup(str);
	if (*str == '-')
		str++;
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		s.result = s.result * 10.0 + (*str - '0');
		str++;
	}
	if (*str == '.')
	{
		str++;
		while (*str >= '0' && *str <= '9')
		{
			s.result += (*str - '0') / s.divisor;
			s.divisor *= 10.0;
			str++;
		}
	}
	return (s.sign * s.result);
}

int	is_float(const char *str)
{
	int	decimal_index;
	int	i;
	int	len;

	decimal_index = -1;
	i = 0;
	len = ft_strlen(str);
	if (str[len - 1] == '\n')
		len--;
	while (str[i] && i < len)
	{
		if (str[i] == '.' && (i == 0 || i == len - 1 || decimal_index != -1))
			return (0);
		else if (str[i] == '.')
			decimal_index = i;
		else if (!ft_isdigit(str[i]) && (i > 0
				|| (str[i] != '-' && str[i] != '+')))
			return (0);
		i++;
	}
	return (1);
}

t_vec	clamp_vec(t_vec a, float min, float max)
{
	t_vec	result;

	result.x = clamp(a.x, min, max);
	result.y = clamp(a.y, min, max);
	result.z = clamp(a.z, min, max);
	return (result);
}
