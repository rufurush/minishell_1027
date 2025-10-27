/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotadashirui <kotadashirui@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 19:43:26 by kotadashiru       #+#    #+#             */
/*   Updated: 2025/08/18 21:31:36 by kotadashiru      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check_overflow(long r, int d, int s)
{
	if (s == 1)
	{
		if (r > INT_MAX / 10 || (r == INT_MAX / 10 && d > 7))
			return (INT_MAX);
	}
	else
	{
		if (r > (-(long)INT_MIN) / 10 || (r == (-(long)INT_MIN) / 10 && d > 8))
			return (INT_MIN);
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	size_t	i;
	long	result;
	int		sign;
	int		digit;
	int		overflow;

	i = 0;
	result = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		digit = str[i] - '0';
		overflow = ft_check_overflow(result, digit, sign);
		if (overflow)
			return (overflow);
		result = result * 10 + digit;
		i++;
	}
	return ((int)(result * sign));
}
