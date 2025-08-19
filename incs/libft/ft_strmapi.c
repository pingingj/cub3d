/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:34:07 by dpaes-so          #+#    #+#             */
/*   Updated: 2024/10/31 13:32:22 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		size;
	int		i;
	char	*buffer;

	size = 0;
	i = 0;
	if (!s)
		return (NULL);
	while (s[size] != '\0')
		size++;
	buffer = malloc(sizeof(char) * size + 1);
	if (!buffer)
		return (NULL);
	while (s[i] != '\0')
	{
		buffer[i] = f(i, s[i]);
		i++;
	}
	buffer[i] = '\0';
	return (buffer);
}

/*
char toupper(unsigned int index, char c) {

    if (c >= 'a' && c <= 'z') 
        return c - 32;
    return c; 
}

int main() {
    char *str = "hello world!";
    char *res;
    res = ft_strmapi(str, toupper);
    printf("Original: %s\n", str);
    printf("Transformed: %s\n", res);
    free(res); 


    return 0;
}*/