/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:55:44 by dpaes-so          #+#    #+#             */
/*   Updated: 2024/10/31 17:27:03 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*buffer;
	size_t	i;
	size_t	str_len;

	if (!s)
		return (NULL);
	str_len = (size_t)ft_strlen(s);
	i = 0;
	if (start + len > str_len)
		len = str_len - start;
	if (start >= str_len)
		len = 0;
	buffer = malloc(sizeof(char) * (len + 1));
	if (buffer == NULL)
		return (NULL);
	while (i < len && s[start + i] != '\0')
	{
		buffer[i] = s[start + i];
		i++;
	}
	buffer[i] = '\0';
	return (buffer);
}

/*int main() 
{
    const char *original = "Hello, World!";
    unsigned int start = 5; 
    size_t len = 9;      
    char *substring = ft_substr(original, start, len);
	
    printf("Original string: %s\n", original);
    printf("Substring: %s\n", substring);
    free(substring);

    return 0;
}*/
