/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarcez- < dgarcez-@student.42lisboa.com > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:46:45 by dgarcez-          #+#    #+#             */
/*   Updated: 2025/12/05 14:54:22 by dgarcez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

bool	flood_fill(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (map->grid[y])
	{
		x = 0;
		while (map->grid[y][x])
		{
			if (ft_strchr("0NEWSD", map->grid[y][x]) != NULL)
				if (flood_map(map, x, y) == false)
					return (false);
			x++;
		}
		y++;
	}
	return (true);
}

bool	check_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->map.grid[y])
	{
		x = 0;
		while (game->map.grid[y][x])
		{
			if (ft_strchr("01 NEWSDCJ\n", game->map.grid[y][x]) == NULL)
				return (false);
			x++;
		}
		y++;
	}
	return (true);
}

void	fill_spaces(t_map *map, char **new, int *i, int *j)
{
	while (*j < map->pos.x)
	{
		new[*i][*j] = ' ';
		(*j)++;
	}
	new[*i][*j] = '\0';
	(*i)++;
}

bool	change_map(t_map *map)
{
	char	**new;
	int		i;
	int		j;

	i = 0;
	new = ft_calloc(map->pos.y + 1, sizeof(char *));
	if (new == NULL)
		return (false);
	while (i < map->pos.y)
	{
		j = 0;
		new[i] = ft_calloc(map->pos.x + 1, sizeof(char));
		if (new[i] == NULL)
			return (freetrix(new), false);
		new[i] = ft_memcpy(new[i], map->grid[i], ft_strlen(map->grid[i]));
		while (new[i][j] && new[i][j] != '\n' )
			j++;
		fill_spaces(map, new, &i, &j);
	}
	new[i] = NULL;
	freetrix(map->grid);
	map->grid = new;
	return (true);
}

void	parse_map(t_game *game, char *filename, char *line)
{
	char	*funny_msg;

	get_map(game, filename, line);
	if (check_map(game) == false)
		print_errors(game, 1, "Invalid char found");
	if (get_player(game) == false)
		print_errors(game, 1, "Player not found or multiple players in map");
	if (flood_fill(&game->map) == false)
		print_errors(game, 1, "Map is invalid");
	funny_msg = check_doors(game->map, *game);
	if (funny_msg != NULL)
		print_errors(game, 1, funny_msg);
	if (change_map(&game->map) == false)
		print_errors(game, 1, "Error while changing map grid");
}
