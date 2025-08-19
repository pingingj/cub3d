/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:04:42 by dgarcez-          #+#    #+#             */
/*   Updated: 2025/08/19 15:09:59 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include <X11/X.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdlib.h>

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_img;

typedef struct s_pos
{
	int			x;
	int			y;
}				t_pos;

typedef struct s_game
{
	char		**map;
	t_pos		pos;
	t_img		bg_img;
	int			i;
	void		*mlx;
	void		*win;
}				t_game;


//generation.c
void map_gen(t_game *game);
//clean.c
int	closex(t_game *mlx);
//events.c
int	keys(int keycode, t_game *mlx);
#endif