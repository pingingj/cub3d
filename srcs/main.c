/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:04:14 by dgarcez-          #+#    #+#             */
/*   Updated: 2025/10/28 16:13:25 by dpaes-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

int	mouse(int x, int y, t_game *game)
{
	game->mouse.x = x - WIDTH / 2;
    if(game->g_flags.game_state != running)
        return(1);
    if (x > WIDTH / 2)
	    game->move[4] = 1;
	if (x < WIDTH / 2)
		game->move[5] = 1;
	if (x == WIDTH / 2)
	{
		game->move[4] = 0;
		game->move[5] = 0;
	}
	game->mouse.y = y - HEIGHT / 2;
	if (y > HEIGHT / 2)
	{
		game->player.look -= game->mouse.y / 10;
		if (game->player.look < -1000)
			game->player.look += game->mouse.y / 10;
	}
	if (y < HEIGHT / 2)
	{
		game->player.look += -game->mouse.y / 10;
		if (game->player.look > 1000)
			game->player.look -= -game->mouse.y / 10;
	}
    if(game->g_flags.game_state == running)
    {
        if (x != WIDTH / 2 || y != HEIGHT / 2)
            mlx_mouse_move(game->mlx, game->win, WIDTH / 2, HEIGHT / 2);
    }
	return (0);
}

void ft_sleep(double mili_secs)
{
    double last_time = 0.0;
    struct timeval now;
    double current_time;

    if (mili_secs <= 0.0)
        return;

    gettimeofday(&now, NULL);
    current_time = (now.tv_sec * 1000.0) + (now.tv_usec / 1000.0);
    if (last_time == 0.0)
        last_time = current_time;
    while (1)
    {
        gettimeofday(&now, NULL);
        current_time = (now.tv_sec * 1000.0) + (now.tv_usec / 1000.0);
        if (current_time - last_time >= mili_secs)
            break;
    }
}

double fps_counter(t_game *game)
{
    static int frames;
    struct timeval now;
    static double last_time;
    static double next_deadline_ms;
    double current_time;
    double fsleep = 0.0;

    if (game->fps_lock > 0)
    {
        double target_ms = 1000.0 / (double)game->fps_lock;
        gettimeofday(&now, NULL);
        double now_ms = (now.tv_sec * 1000.0) + (now.tv_usec / 1000.0);
        if (next_deadline_ms == 0.0)
            next_deadline_ms = now_ms + target_ms;
        fsleep = next_deadline_ms - now_ms;
        if (fsleep < 0.0)
            fsleep = 0.0;
        next_deadline_ms += target_ms;
        if (next_deadline_ms < now_ms - target_ms)
            next_deadline_ms = now_ms + target_ms;
    }
    else
        next_deadline_ms = 0.0;
    gettimeofday(&now, NULL);
    current_time = now.tv_sec + now.tv_usec / 1000000.0;
    if (last_time == 0.0)
        last_time = current_time;
    frames++;
    if (current_time - last_time >= 1.0)
    {
        ft_printf("FPS: %d\n", frames);
        frames = 0;
        last_time = current_time;
    }
    return (fsleep);
}

int	new_blank_img(t_game *game, t_img *img, int w, int h)
{
	img->img = mlx_new_image(game->mlx, w, h);
	if (!img->img)
		return (0);
	img->addr = mlx_get_data_addr(img->img,
			&img->bits_per_pixel, &img->line_length, &img->endian);
	if (!img->addr)
	{
		mlx_destroy_image(game->mlx, img->img);
		img->img = NULL;
		return (0);
	}
	img->w = w;
	img->h = h;
	img->filename = NULL;
	return (1);
}

void	draw_scaled_img(t_game *game, t_img *src,bool apply,double intensity)
{
	t_img			dst;
	int				s_bpp;
	int				d_bpp;
	int				x;
	int				y;
	int				sx;
	int				sy;
	unsigned char	*dst_row;
	unsigned char	*src_row;
	unsigned char b;
	unsigned char g;
	unsigned char r;
	unsigned char a;
	int color;

	if (!game || !src || !src->img || !src->addr || src->w <= 0 || src->h <= 0)
		return ;
	if (!new_blank_img(game, &dst, WIDTH, HEIGHT))
	{
		mlx_put_image_to_window(game->mlx, game->win, src->img,
			(WIDTH - src->w) / 2, (HEIGHT - src->h) / 2);
		return ;
	}
	s_bpp = src->bits_per_pixel / 8;
	d_bpp = dst.bits_per_pixel / 8;
	y = 0;
	while (y < dst.h)
	{
		sy = (int)((long long)y * src->h / dst.h);
		if (sy >= src->h)
			sy = src->h - 1;
		dst_row = (unsigned char *)dst.addr + y * dst.line_length;
		src_row = (unsigned char *)src->addr + sy * src->line_length;
		x = 0;
		while (x < dst.w)
		{
			sx = (int)((long long)x * src->w / dst.w);
			if (sx >= src->w)
				sx = src->w - 1;
			b = src_row[sx * s_bpp + 0];
			g = src_row[sx * s_bpp + 1];
			r = src_row[sx * s_bpp + 2];
			a = src_row[sx * s_bpp + 3];
			color = (r << 16) | (g << 8) | b;
			if (apply)
				color = add_light(color, intensity);
			dst_row[x * d_bpp + 0] = color & 0xFF;         // b
			dst_row[x * d_bpp + 1] = (color >> 8) & 0xFF;  // g
			dst_row[x * d_bpp + 2] = (color >> 16) & 0xFF; // r
			dst_row[x * d_bpp + 3] = a;                    // preserve alpha
			x++;
		}
		y++;
	}
	mlx_clear_window(game->mlx, game->win);
	// mlx_put_image_to_window(game->mlx, game->win, game->bg_img.img, 0, 0);
	mlx_put_image_to_window(game->mlx, game->win, dst.img, 0, 0);
	mlx_destroy_image(game->mlx, dst.img);
}


void	make_fade_screen(t_game *game,t_img *img)
{
	static double i;

	mlx_mouse_show(game->mlx, game->win);
	if(i > 1.5)
	{
		game->g_flags.game_state = Finished;
	}
	draw_scaled_img(game,img,true,i);
	i+= 0.003;
}

void make_pause_screen(t_game *game)
{
    // static int i;

    if(game->g_flags.game_state == Pause)
    {
        mlx_clear_window(game->mlx,game->win);
        mlx_put_image_to_window(game->mlx,game->win,game->ass.pause_screen.img,WIDTH/2 - 150,HEIGHT/2 - 84);
        // i = 1;
    }
    // printf("player x = %f   player y = %f\n",game->player.posx,game->player.posy);

}

int main_loop(t_game *game)
{
    double fsleep;

	if(game->collected_comics == game->ass.collect_amount && game->g_flags.game_state != Finished)
		game->g_flags.game_state = Win_screen;
    if(game->g_flags.game_state == running)
    {
        move(game);
        if (game->ass.enemy.cords.x != -1)
            monster(game);
        create_frame(game);
        fsleep = fps_counter(game);
        if (game->fps_lock > 0 && fsleep > 0.0)
            ft_sleep(fsleep);
    }
    else if (game->g_flags.game_state == death_screen)
        make_fade_screen(game,&game->ass.death_screen);
    else if (game->g_flags.game_state == Pause)
        make_pause_screen(game);
	else if (game->g_flags.game_state == Win_screen)
		make_fade_screen(game,&game->ass.win_screen);
    return (0);
}
int	main(int argc, char **argv)
{
	t_game	game;

	ft_bzero(&game, sizeof(t_game));
	if (argc == 2)
	{
		if (parse(&game, argv[1]) == false)
			return (1);
		game.fps_lock = 60;
		game.mlx = mlx_init();
		print_info(game);
		textures(&game);
		map_gen(&game);
		mlx_hook(game.win, 17, 0, closex, &game);
		mlx_hook(game.win, 2, 1L << 0, key_press, &game);
		mlx_hook(game.win, 3, 1L << 1, key_release, &game);
		mlx_hook(game.win, 6, 1L << 6, mouse, &game);
		mlx_loop_hook(game.mlx, main_loop, &game);
		mlx_loop(game.mlx);
		free_game(&game);
		return (1);
	}
	else
		return (print_errors(&game, 1, "Not valid amount of arguments"), 1);
	return (0);
}
