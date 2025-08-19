/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdputnbrbasef.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:55:00 by dpaes-so          #+#    #+#             */
/*   Updated: 2025/05/21 16:28:08 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdprintf.h"

static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

void	ft_dputnbrbasef(unsigned int nb, char *base, int *counter, int fd)
{
	unsigned int	len;

	len = ft_strlen(base);
	if (nb < len)
		ft_dputcharf(base[nb], counter, fd);
	else
	{
		ft_dputnbrbasef(nb / len, base, counter, fd);
		ft_dputnbrbasef(nb % len, base, counter, fd);
	}
}
