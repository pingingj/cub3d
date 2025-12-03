/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:04:42 by dgarcez-          #+#    #+#             */
/*   Updated: 2025/12/03 17:04:33 by dpaes-so         ###   ########.fr       */
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
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

// pixels
# define WIDTH 1440
# define HEIGHT 900
# define AMBIENT 0.03
# define MOVE_SPEED 0.08
# define MONSTER_SPEED 0.1
# define RUN_SPEED 0.11

// keys
# define W 119
# define S 115
# define A 97
# define D 100
# define F 102
# define COMMA 44
# define DOT 46
# define PI 3.14159265358979323846
# define RADIUS 0.1
# define ARROW_LEFT 65361
# define ARROW_UP 65362
# define ARROW_RIGHT 65363
# define ARROW_DOWN 65364
# define ANGLE_NUMBERS 8
# define ROT_SPEED 0.0008
# define ARROW_ROT_SPEED 0.06
# define F 102
# define M 109
# define L 108
# define H 104
# define P 112
# define ENTER 65293
# define SHIFT 65505
# define ARROW_RIGHT 65363
# define ARROW_LEFT 65361
// shit code

# define SPRITE_SZ 96
# define COUNTER_H 152
# define COUNTER_W 288
# define NUM_H 101
# define NUM_W 42

// parser
# define NO 0
# define EA 1
# define WE 2
# define SO 3
# define CL 4
# define EN 5
# define DO 6
# define MAX_CL 8

typedef struct s_img
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				w;
	int				h;
	char			*filename;
}					t_img;

typedef struct s_point
{
	int				x;
	int				y;
}					t_point;

typedef struct s_pos
{
	double			x;
	double			y;
}					t_pos;

typedef struct s_player
{
	double			speed;
	double			posx;
	double			posy;
	double			dirx;
	double			diry;
	double			planex;
	double			planey;
	int				look;
}					t_player;

typedef struct s_math
{
	double			camerax;
	double			raydirx;
	double			raydiry;
	int				mapx;
	int				mapy;
	double			deltadistx;
	double			deltadisty;
	int				stepx;
	int				stepy;
	double			sidedistx;
	double			sidedisty;
	int				orientation;
	bool			door;
	bool			looking_door;
	int				line_height;
}					t_math;

typedef struct s_color
{
	int				red;
	int				green;
	int				blue;
	char			*nums;
	int				hexa;
}					t_color;

typedef struct s_sprite
{
	bool			enemy;
	bool			exists;
	t_img			texture;
	t_pos			cords;
	int				width;
	int				height;
}					t_sprite;

typedef struct s_assets
{
	t_img			textures[7];
	t_img			barrel;
	t_color			ceiling;
	t_color			floor;
	t_sprite		*sprites;
	t_sprite		enemy;
	t_sprite		door;
	t_img			death_screen;
	t_img			pause_screen;
	t_img			win_screen;
	int				collect_amount;
}					t_assets;

typedef struct s_door
{
	t_point			cords;
	struct timeval	open_time;
	double			open_s;
	struct s_door	*next;
	int				frame;
	bool			to_delete;
}					t_door;

typedef struct s_map
{
	char			**grid;
	int				breakp;
	t_pos			pos;
	bool			exists;
	int				height;
}					t_map;

typedef struct s_arrow
{
	double			size;
	double			tip_len;
	double			base_len;
	double			bottom_len;
	double			sides_len;
	t_pos			tip;
	t_pos			left;
	t_pos			right;
	t_pos			bottom;
}					t_arrow;

typedef struct s_mini
{
	int				tile_size;
	bool			show;
	int				height;
	int				width;
	int				offset;
	t_pos			size;
	t_pos			center;
	t_arrow			arrow;
}					t_mini;

typedef struct s_queue
{
	t_point			*content;
	struct s_queue	*next;
}					t_queue;

typedef struct s_spath
{
	int				i;
	double			mathx;
	double			mathy;
	double			transformx;
	double			transformy;
	double			inverse;
	double			spritexlocation;
	double			sprite_height;
	double			sprite_width;
	int				sdrawx;
	int				sdrawy;
	int				edrawx;
	int				edrawy;
	int				sp_index;
	int				texx;
	int				screen_center;
	int				py;
	int				d;
	int				texy;
	int				color;
	double			intensity;
	t_img			spt;
}					t_spath;

enum				e_game_state
{
	main_menu,
	running,
	Pause,
	death_screen,
	Win_screen,
	Finished
};

enum				e_move
{
	forwards,
	backwards,
	left,
	right,
	arrow_right,
	arrow_left,
	arrow_up,
	arrow_down,
	zoom_in,
	zoom_out
};

typedef struct s_game_flags
{
	int				game_state;
	bool			collectibles_exist;
	bool			button_ready;
	bool			look_flag_right;
	bool			look_flag_left;
	bool			laggy_lantern;
}					t_game_flags;

typedef struct s_cale_img_math
{
	unsigned char	*dst_row;
	unsigned char	*src_row;
	unsigned char	rgba[4];
	int				color;
	int				s_bpp;
	int				d_bpp;
	t_point			xy;
	t_point			s_xy;
}					t_cale_img_math;

