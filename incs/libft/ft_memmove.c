/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:50:08 by dpaes-so          #+#    #+#             */
/*   Updated: 2024/10/31 11:17:34 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*s1;
	const unsigned char	*s2;

	s1 = (unsigned char *)dest;
	s2 = (const unsigned char *)src;
	if (s2 < s1)
	{
		s1 += n;
		s2 += n;
		while (n--)
		{
			*(--s1) = *(--s2);
		}
	}
	else
	{
		i = 0;
		while (i < n)
		{
			s1[i] = s2[i];
			i++;
		}
	}
	return (dest);
}
/*int main()
{
    char str[] = "Hello, world";
    char str2[] = "Hello, world";
    ft_memmove(str2,str2 + 7,5);
    printf("%s\n",str2);
    write(1,"\n",1);
    memmove(str,str+ 7 ,5);
    printf("%s\n",str);
}*/