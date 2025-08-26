/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarcez- <dgarcez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 22:06:42 by daniel            #+#    #+#             */
/*   Updated: 2025/08/26 19:46:05 by dgarcez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

bool	skip_comma(t_color *colors, int *i, bool last_check)
{
	if (colors->nums[*i] && colors->nums[*i] == ',')
		return (false);
	while (colors->nums[*i] && colors->nums[*i] != ',')
		(*i)++;
	if (colors->nums[*i] && colors->nums[*i] == ',' && last_check == false)
		(*i)++;
	if (colors->nums[*i] == '\0' && last_check == false)
		return (false);
	if (colors->nums[*i] != '\0' && last_check == true)
		return (false);
	return (true);
}

bool	get_colors(t_color *colors)
{
	int		i;
	char	*red;
	char	*blue;
	char	*green;

	i = 0;
	red = get_word(colors->nums, ',');
	if (skip_comma(colors, &i, false) == false)
		return (free(red), false);
	green = get_word(colors->nums + i, ',');
	if (skip_comma(colors, &i, false) == false)
		return (free(red), free(green), false);
	blue = get_word(colors->nums + i, ',');
	if (skip_comma(colors, &i, true) == false)
		return (free(red), free(green), free(blue), false);
	colors->red = ft_atol(red);
	colors->green = ft_atol(green);
	colors->blue = ft_atol(blue);
	free(red);
	free(blue);
	free(green);
	return (true);
}

bool	check_colors(t_color colors)
{
	int	i;

	i = 0;
	while (colors.nums[i])
	{
		if (!ft_isdigit(colors.nums[i]) && colors.nums[i] != ',')
			return (false);
		i++;
	}
	if (colors.red < 0 || colors.red > 255)
		return (false);
	if (colors.green < 0 || colors.green > 255)
		return (false);
	if (colors.blue < 0 || colors.blue > 255)
		return (false);
	return (true);
}

void	parse_colors(t_game *game, int fd)
{
	if (get_colors(&game->ass.ceiling) == false
		|| get_colors(&game->ass.floor) == false)
		print_errors(game, 1, "Colors aren't valid", fd);
	if (check_colors(game->ass.ceiling) == false
		|| check_colors(game->ass.floor) == false)
		print_errors(game, 1, "Colors values aren't valid", fd);
	game->ass.ceiling.hexa = color_hexa(game->ass.ceiling);
	game->ass.floor.hexa = color_hexa(game->ass.floor);
}
