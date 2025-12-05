/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarcez- < dgarcez-@student.42lisboa.com > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 17:43:49 by dgarcez-          #+#    #+#             */
/*   Updated: 2025/12/05 16:17:36 by dgarcez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

t_door	*ft_newdoor(int x, int y)
{
	t_door	*new_node;

	new_node = ft_calloc(1, sizeof(t_door));
	if (new_node == NULL)
		return (NULL);
	new_node->cords.x = x;
	new_node->cords.y = y;
	gettimeofday(&new_node->open_time, NULL);
	new_node->open_s = (new_node->open_time.tv_sec)
		+ (new_node->open_time.tv_usec / 1000000.0);
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

void	free_doors(t_game *game)
{
	t_door	*remove_node;

	if (game->doors_opened == NULL)
		return ;
	while (game->doors_opened)
	{
		remove_node = game->doors_opened;
		game->doors_opened = game->doors_opened->next;
		free(remove_node);
	}
}

void	delete_door_node(t_door **doors)
{
	t_door	*temp;
	t_door	*remove_node;

	if (*doors == NULL)
		return ;
	temp = *doors;
	while (temp)
	{
		if (temp->to_delete == true)
		{
			remove_node = temp;
			(*doors) = temp->next;
			free(remove_node);
			return ;
		}
		if (temp->next->to_delete == true)
		{
			remove_node = temp->next;
			temp->next = temp->next->next;
			free(remove_node);
			return ;
		}
		temp = temp->next;
	}
}
