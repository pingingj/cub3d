
#include "../../incs/cub3d.h"

static int	line_of_sight_loop(t_point xy, t_point d, t_point endxy, t_point s)
{
	int		err;
	int		e2;
	t_game	*game;

	err = d.x - d.y;
	game = mem_save(NULL);
	while (xy.x != endxy.x || xy.y != endxy.y)
	{
		if (xy.y >= 0 && xy.y < game->map.pos.y && xy.x >= 0
			&& xy.x < (int)ft_strlen(game->map.grid[xy.y])
			&& game->map.grid[xy.y][xy.x] == '1')
			return (0);
		e2 = 2 * err;
		if (e2 > -d.y)
		{
			err -= d.y;
			xy.x += s.x;
		}
		if (e2 < d.x)
		{
			err += d.x;
			xy.y += s.y;
		}
	}
	return (1);
}
int	has_line_of_sight(double ex, double ey, double px, double py)
{
	t_point	xy;
	t_point	endxy;
	t_point	d;
	t_point	s;

	xy.x = (int)ex;
	xy.y = (int)ey;
	endxy.x = (int)px;
	endxy.y = (int)py;
	d.x = abs(endxy.x - xy.x);
	d.y = abs(endxy.y - xy.y);
	if (xy.x < endxy.x)
		s.x = 1;
	else
		s.x = -1;
	if (xy.y < endxy.y)
		s.y = 1;
	else
		s.y = -1;
	return (line_of_sight_loop(xy, d, endxy, s));
}

int	is_near_wall(t_game *game, double x, double y)
{
	int	i;
	t_point n;
	t_point c;
	int	dx[4];
	int	dy[4];

	init_dirs(dx,dy);
	c.x = (int)x;
	c.y = (int)y;
	i = 0;
	while (i < 4)
	{
		n.x = c.x + dx[i];
		n.y = c.y + dy[i];
		if (n.y >= 0 && n.y < game->map.pos.y && n.x >= 0
			&& n.x < (int)ft_strlen(game->map.grid[n.y])
			&& (game->map.grid[n.y][n.x] == '1' || game->map.grid[n.y][n.x] == 'd'))
			return (1);
		i++;
	}
	return (0);
}