/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel <daniel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:56:13 by dpaes-so          #+#    #+#             */
/*   Updated: 2025/05/21 02:29:29 by daniel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

	// Commented because it wont let u initialize the node of a trees args
	// if (!s1)
	// 	return (NULL);

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*buffer;
	int		i;
	int		j;

	i = 0;
	j = 0;
	buffer = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!buffer)
		return (free((char *)s1), NULL);
	while (i < ft_strlen(s1))
	{
		buffer[i] = s1[i];
		i++;
	}
	while (j < ft_strlen(s2))
	{
		buffer[i + j] = s2[j];
		j++;
	}
	buffer[i + j] = '\0';
	free((char *)s1);
	return (buffer);
}

/*int main()
{
	char str[] = "hello, ";
	char str2[] = "world";
	char *res = ft_strjoin(str,str2);
	printf("%s\n",res);
}*/