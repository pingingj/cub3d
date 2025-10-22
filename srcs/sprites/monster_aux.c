/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monster_clean.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 14:51:03 by dpaes-so          #+#    #+#             */
/*   Updated: 2025/10/16 14:51:30 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

void	free_queue(t_queue *queue)
{
	t_queue	*tmp;

	while (queue)
	{
		tmp = queue->next;
		free(queue->content);
		free(queue);
		queue = tmp;
	}
}

void	ft_queueadd_back(t_queue **lst, t_queue *new)
{
	t_queue	*buffer;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	buffer = *lst;
	while (buffer->next != NULL)
		buffer = buffer->next;
	buffer->next = new;
}

t_queue	*ft_queuenew(void *content)
{
	t_queue	*new_node;

	new_node = malloc(sizeof(t_queue));
	if (new_node == NULL)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}
