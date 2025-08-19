/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:55:39 by dpaes-so          #+#    #+#             */
/*   Updated: 2024/11/04 14:36:35 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbrf(int n, int *counter)
{
	char	num[50];
	int		i;

	i = 0;
	if (n == 0)
		ft_putcharf('0', counter);
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		(*counter) += 11;
	}
	else if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
		(*counter)++;
	}
	while (n > 0)
	{
		num[i++] = (n % 10) + '0';
		n = n / 10;
	}
	while (i > 0)
		ft_putcharf(num[--i], counter);
}
