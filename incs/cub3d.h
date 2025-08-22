/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:04:42 by dgarcez-          #+#    #+#             */
/*   Updated: 2025/08/21 19:10:01 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include "math.h"
# include "minilibx-linux/mlx.h"
# include <X11/X.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdlib.h>

# define WIDTH 1440
# define HEIGHT 900
# define MOVE_SPEED 0.15
# define W 119
# define S 115
# define A 97
# define D 100
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

typedef struct s_player
{
	double		posx;
	double		posy;
	double		dirx;
	double		diry;
	double		planex;
	double		planey;
}				t_player;

typedef struct s_math
{
	double		camerax;
	double		raydirx;
	double		raydiry;
	int			mapx;
	int			mapy;
	double		deltadistx;
	double		deltadisty;
	int			stepx;
	int			stepy;
	double		sidedistx;
	double		sidedisty;
	int 		orientation;
}				t_math;

typedef struct s_game
{
	char		**map;
	t_player	player;
	t_img		bg_img;
	t_img		mini_map;
	t_math		meth;
	int			i;
	void		*mlx;
	void		*win;

}				t_game;

// generation.c
void			map_gen(t_game *game);
// clean.c
int				closex(t_game *mlx);
// events.c
int				keys(int keycode, t_game *mlx);
//mlx_adds.c
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);
#endif