/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdputnbrf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:55:39 by dpaes-so          #+#    #+#             */
/*   Updated: 2025/05/21 16:28:13 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdprintf.h"

void	ft_dputnbrf(int n, int *counter, int fd)
{
	char	num[50];
	int		i;

	i = 0;
	if (n == 0)
		ft_dputcharf('0', counter, fd);
	if (n == -2147483648)
		ft_dputstrf("-2147483648", counter, fd);
	else if (n < 0)
	{
		ft_dputcharf('-', counter, fd);
		n = -n;
	}
	while (n > 0)
	{
		num[i++] = (n % 10) + '0';
		n = n / 10;
	}
	while (i > 0)
		ft_dputcharf(num[--i], counter, fd);
}
