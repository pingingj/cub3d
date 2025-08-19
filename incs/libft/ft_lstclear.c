/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:30:00 by dpaes-so          #+#    #+#             */
/*   Updated: 2024/10/30 11:06:42 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*buffer;

	while (*lst != NULL)
	{
		buffer = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		(*lst) = buffer;
	}
	*lst = NULL;
}
