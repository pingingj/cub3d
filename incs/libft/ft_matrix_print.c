/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 16:11:27 by dpaes-so          #+#    #+#             */
/*   Updated: 2025/08/19 18:06:09 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_matrix_print(char **matrix)
{
	int	j;
	int	i;

	j = 0;
	while (matrix[j])
	{
		i = 0;
		while (matrix[j][i])
		{
			ft_printf("%c", matrix[j][i]);
			i++;
		}
		j++;
	}
}
