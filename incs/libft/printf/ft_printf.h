/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:37:20 by dpaes-so          #+#    #+#             */
/*   Updated: 2024/11/04 14:24:41 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H

# define FT_PRINTF_H

# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int		ft_printf(const char *str, ...);
void	ft_putstrf(const char *str, int *counter);
void	ft_putnbrf_unsigned(unsigned int n, int *counter);
void	ft_putnbrf(int n, int *counter);
void	ft_putstrf(const char *str, int *counter);
void	ft_putcharf(const char c, int *counter);
void	ft_putnbrbasef(unsigned int nb, char *base, int *counter);
void	ft_putptr(unsigned long int nb, char *base, int *counter);
void	check_null(unsigned long int nb, char *base, int *counter);
void	ft_format(const char *str, va_list args, int i, int *counter);

#endif