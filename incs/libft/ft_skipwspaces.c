/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skipwspaces.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarcez- <dgarcez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 15:31:16 by dgarcez-          #+#    #+#             */
/*   Updated: 2025/08/19 15:31:28 by dgarcez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	skip_wspaces(char **input)
{
	if (**input && (**input == ' ' || (**input >= 9 && **input <= 13)))
	{
		while (**input && (**input == ' ' || (**input >= 9 && **input <= 13)))
			(*input)++;
		return (true);
	}
	return (false);
}