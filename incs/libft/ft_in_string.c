/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_instr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel <daniel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 17:06:28 by daniel            #+#    #+#             */
/*   Updated: 2025/08/25 17:12:13 by daniel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/// @brief Goes through the inspect string and if there is any encounter 
///		   of any character from the find string returns true
/// @param inspect string that gets searched
/// @param find string with characters to find
/// @return true if character found in inspect
bool	in_string(char	*inspect, char *find)
{
	int		i;
	int		j;

	i = 0;
	while (inspect && inspect[i] != '\0')
	{
		j = 0;
		while(find && find[j] != '\0')
		{
			if (inspect[i] == find[j])
				return (true);
			j++;
		}
		i++;
	}
	return (false);
}
