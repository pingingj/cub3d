/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel <daniel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:49:01 by dpaes-so          #+#    #+#             */
/*   Updated: 2025/08/24 02:35:20 by daniel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *str, size_t n)
{
	size_t			i;
	unsigned char	*array;

	i = 0;
	array = (unsigned char *)str;
	while (i < n)
	{
		array[i] = 0;
		i++;
	}
}
/*
int main() {
    char arr[10] = "HelloWorld";
    printf("Before ft_bzero: ");
    size_t i = 0;
    while (i < 10) {
        printf("%c", arr[i]);
        i++;
    }
    printf("\n");
    ft_bzero(arr, 5);
    printf("After ft_bzero: ");
    i = 0;
    while (i < 10) {
        printf("%c", arr[i]);
        i++;
    }
    printf("\n");
    return 0;
}*/