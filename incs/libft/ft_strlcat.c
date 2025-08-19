/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:45:29 by dpaes-so          #+#    #+#             */
/*   Updated: 2024/10/31 10:31:15 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlcat(char *dest, const char *src, unsigned int size)
{
	unsigned int	i;
	unsigned int	dl;
	unsigned int	sl;

	i = 0;
	dl = 0;
	sl = 0;
	while (dest[dl] != '\0')
		dl++;
	while (src[sl] != '\0')
		sl++;
	if (size <= dl)
		return (sl + size);
	while (src[i] != '\0' && dl + i < (size - 1))
	{
		dest[i + dl] = src[i];
		i++;
	}
	dest[i + dl] = '\0';
	return (dl + sl);
}
/*int main() {
    char dest[50] = "Hello";
    const char *src = "Worldsvarios";
    unsigned int size = sizeof(dest);

    unsigned int result = ft_strlcat(dest, src,4);

    printf("Resulting string: %s\n", dest);
    printf("Length of new string: %u\n", result);
    return 0;
}*/