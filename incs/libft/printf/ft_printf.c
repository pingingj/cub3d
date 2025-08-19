/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:31:01 by dpaes-so          #+#    #+#             */
/*   Updated: 2024/11/04 14:31:01 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "limits.h"

void	ft_format(const char *str, va_list args, int i, int *counter)
{
	unsigned long	addr;

	if (str[i] == 'c')
		ft_putcharf((char)va_arg(args, int), counter);
	if (str[i] == 's')
		ft_putstrf(va_arg(args, char *), counter);
	if (str[i] == 'd' || str[i] == 'i')
		ft_putnbrf(va_arg(args, int), counter);
	if (str[i] == 'u')
		ft_putnbrf_unsigned(va_arg(args, unsigned int), counter);
	if (str[i] == 'X')
		ft_putnbrbasef(va_arg(args, int), "0123456789ABCDEF", counter);
	if (str[i] == 'x')
		ft_putnbrbasef(va_arg(args, int), "0123456789abcdef", counter);
	if (str[i] == '%')
		ft_putcharf('%', counter);
	if (str[i] == 'p')
	{
		addr = (unsigned long)va_arg(args, void *);
		check_null(addr, "0123456789abcdef", counter);
	}
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		counter;
	int		i;

	i = 0;
	counter = 0;
	if (str[0] == '\0')
		return (0);
	va_start(args, str);
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			i++;
			ft_format(str, args, i, &counter);
		}
		else
			ft_putcharf(str[i], &counter);
		i++;
	}
	va_end(args);
	return (counter);
}

// int main(void)
// {
// 	ft_printf("%");
// }
