/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarcez- < dgarcez-@student.42lisboa.com > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 17:43:49 by dgarcez-          #+#    #+#             */
/*   Updated: 2025/11/20 19:06:36 by dgarcez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

t_door	*ft_newdoor(int	x, int y)
{
	t_door	*new_node;

	new_node = ft_calloc(1,sizeof(t_door));
	if (new_node == NULL)
		return (NULL);
	new_node->cords.x = x;
	new_node->cords.y = y;
	gettimeofday(&new_node->open_time, NULL);
	new_node->open_s = (new_node->open_time.tv_sec) + (new_node->open_time.tv_usec / 1000000.0);
	new_node->next = NULL;
	return (new_node);
}

void	add_backdoor(t_door **lst, t_door *new)
{
	t_door	*buffer;

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

void	delete_1stnode(t_door **doors)
{
	t_door	*removed_node;

	if (*doors == NULL)
		return ;
	removed_node = *doors;
	*doors = (*doors)->next;
	removed_node->next = NULL;
	free(removed_node);
}

