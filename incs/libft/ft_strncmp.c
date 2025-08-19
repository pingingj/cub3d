/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:44:37 by dpaes-so          #+#    #+#             */
/*   Updated: 2024/11/04 12:03:10 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n - 1)
	{
		if (!(s1[i] == s2[i]))
			return ((unsigned char)s1[i] - ((unsigned char )s2[i]));
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
