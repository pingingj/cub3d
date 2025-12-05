/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarcez- < dgarcez-@student.42lisboa.com > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:37:20 by dpaes-so          #+#    #+#             */
/*   Updated: 2025/12/05 15:16:17 by dgarcez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FDPRINTF_H

# define FT_FDPRINTF_H

# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int		ft_dprintf(int fd, const char *str, ...);
void	ft_dputcharf(const char c, int *counter, int fd);
void	ft_dputstrf(const char *str, int *counter, int fd);
void	ft_dputnbrf_unsigned(unsigned int n, int *counter, int fd);
void	ft_dputnbrf(int n, int *counter, int fd);
void	ft_dputnbrbasef(unsigned int nb, char *base, int *counter, int fd);
void	ft_dputptr(unsigned long int nb, char *base, int *counter, int fd);
void	check_null_fd(unsigned long int nb, char *base, int *counter, int fd);
int		ft_dformat(const char *str, va_list args, int i, int fd);
void	fd_derror(int ret);
#endif
