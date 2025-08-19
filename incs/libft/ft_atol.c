/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarcez- <dgarcez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:30:24 by dpaes-so          #+#    #+#             */
/*   Updated: 2025/05/16 15:30:55 by dgarcez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_atol(const char *nptr, int *f)
{
	int			i;
	int			minus;
	long long	result;

	i = 0;
	minus = 1;
	result = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			minus = -minus;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9' && result < LONG_MAX)
	{
		if (minus == 1 && (result > (LONG_MAX - (nptr[i] - '0')) / 10))
			return ((*f) = 1, LONG_MAX);
		else if (minus == -1 && (-result < (LONG_MIN + (nptr[i] - '0')) / 10))
			return ((*f) = 1, LONG_MIN);
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	return (result * minus);
}
