/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarcez- < dgarcez-@student.42lisboa.com > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:30:24 by dpaes-so          #+#    #+#             */
/*   Updated: 2025/12/05 17:09:37 by dgarcez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol(char *num)
{
	int		i;
	int		sign;
	long	result;

	sign = 1;
	i = 0;
	result = 0;
	while (num[i] && (num[i] == ' ' || (num[i] >= 9 && num[i] <= 13)))
		i++;
	if (num[i] == '+' || num[i] == '-')
	{
		if (num[i] == '-')
			sign = -1;
		i++;
	}
	while (num[i] && (num[i] >= '0' && num[i] <= '9'))
	{
		result = result * 10 + num[i] - '0';
		if (result > INT_MAX)
			break ;
		i++;
	}
	if (num[i] && (num[i] < '0' || num[i] > '9'))
		result = -1;
	return (result * sign);
}
