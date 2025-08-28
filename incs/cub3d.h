/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:04:42 by dgarcez-          #+#    #+#             */
/*   Updated: 2025/08/28 14:00:45 by dpaes-so         ###   ########.fr       */
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

# define WIDTH 1920
# define HEIGHT 1080
# define MOVE_SPEED 0.03
# define RUN_SPEED 0.05
# define W 119
# define S 115
# define A 97
# define D 100
# define F 102
# define PI 3.14159265358979323846
# define RADIUS 0.1
# define ARROW_RIGHT 65363
# define ARROW_LEFT 65361
# define ANGLE_NUMBERS 8
# define rot_speed 0.04
# define SHIFT 65505
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

typedef struct s_player
{
	double		speed;
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
	int			orientation;
	bool		door;
}				t_math;

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

typedef struct s_map
{
	char		**grid;
	int			breakp;
	t_pos		pos;
	bool		exists;
}				t_map;

typedef struct s_game
{
	t_map		map;
	t_assets	ass;
	t_pos		pos;
	t_img		bg_img;
	t_player	player;
	t_img		mini_map;
	t_math		meth;
	int			*move;
	int			i;
	void		*mlx;
	void		*win;

}				t_game;

// generation
void			map_gen(t_game *game);
void			math_with_an_e(t_game *game);
int				draw_minimap(t_game *game);
void			setup_ray(t_game *game, int x);
void			dda_prep(t_game *game);
int				hit_wall(t_game *game);
double			calc_wall_dist(t_game *game);
void			wall_size(t_game *game, double walldist, int *sdraw,
					int *edraw);
void			create_frame(t_game *game);
void			artistic_moment(t_game *game, int x, int sdraw, int edraw);
// clean
int				closex(t_game *mlx);
// mlx_adds
void			my_mlx_pixel_put(t_img *data, int x, int y, int color);
// events
int				keys(int keycode, t_game *mlx);
int				pixel_get(t_img *data, int x, int y);
int				key_press(int keycode, t_game *game);
int				key_release(int keycode, t_game *game);
int				move(t_game *game);
void			move_foward(t_game *game, double speed);
void			move_back(t_game *game, double speed);
void			move_left(t_game *game, double speed);
void			move_right(t_game *game, double speed);
void			look_right(t_game *game);
void			look_left(t_game *game);
bool			hit_box(t_game *game, double x, double y);
// drawing map
void			draw_wall(t_game *game, int cx, int cy);
void			draw_floor(t_game *game, int cx, int cy);
int				draw_minimap(t_game *game);
// parse
bool			parse(t_game *game, char *filename);
void			print_errors(t_game *game, int error, char *msg, int fd);
void			free_game(t_game *game);
void			parse_colors(t_game *game, int fd);
bool			skip_comma(t_color *colors, int *i, bool last_check);
bool			get_colors(t_color *colors);
bool			check_colors(t_color colors);
int				color_hexa(t_color color);
void			parse_map(t_game *game, int fd, char *filename);
bool			get_map(t_game *game, int fd, char *filename);
bool			flood_map(t_map *map, int x, int y);
void			print_info(t_game game);
#endif