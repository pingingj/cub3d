/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:44:12 by dpaes-so          #+#    #+#             */
/*   Updated: 2024/11/19 16:44:12 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_linelen(const char *str)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] != '\n')
		i++;
	if (str && str[i] == '\n')
		i++;
	return (i);
}

char	*ft_strjoin2(char *s1, char *s2)
{
	char	*buffer;
	int		i;
	int		j;

	i = 0;
	j = 0;
	buffer = malloc(sizeof(char) * (ft_linelen(s1) + ft_linelen(s2) + 1));
	if (!buffer)
		return (NULL);
	while (s1 && s1[i] != '\0')
	{
		buffer[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0' && s2[j] != '\n')
		buffer[i++] = s2[j++];
	if (s2[j] == '\n')
		buffer[i++] = '\n';
	buffer[i] = '\0';
	free(s1);
	return (buffer);
}

void	buffermove(char *buffer)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (buffer[i] != '\n' && buffer[i])
		i++;
	if (buffer[i] == '\n')
		i++;
	while (buffer[i + j] != '\0')
	{
		buffer[j] = buffer[i + j];
		j++;
	}
	while (buffer[j])
	{
		buffer[j] = '\0';
		j++;
	}
}

int	ft_withnewline(char *line)
{
	int	len;

	len = ft_linelen(line);
	while (len >= 0)
	{
		if (line[len] == '\n')
			return (1);
		len--;
	}
	return (0);
}

void	*ft_buffzero(char *buff, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		buff[i++] = 0;
	return (NULL);
}
