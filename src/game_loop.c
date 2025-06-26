/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:11:05 by ruida-si          #+#    #+#             */
/*   Updated: 2025/06/26 17:20:16 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_moves(t_cub *cub);
static void	check_moves2(t_cub *cub, t_player *player, double x, double y);
static void	check_wall_collision(t_cub *cub, double new_x, double new_y);
static void	fill_image(int *data, t_cub *cub);

int	game_loop(t_cub *cub)
{
	if (cub->img)
		mlx_destroy_image(cub->mlx, cub->img);
	cub->img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	cub->img_data = (int *)mlx_get_data_addr(cub->img, &cub->bpp,
			&cub->size_line, &cub->endian);
	check_moves(cub);
	fill_image(cub->img_data, cub);
	raycast(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img, 0, 0);
	return (0);
}

static int	check_moves(t_cub *cub)
{
	t_player	*player;

	player = &cub->player;
	if (cub->keys.left)
		player->angle = (int)(player->angle + ROT) % 360;
	if (cub->keys.right)
		player->angle = (int)(player->angle - ROT + 360) % 360;
	check_moves2(cub, player, -1, -1);
	return (0);
}

static void	check_moves2(t_cub *cub, t_player *player, double x, double y)
{
	if (cub->keys.w)
	{
		x = player->pos_x + cos(deg_to_rad(player->angle)) * SPEED;
		y = player->pos_y - sin(deg_to_rad(player->angle)) * SPEED;
	}
	if (cub->keys.s)
	{
		x = player->pos_x - cos(deg_to_rad(player->angle)) * SPEED;
		y = player->pos_y + sin(deg_to_rad(player->angle)) * SPEED;
	}
	if (cub->keys.a)
	{
		x = player->pos_x + cos(deg_to_rad(player->angle + 90.0)) * SPEED;
		y = player->pos_y - sin(deg_to_rad(player->angle + 90.0)) * SPEED;
	}
	if (cub->keys.d)
	{
		x = player->pos_x + cos(deg_to_rad(player->angle - 90.0)) * SPEED;
		y = player->pos_y - sin(deg_to_rad(player->angle - 90.0)) * SPEED;
	}
	if (x != -1 && y != -1)
		check_wall_collision(cub, x, y);
}

static void	check_wall_collision(t_cub *cub, double new_x, double new_y)
{
	int	x;
	int	y;

	x = (int)new_x;
	y = (int)new_y;
	if (cub->map.map[y][x] != '1')
	{
		cub->player.pos_x = new_x;
		cub->player.pos_y = new_y;
	}
}

static void	fill_image(int *data, t_cub *cub)
{
	int	y;
	int	x;

	(void)cub;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < HEIGHT / 2)
				data[y * WIDTH + x] = cub->map.c;
			else
				data[y * WIDTH + x] = cub->map.f;
			x++;
		}
		y++;
	}
}
