/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:48:31 by dpaes-so          #+#    #+#             */
/*   Updated: 2024/10/31 11:28:28 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t size)
{
	size_t			i;
	unsigned char	*array;

	i = 0;
	array = (unsigned char *)str;
	while (i < size)
	{
		array[i] = (unsigned char)c;
		i++;
	}
	return (str);
}

/*int main() 
{
    char arr[10] = "abcdefghi";  // Initialize with some values
    printf("Before ft_memset: %s\n", arr);
    ft_memset(arr, 'X', 5);
    printf("After ft_memset: %s\n", arr); 
    printf("Byte values in arr:\n");
    return 0;
}*/