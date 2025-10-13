/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarcez- <dgarcez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:04:42 by dgarcez-          #+#    #+#             */
/*   Updated: 2025/10/09 14:08:16 by dpaes-so         ###   ########.fr       */
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

// pixels
# define WIDTH 1440
# define HEIGHT 900
# define AMBIENT 0.03
# define MOVE_SPEED 0.09
# define RUN_SPEED 0.12
# define CTRL 65507
# define SPACE 32
# define TILE_SIZE 40
# define MINIMAP_RADIUS 2
# define MINIMAP_TILES 5

// keys
# define W 119
# define S 115
# define A 97
# define D 100
# define F 102
# define PI 3.14159265358979323846
# define RADIUS 0.1
# define ARROW_LEFT 65361
# define ARROW_UP 65362
# define ARROW_RIGHT 65363
# define ARROW_DOWN 65364
# define ANGLE_NUMBERS 8
# define ROT_SPEED 0.0003
# define ARROW_ROT_SPEED 0.06
# define M 109
# define F 102
# define SHIFT 65505
# define ARROW_RIGHT 65363
# define ARROW_LEFT 65361

// circle bullshit
# define RADIUS_MINI 5
# define ANGLE_NUMBERS_MINI 50

// parser
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
	int			w;
	int			h;
	char		*filename;
}				t_img;


typedef struct s_point
{
	int		x;
	int		y;
}				t_point;

typedef struct s_pos
{
	double		x;
	double		y;
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
	int			look;
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
	bool		looking_door;
}				t_math;

typedef struct s_color
{
	int			red;
	int			green;
	int			blue;
	char		*nums;
	int			hexa;
}				t_color;

typedef struct s_sprite
{
	t_img		texture;
	t_pos		cords;
	int			width;
	int			height;
}				t_sprite;

typedef struct s_assets
{
	t_img		walls[4];
	t_color		ceiling;
	t_color		floor;
	t_img		barrel;
	t_sprite	*collectible;
	t_sprite	enemy;
	int			collect_amount;
}				t_assets;

typedef struct s_map
{
	char		**grid;
	int			breakp;
	t_pos		pos;
	bool		exists;
	int			height;
}				t_map;

typedef struct s_mini
{
	int			tile_size;
	bool		show;
	int			height;
	int			width;
	int			offset;
	t_pos		size;
	t_pos		center;
}				t_mini;

typedef struct s_game
{
	t_map		map;
	t_assets	ass;
	t_img		bg_img;
	t_player	player;
	t_mini		mini;
	t_math		meth;
	t_pos		mouse;
	bool		look_flag_right;
	bool		look_flag_left;
	void		*mlx;
	void		*win;
	double		light;
	double		walldist;
	int			wall_dist_sp[WIDTH];
	int			*move;
	int			bob;
	int 		**visited;
	t_point 	**parent;
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
int	add_light(int color, double intensity);
double	flashlight(int x, int y, t_game *game, bool is_wall);
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
int				convert_dec(char *hexa);
void			convert_hexa(int color, char **result, char *base, int *i);

// textures
int				textures(t_game *game);
#endif