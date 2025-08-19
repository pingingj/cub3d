/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrbasef.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:55:00 by dpaes-so          #+#    #+#             */
/*   Updated: 2024/11/05 14:43:57 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbrbasef(unsigned int nb, char *base, int *counter)
{
	if (nb < 16)
		ft_putcharf(base[nb], counter);
	else
	{
		ft_putnbrbasef(nb / 16, base, counter);
		ft_putnbrbasef(nb % 16, base, counter);
	}
}
