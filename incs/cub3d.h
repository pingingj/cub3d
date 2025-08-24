/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel <daniel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:04:42 by dgarcez-          #+#    #+#             */
/*   Updated: 2025/08/24 03:35:55 by daniel           ###   ########.fr       */
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

# define NO 0
# define EA 1
# define WE 2
# define SO 3

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	char		*filename;
}				t_img;

typedef struct s_pos
{
	int			x;
	int			y;
}				t_pos;

typedef struct s_color
{
	int			red;
	int			green;
	int			blue;
	char		*nums;
	int			hexa;
}				t_color;

typedef struct s_assets
{
	t_img		walls[4];
	t_color		ceiling;
	t_color		floor;
}				t_assets;

typedef struct s_game
{
	char		**map;
	t_assets	ass;
	t_pos		pos;
	t_img		bg_img;
	void		*mlx;
	void		*win;
}				t_game;

bool	parse(char *filename, t_game *game);
void	print_errors(t_game *game, int error, char *msg);
void	free_game(t_game *game);
bool	skip_comma(t_color *colors, int	*i, bool last_check);
bool	get_colors(t_color *colors);
bool	check_colors(t_color colors);
int		color_hexa(t_color color);

#endif