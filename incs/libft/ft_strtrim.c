/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:57:38 by dpaes-so          #+#    #+#             */
/*   Updated: 2024/10/31 17:26:27 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_c(const char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (c == set[i])
		{
			return (1);
		}
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		len;
	int		i;
	int		j;
	char	*buffer;

	j = 0;
	i = 0;
	if (s1 == NULL)
		return (NULL);
	len = ft_strlen(s1);
	while (s1[i] && check_c(s1[i], set))
		i++;
	while (len > i && check_c(s1[len - 1], set))
		len--;
	buffer = malloc(sizeof(char) * ((len - i) + 1));
	if (!buffer)
		return (NULL);
	while ((i + j) < len)
	{
		buffer[j] = s1[i + j];
		j++;
	}
	buffer[j] = '\0';
	return (buffer);
}

/*int main()
{
	char *str = "   xxxxtripoulletx   xxxx";
	char *test = ft_strtrim(str,"x");
	printf("%s",test);
}*/
