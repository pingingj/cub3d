/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monster_aux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarcez- < dgarcez-@student.42lisboa.com > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 14:51:03 by dpaes-so          #+#    #+#             */
/*   Updated: 2025/11/25 16:36:45 by dgarcez-         ###   ########.fr       */
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

	new_node = ft_calloc(1,sizeof(t_queue));
	if (new_node == NULL)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

void	init_dirs(int *dx, int *dy)
{
	dx[0] = 0;
	dx[1] = 0;
	dx[2] = -1;
	dx[3] = 1;
	dy[0] = -1;
	dy[1] = 1;
	dy[2] = 0;
	dy[3] = 0;
}
