/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/11/19 16:43:44 by dpaes-so          #+#    #+#             */
/*   Updated: 2024/11/19 16:43:44 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2
# endif

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

char	*get_next_line(int fd);
char	*ft_strjoin2(char *s1, char *s2);
void	buffermove(char *buffer);
void	*ft_buffzero(char *buff, size_t n);
int		ft_linelen(const char *str);
int		ft_withnewline(char *line);

#endif