typedef struct s_game
{
	int				fd;
	t_map			map;
	t_assets		ass;
	t_img			bg_img;
	t_player		player;
	t_mini			mini;
	t_math			meth;
	t_pos			mouse;
	t_queue			*queue;
	t_point			**prev;
	t_spath			spath;
	t_game_flags	g_flags;
	t_img			slash;
	t_img			title[194];
	t_img			door_frames[5];
	t_img			nums[9];
	t_door			*doors_opened;
	t_cale_img_math	scaling;
	int				collected_comics;
	bool			look_flag_right;
	bool			look_flag_left;
	bool			laggy_lanter;
	void			*mlx;
	void			*win;
	double			light;
	double			walldist;
	int				wall_dist_sp[WIDTH];
	int				move[10];
	double			bob;
	int				**visited;
	int				monster_target_x;
	int				monster_target_y;
	int				monster_has_target;
	int				fps_lock;
}					t_game;

// fps
void				ft_sleep(double mili_secs);
double				fps_counter(t_game *game);
t_img				*draw_scaled_img(t_game *game, t_img *src, t_point scale,
						double intensity);
void				make_fade_screen(t_game *game, t_img *img);
void				make_pause_screen(t_game *game);
// extras
t_game				*mem_save(t_game *to_save);
int					mouse(int x, int y, t_game *game);
int					mouse_press(int keycode, int x, int y, t_game *game);
// generation
void				map_gen(t_game *game);
void				math_with_an_e(t_game *game);
void				setup_ray(t_game *game, int x);
void				dda_prep(t_game *game);
int					hit_wall(t_game *game);
double				calc_wall_dist(t_game *game);
void				wall_size(t_game *game, double walldist, int *sdraw,
						int *edraw);
void				create_frame(t_game *game);
void				artistic_moment(t_game *game, int x, int sdraw, int edraw);
int					add_light(int color, double intensity);
double				flashlight(int x, int y, t_game *game, bool is_wall);
void				draw_title(t_game *game, int i);
int					menu(t_game *game);
double				flashlight(int x, int y, t_game *game, bool is_wall);

// monster
int					monster(t_game *game);
t_queue				*ft_queuenew(void *content);
void				ft_queueadd_back(t_queue **lst, t_queue *new);
void				free_queue(t_queue *queue);
void				init_dirs(int *dx, int *dy);
void				choose_pathfinding_alg(t_game *game, t_pos target, t_pos *d,
						bool *step_monster);

int					has_line_of_sight(double ex, double ey, double px,
						double py);
int					is_near_wall(t_game *game, double x, double y);
// sprites
void				draw_sprite(t_game *game);
void				draw_sprite_prep(t_game *game);
void				sprite_math(t_game *game, int *order);
void				start_sprite_handle(t_game *game, int *order);
void				hande_sprites(t_game *game);
void				sort_dist(int *order, double *sprit_distance, t_game *game);
void				sprite_text_boundary_check(t_game *game);
double				sprite_flashlight(int x, int y, t_game *game,
						double sprite_dist);
// clean
int					closex(t_game *mlx);
// mlx_adds
void				my_mlx_pixel_put(t_img *data, int x, int y, int color);
// events
int					keys(int keycode, t_game *mlx);
int					pixel_get(t_img *data, int x, int y);
int					key_press(int keycode, t_game *game);
int					key_release(int keycode, t_game *game);
int					action(t_game *game);
void				move_foward(t_game *game, double speed);
void				move_back(t_game *game, double speed);
void				move_left(t_game *game, double speed);
void				move_right(t_game *game, double speed);
void				look_right(t_game *game);
void				look_left(t_game *game);
bool				hit_box(t_game *game, double x, double y, int who);
bool				open_door(t_game *game, double x, double y);
void				change_flag(int key, t_game *game);

// drawing map
void				draw_wall(t_game *game, int cx, int cy);
void				draw_floor(t_game *game, int cx, int cy);
void				draw_minimap(t_game *game, double playerx, double playery);
void				draw_arrow(t_game *game, int cx, int cy);
void				draw_miniframe(t_game *game);
void				minimap_tiles(t_game game, t_pos tile_pos, t_pos win_pos);
bool				parse(t_game *game, char *filename);
void				print_errors(t_game *game, int error, char *msg);
void				free_game(t_game *game);
void				init_vars(t_game *game);
char				*get_textures(t_game *game);
char				**letters_init(void);
void				parse_colors(t_game *game);
bool				skip_comma(t_color *colors, int *i, bool last_check);
bool				get_colors(t_color *colors);
bool				check_colors(t_color colors);
int					color_hexa(t_color color);
void				parse_map(t_game *game, char *filename, char *line);
bool				get_map(t_game *game, char *filename, char *line);
bool				flood_map(t_map *map, int x, int y);
bool				get_player(t_game *game);
char				*check_doors(t_map map, t_game game);
void				make_enemy(t_game *game);
void				print_info(t_game game);
int					convert_dec(char *hexa);
void				convert_hexa(int color, char **result, char *base, int *i);
void				free_queue(t_queue *queue);

// textures
int					textures(t_game *game);
void				img_init(t_game *game, char *filename, t_img *img);
void				ft_sleep(double mili_secs);
t_img				*draw_scaled_img(t_game *game, t_img *src, t_point scale,
						double intensity);

// doors
t_door				*ft_newdoor(int x, int y);
void				add_backdoor(t_door **lst, t_door *new);
void				door_timer(t_game *game);
void				delete_door_node(t_door **doors);
void				free_doors(t_game *game);
#endif