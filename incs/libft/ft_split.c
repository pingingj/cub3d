/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 15:01:18 by dpaes-so          #+#    #+#             */
/*   Updated: 2025/05/20 19:00:06 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	countwords(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i])
			count++;
		while (s[i] != c && s[i])
			i++;
	}
	return (count);
}

static char	*wordalloc(char const **s, char c)
{
	char		*word;
	char const	*str;
	int			len;

	len = 0;
	while (**s && **s == c)
		(*s)++;
	str = (*s);
	while (**s && **s != c)
	{
		(*s)++;
		len++;
	}
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	ft_strlcpy(word, str, len + 1);
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		stringnum;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	stringnum = countwords(s, c);
	result = malloc(sizeof(char *) * (stringnum + 1));
	if (!result)
		return (NULL);
	result[stringnum] = 0;
	while (i < stringnum)
	{
		result[i] = wordalloc(&s, c);
		if (!result[i])
		{
			while (i--)
				free(result[i]);
			free(result);
			return (NULL);
		}
		i++;
	}
	return (result);
}
/*int	main(void)
{
	const char *str = '\0';
	char delimiter = ',';
	char **result = ft_split(str, delimiter);

	if (result)
	{
		for (int i = 0; result[i] != NULL; i++)
		{
			printf("Substring %d: %s\n", i, result[i]);
		}
		for (int i = 0; result[i] != NULL; i++)
		{
			free(result[i]); // Free each allocated substring
		}
		free(result); // Finally, free the array of pointers
	}
	else
	{
		printf("Memory allocation failed. (main)\n");
	}
	return (0);
}*/