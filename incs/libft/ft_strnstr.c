/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel <daniel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:46:47 by dpaes-so          #+#    #+#             */
/*   Updated: 2025/05/08 00:14:52 by daniel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hay, const char *needle, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (needle[0] == '\0')
		return ((char *)hay);
	while (hay[i] != '\0' && i < n)
	{
		j = 0;
		while (needle[j] != '\0' && hay[i + j] == needle[j] && (i + j) < n)
		{
			j++;
		}
		if (needle[j] == '\0')
			return ((char *)(hay + i));
		i++;
	}
	return (NULL);
}

/*int main()
{
	char hay[] = "eu nao gosto die laranjas nem de couve";
	char needle[] = "de";
	char *res = ft_strnstr(hay,needle,60);
	printf("%s\n",res);
}*/