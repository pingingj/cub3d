/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrf_unsigned.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:55:27 by dpaes-so          #+#    #+#             */
/*   Updated: 2024/11/04 14:37:37 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbrf_unsigned(unsigned int n, int *counter)
{
	char	num[50];
	int		i;

	i = 0;
	if (n == 0)
	{
		ft_putcharf('0', counter);
		return ;
	}
	while (n > 0)
	{
		num[i++] = (n % 10) + '0';
		n = n / 10;
	}
	while (i > 0)
		ft_putcharf(num[--i], counter);
}
