/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freeany.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarcez- < dgarcez-@student.42lisboa.com > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 17:49:55 by dpaes-so          #+#    #+#             */
/*   Updated: 2025/12/05 17:09:27 by dgarcez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	freeany(void *arr)
{
	int		i;
	void	**ptr;

	ptr = (void **)arr;
	i = 0;
	if (!ptr)
		return ;
	while (ptr && ptr[i])
	{
		if (ptr[i])
			free(ptr[i]);
		i++;
	}
	free(arr);
}
