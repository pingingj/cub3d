/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/11/19 16:41:53 by dpaes-so          #+#    #+#             */
/*   Updated: 2024/11/19 16:41:53 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE + 1];
	int			len_read;
	char		*str;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (ft_buffzero(buff, BUFFER_SIZE));
	str = ft_strjoin2(NULL, buff);
	if (!str)
		return (NULL);
	buffermove(buff);
	len_read = 1;
	while (!(ft_withnewline(str)))
	{
		len_read = read(fd, buff, BUFFER_SIZE);
		if (len_read <= 0)
			break ;
		str = ft_strjoin2(str, buff);
		if (!str)
			return (NULL);
		buffermove(buff);
	}
	if (!str[0] || len_read < 0)
		return (free(str), NULL);
	return (str);
}
