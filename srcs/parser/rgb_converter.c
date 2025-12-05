/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_converter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarcez- < dgarcez-@student.42lisboa.com > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:37:31 by dgarcez-          #+#    #+#             */
/*   Updated: 2025/12/05 16:56:27 by dgarcez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

int	convert_dec(char *hexa)
{
	int	digit;
	int	value;
	int	i;

	value = 0;
	i = 0;
	digit = 0;
	while (hexa[i])
	{
		if (hexa[i] && hexa[i] >= '0' && hexa[i] <= '9')
			digit = hexa[i] - '0';
		else
			digit = 10 + (hexa[i] - 'A');
		value = value * 16 + digit;
		i++;
	}
	return (value);
}

void	convert_hexa(int color, char **result, char *base, int *i)
{
	int	remainder;

	if (color > 16)
	{
		convert_hexa(color / 16, result, base, i);
		(*i)++;
	}
	remainder = color % 16;
	(*result)[*i] = base[remainder];
}

int	color_hexa(t_game *game, t_color color)
{
	char	*hexa;
	int		result;
	int		i;

	i = 0;
	hexa = ft_calloc(7, sizeof(char));
	if (hexa == NULL)
		print_errors(game, 1, "Malloc failed in color hexa");
	convert_hexa(color.red, &hexa, "0123456789ABCDEF", &i);
	i++;
	convert_hexa(color.green, &hexa, "0123456789ABCDEF", &i);
	i++;
	convert_hexa(color.blue, &hexa, "0123456789ABCDEF", &i);
	result = convert_dec(hexa);
	free(hexa);
	return (result);
}
