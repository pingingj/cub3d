/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freeany.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 17:49:55 by dpaes-so          #+#    #+#             */
/*   Updated: 2025/10/15 17:51:40 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void freeany(void *arr)
{
	int	i;
	void **ptr;

	ptr = (void**)arr;
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