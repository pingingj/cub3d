/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstrf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:25:35 by dpaes-so          #+#    #+#             */
/*   Updated: 2024/11/04 14:34:00 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putstrf(const char *str, int *counter)
{
	int	i;

	i = 0;
	if (!str)
	{
		write(1, "(null)", 6);
		(*counter) += 6;
		return ;
	}
	while (str[i] != '\0')
	{
		write(1, &str[i], 1);
		i++;
		(*counter)++;
	}
}
