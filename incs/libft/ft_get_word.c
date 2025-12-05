/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarcez- < dgarcez-@student.42lisboa.com > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 17:08:45 by dgarcez-          #+#    #+#             */
/*   Updated: 2025/12/05 17:10:45 by dgarcez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/// @brief a strdup but it stops at first encounter of a character in the string
/// @param line string u want word
/// @param c character that seperates words example space
/// @return memory allocated word
char	*get_word(char *line, char c)
{
	int		i;
	char	*word;

	i = 0;
	while (line[i] != '\0' && (line[i] != c && (line[i] < 9 || line[i] > 13)))
		i++;
	word = ft_calloc(i + 1, sizeof(char));
	if (word == NULL)
		return (NULL);
	ft_strlcpy(word, line, i + 1);
	return (word);
}
