/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:49:01 by dpaes-so          #+#    #+#             */
/*   Updated: 2024/10/31 10:46:52 by dpaes-so         ###   ########.fr       */
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