/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarcez- < dgarcez-@student.42lisboa.com > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 16:11:27 by dpaes-so          #+#    #+#             */
/*   Updated: 2025/11/21 14:24:53 by dgarcez-         ###   ########.fr       */
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
