/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel <daniel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 02:29:34 by daniel            #+#    #+#             */
/*   Updated: 2025/05/21 02:29:35 by daniel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_sort_matrix(char **matrix)
{
	int		i;
	int		j;
	int		size;
	char	*tmp;

	i = 0;
	size = 0;
	while (matrix[size])
		size++;
	while (i < size - 1)
	{
		j = i + 1;
		while (j < size)
		{
			if (ft_strcmp(matrix[i], matrix[j]) > 0)
			{
				tmp = matrix[i];
				matrix[i] = matrix[j];
				matrix[j] = tmp;
			}
			j++;
		}
		i++;
	}
}
