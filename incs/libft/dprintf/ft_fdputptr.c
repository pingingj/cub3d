/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdputptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:56:01 by dpaes-so          #+#    #+#             */
/*   Updated: 2025/05/21 16:28:16 by dpaes-so         ###   ########.fr       */
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

void	check_null_fd(unsigned long int nb, char *base, int *counter, int fd)
{
	if (!nb)
		ft_dputstrf("(nil)", counter, fd);
	else
	{
		ft_dputstrf("0x", counter, fd);
		ft_dputptr(nb, base, counter, fd);
	}
}

void	ft_dputptr(unsigned long int nb, char *base, int *counter, int fd)
{
	unsigned long int	len;

	len = ft_strlen(base);
	if (nb < len)
		ft_dputcharf(base[nb], counter, fd);
	else
	{
		ft_dputptr(nb / len, base, counter, fd);
		ft_dputptr(nb % len, base, counter, fd);
	}
}
