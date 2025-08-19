/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:42:04 by dpaes-so          #+#    #+#             */
/*   Updated: 2024/10/31 13:30:39 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		i;
	char	*s;

	i = 0;
	s = (char *)str;
	while (s[i] != '\0')
		i++;
	while (i >= 0)
	{
		if (str[i] == (char)c)
			return (s + i);
		i--;
	}
	return (NULL);
}

/*int main()
{
	char *s = "hello world";
	char c = 'l';
	char *res = ft_strrchr(s,c);
	printf("%s\n",res);
}*/