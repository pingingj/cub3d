/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/11/04 14:31:01 by dpaes-so          #+#    #+#             */
/*   Updated: 2024/11/04 14:31:01 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdprintf.h"

int	ft_dformat(const char *str, va_list args, int i, int fd)
{
	unsigned long	addr;
	int				counter;

	if (str[i] == 'c')
		ft_dputcharf((char)va_arg(args, int), &counter, fd);
	if (str[i] == 's')
		ft_dputstrf(va_arg(args, char *), &counter, fd);
	if (str[i] == 'd' || str[i] == 'i')
		ft_dputnbrf(va_arg(args, int), &counter, fd);
	if (str[i] == 'u')
		ft_dputnbrf_unsigned(va_arg(args, unsigned int), &counter, fd);
	if (str[i] == 'X')
		ft_dputnbrbasef(va_arg(args, int), "0123456789ABCDEF", &counter, fd);
	if (str[i] == 'x')
		ft_dputnbrbasef(va_arg(args, int), "0123456789abcdef", &counter, fd);
	if (str[i] == '%')
		ft_dputcharf('%', &counter, fd);
	if (str[i] == 'p')
	{
		addr = (unsigned long)va_arg(args, void *);
		check_null_fd(addr, "0123456789abcdef", &counter, fd);
	}
	return (counter);
}

int	ft_dprintf(int fd, const char *str, ...)
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
			counter = ft_dformat(str, args, i, fd);
		}
		else
			ft_dputcharf(str[i], &counter, fd);
		i++;
	}
	va_end(args);
	return (counter);
}
